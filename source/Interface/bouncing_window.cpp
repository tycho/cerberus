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
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/bouncing_window.h"
#include "Sound/soundsystem.h"

BouncingWindow::BouncingWindow()
 : Window()
{
    SetVelocity ( 0, 0 );
}

BouncingWindow::BouncingWindow ( Uint16 x, Uint16 y, Uint16 w, Uint16 h, Sint16 xvel, Sint16 yvel )
 : Window ( x, y, w, h )
{
    SetVelocity ( xvel, yvel );
}

BouncingWindow::~BouncingWindow()
{
}

void BouncingWindow::SetVelocity ( Sint16 xvel, Sint16 yvel )
{
    m_xvelocity = xvel;
    m_yvelocity = yvel;
}

void BouncingWindow::Update()
{
    Window::Update();
    if ( m_xvelocity )
    {
        // Advance the X position.
        m_position.x += (Sint16)( m_xvelocity * g_game->GetGameSpeed() );
        if ( m_position.x < 0 )
        {
            // Bounce off the left side.
            m_position.x = 0;
            m_xvelocity *= -1;
            //PlayBounceNoise();
        }
        if ( m_position.x + m_position.w > (Sint32)g_graphics->GetScreenWidth() )
        {
            // Bounce off the right side.
            m_position.x = g_graphics->GetScreenWidth() - m_position.w;
            m_xvelocity *= -1;
            //PlayBounceNoise();
        }
    }
    if ( m_yvelocity )
    {
        // Advance the Y position.
        m_position.y += (Sint16)( m_yvelocity * g_game->GetGameSpeed() );
        if ( m_position.y < 0 )
        {
            // Bounce off the top.
            m_position.y = 0;
            m_yvelocity *= -1;
            //PlayBounceNoise();
        }
        if ( m_position.y + m_position.h > (Sint32)g_graphics->GetScreenHeight() )
        {
            // Bounce off the bottom.
            m_position.y = g_graphics->GetScreenHeight() - m_position.h;
            m_yvelocity *= -1;
            //PlayBounceNoise();
        }
    }
}
