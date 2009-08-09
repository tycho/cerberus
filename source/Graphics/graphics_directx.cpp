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

#ifdef ENABLE_DIRECT3D

#include <SDL_syswm.h>

#include "resource.h"

#include "App/app.h"
#include "App/preferences.h"
#include "App/version.h"
#include "Graphics/font_directx.h"
#include "Graphics/graphics_directx.h"

DirectXGraphics::DirectXGraphics()
 : Graphics(),
   m_deviceLost(false),
   m_sdlScreen(NULL),
   m_d3d(NULL),
   m_device(NULL),
   m_vertexBuffer(NULL),
   m_icon(NULL)
{
    int retval = SDL_Init ( SDL_INIT_VIDEO );
    CrbReleaseAssert ( retval == 0 );
}

DirectXGraphics::~DirectXGraphics()
{
	size_t i;
    for ( i = 0; i < m_textures.size(); i++ )
    {
        if ( m_textures.valid(i) )
        {
            DirectXTexture *tex = m_textures[i];
            m_textures.remove ( i );
            delete tex;
        }
    }
	if ( m_vertexBuffer )
		m_vertexBuffer->Release();
	if ( m_device )
		m_device->Release();
	if ( m_d3d )
		m_d3d->Release();

    delete g_openGL;
    g_openGL = NULL;

	if (m_icon)
		::DestroyIcon(m_icon);

    SDL_Quit ();
}

const char *DirectXGraphics::RendererName()
{
	static char renderer[64] = {'\0'};
	if ( !strlen ( renderer ) )
	{
		sprintf ( renderer, "Direct3D 9 (engine v%d.%d)",
			m_rendererVersionMajor, m_rendererVersionMinor );
	}
	return renderer;
}

Uint32 DirectXGraphics::CreateDisplayList()
{
	return 0;
}

void DirectXGraphics::DestroyDisplayList(Uint32 _list)
{
}

void DirectXGraphics::BeginDisplayList(Uint32 _list)
{
}

void DirectXGraphics::EndDisplayList(Uint32 _list)
{
}

void DirectXGraphics::CallDisplayList(Uint32 _list)
{
}

Uint32 DirectXGraphics::CreateFont ( const char *_fontFace, int _height)
{
#ifdef ENABLE_FONTS
	return m_fonts.insert(new DirectXFont(_fontFace, _height));
#else
	return 0;
#endif
}

void DirectXGraphics::DrawText ( Uint32 _font, Uint16 _x, Uint16 _y, Color32 _color, const char *_text)
{
#ifdef ENABLE_FONTS
	DirectXFont *font = m_fonts[_font];
	CoreAssert ( font );

	font->Draw(_x, _y, _text, _color);
#endif
}

void DirectXGraphics::TextRect ( Uint32 _font, const char *_text, SDL_Rect &_pos )
{
#ifdef ENABLE_FONTS
	DirectXFont *font = m_fonts[_font];
	CoreAssert ( font );

	font->Rect(_text, _pos);
#endif
}

void DirectXGraphics::DrawRect ( SDL_Rect *_pos, Color32 _color )
{
    CoreAssert ( _pos );
	DXVertex *vertices;

	if ( m_deviceLost)
		return;

	D3DCOLOR vertexColour = _color | FULL_ALPHA;

	m_vertexBuffer->Lock(0, 0, (void **)&vertices, NULL);

	vertices[0].x = _pos->x;
	vertices[0].y = _pos->y;
	vertices[0].z = 0.0f;
	vertices[0].colour = vertexColour;
	vertices[0].rhw = 1.0f;
	vertices[0].v = 0.0f;
	vertices[0].u = 0.0f;

	vertices[1].x = _pos->x + _pos->w;
	vertices[1].y = _pos->y;
	vertices[1].z = 0.0f;
	vertices[1].colour = vertexColour;
	vertices[1].rhw = 1.0f;
	vertices[1].v = 0.0f;
	vertices[1].u = 0.0f;

	vertices[2].x = _pos->x + _pos->w;
	vertices[2].y = _pos->y + _pos->h;
	vertices[2].z = 0.0f;
	vertices[2].colour = vertexColour;
	vertices[2].rhw = 1.0f;
	vertices[2].v = 0.0f;
	vertices[2].u = 0.0f;

	vertices[3].x = _pos->x;
	vertices[3].y = _pos->y + _pos->h;
	vertices[3].z = 0.0f;
	vertices[3].colour = vertexColour;
	vertices[3].rhw = 1.0f;
	vertices[3].v = 0.0f;
	vertices[3].u = 0.0f;

	vertices[4].x = _pos->x;
	vertices[4].y = _pos->y;
	vertices[4].z = 0.0f;
	vertices[4].colour = vertexColour;
	vertices[4].rhw = 1.0f;
	vertices[4].v = 0.0f;
	vertices[4].u = 0.0f;

	m_vertexBuffer->Unlock();

	m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	m_device->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);

	m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
}

