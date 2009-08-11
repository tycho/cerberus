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
#include "App/preferences.h"
#include "App/version.h"
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/window.h"
#include "Network/net.h"
#include "Sound/soundsystem.h"

IO::Console *g_console;

bool g_bActive = true;
int iPlaying;
bool bSound;

void Init_App( char *apppath );
void Init_Game();
void Init_Graphics();
void Init_Interface();
void Init_Sound();

int main ( int argc, char **argv )
{
    int i = 0;
    char temp[1024];

    memset ( temp, 0, sizeof(temp) );

    g_console = new IO::Console ( true, true );
	sprintf(temp, "%s v%s", APP_NAME, Cerberus::Version::LongVersion());
    g_console->SetTitle ( temp );

#ifdef TARGET_OS_MACOSX
    sprintf ( temp, "%s", "../Resources/" );
#endif

    // first find the location of the EXE.
    for (i = (int)strlen(argv[0]); i > 0; i--)
    {
        if (argv[0][i] == '\\')
        {
            argv[0][i + 1] = '\x0';
            strcat(temp, argv[0]);
            break;
        }
    }

    g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
    g_console->WriteLine ( "=======================" );
    g_console->WriteLine ( "=  Codename Cerberus  =" );
    g_console->WriteLine ( "=======================" );
    g_console->SetColour ();
	g_console->WriteLine ( "Copyright (c) 2009 Steven Noonan <steven@uplinklabs.net>" );
	g_console->WriteLine ( "               and Miah Clayton <miah@ferrousmoon.com>");
	g_console->WriteLine ( "All rights reserved." );
	g_console->WriteLine ( "Licensed under the terms of the New BSD License.\n" );
	g_console->WriteLine ( "Version %s", Cerberus::Version::LongVersion() );

    g_console->Write ( "Built for " );
    g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
#if defined ( TARGET_OS_WINDOWS )
    g_console->Write ( "Microsoft Windows" );
#elif defined ( TARGET_OS_MACOSX )
    g_console->Write ( "Mac OS X" );
#elif defined ( TARGET_OS_LINUX )
    g_console->Write ( "Linux" );
#else
    g_console->Write ( "Unknown OS" );
#endif
    g_console->SetColour ();
    g_console->Write ( " using " );
    g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
#if defined ( TARGET_COMPILER_VC )
    g_console->Write ( "Visual Studio" );
    #if _MSC_VER >= 1500
        g_console->Write ( " 2008" );
    #elif _MSC_VER >= 1400
        g_console->Write ( " 2005" );
    #elif _MSC_VER >= 1310
        g_console->Write ( " .NET 2003" );
    #elif _MSC_VER >= 1300
        g_console->Write ( " .NET 2002" );
    #elif _MSC_VER >= 1200
        g_console->Write ( " 6.0" );
    #endif
#elif defined ( TARGET_COMPILER_GCC )
    g_console->Write ( "GNU C++ Compiler v%d.%d.%d", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ );
#elif defined ( TARGET_COMPILER_ICC )
    g_console->Write ( "Intel C++ Compiler" );
#else
    g_console->Write ( "Unknown Compiler" );
#endif
    g_console->SetColour ();
    g_console->WriteLine ( "\nBuilt on " __DATE__ " at " __TIME__ );

    Init_App(temp);
    Init_Graphics();
    Init_Interface();
    Init_Sound();
    Init_Game();

    g_app->Run ();

    // deconstruct the classes
    g_console->WriteLine ( "Destroying classes...");
    g_graphics->ShowCursor ( true );

    // free up the allocated memory
    delete g_game; g_game = NULL;
    delete g_interface; g_interface = NULL;
    delete g_graphics; g_graphics = NULL;
    delete g_soundSystem; g_soundSystem = NULL;

    // notify that the exit operations were successful
    g_console->WriteLine ( "Program is exiting cleanly.\n");

    g_prefsManager->Save();

    delete g_prefsManager; g_prefsManager = NULL;
    delete g_app; g_app = NULL;
    delete g_console; g_console = NULL;

    // success!
    return 0;
}

