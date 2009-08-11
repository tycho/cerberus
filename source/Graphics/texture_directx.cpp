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

#include "App/app.h"
#include "Graphics/graphics_directx.h"
#include "Graphics/texture_directx.h"

static DirectXGraphics *graphics = NULL;

DirectXTexture::DirectXTexture ()
 : m_texture(NULL),
   Texture()
{
	if ( !graphics )
		graphics = dynamic_cast<DirectXGraphics *>(g_graphics);
	CrbReleaseAssert ( graphics );
}

DirectXTexture::~DirectXTexture()
{
	Dispose();
}

void DirectXTexture::Dispose()
{
	if (m_texture) {
		m_texture->Release();
		m_texture = NULL;
	}
	Texture::Dispose();
}

bool DirectXTexture::Load ( const char *_filename )
{
	m_sdlSurface = g_app->m_resource->GetImage ( _filename );
	if ( !m_sdlSurface ) return false;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
	SDL_Surface *copy = SDL_CreateRGBSurface ( SDL_SWSURFACE, m_sdlSurface->w, m_sdlSurface->h, 32, rmask, gmask, bmask, amask );
    SDL_SetAlpha ( copy, 0, SDL_ALPHA_OPAQUE );
	SDL_BlitSurface ( m_sdlSurface, NULL, copy, NULL );
	SDL_FreeSurface ( m_sdlSurface );
	m_sdlSurface = copy;
	copy = NULL;

	MemMappedFile *src = g_app->m_resource->GetUncompressedFile ( _filename );
	if ( !src ) return false;

	D3DCOLOR colorKey = _isColorKeyed ? g_graphics->GetColorKey() : 0;

	if (FAILED(D3DXCreateTexture(
		graphics->m_device,
		m_sdlSurface->w,
		m_sdlSurface->h,
		1,
		0,
		D3DFMT_A8B8G8R8,
		D3DPOOL_MANAGED,
		&m_texture)))
		return false;

	m_damaged = true;

	return true;
}

bool DirectXTexture::Create ( Uint16 _width, Uint16 _height )
{
    CrbReleaseAssert ( _width > 0 ); CrbReleaseAssert ( _height > 0 );

    Uint32 oldWidth = _width, oldHeight = _height;
    //if ( !g_openGL->GetSetting ( OPENGL_TEX_ALLOW_NPOT ) ) {
        if ( !isPowerOfTwo ( _width ) )
            _width = nearestPowerOfTwo ( _width );
        if ( !isPowerOfTwo ( _height ) )
            _height = nearestPowerOfTwo ( _height );
        CrbReleaseAssert ( isPowerOfTwo ( _width * _height ) );
    //}

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    m_sdlSurface = SDL_CreateRGBSurface ( SDL_SWSURFACE, _width, _height, 32, rmask, gmask, bmask, amask );
    CrbReleaseAssert ( m_sdlSurface != NULL );

    SDL_SetAlpha ( m_sdlSurface, 0, SDL_ALPHA_OPAQUE );

	if (FAILED(D3DXCreateTexture(
		graphics->m_device,
		_width,
		_height,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_texture)))
		return false;

	//CrbReleaseAbort ( "Create() not implemented." );

    m_originalWidth = oldWidth;
    m_originalHeight = oldHeight;

    Damage ();

    return true;
}

bool DirectXTexture::Reset()
{
	if (m_texture) {
		m_texture->Release();
		m_texture = NULL;
	}
	if (FAILED(D3DXCreateTexture(
		graphics->m_device,
		m_originalWidth,
		m_originalHeight,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		&m_texture)))
		return false;
	Damage();
	return true;
}

void DirectXTexture::Bind()
{
	if ( !graphics->m_deviceLost )
	{
		HRESULT hr = graphics->m_device->SetTexture ( 0, m_texture );
		CrbDebugAssert ( hr == D3D_OK );
	}
}

bool DirectXTexture::Upload()
{
    if ( !m_damaged ) return false;

    CrbReleaseAssert ( m_sdlSurface != NULL );
	CrbReleaseAssert ( m_texture != NULL );

	RECT rect = {0, 0, m_sdlSurface->w, m_sdlSurface->h};

	LPDIRECT3DSURFACE9 surf;
	HRESULT hr = m_texture->GetSurfaceLevel (0, &surf);

	if ( FAILED(hr) )
		return false;

	bool isLocked = false;
	if ( !m_sdlSurface->pixels )
	{
		isLocked = true;
		SDL_LockSurface ( m_sdlSurface );
	}

	CrbReleaseAssert ( m_sdlSurface->pixels );

	hr = D3DXLoadSurfaceFromMemory( surf,
		NULL, NULL, m_sdlSurface->pixels, D3DFMT_A8B8G8R8,
		m_sdlSurface->w * 4,
		NULL, &rect, D3DX_FILTER_NONE, graphics->m_colorKey );

	if ( isLocked )
		SDL_UnlockSurface ( m_sdlSurface );

	CrbDebugAssert ( !FAILED(hr) );

    m_damaged = false;

    return true;
}

#endif
