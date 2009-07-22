/*
 * Copyright (c) 2009 Steven Noonan <steven@uplinklabs.net>
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

#include <time.h>

#include "App/app.h"
#include "App/file_utils.h"
#include "App/preferences.h"
#include "App/version.h"
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/bouncing_window.h"
#include "Interface/error_window.h"
#include "Interface/text.h"
#include "Interface/button.h"
#include "Interface/interface.h"
#include "Network/net.h"
#include "Sound/soundsystem.h"

Game::Game()
 : m_gameSpeed(5),
   m_fps(0),
   m_running(true),
   m_playing(false)
{
}

Game::~Game()
{
}

void Game::Initialise()
{
    TextUI *text = new TextUI (
        "\2" APP_NAME,
        false, g_graphics->GetScreenWidth () - 290, g_graphics->GetScreenHeight () - 38, 270, 12 );
    g_interface->AddWidget ( text );

	char buffer[1024];
	sprintf(buffer, "\2For testing purposes only. v%s", Cerberus::Version::LongVersion());

    text = new TextUI (
        buffer,
        false, g_graphics->GetScreenWidth () - 290, g_graphics->GetScreenHeight () - 25, 270, 12 );
    g_interface->AddWidget ( text );

#ifndef RELEASE_BUILD
    text = new TextUI (
        "\2NOT FOR PUBLIC INSPECTION OR REDISTRIBUTION",
        false, g_graphics->GetScreenWidth () - 290, g_graphics->GetScreenHeight () - 12, 270, 12 );
    g_interface->AddWidget ( text );
#endif
}

void Game::Quit()
{
    m_running = false;
}

void Game::LoadSounds ()
{
	// TODO: Move this outta the Game class.
}

void Game::Run () // TODO: Would this be better placed in the App class?
{
    int framesThisSecond = 0;
	bool deviceLost = false;

    //g_interface->UpdateFPS ( 0 );

    m_tmrFPS.Start();
    m_tmrGameSpeed.Start();

    System::Stopwatch lastFrame;
    lastFrame.Start();

    CrbReleaseAssert ( g_interface != NULL );
    CrbReleaseAssert ( g_graphics != NULL );

    SDL_EnableUNICODE ( 1 );

#ifdef BENCHMARK_BUILD
    for ( int i = 0; i < BENCHMARK_WIDGETS; i++ )
    {
        short xpos = rand() % (g_graphics->GetScreenWidth() - 48),
              ypos = rand() % (g_graphics->GetScreenHeight() - 48);
        g_interface->AddWidget ( new BouncingWindow ( xpos, ypos, 48, 48, rand() % 20 - 10, rand() % 20 - 10 ) );
    }
#endif

	g_interface->UpdateRendererWidget();

    while ( m_running )
    {
        // Force 60fps max.
#ifndef FORCE_VSYNC
        if ( g_prefsManager->GetInt ( "WaitVerticalRetrace", 1 ) != 0 )
#endif
        {
            int sleepTime;
            lastFrame.Stop();
            sleepTime = (int)( ( 1000.0 / 60.0 ) - ( lastFrame.Elapsed() * 1000.0 ) );
            if ( sleepTime > 0 )
                System::ThreadSleep ( sleepTime );
            lastFrame.Start();
        }

        ProcessEvents();
        g_interface->ProcessMouseEvents();

        if ( m_playing ) {
			// TODO: Update game world, etc.
        } else {

        }

        /// RENDER WIDGETS
        g_interface->RenderWidgets();

        // Play any queued sounds.
        if ( g_soundSystem != NULL )
            g_soundSystem->Update();

        if ( !g_graphics->Flip() )
		{
			if ( !deviceLost )
			{
				g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
				g_console->WriteLine ( "WARNING: Device lost, textures need to be recreated." );
				g_console->SetColour ();
				deviceLost = true;
			}
		} else {
			if ( deviceLost )
			{
				g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
				g_console->WriteLine ( "WARNING: Device recaptured. Recreating textures." );
				g_console->SetColour ();
				deviceLost = false;
			}
		}

        // Add a frame to the count.
        framesThisSecond++;

        // Now make sure we haven't used up a second yet.
        m_tmrFPS.Stop();
        if ( m_tmrFPS.Elapsed() >= 1.0 )
        {
            g_interface->UpdateFPS ( framesThisSecond );
            framesThisSecond = 0;
            m_tmrFPS.Start();
        }

        // Let's hold movement speed at a constant.
        m_tmrGameSpeed.Stop();
        m_gameSpeed = 71.5 * m_tmrGameSpeed.Elapsed();
        if ( m_gameSpeed > 50.0 ) m_gameSpeed = 50.0;
        m_tmrGameSpeed.Start();
    }
}

bool Game::Playing()
{
    return m_playing;
}

void Game::ProcessEvents ()
{

    SDL_Event event;
    while ( SDL_PollEvent ( &event ) )
    {
        switch ( event.type )
        {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_KEYDOWN:
            {
            }
            break;
        }
    }

    // Handle Command+Q on Mac OS X
#ifdef TARGET_OS_MACOSX
    int arraySz = 0;
    Uint8 *keyState = SDL_GetKeyState(&arraySz);

    static bool cmdQ = false;
    if ( !cmdQ && ( keyState[SDLK_LMETA] || keyState[SDLK_RMETA] ) && keyState[SDLK_q] )
    {
        cmdQ = true;
        if ( m_playing )
        {
            QuitWindow *quitWindow;
            if ( (quitWindow = (QuitWindow *)g_interface->GetWidgetOfType ( "QuitWindow" )) != NULL )
            {
                g_interface->RemoveWidget ( quitWindow );
            } else {
                QuitWindow *quitWindow = new QuitWindow();
                g_interface->AddWidget ( quitWindow );
                quitWindow = NULL;
            }
        } else {
            m_running = false;
        }
    } else if ( cmdQ && ( !keyState[SDLK_LMETA] && !keyState[SDLK_RMETA] ) || !keyState[SDLK_q] ) {
        cmdQ = false;
    }
#endif
}

double Game::GetGameSpeed()
{
    return m_gameSpeed;
}

Game *g_game;
