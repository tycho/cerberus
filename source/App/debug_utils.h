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

#ifndef __included_debug_utils_h
#define __included_debug_utils_h

//! Generates a crash log to the OS-appropriate location.
/*!
	\param _msg The error message to print along with the crash log.
 */
void GenerateBlackBox ( const char *_msg );
void CerberusReleaseAssert_Helper ( const char *_format, ... );

#if defined ( NDEBUG ) && defined ( TARGET_OS_WINDOWS )
#define PAUSE_COMMAND "PAUSE"
#else
#define PAUSE_COMMAND ""
#endif


#define  CrbReleaseAssert(x)  {                                             \
        if (!(x)) {                                                         \
            CerberusReleaseAssert_Helper (                                  \
                     "Assertion failure\n"                                  \
                     "Condition : %s\n"                                     \
                     "Location  : %s, line %d\n",                           \
                     #x, __FILE__, __LINE__ );                              \
        }                                                                   \
    }

#ifdef _DEBUG
  #ifdef TARGET_COMPILER_VC
    #define CrbDebugAssert(x)                                               \
        if(!(x)) {                                                          \
            /*GenerateBlackBox();*/                                         \
            ::ShowCursor(true);                                             \
            _ASSERT(x);                                                     \
        }
  #else
    #define CrbDebugAssert(x) { assert(x); }
  #endif
#else
    #define CrbDebugAssert(x)
#endif



//
// Abort - print message then bomb out (reset the resolution, too!)
//

#ifdef DEBUGLOG_ENABLED

    #define  CrbReleaseAbort(msg) {                                         \
        char message[1024];                                                 \
        sprintf ( message,  "\n"                                            \
                 "Cerberus has been forced to abort\n"                      \
                 "=================================\n"                      \
                 " Message   : %s\n"                                        \
                 " Location  : %s, line %d\n\n",                            \
                 msg, __FILE__, __LINE__ );                                 \
        fprintf ( stderr, message );                                        \
        SDL_Quit();                                                         \
        system ( PAUSE_COMMAND );                                           \
        exit(255);                                                          \
    }

#else

    #define  CrbReleaseAbort(msg) {                                                \
        g_stderr->WriteLine ( "\n"                                          \
                 "Cerberus has been forced to abort\n"                      \
                 "========---======================\n"                      \
                 " Message   : %s\n"                                        \
                 " Location  : %s, line %d\n\n",                            \
                 msg, __FILE__, __LINE__ );                                 \
            CrissCross::Debug::PrintStackTrace ( g_stderr );                \
            g_stderr->WriteLine ();                                         \
            CerberusReleaseAssert_Helper ( msg );                                \
    }

#endif

#endif