void DirectXGraphics::ShowCursor ( bool _show )
{
    SDL_ShowCursor ( _show );
}

int DirectXGraphics::SetSurfaceAlpha ( Uint32 _surfaceID, Uint8 alpha )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    m_textures.get ( _surfaceID )->SetAlpha ( alpha );

    return 0;
}

void DirectXGraphics::DrawLine ( Uint32 _surfaceID, Color32 _color, int _startX, int _startY, int _stopX, int _stopY )
{
    CoreAssert ( _surfaceID == SCREEN_SURFACE_ID );
	DXVertex *vertices;

	if ( m_deviceLost)
		return;

	D3DCOLOR vertexColour = _color | FULL_ALPHA;

	m_vertexBuffer->Lock(0, 0, (void **)&vertices, NULL);

	vertices[0].colour = vertexColour;
	vertices[0].x = (float)_startX;
	vertices[0].y = (float)_startY;
	vertices[0].z = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	vertices[1].colour = vertexColour;
	vertices[1].x = (float)_stopX;
	vertices[1].y = (float)_stopY;
	vertices[1].z = 0.0f;
	vertices[1].rhw = 1.0f;
	vertices[1].u = 0.0f;
	vertices[1].v = 0.0f;

	m_vertexBuffer->Unlock();

	m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	HRESULT hr = m_device->DrawPrimitive ( D3DPT_LINELIST, 0, 1 );

	m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	CrbDebugAssert ( !FAILED(hr) );
}


Uint32 DirectXGraphics::GetPixel ( Uint32 _surfaceID, int x, int y )
{
    DirectXTexture *tex = m_textures.get ( _surfaceID );
    return tex->GetPixel ( x, y );
}

void DirectXGraphics::SetPixel ( Uint32 _surfaceID, int x, int y, Color32 _color )
{
    if ( _surfaceID == SCREEN_SURFACE_ID )
    {
		if ( m_deviceLost)
			return;

		DXVertex *vertices;

		D3DCOLOR vertexColour = _color | FULL_ALPHA;

		m_vertexBuffer->Lock(0, 0, (void **)&vertices, NULL);

		vertices[0].colour = vertexColour;
		vertices[0].x = (float)x;
		vertices[0].y = (float)y;
		vertices[0].z = 0.0f;
		vertices[0].rhw = 1.0f;
		vertices[0].u = 0.0f;
		vertices[0].v = 0.0f;

		m_vertexBuffer->Unlock();

		m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
		m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		HRESULT hr = m_device->DrawPrimitive ( D3DPT_POINTLIST, 0, 1 );

		m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

		CrbDebugAssert ( !FAILED(hr) );
    }
    else
    {
        CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
        DirectXTexture *tex = m_textures.get ( _surfaceID );
        tex->SetPixel ( x, y, _color );
        tex->Damage();
    }
}

Uint32 DirectXGraphics::LoadImage ( const char *_filename, bool _isColorKeyed )
{
    CrbReleaseAssert ( _filename != NULL );
    DirectXTexture *tex = new DirectXTexture();
	tex->Load ( _filename, _isColorKeyed );
    Uint32 ret = m_textures.insert ( tex );
    return ret;
}

int DirectXGraphics::DeleteSurface ( Uint32 _surfaceID )
{
    if ( !m_textures.valid ( _surfaceID ) ) return -1;

    DirectXTexture *tex = m_textures.get ( _surfaceID );
    CrbReleaseAssert ( tex != NULL );
    delete tex;
    m_textures.remove ( _surfaceID );

    return 0;
}

Uint32 DirectXGraphics::CreateSurface ( Uint32 _width, Uint32 _height, bool _isColorKeyed )
{
    DirectXTexture *tex = new DirectXTexture();

	bool textureCreated = tex->Create ( _width, _height, _isColorKeyed );
	CrbReleaseAssert ( textureCreated );

    Uint32 ret = m_textures.insert ( tex );

    return ret;
}

