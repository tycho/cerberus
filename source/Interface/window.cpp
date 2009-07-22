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
#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "Interface/window.h"

Window::Window()
 : Widget(),
   m_dragging(false)
{
   m_widgetClass = WIDGET_WINDOW;
}

Window::Window ( Sint16 x, Sint16 y, Uint16 w, Uint16 h )
 : Widget(x,y,w,h),
   m_dragging(false)
{
   m_widgetClass = WIDGET_WINDOW;
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

int Window::MouseDown ( bool _mouseDown, Sint32 x, Sint32 y )
{
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
            if ( !(widget->MouseDown ( _mouseDown, x, y )) )
                break;
            return -1;
            break;
        }
    }
    if ( !m_dragging && _mouseDown ) {
        g_interface->SetDragWindow ( this );
        m_dragging = true;
        m_mouseXOffset = x - m_position.x;
        m_mouseYOffset = y - m_position.y;
    } else if ( m_dragging && _mouseDown ) {
        SetPosition ( x - m_mouseXOffset, y - m_mouseYOffset );
    } else if ( m_dragging && !_mouseDown ) {
        g_interface->SetDragWindow ( NULL );
        m_dragging = false;
    }
    return 1;
}

void Window::Update()
{
    Widget::Update();
	if (m_cachedSurfaceID == INVALID_SURFACE_ID) {
		m_cachedSurfaceID = g_graphics->CreateSurface(m_position.w, m_position.h);
		g_graphics->FillRect(m_cachedSurfaceID, NULL, MAKERGBA(128,200,128,255));
	}
}
