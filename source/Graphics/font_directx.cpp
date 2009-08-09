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
#ifdef ENABLE_FONTS

#include "Graphics/graphics.h"
#include "Graphics/font_directx.h"

DirectXFont::DirectXFont(const char *_fontFace, int _height)
{
	D3DXFONT_DESC lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));

	lf.Height = (int)(_height * 1.25f);
	lf.MipLevels = D3DX_DEFAULT;
	lf.Width = _height * 0.5f;
	lf.Weight = FW_NORMAL;
	lf.Italic = 0;
	lf.CharSet = DEFAULT_CHARSET;
	lf.Quality = PROOF_QUALITY;
    lf.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
	strncpy(lf.FaceName, _fontFace, 31);

	D3DXCreateFontIndirect(((DirectXGraphics *)g_graphics)->m_device, &lf, &m_font);
}

DirectXFont::~DirectXFont()
{
	m_font->Release();
	m_font = NULL;
}

void DirectXFont::Draw(Uint16 _x, Uint16 _y, const char *_text, Color32 _color)
{
	RECT rect;
	rect.left = _x;
	rect.top = _y;
	rect.right = 0;
	rect.bottom = 0;

	D3DCOLOR color = _color;

	CoreAssert ( m_font );

	m_font->DrawText(NULL, _text, -1, &rect, DT_CALCRECT, 0);
	m_font->DrawText(NULL, _text, -1, &rect, DT_LEFT | DT_NOCLIP, _color);
}

#endif
#endif