Uint16 DirectXGraphics::GetMaximumTextureSize()
{
	CrbDebugAssert ( m_caps.MaxTextureWidth == m_caps.MaxTextureHeight );
	return (Uint16)m_caps.MaxTextureWidth;
}

int DirectXGraphics::SetColorKey ( Color32 _color )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    m_colorKey = _color;
    m_colorKeySet = true;

    return 0;
}

void DirectXGraphics::ApplyColorKey ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

	DirectXTexture *surface = m_textures.get ( _surfaceID );
	SDL_SetColorKey ( surface->m_sdlSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, m_colorKey );
}

int DirectXGraphics::FillRect ( Uint32 _surfaceID, SDL_Rect *_destRect, Color32 _color )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    if ( _color == m_colorKey )
        _color = m_colorKey & ZERO_ALPHA;

    if ( _surfaceID == SCREEN_SURFACE_ID )
	{
		if ( m_deviceLost)
			return -1;

		RECT rect;
		if ( _destRect )
		{
			rect.left = _destRect->x;
			rect.top = _destRect->y;
			rect.right = _destRect->x + _destRect->w;
			rect.bottom = _destRect->y + _destRect->h;
		}
		IDirect3DSurface9 *surf;
		m_device->GetBackBuffer ( 0, 0, D3DBACKBUFFER_TYPE_MONO, &surf );
		m_device->ColorFill ( surf, _destRect ? &rect : NULL, _color );
		surf->Release();
        return 0;
    }
    else
    {
        CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
        DirectXTexture *tex = m_textures.get ( _surfaceID );
        CrbReleaseAssert ( tex != NULL );

        int r = SDL_FillRect ( tex->m_sdlSurface, _destRect, _color );

        tex->Damage ();

        return r;
    }
}

