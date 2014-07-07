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
#include "Game/game.h"
#include "Input/input.h"
#include "Scripting/scripting.h"

Input::Input()
 : m_mouseX(0),
   m_mouseY(0),
   m_lastButtonState(0),
   m_buttonState(0)
{
}

Input::~Input()
{
    m_observers.empty();
}

void Input::Update ()
{
    m_lastButtonState = m_buttonState;
    m_buttonState = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    m_events.empty();

    SDL_Event event;
    while ( SDL_PollEvent ( &event ) )
    {
        for (size_t i = 0; i < m_observers.size(); i++) {
            if (event.type == m_observers[i].eventType) {
                Vector *pos;
                float w, h;
                if (m_observers[i].observer->GetProperty("position", pos)) {
                    if (m_observers[i].observer->GetProperty("width", w) &&
                            m_observers[i].observer->GetProperty("height", h)) {
                        // If mouse events, check if the mouse is within the entity's bounding box
                        if (event.type == SDL_MOUSEMOTION ||
                                event.type == SDL_MOUSEBUTTONDOWN ||
                                event.type == SDL_MOUSEBUTTONUP) {
                            float x = -1, y = -1;
                            if (event.type == SDL_MOUSEMOTION) {
                                x = (float)event.motion.x;
                                y = (float)event.motion.y;
                            } else {
                                x = (float)event.button.x;
                                y = (float)event.button.y;
                            }
                            if (!(x <= (pos->x + w) &&
                                    x >= (pos->x) &&
                                    y >= (pos->y) &&
                                    y <= (pos->y + h))) {
                                continue;
                            }
                        }
                    }
                }
                switch(event.type) {
                case SDL_KEYDOWN:
                    g_scripting->ExecuteHook(m_observers[i].observer, "onKeyDown", event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    g_scripting->ExecuteHook(m_observers[i].observer, "onKeyUp", event.key.keysym.sym);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    g_scripting->ExecuteHook(m_observers[i].observer, "onMouseDown", event.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    g_scripting->ExecuteHook(m_observers[i].observer, "onMouseUp", event.button.button);
                    break;
                case SDL_MOUSEMOTION:
                    g_scripting->ExecuteHook(m_observers[i].observer, "onMouseOver", event.button.button);
                    break;
                }
            }
        }
        m_events.insert(event);
    }

    int arraySz = 0;
    m_keyState = SDL_GetKeyState(&arraySz);

    // Handle Command+Q on Mac OS X
#ifdef TARGET_OS_MACOSX
    static bool cmdQ = false;
    if ( !cmdQ && ( m_keyState[SDLK_LMETA] || m_keyState[SDLK_RMETA] ) && m_keyState[SDLK_q] )
    {
        cmdQ = true;
        if ( g_game->Playing() )
        {
#if 0
            QuitWindow *quitWindow;
            if ( (quitWindow = (QuitWindow *)g_app->GetInterface()->GetWidgetOfType ( WIDGET_QUIT_WINDOW )) != NULL )
            {
                g_app->GetInterface()->RemoveWidget ( quitWindow );
            } else {
                quitWindow = new QuitWindow();
                g_app->GetInterface()->AddWidget ( quitWindow );
                quitWindow = NULL;
            }
#endif
        } else {
            g_app->Quit();
        }
    } else if ( cmdQ && ( !m_keyState[SDLK_LMETA] && !m_keyState[SDLK_RMETA] ) || !m_keyState[SDLK_q] ) {
        cmdQ = false;
    }
#endif
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

SDL_Event *Input::GetEvent(size_t _index)
{
    if (_index < m_events.size()) {
        return &m_events[_index];
    } else {
        return NULL;
    }
}

void Input::RegisterEventObserver(Uint8 _type, Entity *_observer)
{
    EventObserver e;
    e.eventType = _type;
    e.observer = _observer;

    m_observers.insert(e);
}
Input *g_input;
