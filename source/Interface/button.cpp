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
    m_caption = new TextUI(_caption, Color32(255,0,0), 0, 0);
    AddWidget(m_caption);

    // Forces a position recalculation for m_caption.
    m_damaged = true;

    m_inactiveColor = Color32(20,0,0);
    m_hoverColor = Color32(128,0,0);
    m_color = m_inactiveColor;
}

Button::~Button()
{
}

void Button::Render()
{
    SDL_Rect absolutePosition = GetAbsolutePosition();

    // Draw the background and border
    g_graphics->FillRect(SCREEN_SURFACE_ID, &absolutePosition, m_color);
    g_graphics->DrawRect(&absolutePosition, Color32(255,0,0));

    Widget::Render();
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
    if (m_damaged)
    {
        SDL_Rect absolutePosition = GetAbsolutePosition();

        // Figure out where the text should be
        SDL_Rect attr;
        g_graphics->TextRect(g_graphics->DefaultFont(), m_caption->GetText(), attr);
        SDL_Rect txtpos;
        txtpos.y = m_position.h / 2 - (attr.h / 2);

        m_caption->SetPosition(absolutePosition.w / 2, txtpos.y, true);

        m_damaged = false;
    }
    Widget::Update();
}