int DirectXGraphics::Blit ( Uint32 _sourceSurfaceID, SDL_Rect const *_sourceRect,
                           Uint32 _destSurfaceID,   SDL_Rect const *_destRect )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    DirectXTexture *fromSurface = NULL;
    DirectXTexture *toSurface = NULL;

    SDL_Rect *sourceRect = NULL;
    SDL_Rect *destRect = NULL;

    if ( _sourceSurfaceID == SCREEN_SURFACE_ID )
    {
        // trying to blit from screen?
        // not at the moment, sadly
        return -1;
    }

	if ( _destSurfaceID == SCREEN_SURFACE_ID )
	{
		// Our device is toasted.
		if ( m_deviceLost )
			return -1;
	}

    // Get the SDL surface for the source surface.
    CrbReleaseAssert ( m_textures.valid ( _sourceSurfaceID ) );
    fromSurface = m_textures.get ( _sourceSurfaceID );
    CrbReleaseAssert ( fromSurface != NULL );

    // Get the SDL surface for the destination surface.
    if ( _destSurfaceID != SCREEN_SURFACE_ID )
    {
        CrbReleaseAssert ( m_textures.valid ( _destSurfaceID ) );
        toSurface = m_textures.get ( _destSurfaceID );
        CrbReleaseAssert ( toSurface != NULL );
    } else {
        toSurface = NULL;
    }

    // With SDL, you can have a NULL destination rectangle if you are just
    // writing to 0,0 and the max possible WxH on the surface.
    SDL_Rect nullDestRect;
    if ( !_destRect )
    {
        nullDestRect.x = 0; nullDestRect.y = 0;
        nullDestRect.w = m_sdlScreen->w;
        nullDestRect.h = m_sdlScreen->h;
        destRect = &nullDestRect;
    } else {
        memcpy ( &nullDestRect, _destRect, sizeof(SDL_Rect) );
        destRect = &nullDestRect;
    }

    // With SDL, you can have a NULL source rectangle if you are just
    // reading from 0,0 and the max possible WxH on the surface.
    SDL_Rect nullSourceRect;
    if ( !_sourceRect )
    {
        nullSourceRect.x = 0; nullSourceRect.y = 0;
        nullSourceRect.w = fromSurface->m_originalWidth;
        nullSourceRect.h = fromSurface->m_originalHeight;
        sourceRect = &nullSourceRect;
    } else {
        memcpy ( &nullSourceRect, _sourceRect, sizeof(SDL_Rect) );
        sourceRect = &nullSourceRect;
    }

	Uint16 surfW, surfH;
	if ( toSurface )
	{
		surfW = toSurface->m_sdlSurface->w;
		surfH = toSurface->m_sdlSurface->h;
	} else {
		surfW = m_sdlScreen->w;
		surfH = m_sdlScreen->h;
	}

    if ( destRect->x > surfW ) {
        // This blit is completely off the surface.
        return 1;
    }
    if ( destRect->y > surfH ) {
        // This blit is completely off the surface.
        return 1;
    }

    // Is this blit is going to be partially off the surface?
    if ( destRect->x + sourceRect->w > surfW )
        sourceRect->w = surfW - destRect->x;
    if ( destRect->y + sourceRect->h > surfH )
        sourceRect->h = surfH - destRect->y;

    // With SDL, you don't have to specify the dest width/height. With OpenGL, we do.
    destRect->w = sourceRect->w;
    destRect->h = sourceRect->h;

    // Now we need to do the actual blit!
    if ( _destSurfaceID == SCREEN_SURFACE_ID )
    {
		DXVertex *vertices;

		fromSurface->Upload();

        float texW = (float)fromSurface->m_sdlSurface->w,
              texH = (float)fromSurface->m_sdlSurface->h;
        float texX = (float)sourceRect->x,
              texY = (float)sourceRect->y;

		float srcR =  (float)(sourceRect->x + sourceRect->w) / texW,
			  srcB =  (float)(sourceRect->y + sourceRect->h) / texH;
		float srcX =  texX / texW,
			  srcY =  texY / texH;

		float destX = (float)destRect->x,
			  destY = (float)destRect->y;
		float destR = (float)(destRect->x + destRect->w),
			  destB = (float)(destRect->y + destRect->h);

		D3DCOLOR vertexColour = 0x00FFFFFF | (fromSurface->m_alpha << 24);

		if ( FAILED(m_vertexBuffer->Lock(0, 0, (void **)&vertices, NULL)) )
			return -1;

		int i = 0;

		// Top left
		vertices[0].colour = vertexColour;
		vertices[0].x = destX - 0.5f;
		vertices[0].y = destY - 0.5f;
		vertices[0].z = 0.0f;
		vertices[0].rhw = 1.0f;
		vertices[0].u = srcX;
		vertices[0].v = srcY;

		// Top right
		vertices[1].colour = vertexColour;
		vertices[1].x = destR - 0.5f;
		vertices[1].y = destY - 0.5f;
		vertices[1].z = 0.0f;
		vertices[1].rhw = 1.0f;
		vertices[1].u = srcR;
		vertices[1].v = srcY;

		// Bottom right
		vertices[2].colour = vertexColour;
		vertices[2].x = destR - 0.5f;
		vertices[2].y = destB - 0.5f;
		vertices[2].z = 0.0f;
		vertices[2].rhw = 1.0f;
		vertices[2].u = srcR;
		vertices[2].v = srcB;

		// Bottom left
		vertices[3].colour = vertexColour;
		vertices[3].x = destX - 0.5f;
		vertices[3].y = destB - 0.5f;
		vertices[3].z = 0.0f;
		vertices[3].rhw = 1.0f;
		vertices[3].u = srcX;
		vertices[3].v = srcB;

		m_vertexBuffer->Unlock();

		fromSurface->Bind();

		HRESULT hr = m_device->DrawPrimitive ( D3DPT_TRIANGLEFAN, 0, 2 );
		if ( FAILED(hr) )
			return -1;

        return 0;
    }
    else
    {
        // Blit
        int res = SDL_BlitSurface ( fromSurface->m_sdlSurface, sourceRect, toSurface->m_sdlSurface, destRect );

        // We want to upload the textures to graphics memory
        // later in order to make things fast.
        toSurface->Damage();

        return res;
    }

}

void DirectXGraphics::ReplaceColour ( Uint32 _surfaceID, SDL_Rect *_destRect, Uint32 findcolor, Uint32 replacecolor )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( _surfaceID != SCREEN_SURFACE_ID );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    m_textures.get ( _surfaceID )->ReplaceColour ( _destRect, findcolor, replacecolor );

}

SDL_PixelFormat *DirectXGraphics::GetPixelFormat ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    if (_surfaceID == SCREEN_SURFACE_ID)
        return m_sdlScreen->format;

    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->format;
}

