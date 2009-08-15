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
#include "Graphics/Animation/expirewidget.h"
#include "Graphics/Animation/fade.h"
#include "Graphics/Animation/rotate.h"
#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/text.h"
#include "Interface/window.h"

#define TITLE_X 4
#define TITLE_Y 6

Window::Window(const char *_title)
 : Widget(),
   m_dragging(false)
{
   m_widgetClass = WIDGET_WINDOW;
   m_title = new TextUI(_title, Color32(255,0,0), TITLE_X, TITLE_Y);
   AddWidget(m_title);
}

Window::Window (const char *_title, Sint16 x, Sint16 y, Uint16 w, Uint16 h )
 : Widget(x,y,w,h),
   m_dragging(false)
{
   m_widgetClass = WIDGET_WINDOW;
   m_title = new TextUI(_title, Color32(255,0,0), TITLE_X, TITLE_Y);
   AddWidget(m_title);
}

Window::~Window()
{
}

int Window::SendEnterKey ()
{
    if ( HasEnterKeyDefault() )
    {
        return m_enterKeyDefault->SendEnterKey ();
    } else {
        return 0;
    }
}

Widget *Window::MouseUpdate ()
{
	int x = g_interface->MouseX(),
	    y = g_interface->MouseY();
	if ( !m_dragging && g_interface->MouseLeft() )
	{
		// The mouse click is within the window, so this window
		// should be moved to the foreground.
		g_interface->SetWindowFocus(this);
	}
    if ( !m_dragging )
    {
        SDL_Rect actualPosition;
        for ( int i = m_widgets.size() - 1; i >= 0; i-- )
        {
            Widget *widget = m_widgets[i];

            // Window widget positions are relative to the window's position.
            actualPosition.x = widget->m_position.x + m_position.x;
            actualPosition.y = widget->m_position.y + m_position.y;
            actualPosition.w = widget->m_position.w;
            actualPosition.h = widget->m_position.h;

            if ( x < actualPosition.x || y < actualPosition.y )
                continue;
            if ( x > ( actualPosition.x + actualPosition.w ) ||
                y > ( actualPosition.y + actualPosition.h ) )
                continue;

            Widget *active = widget->MouseUpdate();
            if ( !active )
                break; // The sub-widget doesn't have a defined behaviour for MouseUpdate.

			// The sub-widget accepted the MouseUpdate.
            return active;
        }
    }
    if ( !m_dragging &&
          g_interface->MouseLeft() &&
          g_interface->MouseLeftEdge() )
    {
		// Must click on the titlebar to drag.
		if (y - m_position.y <= 20) {
			g_interface->SetDragWindow ( this );
			m_dragging = true;
			m_mouseXOffset = x - m_position.x;
			m_mouseYOffset = y - m_position.y;
		}
    } else if ( m_dragging ) {
		if ( g_interface->MouseLeft() ) {
            SetPosition ( x - m_mouseXOffset, y - m_mouseYOffset );
		} else {
            g_interface->SetDragWindow ( NULL );
            m_dragging = false;
        }
    }
    return this;
}

void Window::Close()
{
	m_anims.insert(new Rotate(&m_position,0.0f, 45.0f, 0.9f));
	m_anims.insert(new Fade(1.0f, 0.0f, 0.375f));
	m_anims.insert(new ExpireWidget(this, 2.0f));
}

void Window::Render()
{
	BeginAnims();

	// Frame
	Color32 fillColor(50,0,0,191),
			borderColor(255,0,0);

	g_graphics->FillRect(SCREEN_SURFACE_ID, &m_position, fillColor);

	g_graphics->DrawRect(&m_position, borderColor);

	// Titlebar bottom
	g_graphics->DrawLine(SCREEN_SURFACE_ID, borderColor,
		m_position.x, m_position.y + 21,
		m_position.x + m_position.w, m_position.y + 21);

	// Render the window's contents
	Widget::Render();

	Widget::EndAnims();
}

void Window::Update()
{
	Widget::Update();
}
