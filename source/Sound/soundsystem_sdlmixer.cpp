/*
 * Copyright (c) 2010 Steven Noonan <steven@uplinklabs.net>
 *                and Miah Clayton <miah@ferrousmoon.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "universal_include.h"

#ifdef USE_SDLMIXER

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
#    pragma comment (lib, "SDL_mixer.lib")
#    pragma comment (lib, "timidity.lib")
#    pragma comment (lib, "native_midi.lib")
#endif

#include "App/app.h"
#include "App/preferences.h"
#include "Graphics/graphics.h"
#include "Sound/soundsystem.h"

SDLMixerSoundSystem::SDLMixerSoundSystem()
 : m_queuesEmpty(true)
{
    int retval = SDL_InitSubSystem ( SDL_INIT_AUDIO );
    CrbReleaseAssert ( retval == 0 );

    int channels = g_prefsManager->GetInt ( "SoundChannels", 32 ),
        frequency = g_prefsManager->GetInt ( "SoundMixFreq", 22050 ),
        bufferSize = g_prefsManager->GetInt ( "SoundBufferSize", 1024 );

    if ( channels < 16 ) channels = 16;
    if ( frequency < 22050 ) frequency = 22050;
    if ( bufferSize < 512 ) bufferSize = 512;

    if ( !isPowerOfTwo ( bufferSize ) ) bufferSize = nearestPowerOfTwo ( bufferSize );

    retval = Mix_OpenAudio ( frequency, AUDIO_S16SYS, 2, bufferSize );
    CrbReleaseAssert ( retval == 0 );

    Mix_AllocateChannels ( channels );
    m_channelPlaying.setSize ( channels );
}

SDLMixerSoundSystem::~SDLMixerSoundSystem()
{
    // Delete the loaded sound data
    Data::DArray<Mix_Chunk *> *entries = m_chunks.ConvertToDArray();
	size_t i;
    for ( i = 0; i < entries->size(); i++ )
    {
        if ( !entries->valid ( i ) ) continue;
        Mix_FreeChunk ( entries->get(i) );
    }
    delete entries;

    // Clear out the used channel array
    for ( i = 0; i < m_channelPlaying.size(); i++ )
    {
        if ( !m_channelPlaying.valid ( i ) ) continue;
        free ( m_channelPlaying.get ( i ) );
        m_channelPlaying.remove ( i );
    }

    // Eliminate the remaining queues
    for ( i = 0; i < m_queues.size(); i++ )
    {
        if ( !m_queues.valid ( i ) ) continue;
        delete m_queues.get ( i );
        m_queues.remove ( i );
    }
    Mix_CloseAudio();
    SDL_QuitSubSystem ( SDL_INIT_AUDIO );
}

void SDLMixerSoundSystem::AddQueue ( Data::LList<std::string> *_queue )
{
    // A "queue" is a list of sounds to play in immediate sequence.
    // An example of such a queue is: "Green"    "flag captured by" "red"    "team"
    //  which is queue of the sounds:  green.wav  flagcap.wav        red.wav  team.wav
    m_queues.insert ( _queue );
}

int SDLMixerSoundSystem::PlaySound ( const char *_soundName, short _distX, short _distY )
{
    CrbReleaseAssert ( _soundName != NULL );

    // Let's see if it's cached.
    Mix_Chunk *wave = m_chunks.find ( _soundName, NULL );
    if ( !wave )
    {
        // Ouch. Performance hit as we load the sound.
        g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "WARNING: %s was not found in the sound cache!", _soundName );
        g_console->SetColour ();
        LoadWave ( _soundName );
        wave = m_chunks.find ( _soundName, NULL );
    }
    if ( !wave )
    {
        // The sound is completely unloadable.
        g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "ERROR: %s could not be loaded!", _soundName );
        g_console->SetColour ();
        return -1;
    }

    // Use the pythagorean theorem to calculate a precise distance, in pixels.
    int distX2 = _distX * _distX;
    int distY2 = _distY * _distY;
    int dist = (int)sqrt((double)distX2 + (double)distY2);

    // We use a box range for the maximum distance. Just off screen (left or right) sounds would play at 30% volume.
    float maxDist = (float)max(g_graphics->GetScreenHeight(),g_graphics->GetScreenWidth()) * 0.75f;
    float volumePercentage = (float)(maxDist - dist) / (float)maxDist;

    // The volume is the percentage just calculated * maximum volume
    int newVolume = (int)(( (float)MIX_MAX_VOLUME * 0.75f ) * volumePercentage);
    if ( newVolume <= 0 ) return 1;

    int channel = Mix_PlayChannel ( -1, wave, 0 );
    int left = ( _distX * -1 ) + 128;
    if ( left < 0 ) left = 0;
    if ( left > 255 ) left = 255;
    Mix_SetPanning ( channel, left, 255 - left );
    Mix_Volume ( channel, newVolume );
    if ( m_channelPlaying.valid ( channel ) ) {
        free ( m_channelPlaying.get ( channel ) );
        m_channelPlaying.remove ( channel );
    }
    if ( channel != -1 )
    {
        /*g_console->WriteLine ( "Playing %s at %.1lf%% volume (distance: %d, channel: %d)",
            _soundName, volumePercentage * 100.0f, dist, channel );*/
        m_channelPlaying.insert ( cc_strdup ( _soundName ), channel );
    }
    return 0;
}

int SDLMixerSoundSystem::LoadWave ( const char *_soundName )
{
    CrbReleaseAssert ( _soundName != NULL );
    if ( m_chunks.exists(_soundName) ) return 1;
    char fileName[128];
    sprintf ( fileName, "sound/%s.wav", _soundName );
    Mix_Chunk *wave = g_app->m_resource->GetSound ( fileName );
    if ( !wave ) return 1;
    m_chunks.insert ( _soundName, wave );
    return 0;
}

bool SDLMixerSoundSystem::IsPlaying ( const char *_soundName )
{
    for ( size_t i = 0; i < m_channelPlaying.size(); i++ )
    {
        if ( !m_channelPlaying.valid ( i ) ) continue;
        if ( Mix_Playing ( i ) )
        {
            if ( strcmp ( m_channelPlaying.get ( i ), _soundName ) == 0 )
            {
                return true;
            }
        } else {
            free ( m_channelPlaying.get ( i ) );
            m_channelPlaying.remove ( i );
        }
    }
    return false;
}

void SDLMixerSoundSystem::Update ()
{
    while ( true )
    {
        if ( !m_queues.valid ( 0 ) )
        {
            m_queuesEmpty = true;
            return;
        }
        Data::LList<std::string> *queue = m_queues.get ( 0 );
        if ( !IsPlaying ( queue->get ( 0 ).c_str() ) )
        {
            if ( !m_queuesEmpty )
                queue->remove ( 0 );
            if ( queue->size() < 1 )
            {
                m_queues.remove ( 0 );
                delete queue;
                continue;
            }
            PlaySound ( queue->get ( 0 ).c_str(), 0, 0 );
            m_queuesEmpty = false;
            break;
        } else {
            break;
        }
    }
}

#endif
