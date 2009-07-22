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

#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/button.h"
#include "Interface/error_window.h"
#include "Interface/text.h"

void ErrorWindow_OnOKClick ( Window *_window )
{
    dynamic_cast<ErrorWindow *>(_window)->OnOKClick();
}

ErrorWindow::ErrorWindow ( const char *_text, bool _critical )
: Window ( g_graphics->GetCenterX() - 136, g_graphics->GetCenterY() - 44, 256, 72 ),
  m_critical(_critical)
{
    SetWidgetClass ( "ErrorWindow" );

    m_caption = new TextUI ( "[null]", false, 35, 16, 600, 9 );
    AddWidget ( m_caption );

    Button *button = new Button ( (InputCallback)ErrorWindow_OnOKClick, this, BUTTON_TYPE_OK, (m_position.w / 2) - (58 / 2), 40 );
    m_enterKeyDefault = button;
    AddWidget ( button ); button = NULL;

    SetCaption ( _text );
}

ErrorWindow::~ErrorWindow()
{
}

void ErrorWindow::OnOKClick ()
{
    if ( m_critical )
        g_game->Quit();
    else
        m_expired = true;
}

void ErrorWindow::SetCaption ( const char *_caption )
{
    CrbReleaseAssert ( _caption != NULL );
    if ( strlen ( _caption ) != strlen ( m_caption->GetText() ) )
    {
        int newWidth = (int)((double)strlen ( _caption ) * 5.5 + 72.0);
        m_position.w = newWidth;
        m_position.x = g_graphics->GetCenterX() - (newWidth / 2);
        if ( (int)m_cachedSurfaceID != -1 )
        {
            g_graphics->DeleteSurface ( m_cachedSurfaceID ); m_cachedSurfaceID = -1;
        }
        m_caption->SetPosition ( (Sint16)((m_position.w / 2) - ( (strlen ( _caption ) * 5.8 ) / 2 )), 20 );
        m_caption->SetText ( _caption );
        m_enterKeyDefault->SetPosition ( (m_position.w / 2) - (58 / 2), 40 );
    }
}
