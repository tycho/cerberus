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

#include "Game/game.h"

#include "Scripting/scripting.h"

Game::Game()
 :  m_playing(true),
    m_scene(new Scene())
{
    m_entity.SetTextureBitmap("darwinian.png");
    int w = m_entity.GetTexture()->GetWidth();
    int h = m_entity.GetTexture()->GetHeight();
    Vertex verts[] = {
        { 0, 0, 0, 1, 0, 0, 1, 0, 0, {0, 0, 0} },
        { w, 0, 0, 0, 1, 0, 1, w, 0, {0, 0, 0} },
        { w, h, 0, 0, 0, 1, 1, w, h, {0, 0, 0} },
        { 0, h, 0, 1, 1, 1, 1, 0, h, {0, 0, 0} }
    };
    m_entity.SetVertices(verts, 4);
    m_scene->AddEntity(&m_entity);
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

void Game::HandleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN) {

    } else if (event.type == SDL_KEYUP) {

    }
}

void Game::Render()
{
    m_scene->Render();
}

void Game::Update()
{
    m_scene->Update();
}

Game *g_game;
