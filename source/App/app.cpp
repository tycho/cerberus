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

#ifndef TARGET_OS_WINDOWS
#	include <sys/stat.h>
#else
#	include <shlobj.h>
#endif

#include "App/app.h"
#include "App/file_utils.h"
#include "App/string_utils.h"
#include "App/preferences.h"
#include "App/version.h"
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Input/input.h"
#include "Interface/error_window.h"
#include "Interface/text.h"
#include "Interface/button.h"
#include "Interface/interface.h"
#include "Network/net.h"
#include "Scripting/scripting.h"
#include "Sound/soundsystem.h"

#ifdef TARGET_OS_MACOSX
extern char **NXArgv; // system variable we can exploit
#endif

App::App ()
 : m_gameSpeed(5),
   m_appPath ( NULL ),
   m_appSupportPath ( NULL ),
   m_resourcePath ( NULL ),
   m_fps ( 0 ),
   m_running ( true )
{
    char tempPath[2048];
    memset ( tempPath, 0, sizeof ( tempPath ) );

    // Set up the Application Path variable
#if defined ( TARGET_OS_WINDOWS )

    CrbDebugAssert ( GetModuleFileName ( NULL, tempPath, sizeof ( tempPath ) ) != 0 );
    if ( strlen(tempPath) )
    {
        char *ptr = &tempPath[strlen(tempPath)];
        while ( *(--ptr) != '\\' ) {};
        ptr[1] = '\x0';
    }
    else
        strcpy ( tempPath, ".\\" );

#elif defined ( TARGET_OS_LINUX )

    size_t ret = readlink ( "/proc/self/exe", tempPath, sizeof ( tempPath ) - 1 );
    CrbDebugAssert(ret != -1);
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
    CrbDebugAssert ( SHGetFolderPath ( NULL, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE, NULL, 0, tempPath ) != E_FAIL );
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
    delete m_scene;
    m_scene = NULL;
}

Scene *App::GetScene()
{
    return m_scene;
}

Interface *App::GetInterface()
{
    return m_scene->GetInterface();
}

void App::Initialise()
{
    m_scene = new Scene(new Interface());

    TextUI *text = new TextUI (
        APP_NAME, Color32(255,0,0),
        g_graphics->GetScreenWidth () - 290,
        g_graphics->GetScreenHeight () - 38);
    GetInterface()->AddEntity ( text );

    char buffer[1024];
    sprintf(buffer, "For testing purposes only. v%s", Cerberus::Version::LongVersion());

    text = new TextUI (
        buffer, Color32(255,0,0),
        g_graphics->GetScreenWidth () - 290,
        g_graphics->GetScreenHeight () - 25 );
    GetInterface()->AddEntity ( text );

    Window *win = new Window ( "", 30, 200, 250, 250 );
    GetInterface()->AddEntity ( win );

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
    float timeDelta = 0.0f;
    bool deviceLost = false;

    m_tmrFPS.Start();

    System::Stopwatch lastFrame;
    lastFrame.Start();

    CrbReleaseAssert ( GetInterface() != NULL );
    CrbReleaseAssert ( g_graphics != NULL );

    SDL_EnableUNICODE ( 1 );

    GetInterface()->UpdateRendererWidget();

    m_tmrGameSpeed.Start();

    g_scripting->RunScript("sethello");
    g_scripting->RunScript("printhello");

    GLfloat m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            g_console->Write("%f ", m[j + (i * 4)]);
        }
        g_console->WriteLine();
    }

    while ( m_running )
    {

        // Get time since last frame
        lastFrame.Stop();
        timeDelta = lastFrame.Elapsed();

        // Force 60fps max.
#ifndef FORCE_VSYNC
        if ( g_prefsManager->GetInt ( "WaitVerticalRetrace", 1 ) != 0 )
#endif
        {
            int sleepTime;
            sleepTime = (int)( ( 1000.0 / 60.0 ) - ( timeDelta * 1000.0 ) );
            if ( sleepTime > 0 )
                System::ThreadSleep ( sleepTime );
        }
        lastFrame.Start();

        g_input->Update();

        SDL_Event *event = g_input->GetEvent(0);
        for (size_t i = 0; event != NULL; event = g_input->GetEvent(++i)) {
            switch (event->type) {
            case SDL_QUIT:
                Quit();
                break;
            case SDL_KEYUP:
                if (event->key.keysym.sym == SDLK_ESCAPE) {
                    Quit();
                }
                break;
            }
        }

        GetInterface()->Update(timeDelta);

        if ( g_game->Playing() ) {
            g_game->Update(timeDelta);
        } else {
        }

        g_game->Render(timeDelta);

        // Always render application interface above everything else
        GetInterface()->RenderMouse();
        GetInterface()->Render(timeDelta);

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

        g_graphics->FillRect(SCREEN_SURFACE_ID, NULL, Color32(150,150,255));

		// We don't want the frame rate to affect game speed, so we use
		// a timer to throttle it.
		m_tmrGameSpeed.Stop();
		m_gameSpeed = 71.5 * m_tmrGameSpeed.Elapsed();
		if ( m_gameSpeed > 50.0 ) m_gameSpeed = 50.0;
		m_tmrGameSpeed.Start();

        // Now make sure we haven't used up a second yet.
        m_tmrFPS.Stop();
        if ( m_tmrFPS.Elapsed() >= 1.0 )
        {
            GetInterface()->UpdateFPS ( framesThisSecond );
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

double App::Speed()
{
    return m_gameSpeed;
}

App *g_app;
