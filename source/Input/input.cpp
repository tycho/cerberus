/*
 * Copyright (c) 2011 Steven Noonan <steven@uplinklabs.net>
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
#include "Input/input.h"

Input::Input()
 : m_mouseX(0),
   m_mouseY(0),
   m_lastButtonState(0),
   m_buttonState(0)
{
}

Input::~Input()
{
}

void Input::Update ()
{
    m_buttonState = SDL_GetMouseState ( &m_mouseX, &m_mouseY );
    m_lastButtonState = m_buttonState;
}

int Input::MouseX () const
{
    return m_mouseX;
}

int Input::MouseY () const
{
    return m_mouseY;
}

bool Input::MouseLeft () const
{
    return (m_buttonState & SDL_BUTTON(1)) != 0;
}

bool Input::MouseRight () const
{
    return (m_buttonState & SDL_BUTTON(3)) != 0;
}

bool Input::MouseLeftEdge () const
{
    return (m_buttonState & SDL_BUTTON(1)) !=
            (m_lastButtonState & SDL_BUTTON(1));
}

bool Input::MouseRightEdge () const
{
    return (m_buttonState & SDL_BUTTON(3)) !=
           (m_lastButtonState & SDL_BUTTON(3));
}

Input *g_input;
