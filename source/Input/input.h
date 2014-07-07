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

#ifndef __input_h_included
#define __input_h_included

#include "universal_include.h"

#include "Entity/entity.h"

enum MoreEventTypes {
    MOUSE_OVER = 25,
    MOUSE_LEAVE
};

typedef struct {
    Uint8 eventType;
    Entity *observer;
} EventObserver;

class Input
{
protected:
	int   m_mouseX;
	int   m_mouseY;
	Uint8 m_lastButtonState;
	Uint8 m_buttonState;
	Uint8 *m_keyState;

    Data::LList<EventObserver> m_observers;
    Data::LList<SDL_Event> m_events;

public:
    Input();
    virtual ~Input();

	virtual int MouseX                     () const;
	virtual int MouseY                     () const;
	virtual bool MouseLeft                 () const;
	virtual bool MouseRight                () const;
	virtual bool MouseLeftEdge             () const;
	virtual bool MouseRightEdge            () const;

    virtual SDL_Event *GetEvent(size_t _index);

    virtual void RegisterEventObserver(Uint8 _type, Entity *_observer);

    virtual void Update ();
};

extern Input *g_input;
#endif
