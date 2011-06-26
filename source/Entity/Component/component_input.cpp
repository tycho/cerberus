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

#include "universal_include.h"

#include "Entity/Component/component_input.h"
#include "Input/input.h"

InputComponent::InputComponent(Entity *_entity)
 : Component(_entity)
{
}

void InputComponent::Update(float _delta)
{
    // Handle input
    SDL_Event *event = NULL;
    PhysicsComponent *entityPhysics = m_entity->GetPhysicsComponent();
    if (entityPhysics) {
        event = g_input->GetEvent(0);
        for (size_t i = 0; event != NULL;) {
            switch (event->type) {
            case SDL_KEYDOWN:
                if (event->key.keysym.sym == SDLK_UP) {
                    entityPhysics->m_yAcceleration += -20.0f;
                } else if (event->key.keysym.sym == SDLK_DOWN) {
                    entityPhysics->m_yAcceleration += 20.0f;
                } else if (event->key.keysym.sym == SDLK_LEFT) {
                    entityPhysics->m_xAcceleration += -20.0f;
                } else if (event->key.keysym.sym == SDLK_RIGHT) {
                    entityPhysics->m_xAcceleration += 20.0f;
                }
                break;
            case SDL_KEYUP:
                if (event->key.keysym.sym == SDLK_UP) {
                    entityPhysics->m_yAcceleration -= -20.0f;
                } else if (event->key.keysym.sym == SDLK_DOWN) {
                    entityPhysics->m_yAcceleration -= 20.0f;
                } else if (event->key.keysym.sym == SDLK_LEFT) {
                    entityPhysics->m_xAcceleration -= -20.0f;
                } else if (event->key.keysym.sym == SDLK_RIGHT) {
                    entityPhysics->m_xAcceleration -= 20.0f;
                }
                break;
            }
            event = g_input->GetEvent(++i);
        }
    }
}
