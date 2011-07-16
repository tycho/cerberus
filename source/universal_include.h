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
#ifndef __included_universal_include_h
#define __included_universal_include_h

#define _DEBUG
#undef NDEBUG

#ifdef _DEBUG
#    include <assert.h>
#endif
#ifdef __cplusplus
#  include <crisscross/crisscross.h>
#endif

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
#    pragma warning ( error: 4996 )
#    pragma warning ( error: 4706 )
#    pragma warning ( disable: 4786 )
#    ifdef _DEBUG
#        pragma comment ( lib, "libcpmtd.lib" )
#        pragma comment ( lib, "libcmtd.lib" )
#    else
#        pragma comment ( lib, "libcpmt.lib" )
#        pragma comment ( lib, "libcmt.lib" )
#    endif
#endif

#if defined(TARGET_COMPILER_ICC) && defined(TARGET_OS_WINDOWS)
#    pragma comment ( lib, "libmmds.lib" )
#    pragma comment ( lib, "libircmt.lib" )
#endif

#define TO_C_STRING(s) TO_STRING(s)
#define TO_STRING(s) #s

#define PROTOCOL_VERSION    1

#define VERSION_CODENAME     "Cerberus"
#define VERSION_NAME         "Cerberus"

#define APP_NAME VERSION_NAME

#define RELEASE_BUILD

#ifdef _DEBUG
#  define INTERNAL_BUILD
#else
#  define BETA_BUILD
#endif

#include "App/debug_utils.h"

#define ENABLE_OPENGL

#define ENABLE_FONTS

#if !defined(TARGET_OS_WINDOWS) || defined(DETECT_MEMORY_LEAKS)
#	undef ENABLE_DIRECT3D
#endif

//#define ENABLE_NETWORKING

//********************** SOUND **********************
//#define USE_OPENAL        // In development
#define USE_SDLMIXER        // Fully functional (best choice)

#if !( defined(USE_OPENAL) ^ defined(USE_SDLMIXER) )
#    error You must select one and ONLY one sound engine.
#endif
//********************** SOUND **********************

//******************* SCRIPTING *********************
#define USE_LUA

#if !( defined(USE_LUA) )
#    error You must select one and ONLY one scripting engine.
#endif
//******************* SCRIPTING *********************

//******************* NETWORKING ********************
#ifdef ENABLE_NETWORKING
#define USE_CRISSCROSS_NET    // Fully functional (best choice)

#if !( defined(USE_CRISSCROSS_NET) )
#    error You must select one and ONLY one networking engine.
#endif
#endif
//******************* NETWORKING ********************

// #define FORCE_VSYNC

#ifdef TARGET_COMPILER_VC
#    if _MSC_VER >= 1300 && _MSC_VER < 1400
#        define _INC_MALLOC
#    endif
#endif

#ifdef __cplusplus
#if defined ( TARGET_OS_WINDOWS )
#    include <SDL.h>
#    include <SDL_image.h>
#elif defined ( TARGET_OS_MACOSX )
#    include <SDL/SDL.h>
#    include <SDL_image/SDL_image.h>
#else
#    include <SDL/SDL.h>
#    include <SDL/SDL_image.h>
#endif

#ifdef USE_SDLMIXER
#if defined ( TARGET_OS_WINDOWS )
#    include <SDL_mixer.h>
#elif defined ( TARGET_OS_MACOSX )
#    include <SDL_mixer/SDL_mixer.h>
#else
#    include <SDL/SDL_mixer.h>
#endif
#endif

#ifdef TARGET_OS_WINDOWS
#	define FTGL_LIBRARY_STATIC
#	define NOMINMAX
#	include <windows.h>
#endif

#define GLEW_STATIC

#ifdef TARGET_OS_MACOSX
#  include <GL/glew.h>
#  include <OpenGL/GL.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/gl.h>
#  include <GL/glext.h>
#endif

#ifdef ENABLE_FONTS
#  include <FTGL/ftgl.h>
#endif

#include <zlib.h>

#ifdef TARGET_OS_LINUX
#    include <sys/types.h>
#    include <unistd.h>
#    include <signal.h>
#endif

extern "C" {
#ifdef USE_LUA
#    include <lua.h>
#    include <lualib.h>
#    include <lauxlib.h>
#endif
}

using namespace std;
using namespace CrissCross;

extern IO::Console *g_console;

#ifdef _OPENMP
#  include <omp.h>
#  define TARGET_OPENMP
#endif

#ifndef TARGET_OS_WINDOWS
#    define stricmp strcasecmp
#else
#    define stricmp _stricmp
#endif

#include <cmath>

__inline bool isPowerOfTwo ( Uint32 v ) { return !(v & (v - 1)) && v; }
__inline Uint32 nearestPowerOfTwo ( Uint32 v ) { return (Uint32)pow( 2.0, ceil( log( (double)v ) / log( 2.0 ) ) ); }

#ifndef PI
#    define PI 3.14159265358979323846
#endif

#define DIV180BYPI 180.0 / PI
#define TWOPI PI * 2.0
#define DIVBY360 1.0 / 360.0
#define DIV360MULTPI DIVBY360 * TWOPI
#define TORADIANS(d) DIV360MULTPI * d
#define TODEGREES(x) DIV180BYPI * x

extern Uint32 fontid;

#include "Graphics/color.h"
#include "Graphics/rect.h"
#include "Graphics/vertex.h"

#endif // __cplusplus

#endif
