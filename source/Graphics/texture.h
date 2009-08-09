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

#ifndef __included_texture_h
#define __included_texture_h

#include "Graphics/opengl.h"
#include "Graphics/graphics_opengl.h"

class Texture
{
protected:

    SDL_Surface *m_sdlSurface;

    Uint16       m_originalWidth;
    Uint16       m_originalHeight;

    bool         m_damaged;

    Uint8        m_alpha;

public:
    Texture();
    Texture ( SDL_Surface *_surface );
    virtual ~Texture();

    virtual bool Create ( Uint16 _width, Uint16 _height, bool _isColorKeyed ) = 0;
    virtual void Dispose ();

    bool IsDamaged ();
    void Damage ();

    Color32 GetPixel ( Uint16 _x, Uint16 _y );
    void   SetPixel ( Uint16 _x, Uint16 _y, Color32 _color );
    void   ReplaceColour ( SDL_Rect *_rect, Color32 _find, Color32 _replace );

    void SetAlpha ( Uint8 _alpha );

    virtual void Bind () = 0;

    virtual bool Upload () = 0;
};

#include "Graphics/texture_directx.h"
#include "Graphics/texture_opengl.h"

#endif
