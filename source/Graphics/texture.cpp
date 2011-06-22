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

#include "Graphics/opengl.h"
#include "Graphics/texture.h"

Texture::Texture ()
 : m_sdlSurface(NULL),
   m_originalWidth(0),
   m_originalHeight(0),
   m_damaged(true),
   m_alpha(0xFF)
{
}

Texture::Texture ( SDL_Surface *_surface )
 : m_sdlSurface(_surface),
   m_originalWidth(0),
   m_originalHeight(0),
   m_damaged(true),
   m_alpha(0xFF)
{
}

Texture::~Texture()
{
    Dispose();
}

void Texture::Dispose()
{
    if ( m_sdlSurface )
    {
        SDL_FreeSurface ( m_sdlSurface );
        m_sdlSurface = NULL;
    }
}

void Texture::Damage()
{
    m_damaged = true;
}

Uint16 Texture::GetWidth() {
    return m_originalWidth;
}

Uint16 Texture::GetHeight() {
    return m_originalHeight;
}

void Texture::SetPixel ( Uint16 _x, Uint16 _y, Color32 _pixel )
{
    CrbReleaseAssert ( m_sdlSurface != NULL );

    if ( (Sint16)_x < 0 || (Sint16)_y < 0 ) return;
    if ( _x >= m_sdlSurface->w || _y >= m_sdlSurface->h ) return ;

    SDL_LockSurface ( m_sdlSurface );

    int bpp = m_sdlSurface->format->BytesPerPixel;

    CrbReleaseAssert ( m_sdlSurface->pixels != NULL );

    // Here p is the address to the pixel we want to set
    Uint8 *p = (Uint8 *)m_sdlSurface->pixels + _y * m_sdlSurface->pitch + _x * bpp;

    switch(bpp) {
    case 4:
        *(Uint32 *)p = _pixel.rgba;
        break;
	default:
		CrbReleaseAbort("Whoops, we don't have < 32-bit color implemented.");
    }

    SDL_UnlockSurface ( m_sdlSurface );

	m_damaged = true;
}

Color32 Texture::GetPixel ( Uint16 _x, Uint16 _y )
{
    CrbReleaseAssert ( m_sdlSurface != NULL );
    if ( (Sint16)_x < 0 || (Sint16)_y < 0 ) return 0;
    if ( _x >= m_sdlSurface->w || _y >= m_sdlSurface->h ) return 0;

    bool isLocked = false;

    // Lock only when absolutely necessary. We hate slowness.
    if ( !m_sdlSurface->pixels )
    {
        SDL_LockSurface ( m_sdlSurface );
        isLocked = true;
    }

    int bpp = m_sdlSurface->format->BytesPerPixel;

    // Here p is the address to the pixel we want to retrieve
    Uint8 *p = (Uint8 *)m_sdlSurface->pixels + _y * m_sdlSurface->pitch + _x * bpp;
    Uint32 pixel = 0;

    switch(bpp) {
    case 1:
        pixel = *p;
        break;
    case 2:
        pixel = *(Uint16 *)p;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixel = p[0] << 16 | p[1] << 8 | p[2];
        else
            pixel = p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        pixel = *(Uint32 *)p;
        break;
    }

    if ( isLocked )
        SDL_UnlockSurface ( m_sdlSurface );

    return pixel;
}

void Texture::ReplaceColour ( SDL_Rect *_destRect, Color32 _find, Color32 _replace )
{
    int x1 = _destRect->x,
        x2 = _destRect->x + _destRect->w,
        y1 = _destRect->y,
        y2 = _destRect->y + _destRect->h;

    SDL_LockSurface ( m_sdlSurface );
    for ( int y = y1; y < y2; y++ ) {
        for ( int x = x1; x < x2; x++ ) {
            if ( GetPixel ( x, y ) == _find )
                SetPixel ( x, y, _replace );
        }
    }
    SDL_UnlockSurface ( m_sdlSurface );

	m_damaged = true;
}

void Texture::SetAlpha ( Uint8 _alpha )
{
    CrbReleaseAssert ( m_sdlSurface != NULL );

    m_alpha = _alpha;

    SDL_SetAlpha ( m_sdlSurface, SDL_SRCALPHA | SDL_RLEACCEL, m_alpha );
}