Uint32 DirectXGraphics::GetSurfaceHeight ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    if ( _surfaceID == SCREEN_SURFACE_ID )
        return GetScreenHeight();

    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->h;
}

Uint32 DirectXGraphics::GetSurfaceWidth ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    if (_surfaceID == SCREEN_SURFACE_ID)
        return GetScreenWidth();

    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->w;
}

Uint32 DirectXGraphics::GetScreen ()
{
    return SCREEN_SURFACE_ID;
}

int DirectXGraphics::SetWindowMode ( bool _windowed, Sint16 _width, Sint16 _height, Uint8 _colorDepth )
{
    CrbReleaseAssert ( m_sdlScreen == NULL );

    if ( _colorDepth < 16 || _colorDepth > 32 ) _colorDepth = 16;

    const SDL_VideoInfo* info = NULL;
    info = SDL_GetVideoInfo ();
    CrbReleaseAssert ( info != NULL );

    m_windowed = _windowed;

	if (!_windowed) {
		m_screenX = _width == 0 ? info->current_w : _width;
		m_screenY = _height == 0 ? info->current_h : _height;
	} else {
		m_screenX = _width == 0 ? 1024 : _width;
		m_screenY = _height == 0 ? 768 : _height;
	}

    m_centerX = m_screenX / 2;
    m_centerY = m_screenY / 2;

    m_colorDepth = _colorDepth;

    g_console->WriteLine ( "The requested color depth is %d, and we're using %d.", _colorDepth, m_colorDepth );
    g_console->WriteLine ( "Setting display mode of %dx%dx%d...", m_screenX, m_screenY, m_colorDepth );

    Uint32 flags = SDL_RESIZABLE;

    if ( !m_windowed ) flags |= SDL_FULLSCREEN;

    m_sdlScreen = SDL_SetVideoMode ( m_screenX, m_screenY, m_colorDepth, flags );

    if ( !m_sdlScreen )
    {
        g_console->WriteLine ( "SDL couldn't initialise properly: %s", SDL_GetError() );
        return -1;
    }

    // m_sdlScreen->m_textureID = SCREEN_SURFACE_ID;

    char windowTitle[512];
	sprintf(windowTitle, "%s v%s", APP_NAME, Cerberus::Version::LongVersion());
    SDL_WM_SetCaption ( windowTitle, NULL );

    if ( _windowed )
    {
        HWND hwnd = FindWindow ( NULL, windowTitle );
        RECT workArea, window;
        GetWindowRect ( hwnd, &window );
        SystemParametersInfo ( SPI_GETWORKAREA, 0, &workArea, 0 );
        Uint32 left = workArea.right - (window.right - window.left) - 20;
        Uint32 top =  ( (workArea.top + workArea.bottom) - (window.bottom - window.top) ) / 2;
        SetWindowPos ( hwnd, HWND_TOP, left, top, 0, 0, SWP_NOSIZE );
    }


    info = SDL_GetVideoInfo();

    g_console->WriteLine ( "Display mode set successfully (%dx%dx%d).", info->current_w, info->current_h, info->vfmt->BitsPerPixel );
    g_console->WriteLine ();

	g_prefsManager->SetInt("ScreenWidth", info->current_w);
	g_prefsManager->SetInt("ScreenHeight", info->current_h);

	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if ( !m_d3d ) return -1;

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWMInfo(&wmInfo);
	HWND hWnd = wmInfo.window;

	HINSTANCE handle = ::GetModuleHandle(NULL);
	m_icon = ::LoadIcon(handle, MAKEINTRESOURCE(IDI_MAIN_ICON));
	if (m_icon)
		::SetClassLong(hWnd, GCL_HICON, (LONG) m_icon);

	ZeroMemory ( &m_caps, sizeof ( D3DCAPS9 ) );
	m_d3d->GetDeviceCaps ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_caps);

	ZeroMemory ( &m_presentParams, sizeof ( D3DPRESENT_PARAMETERS ) );

	m_presentParams.Windowed = _windowed;
	m_presentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_presentParams.MultiSampleQuality = 0;
	m_presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_presentParams.hDeviceWindow = hWnd;
	m_presentParams.BackBufferCount = 1;
	m_presentParams.PresentationInterval =
		g_prefsManager->GetInt ( "WaitVerticalRetrace", 1 ) != 0 ?
		D3DPRESENT_INTERVAL_ONE :		// Wait for vertical retrace (vsync)
		D3DPRESENT_INTERVAL_IMMEDIATE;  // Don't wait for vertical retrace

	if ( _windowed )
	{
		D3DDISPLAYMODE d3ddm;
		RECT rWindow;

		m_d3d->GetAdapterDisplayMode ( D3DADAPTER_DEFAULT, &d3ddm );

		GetClientRect ( hWnd, &rWindow );

		_width = (Sint16)(rWindow.right - rWindow.left);
		_height = (Sint16)(rWindow.bottom - rWindow.top);

		m_presentParams.BackBufferFormat = d3ddm.Format;
	}
	else
	{
		m_presentParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	}

	m_presentParams.BackBufferWidth = _width;
	m_presentParams.BackBufferHeight = _height;

	bool bHwVertexProcessing = (m_caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) != 0;

	// Set default settings
	UINT AdapterToUse = D3DADAPTER_DEFAULT;
	D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
