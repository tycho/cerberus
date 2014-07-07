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

#include "universal_include.h"

#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/button.h"
#include "Input/input.h"

enum {
	BUTTON_STATE_INACTIVE = 0,
	BUTTON_STATE_ACTIVE,
	BUTTON_STATE_HOVER,
	BUTTON_STATE_PRESSED
};

Uint32 Button::s_images[4] = { INVALID_SURFACE_ID, INVALID_SURFACE_ID, INVALID_SURFACE_ID, INVALID_SURFACE_ID };

Button::Button ( InputCallback _callback, Widget *_callbackParam, const char *_caption, SDL_Rect &_pos )
 : InputWidget ( _callback, _callbackParam, _pos.x, _pos.y, _pos.w, _pos.h ),
   m_state(BUTTON_STATE_ACTIVE)
{
	if (Button::s_images[0] == INVALID_SURFACE_ID) {
		Button::s_images[BUTTON_STATE_INACTIVE] = g_graphics->LoadImage("themes/default/button/inactive.png");
		Button::s_images[BUTTON_STATE_ACTIVE] = g_graphics->LoadImage("themes/default/button/active.png");
		Button::s_images[BUTTON_STATE_HOVER] = g_graphics->LoadImage("themes/default/button/hover.png");
		Button::s_images[BUTTON_STATE_PRESSED] = g_graphics->LoadImage("themes/default/button/pressed.png");
	}

    m_widgetClass = WIDGET_BUTTON;
    m_caption = new TextUI(_caption, Color32(255,0,0), 0, 0);
    AddWidget(m_caption);

    // Forces a position recalculation for m_caption.
    m_damaged = true;
}

Button::~Button()
{
}

void Button::Render()
{
    SDL_Rect absolutePosition = GetAbsolutePosition();

    // Draw the background and border
	g_graphics->Blit(s_images[m_state], NULL, SCREEN_SURFACE_ID, &absolutePosition, Color32(255,0,0,128));
    g_graphics->DrawRect(&absolutePosition, Color32(255,0,0));

    Widget::Render();
}

Widget *Button::MouseUpdate()
{
    if ( IsInsideWidget(g_input->MouseX(), g_input->MouseY()) ) {
		if (g_input->MouseLeft()) {
			m_state = BUTTON_STATE_PRESSED;
		} else {
			m_state = BUTTON_STATE_HOVER;
		}
    } else {
        m_state = BUTTON_STATE_ACTIVE;
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