void Init_App( char *apppath )
{
    g_app = new App();
    CrbReleaseAssert ( g_app != NULL );

    char preferencesPath[2048];
#ifndef TARGET_OS_WINDOWS
    sprintf( preferencesPath, "%s%s", g_app->GetApplicationSupportPath(), "preferences.txt" );
#else
    sprintf( preferencesPath, "%s%s", g_app->GetApplicationPath(), "preferences.txt" );
#endif
    g_prefsManager = new Preferences ( preferencesPath );
    CrbReleaseAssert ( g_prefsManager != NULL );

    // We save the preferences here to ensure that preferences.txt exists.
    // If the application prints a blackbox.txt, this file needs to be there.
    g_prefsManager->Save();

	if ( g_prefsManager->GetInt ( "IgnoreDataFiles", 0 ) == 0 )
	{
		char tempPath[2048];
		sprintf ( tempPath, "%s%s", g_app->GetResourcePath(), "data.dat" );
		g_app->m_resource->ParseArchive ( tempPath, NULL );
		sprintf ( tempPath, "%s%s", g_app->GetResourcePath(), "font.dat" );
		g_app->m_resource->ParseArchive ( tempPath, NULL );
		sprintf ( tempPath, "%s%s", g_app->GetResourcePath(), "graphics.dat" );
		g_app->m_resource->ParseArchive ( tempPath, NULL );
		sprintf ( tempPath, "%s%s", g_app->GetResourcePath(), "sounds.dat" );
		g_app->m_resource->ParseArchive ( tempPath, NULL );
		sprintf ( tempPath, "%s%s", g_app->GetResourcePath(), "maps.dat" );
		g_app->m_resource->ParseArchive ( tempPath, NULL );
	}
}

void Init_Game()
{
    g_game = new Game();
    CrbReleaseAssert ( g_game != NULL );
}

void Init_Graphics()
{
    const char *graphicsDriver = g_prefsManager->GetString ( "Renderer", "opengl" );
    int ret = -1;

	CrbDebugAssert ( g_graphics == NULL );
	while ( !g_graphics )
	{
		// Pick a renderer.
		if ( Data::Compare<const char *> ( graphicsDriver, "opengl" ) == 0 )
		{
			// OpenGL
			g_console->WriteLine ( "Attempting to use OpenGLGraphics..." );
#ifdef ENABLE_OPENGL
			g_graphics = new OpenGLGraphics ();
#else
			g_console->WriteLine ( "OpenGL support not enabled." );
#endif
		}

		// Try and set the window mode.
		if ( g_graphics )
		{
			ret = g_graphics->SetWindowMode (
				g_prefsManager->GetInt ( "ScreenWindowed", 0 ) == 1,
				g_prefsManager->GetInt ( "ScreenWidth", 0 ),
				g_prefsManager->GetInt ( "ScreenHeight", 0 ),
				g_prefsManager->GetInt ( "ScreenColourDepth", 32 )
			);
		}

		// Something went wrong.
		if ( ret )
		{
			delete g_graphics; g_graphics = NULL;

			if ( Data::Compare<const char *> ( graphicsDriver, "opengl" ) == 0  )
			{
				// You're screwed.
				break;
			}
			else if ( Data::Compare<const char *> ( graphicsDriver, "direct3d" ) == 0  )
			{
				// Direct3D may not be available on this platform.
				graphicsDriver = "opengl";
			}
			else
			{
				// Er, what the hell -did- they put in preferences?
				graphicsDriver = "opengl";
			}
		} else {
			break;
		}
	}

	// Something's terribly wrong.
	if ( !g_graphics )
		CrbReleaseAbort ( "Could not initialize the graphics engine." );

    // Hide the OS cursor
    g_graphics->ShowCursor ( true );
}

void Init_Interface()
{
    g_interface = new Interface();
    CrbReleaseAssert ( g_interface != NULL );

	g_app->Initialise();
}

void Init_Sound()
{
#if defined(USE_OPENAL)
	g_soundSystem = new OpenALSoundSystem();
#elif defined(USE_SDLMIXER)
	g_soundSystem = new SDLMixerSoundSystem();
#endif
	if ( !g_soundSystem )
		g_soundSystem = new NullSoundSystem();
}