#ifndef USE_NVPERFHUD
	// When building a shipping version, disable PerfHUD (opt-out)
#else
	// Look for 'NVIDIA PerfHUD' adapter
	// If it is present, override default settings
	for ( UINT Adapter = 0; Adapter < m_d3d->GetAdapterCount(); Adapter++ ) {
		D3DADAPTER_IDENTIFIER9 Identifier;
		HRESULT Res;
		Res = m_d3d->GetAdapterIdentifier ( Adapter, 0, &Identifier );
		if ( strstr ( Identifier.Description, "PerfHUD" ) != 0 ) {
			AdapterToUse = Adapter;
			DeviceType = D3DDEVTYPE_REF;
			break;
		}
	}
#endif

	if (FAILED(m_d3d->CreateDevice (
			AdapterToUse,
			DeviceType,
			hWnd,
			bHwVertexProcessing ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_presentParams,
			&m_device)))
		return -1;

	const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	m_device->SetVertexShader ( NULL );
	m_device->SetFVF ( D3DFVF_TLVERTEX );

	if ( FAILED(m_device->CreateVertexBuffer ( sizeof(DXVertex) * 5, NULL, D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)) )
		return -1;

	m_device->SetStreamSource ( 0, m_vertexBuffer, 0, sizeof(DXVertex) );

	m_device->SetRenderState ( D3DRS_LIGHTING, FALSE );
	m_device->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );
	m_device->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_device->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	m_device->SetRenderState ( D3DRS_CULLMODE, D3DCULL_NONE );
	m_device->SetRenderState ( D3DRS_ZENABLE, D3DZB_FALSE );
	m_device->SetTextureStageState ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

	m_defaultFont = CreateFont("Arial", 12);

	if ( FAILED(m_device->BeginScene()) ) return -1;

	if ( FAILED(m_device->Clear(0, NULL, D3DCLEAR_TARGET, 0, 0.0f, 0)) ) return -1;

    return 0;
}

bool DirectXGraphics::Flip()
{
	HRESULT hr;
	bool retval = true;
	if ( !m_deviceLost )
	{
		m_device->EndScene();
		hr = m_device->Present(NULL,NULL,NULL,NULL);
		if ( FAILED(hr) )
		{
			retval = false;
			m_deviceLost = true;
		}
	}
	if ( m_deviceLost )
	{
		retval = false;
		hr = m_device->TestCooperativeLevel();
		if ( hr == D3DERR_DEVICENOTRESET )
		{
			hr = m_device->Reset ( &m_presentParams );
			CrbDebugAssert ( hr == D3D_OK );
		}
		if ( hr == D3D_OK )
		{
			const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

			m_device->SetVertexShader ( NULL );
			m_device->SetFVF ( D3DFVF_TLVERTEX );

			m_device->SetStreamSource ( 0, m_vertexBuffer, 0, sizeof(DXVertex) );

			m_device->SetRenderState ( D3DRS_LIGHTING, FALSE );
			m_device->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );
			m_device->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			m_device->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			m_device->SetRenderState ( D3DRS_CULLMODE, D3DCULL_NONE );
			m_device->SetRenderState ( D3DRS_ZENABLE, D3DZB_FALSE );
			m_device->SetTextureStageState ( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );

			m_deviceLost = false;
			retval = true;
		}
	}
	if ( !m_deviceLost)
	{
		hr = m_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
		CrbDebugAssert ( hr == D3D_OK );
		hr = m_device->BeginScene();
		CrbDebugAssert ( hr == D3D_OK );
	}
	return retval;
}

#endif
