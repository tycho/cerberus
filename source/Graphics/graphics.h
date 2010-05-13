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

#ifndef __graphics_h_included
#define __graphics_h_included

class Texture;
class OpenGLTexture;
class DirectXTexture;

class Graphics
{
protected:
    bool    m_windowed;

    Uint16  m_screenX;
    Uint16  m_screenY;

    Uint16  m_colorDepth;

    Uint16  m_centerX;
    Uint16  m_centerY;

	Uint32  m_defaultFont;

public:
    Graphics ();
    virtual ~Graphics();

	virtual const char *RendererName() = 0;

	virtual Uint32 DefaultFont();

	virtual Uint32 CreateFont ( const char *_fontFace, int _height) = 0;
	virtual void   DrawText ( Uint32 _font, Uint16 _x, Uint16 _y, Color32 _color, const char *_text ) = 0;
	virtual void   TextRect ( Uint32 _font, const char *_text, SDL_Rect &_rect ) = 0;

	virtual void   DrawRect ( SDL_Rect *_pos, Color32 _color ) = 0;

    virtual Uint16 GetMaximumTextureSize() = 0;

    virtual Sint32 GetCenterX();
    virtual Sint32 GetCenterY();

    virtual Sint32 GetScreenWidth();
    virtual Sint32 GetScreenHeight();

    virtual Uint32 GetScreen() = 0;

    virtual Uint32 GetSurfaceWidth ( Uint32 _surfaceID ) = 0;
    virtual Uint32 GetSurfaceHeight ( Uint32 _surfaceID ) = 0;
    virtual Color32 GetPixel ( Uint32 _surfaceID, int x, int y ) = 0;
    virtual void   SetPixel ( Uint32 _surfaceID, int x, int y, Color32 _color ) = 0;
    virtual void   DrawLine ( Uint32 _surfaceID, Color32 _color, int _startX, int _startY, int _stopX, int _stopY ) = 0;

    virtual int    SetSurfaceAlpha ( Uint32 _surfaceID, Uint8 alpha ) = 0;

    virtual void   ShowCursor ( bool _show ) = 0;

    virtual SDL_PixelFormat *GetPixelFormat ( Uint32 _surfaceID ) = 0;
    virtual void   ReplaceColour(Uint32 _surfaceID, SDL_Rect *_destRect, Color32 findcolor, Color32 replacecolor) = 0;

    virtual Uint32 LoadImage ( const char *_filename ) = 0;
    virtual Uint32 CreateSurface ( Uint32 _width, Uint32 _height ) = 0;
    virtual int    DeleteSurface ( Uint32 _surfaceID ) = 0;
    virtual int    FillRect ( Uint32 _surfaceID, SDL_Rect *_destRect, Color32 _color ) = 0;
    virtual int    Blit ( Uint32 _sourceSurfaceID, SDL_Rect const *_sourceRect,
                          Uint32 _destSurfaceID,   SDL_Rect const *_destRect, Color32 _color = Color32(255,255,255,255) ) = 0;
    virtual int    SetWindowMode ( bool _windowed, Sint16 _width, Sint16 _height, Uint8 _colorDepth ) = 0;
    virtual bool Flip() = 0;

	friend class Texture;
	friend class DirectXTexture;
	friend class OpenGLTexture;
};

extern Graphics *g_graphics;

#include "Graphics/graphics_opengl.h"
#include "Graphics/texture.h"

#endif
