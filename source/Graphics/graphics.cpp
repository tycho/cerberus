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

#include "Graphics/graphics.h"
#include "App/app.h"

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
// SDL Dependencies
#    pragma comment (lib, "advapi32.lib")
#    pragma comment (lib, "gdi32.lib")
#    pragma comment (lib, "shell32.lib")
#    pragma comment (lib, "user32.lib")

// SDL
#    pragma comment (lib, "SDL.lib")
#    pragma comment (lib, "SDLmain.lib")
#    pragma comment (lib, "SDL_image.lib")
#    pragma comment (lib, "dxguid.lib")
#    pragma comment (lib, "libpng.lib")
#    pragma comment (lib, "winmm.lib")
#    pragma comment (lib, "zlib.lib")
#endif

Graphics::Graphics()
 : m_windowed(false), m_screenX(0), m_screenY(0), m_colorDepth(0),
   m_centerX(0), m_centerY(0), m_defaultFont(0)
{
}

Graphics::~Graphics()
{
}

Uint32 Graphics::DefaultFont()
{
	return m_defaultFont;
}

Sint32 Graphics::GetCenterX()
{
    return m_centerX;
}

Sint32 Graphics::GetCenterY()
{
    return m_centerY;
}

Sint32 Graphics::GetScreenWidth()
{
    return m_screenX;
}

Sint32 Graphics::GetScreenHeight()
{
    return m_screenY;
}

Graphics *g_graphics;
