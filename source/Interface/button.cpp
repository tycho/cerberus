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

#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/button.h"

Button::Button ( InputCallback _callback, Widget *_callbackParam, const char *_caption, SDL_Rect &_pos )
 : InputWidget ( _callback, _callbackParam, _pos.x, _pos.y, _pos.w, _pos.h )
{
    m_widgetClass = WIDGET_BUTTON;
    m_caption = cc_newstr(_caption);

    m_inactiveColor = Color32(20,0,0);
    m_hoverColor = Color32(128,0,0);
    m_color = m_inactiveColor;
}

Button::~Button()
{
    delete [] m_caption;
    m_caption = NULL;
}

void Button::Render()
{
    // Draw the background and border
    g_graphics->FillRect(SCREEN_SURFACE_ID, &m_position, m_color);
    g_graphics->DrawRect(&m_position, Color32(255,0,0));

    // Figure out where the text should be
    SDL_Rect attr;
    g_graphics->TextRect(g_graphics->DefaultFont(), m_caption, attr);
    SDL_Rect txtpos;
    txtpos.x = m_position.x + (m_position.w / 2 - (attr.w / 2));
    txtpos.y = m_position.y + (m_position.h / 2 - (attr.h / 2));

    // Render the caption
    g_graphics->DrawText(g_graphics->DefaultFont(), txtpos.x, txtpos.y, Color32(255,0,0), m_caption);
}

void Button::Render ( Sint16 _xOffset, Sint16 _yOffset )
{
    SDL_Rect pos = m_position;
    pos.x += _xOffset;
    pos.y += _yOffset;

    // Draw the background and border
    g_graphics->FillRect(SCREEN_SURFACE_ID, &pos, m_color);
    g_graphics->DrawRect(&pos, Color32(255,0,0));

    // Figure out where the text should be
    SDL_Rect attr;
    g_graphics->TextRect(g_graphics->DefaultFont(), m_caption, attr);
    SDL_Rect txtpos;
    txtpos.x = pos.x + (pos.w / 2 - (attr.w / 2));
    txtpos.y = pos.y + (pos.h / 2 - (attr.h / 2));

    // Render the caption
    g_graphics->DrawText(g_graphics->DefaultFont(), txtpos.x, txtpos.y, Color32(255,0,0), m_caption);
}

Widget *Button::MouseUpdate()
{
    if ( IsInsideWidget(g_interface->MouseX(), g_interface->MouseY()) ) {
        m_color = m_hoverColor;
    } else {
        m_color = m_inactiveColor;
    }
    return InputWidget::MouseUpdate();
}

void Button::Update()
{
    Widget::Update();
}
