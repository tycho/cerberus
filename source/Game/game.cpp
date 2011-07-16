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
#include "Game/game.h"
#include "Input/input.h"
#include "Scripting/scripting.h"

Game::Game()
 :  m_playing(true),
    m_drawEntityBorders(false),
    m_scene(new Scene()),
    m_entity(NULL)
{
    m_entity = new Entity(0, 0, 31, 32, Color32(255, 255, 255, 255), "darwinian.png");
    m_entity->SetBorderEnabled(true);
    m_entity->SetInputComponent(new InputComponent(m_entity));
    m_entity->SetPhysicsComponent(new PhysicsComponent(m_entity));
    m_entity->SetRenderComponent(new RenderComponent(m_entity));
    m_scene->AddEntity(m_entity);

    Entity *santa = new Entity(7, -14, 16, 16, Color32(255, 255, 255, 255), "santahat.png");
    santa->SetBorderEnabled(true);
    santa->SetRenderComponent(new RenderComponent(santa));
    m_entity->AttachChild(santa);
}

Game::~Game()
{
    delete m_scene;
    m_scene = NULL;
}

bool Game::Playing()
{
    return m_playing;
}

bool Game::EntityBordersEnabled()
{
    return m_drawEntityBorders;
}

void Game::SetEntityBorders(bool _borders)
{
    m_drawEntityBorders = _borders;
}

void Game::Render(float _delta)
{
    m_scene->Render(_delta);
}

void Game::Update(float _delta)
{
    if (m_playing) {
        SDL_Event *event = g_input->GetEvent(0);
        for (size_t i = 0; event != NULL; event = g_input->GetEvent(++i)) {
            switch (event->type) {
            case SDL_KEYUP:
                if (event->key.keysym.sym == SDLK_b) {
                    if (m_drawEntityBorders) {
                        m_drawEntityBorders = false;
                    } else {
                        m_drawEntityBorders = true;
                    }
                }
                break;
            }
        }

        m_scene->Update(_delta);
    }
}

Game *g_game;
