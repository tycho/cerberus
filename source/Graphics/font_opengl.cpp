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

#ifdef ENABLE_FONTS

#ifdef ENABLE_OPENGL

#include "Graphics/graphics.h"
#include "Graphics/font_opengl.h"

#ifdef TARGET_COMPILER_VC
#  pragma comment (lib, "ftgl_static.lib")
#  pragma comment (lib, "freetype.lib")
#endif


OpenGLFont::OpenGLFont(const char *_fontFile)
 : m_italic(false)
{
	m_font = new FTGLTextureFont(_fontFile);
	m_font->UseDisplayList(false);
}
OpenGLFont::OpenGLFont(const unsigned char *_data, size_t _size)
 : m_italic(false)
{
	m_font = new FTGLTextureFont(_data, _size);
	m_font->UseDisplayList(false);
}

OpenGLFont::~OpenGLFont()
{
	delete m_font;
}

void OpenGLFont::SetFontSize(Uint16 _size)
{
	m_font->FaceSize(_size, 72);
}

void OpenGLFont::SetBold(bool _bold)
{
	m_bold = _bold;
}

void OpenGLFont::SetItalic(bool _italic)
{
	m_italic = _italic;
}

void OpenGLFont::Draw(Uint16 _x, Uint16 _y, const char *_text, Uint32 _color)
{
	// TODO: Bold text is unimplemented.

	glPushMatrix();
	glTranslatef(_x, _y + m_font->LineHeight(), 0.0f);
	glScalef(1.0f, -1.0f, 1.0f);
	if ( m_italic )
	{
		GLfloat matrix[] =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.2f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		glMultMatrixf(matrix);
	}
	glColor4ub(GET_R(_color), GET_G(_color), GET_B(_color), GET_A(_color));
	m_font->Render(_text);
	ASSERT_OPENGL_ERRORS;
	glPopMatrix();
}

#endif

#endif
