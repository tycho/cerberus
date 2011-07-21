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

#include "App/app.h"
#include "App/preferences.h"
#include "Graphics/graphics.h"
#include "Input/input.h"
#include "Interface/interface.h"

Interface::Interface()
 : m_dragWindow(NULL),
   m_activeWidget(NULL),
   m_fpsWidget(NULL),
   m_rendererWidget(NULL)
{
}

Interface::~Interface()
{
    m_fpsWidget = NULL; m_rendererWidget = NULL;
}

Widget *Interface::GetWidget(int _index)
{
    if (m_entities.valid(_index)) {
        return dynamic_cast<Widget *>(m_entities[_index]);
    } else {
        return NULL;
    }
}

void Interface::Update (float _delta)
{
    Widget *widget = NULL;
    for ( size_t i = 0; i < m_entities.size(); i++ )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
        if (widget->Expired())
        {
            RemoveEntity(widget);
            i--;
            continue;
        }
        widget->Update();
    }
    SetWidgetFocus(MouseUpdate());
}

void Interface::SetDragWindow ( Window *_window )
{
    m_dragWindow = _window;
}

void Interface::SetWindowFocus ( Window *_window )
{
	int id = m_entities.find(_window);
	m_entities.remove(id);
	m_entities.insert(_window);
}

void Interface::SetWidgetFocus ( Widget *_widget )
{
    if (m_activeWidget)
        m_activeWidget->MouseUpdate();
    m_activeWidget = _widget;
}

Widget *Interface::InsideWidget ( int _mouseX, int _mouseY )
{
    Widget *widget = NULL;

    for ( int i = m_entities.size() - 1; i >= 0; i-- )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
        if ( widget->IsInsideWidget ( _mouseX, _mouseY ) )
            return widget;
    }
    return NULL;
}

void Interface::AddEntity ( Entity *_entity )
{
    Widget *widget = dynamic_cast<Widget *>(_entity);
    if (widget == NULL) return;
    if (widget->GetInterface() == NULL) {
        widget->SetInterface(this);
    }
    Scene::AddEntity(_entity);
}

Widget *Interface::GetWidgetOfType ( WidgetClass _widgetType )
{
    Widget *widget = NULL;
    for ( int i = m_entities.size() - 1; i >= 0; i-- )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
		if ( widget->ClassID() == _widgetType )
        {
            return widget;
        }
    }
    return NULL;
}

void Interface::RemoveEntity ( Entity *_entity )
{
    Widget *widget = dynamic_cast<Widget *>(_entity);
    if (widget != NULL) {
        if ( widget->HasWidget(m_activeWidget) )
            m_activeWidget = NULL;
        if ( widget->HasWidget(m_dragWindow) )
            m_dragWindow = NULL;
    }

    Scene::RemoveEntity(_entity);
}

int Interface::SendEnterKey ()
{
    Widget *widget = NULL;
    for ( int i = m_entities.size() - 1; i >= 0; i-- )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
        if (widget->HasEnterKeyDefault())
            return widget->SendEnterKey();
    }
    return 0;
}

void Interface::RenderMouse()
{
}

Widget *Interface::MouseUpdate ()
{
    if (m_dragWindow != NULL)
    {
        return m_dragWindow->MouseUpdate ();
    } else {
        Widget *widget = NULL;
        for ( int i = m_entities.size() - 1; i >= 0; i-- )
        {
            widget = GetWidget(i);
            if (widget == NULL) continue;
            if ( !widget->IsInsideWidget(g_input->MouseX(), g_input->MouseY()) )
                continue;
            Widget *acceptedMessage = widget->MouseUpdate ();
            if (acceptedMessage)
                return acceptedMessage;
        }
        return NULL;
    }
}

void Interface::UpdateRendererWidget ()
{
    char speedCaption[128];

    sprintf ( speedCaption, "Renderer: %s", g_graphics->RendererName() );

    if ( !m_rendererWidget )
    {
        m_rendererWidget = new TextUI(
			speedCaption, Color32(255,255,255),
			3, g_graphics->GetScreenHeight () - 29 );
        m_entities.insert ( m_rendererWidget );
    }
    m_rendererWidget->SetText ( speedCaption );
}

void Interface::UpdateFPS ( unsigned int _fps )
{
    char fpsCaption[32];
	Color32 color = 0;

    if ( _fps >= 50 )
        color = Color32(0,255,0); // GREEN
    else if ( _fps < 50 && _fps >= 30 )
        color = Color32(255,255,0); // YELLOW
    else if ( _fps < 30 )
        color = Color32(255,0,0); // RED

    sprintf ( fpsCaption, "FPS: %d", _fps );
    if ( !m_fpsWidget )
    {
        m_fpsWidget = new TextUI(
			fpsCaption, color,
			3, g_graphics->GetScreenHeight () - 40 );
        m_entities.insert ( m_fpsWidget );
    }
	m_fpsWidget->SetColor ( color );
    m_fpsWidget->SetText ( fpsCaption );
}

void Interface::Render(float _delta)
{
    Widget *widget = NULL;
    for ( size_t i = 0; i < m_entities.size(); i++ )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
        widget->Render();
    }
}

void Interface::InitWidgets ()
{
    Widget *widget = NULL;
    for ( size_t i = 0; i < m_entities.size(); i++ )
    {
        widget = GetWidget(i);
        if (widget == NULL) continue;
		widget->Initialise();
    }
}
