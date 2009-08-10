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

#include "App/app.h"
#include "App/string_utils.h"
#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/text.h"


TextUI::TextUI ( const char *_text, Color32 _color, Sint16 x, Sint16 y )
 : Widget(),
   m_color(_color)
{
	m_position.x = x;
	m_position.y = y;
	m_widgetClass = WIDGET_TEXT;
    m_text = newStr ( _text );
}

TextUI::~TextUI ()
{
    delete [] m_text;
    m_text = NULL;
    g_graphics->DeleteSurface ( m_cachedSurfaceID );
}

void TextUI::Update ()
{
	Widget::Update();
}

void TextUI::Render ()
{
    SDL_Rect absolutePosition = GetAbsolutePosition();

	g_graphics->DrawText(g_graphics->DefaultFont(),
		absolutePosition.x, absolutePosition.y, m_color, m_text);

	Widget::Render();
}

int TextUI::SendEnterKey ()
{
    return 0;
}

Widget *TextUI::MouseUpdate ()
{
    return NULL;
}

const char *TextUI::GetText ()
{
    CrbReleaseAssert ( m_text != NULL );
    return m_text;
}

void TextUI::SetPosition ( Sint16 x, Sint16 y, bool _centered )
{
    if ( !_centered )
    {
        Widget::SetPosition(x, y);
        return;
    }

    SDL_Rect attr;
    g_graphics->TextRect(g_graphics->DefaultFont(), m_text, attr);

    m_position.x = x - (attr.w / 2);
    m_position.y = y;
}

void TextUI::SetText ( const char *_text )
{
    if ( !m_text || strcmp ( _text, m_text ) != 0 )
    {
        delete [] m_text;
        m_text = newStr ( _text );
		m_rebuildDisplayList = true;
    }
}

void TextUI::SetColor ( Color32 _color )
{
	m_color = _color;
}

int TextUI::MakeText ( const char *_text )
{
    unsigned int length = (int)strlen(_text);

    return length;
}
