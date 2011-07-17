/*
 * Copyright (c) 2011 Eddie Ringle <eddie@eringle.net>
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

#include "Entity/Behaviors/behavior_input.h"
#include "Entity/entity.h"
#include "Scripting/scripting.h"

InputBehavior::InputBehavior(Entity *_entity)
 : Behavior(Behavior::Names[INPUT], _entity)
{
}

void InputBehavior::ReceiveEvent(SDL_Event &_event)
{
    switch (_event.type) {
    case SDL_KEYDOWN:
        g_scripting->SendInput(GetEntity(), "onKeyDown", _event.key.keysym.sym);
        break;
    case SDL_KEYUP:
        g_scripting->SendInput(GetEntity(), "onKeyUp", _event.key.keysym.sym);
        break;
    case SDL_MOUSEBUTTONDOWN:
        g_scripting->SendInput(GetEntity(), "onMouseDown", _event.button.button);
        break;
    case SDL_MOUSEBUTTONUP:
        g_scripting->SendInput(GetEntity(), "onMouseUp", _event.button.button);
        break;
    case SDL_MOUSEMOTION:
        g_scripting->SendInput(GetEntity(), "onMouseOver", 0);
        break;
    }
}

void InputBehavior::Update(float _delta)
{
    // just a lonely stub...
}
