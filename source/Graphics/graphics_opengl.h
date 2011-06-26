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

#ifndef __included_graphics_opengl_h
#define __included_graphics_opengl_h

#include "Graphics/graphics.h"

#ifdef ENABLE_OPENGL

class Entity;

class Texture;
class OpenGLTexture;
class OpenGLFont;

class OpenGLGraphics : public Graphics
{
private:
	static const int                     m_rendererVersionMajor = 1;
	static const int                     m_rendererVersionMinor = 0;

    OpenGLTexture                       *m_sdlScreen;

#ifdef ENABLE_FONTS
	Data::DArray<OpenGLFont *>           m_fonts;
	Data::LList<const char *>                  m_fontpaths;
#endif

    short m_vertexArray[8];
    short m_texCoordArrayi[8];
    float m_texCoordArrayf[8];

public:
    OpenGLGraphics();
    virtual ~OpenGLGraphics();

	virtual const char *RendererName();

	virtual Uint32 CreateFont ( const char *_fontFace, int _height );
	virtual void   DrawText ( Uint32 _font, Uint16 _x, Uint16 _y, Color32 _color, const char *_text );
	virtual void   TextRect ( Uint32 _font, const char *_text, SDL_Rect &_rect );

	virtual void   DrawRect ( SDL_Rect *_pos, Color32 _color );

    virtual Uint32 CreateSurface ( Uint32 _width, Uint32 _height );
    virtual int    DeleteSurface ( Uint32 _surfaceID );
    virtual Uint32 LoadImage ( const char *_filename );

    virtual void DrawEntity ( Entity *_entity );

    virtual void   DrawLine ( Uint32 _surfaceID, Color32 _color, int _startX, int _startY, int _stopX, int _stopY );
    virtual int    FillRect ( Uint32 _surfaceID, SDL_Rect *_destRect, Color32 _color );
    virtual Color32 GetPixel ( Uint32 _surfaceID, int x, int y );
    virtual void   SetPixel ( Uint32 _surfaceID, int x, int y, Color32 _color );
    virtual void   ReplaceColour ( Uint32 _surfaceID, SDL_Rect *_destRect, Color32 _findColour, Color32 _replaceColour );

    virtual Uint16 GetMaximumTextureSize();
    virtual SDL_PixelFormat *GetPixelFormat ( Uint32 _surfaceID );
    virtual Uint32 GetScreen();
    virtual Uint32 GetSurfaceHeight ( Uint32 _surfaceID );
    virtual Uint32 GetSurfaceWidth ( Uint32 _surfaceID );

    virtual Texture *GetTexture ( Uint32 _id );

    virtual void   ShowCursor ( bool _show );

    virtual int    SetSurfaceAlpha ( Uint32 _surfaceID, Uint8 alpha );
    virtual int    Blit ( Uint32 _sourceSurfaceID, SDL_Rect const *_sourceRect,
                          Uint32 _destSurfaceID,   SDL_Rect const *_destRect, Color32 _color );
    virtual int    SetWindowMode ( bool _windowed, Sint16 _width, Sint16 _height, Uint8 _colorDepth );
    virtual inline bool Flip();
};

#endif

#include "Graphics/texture.h"
#include "Graphics/font.h"

#endif
