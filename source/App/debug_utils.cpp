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
#include "App/debug_utils.h"
#include "App/version.h"

void GenerateBlackBox ( const char *_msg )
{
    FILE *_file = fopen( "blackbox.txt", "wt" );

    fprintf( _file, "=============================\n" );
    fprintf( _file, "= CERBERUS BLACK BOX REPORT =\n" );
    fprintf( _file, "=============================\n\n" );

	fprintf( _file, "VERSION : %s v%s\n", APP_NAME, Cerberus::Version::LongVersion() );

    if( _msg ) fprintf( _file, "%s\n", _msg );


    //
    // Print preferences information

    char buffer[4096];
#ifndef TARGET_OS_WINDOWS
    sprintf( buffer, "%s%s", g_app->GetApplicationSupportPath(), "preferences.txt" );
#else
    sprintf( buffer, "%s%s", g_app->GetApplicationPath(), "preferences.txt" );
#endif
    FILE *prefsFile = fopen(buffer, "r");
    if( prefsFile )
    {
        fprintf( _file, "\n" );
        fprintf( _file, "===================\n" );
        fprintf( _file, "=   PREFERENCES   =\n" );
        fprintf( _file, "===================\n\n" );

        char line[256];
        while ( fgets ( line, 256, prefsFile ) != NULL )
        {
            if ( line[0] != '#' && line[0] != '\n' ) // Skip comment lines
            {
                fprintf( _file, "%s", line );
            }
        }
        fclose(prefsFile);
    }

    //
    // Print stack trace
    // Get our frame pointer, chain upwards

    fprintf( _file, "\n" );
    fprintf( _file, "===================\n" );
    fprintf( _file, "=   STACK TRACE   =\n" );
    fprintf( _file, "===================\n\n" );

    CrissCross::IO::CoreIOWriter *cio_file = new CrissCross::IO::CoreIOWriter(_file,false);
    CrissCross::Debug::PrintStackTrace ( cio_file );
    delete cio_file;

    fclose( _file );
}

void CerberusReleaseAssert_Helper ( const char *_format, ... )
{
    va_list list;
    char buffer[512];
    va_start(list, _format);
    vsprintf(buffer, _format, list);
    va_end(list);

    g_stderr->WriteLine ( "\n\n"
         "A Cerberus assertion failure has occurred\n"
         "=========================================\n"
         "%s\n", buffer);
    CrissCross::Debug::PrintStackTrace ( g_stderr );
    g_stderr->WriteLine ();

    SDL_Quit();
    GenerateBlackBox(buffer);
#if defined ( TARGET_OS_WINDOWS )
    MessageBox ( NULL, "A fatal error occured in Cerberus.\n\n"
                       "The details of this error have been written to\n"
                       "blackbox.txt in the directory Cerberus is installed in.\n\n"
                       "Please report this on the Cerberus forums at\n"
                       "http://www.ferrousmoon.com/forums/\n\n"
                       "Cerberus will now shut down.",
                       "Cerberus Fatal Error", MB_ICONEXCLAMATION | MB_OK );
#endif
#if defined ( INTERNAL_BUILD )
    abort();
#else
    exit(255);
#endif
}
