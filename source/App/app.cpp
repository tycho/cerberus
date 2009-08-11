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

#include "App/app.h"
#include "App/file_utils.h"
#include "App/string_utils.h"
#include "App/preferences.h"
#include "App/version.h"
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/error_window.h"
#include "Interface/text.h"
#include "Interface/button.h"
#include "Interface/interface.h"
#include "Network/net.h"
#include "Sound/soundsystem.h"

#ifdef TARGET_OS_MACOSX
extern char **NXArgv; // system variable we can exploit
#endif

App::App ()
 : m_appPath ( NULL ),
   m_appSupportPath ( NULL ),
   m_resourcePath ( NULL ),
   m_fps ( 0 ),
   m_running ( true )
{
    char tempPath[2048];
    memset ( tempPath, 0, sizeof ( tempPath ) );

    // Set up the Application Path variable
#if defined ( TARGET_OS_WINDOWS )

    int retval = GetModuleFileName ( NULL, tempPath, sizeof ( tempPath ) );
    CrbDebugAssert ( retval != 0 );
    if ( strlen(tempPath) )
    {
        char *ptr = &tempPath[strlen(tempPath)];
        while ( *(--ptr) != '\\' ) {};
        ptr[1] = '\x0';
    }
    else
        strcpy ( tempPath, ".\\" );

#elif defined ( TARGET_OS_LINUX )

    int retval = readlink ( "/proc/self/exe", tempPath, sizeof ( tempPath ) );
    CrbDebugAssert ( retval != -1 );
    if ( strlen(tempPath) )
    {
        char *ptr = &tempPath[strlen(tempPath)];
        while ( *(--ptr) != '/' ) {};
        ptr[1] = '\x0';
    }
    else
        strcpy ( tempPath, "./" );

#elif defined ( TARGET_OS_MACOSX )

    strncpy ( tempPath, NXArgv[0], sizeof ( tempPath ) );
    if ( strlen(tempPath) )
    {
        char *ptr = &tempPath[strlen(tempPath)];
        while ( *(--ptr) != '/' ) {};
        ptr[1] = '\x0';
    }
    else
        strcpy ( tempPath, "./" );

#endif

    m_appPath = newStr ( tempPath );

    // Set up the resources directory variable
#if defined ( TARGET_OS_WINDOWS )

    m_resourcePath = newStr ( m_appPath );

#elif defined ( TARGET_OS_LINUX )

    m_resourcePath = newStr ( m_appPath );

#elif defined ( TARGET_OS_MACOSX )

    sprintf ( tempPath, "%s../Resources/", m_appPath );
    m_resourcePath = newStr ( tempPath );

#endif

    // Set up the Application Support path
#if defined ( TARGET_OS_WINDOWS )

    memset ( tempPath, 0, sizeof(tempPath) );
    retval = SHGetFolderPath ( NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, tempPath );
    CrbDebugAssert ( retval != E_FAIL );
    strcat ( tempPath, "\\Cerberus\\" );
    m_appSupportPath = newStr ( tempPath );

#elif defined ( TARGET_OS_LINUX )

    const char *homePath = getenv ( "HOME" );
    CrbReleaseAssert ( homePath );
    sprintf ( tempPath, "%s/.cerberus/", homePath );
    m_appSupportPath = newStr ( tempPath );

#elif defined ( TARGET_OS_MACOSX )

    const char *homePath = getenv ( "HOME" );
    CrbReleaseAssert ( homePath );
    sprintf ( tempPath, "%s/Library/Application Support/Cerberus/", homePath );
    m_appSupportPath = newStr ( tempPath );

#endif

    CreateDirectory ( m_appSupportPath );

    CrbDebugAssert ( m_appPath != NULL );
    CrbDebugAssert ( m_resourcePath != NULL );
    CrbDebugAssert ( m_appSupportPath != NULL );

#ifdef REDIRECT_STDOUT
    FILE *stdoutfile; FILE *stderrfile;
    sprintf ( tempPath, "%sdebug.log", m_appSupportPath );
    remove ( tempPath );
    stdoutfile = freopen ( tempPath, "a", stdout );
    if ( !stdoutfile ) fprintf ( stderr, "WARNING : Failed to open debug.log for writing stdout\n" );
    stderrfile = freopen ( tempPath, "a", stderr );
    if ( !stderrfile ) fprintf ( stderr, "WARNING : Failed to open debug.log for writing stderr\n" );
#endif

    m_resource = new Resource();
}

App::~App()
{
    delete m_resource;
    m_resource = NULL;
    delete [] m_appPath;
    m_appPath = NULL;
    delete [] m_appSupportPath;
    m_appSupportPath = NULL;
    delete [] m_resourcePath;
    m_resourcePath = NULL;
}

void App::Initialise()
{
    TextUI *text = new TextUI (
        APP_NAME, Color32(255,0,0),
        g_graphics->GetScreenWidth () - 290,
        g_graphics->GetScreenHeight () - 38);
    g_interface->AddWidget ( text );

    char buffer[1024];
    sprintf(buffer, "For testing purposes only. v%s", Cerberus::Version::LongVersion());

    text = new TextUI (
        buffer, Color32(255,0,0),
        g_graphics->GetScreenWidth () - 290,
        g_graphics->GetScreenHeight () - 25 );
    g_interface->AddWidget ( text );

}

void App::CreateDirectory ( const char *_path )
{
#ifdef TARGET_OS_WINDOWS
    ::CreateDirectoryA ( _path, NULL );
#else
    mkdir ( _path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
#endif
}

const char *App::GetResourcePath ()
{
    return m_resourcePath;
}

const char *App::GetApplicationPath ()
{
    return m_appPath;
}

const char *App::GetApplicationSupportPath ()
{
    return m_appSupportPath;
}

void App::Run ()
{
    int framesThisSecond = 0;
    bool deviceLost = false;

    m_tmrFPS.Start();

    System::Stopwatch lastFrame;
    lastFrame.Start();

    CrbReleaseAssert ( g_interface != NULL );
    CrbReleaseAssert ( g_graphics != NULL );

    SDL_EnableUNICODE ( 1 );

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

        UpdateInputs();

        g_interface->Update();

        if ( g_game->Playing() ) {
            g_game->Update();
        } else {

        }

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

        g_graphics->FillRect(SCREEN_SURFACE_ID, NULL, Color32(0,0,0));

        // Now make sure we haven't used up a second yet.
        m_tmrFPS.Stop();
        if ( m_tmrFPS.Elapsed() >= 1.0 )
        {
            g_interface->UpdateFPS ( framesThisSecond );
            framesThisSecond = 0;
            m_tmrFPS.Start();
        } else {
            // Add a frame to the count.
            framesThisSecond++;
        }
    }
}

void App::Quit()
{
    m_running = false;
}

void App::UpdateInputs ()
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
        if ( g_game->Playing() )
        {
#if 0
            QuitWindow *quitWindow;
            if ( (quitWindow = (QuitWindow *)g_interface->GetWidgetOfType ( WIDGET_QUIT_WINDOW )) != NULL )
            {
                g_interface->RemoveWidget ( quitWindow );
            } else {
                quitWindow = new QuitWindow();
                g_interface->AddWidget ( quitWindow );
                quitWindow = NULL;
            }
#endif
        } else {
            m_running = false;
        }
    } else if ( cmdQ && ( !keyState[SDLK_LMETA] && !keyState[SDLK_RMETA] ) || !keyState[SDLK_q] ) {
        cmdQ = false;
    }
#endif
}

App *g_app;
