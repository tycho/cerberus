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
#include "App/collide.h"
#include "App/string_utils.h"
#include "Graphics/graphics.h"
#include "Interface/widget.h"

Widget::Widget()
 : m_widgetClass(WIDGET_UNKNOWN),
   m_cachedSurfaceID(-1),
   m_rebuildDisplayList(true),
   m_displayList(0),
   m_enterKeyDefault(NULL),
   m_parentWidget(NULL),
   m_expired(false)
{
    memset ( &m_position, 0, sizeof(m_position) );
}

Widget::Widget ( Sint16 x, Sint16 y, Uint16 w, Uint16 h )
 : m_widgetClass(WIDGET_UNKNOWN),
   m_cachedSurfaceID(-1),
   m_enterKeyDefault(NULL),
   m_expired(false)
{
    SetSize ( w, h );
    SetPosition ( x, y );
}

Widget::~Widget()
{
    if ( (int)m_cachedSurfaceID != -1 )
    {
        g_graphics->DeleteSurface ( m_cachedSurfaceID );
    }
    while ( m_widgets.get(0) )
    {
        delete m_widgets.get(0);
        m_widgets.remove(0);
    }
}

void Widget::Expire()
{
    m_expired = true;
}

bool Widget::Expired ()
{
    return m_expired;
}

void Widget::AddWidget ( Widget *_widget )
{
    _widget->m_parentWidget = this;
    m_widgets.insert ( _widget );
}

bool Widget::HasWidget ( Widget *_widget )
{
    if ( this == _widget ) return true;
    for ( size_t i = 0; i < m_widgets.size(); i++ )
    {
        Widget *widget = m_widgets[i];
        if ( widget == _widget) return true;
        if ( widget->HasWidget(_widget)) return true;
    }
    return false;
}

SDL_Rect Widget::GetAbsolutePosition ()
{
    SDL_Rect pos;
    Widget *w = this;
    pos.x = 0;
    pos.y = 0;
    pos.w = m_position.w;
    pos.h = m_position.h;
    do {
        pos.x += w->m_position.x;
        pos.y += w->m_position.y;
        w = w->m_parentWidget;
    } while (w);
    return pos;
}

Data::LList<Widget *> *Widget::GetWidgetList()
{
    return &m_widgets;
}

bool Widget::IsInsideWidget ( int _mouseX, int _mouseY )
{
    SDL_Rect mousePos;
    mousePos.x = _mouseX;
    mousePos.y = _mouseY;
    mousePos.w = 1; mousePos.h = 1;
    SDL_Rect absolutePosition = GetAbsolutePosition();
    return ( SDL_CollideBoundingBox ( mousePos, absolutePosition ) != 0 );
}

void Widget::Initialise()
{
	g_graphics->DeleteSurface ( m_cachedSurfaceID );
	m_cachedSurfaceID = -1;
    for ( size_t i = 0; i < m_widgets.size(); i++ )
    {
		Widget *widget = m_widgets[i];
		widget->Initialise();
	}
}

void Widget::Render ()
{
    SDL_Rect absolutePosition = GetAbsolutePosition();

    if ( m_cachedSurfaceID != INVALID_SURFACE_ID )
        g_graphics->Blit ( m_cachedSurfaceID, NULL, g_graphics->GetScreen(), &absolutePosition ); // FLAG
    for ( size_t i = 0; i < m_widgets.size(); i++ )
    {
        Widget *widget = m_widgets[i];
        CrbReleaseAssert ( widget );
        widget->Update();
        if ( widget->m_expired )
        {
            m_widgets.remove ( i-- );
            delete widget;
            continue;
        }
        widget->Render();
    }
}

bool Widget::HasEnterKeyDefault ()
{
    return m_enterKeyDefault != NULL;
}

void Widget::SetPosition ( Sint16 x, Sint16 y )
{
    if ( x < 0 ) x = 0; if ( y < 0 ) y = 0;
    m_position.x = x; m_position.y = y;

    if ( m_position.x + m_position.w > (Sint32)g_graphics->GetScreenWidth() )
        m_position.x = g_graphics->GetScreenWidth() - m_position.w;

    if ( m_position.y + m_position.h > (Sint32)g_graphics->GetScreenHeight() )
        m_position.y = g_graphics->GetScreenHeight() - m_position.h;
}

void Widget::SetSize ( Uint16 w, Uint16 h )
{
    m_position.w = w; m_position.h  = h;
}

WidgetClass Widget::ClassID ()
{
    return m_widgetClass;
}

void Widget::Update()
{
    for ( size_t i = 0; i < m_widgets.size(); i++ )
    {
        Widget *widget = m_widgets[i];
        if ( widget->m_expired )
        {
            m_widgets.remove ( i-- );
            delete widget;
            continue;
        }
        m_widgets[i]->Update();
    }
}
