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

#include "Graphics/graphics.h"
#include "Graphics/scene.h"

Scene::Scene()
 : m_overlay(NULL)
{
}

Scene::Scene(Scene *_overlay)
 : m_overlay(_overlay),
   m_interface(NULL)
{
}

Scene::Scene(Interface *_interface)
 : m_overlay(NULL),
   m_interface(_interface)
{
}

Scene::Scene(Scene *_overlay, Interface *_interface)
 : m_overlay(_overlay),
   m_interface(_interface)
{
}

Scene::~Scene()
{
    m_entities.empty();

    if (m_overlay != NULL) {
        delete m_overlay;
        m_overlay = NULL;
    }

    if (m_interface != NULL) {
        delete m_interface;
        m_interface = NULL;
    }
}

void Scene::AddEntity(Entity *_entity)
{
    if (_entity != NULL) {
        m_entities.insert(_entity);
    }
}

Interface *Scene::GetInterface()
{
    return m_interface;
}

Scene *Scene::GetOverlay()
{
    return m_overlay;
}

void Scene::RemoveEntity(Entity *_entity)
{
    if (_entity != NULL) {
        if (size_t index = m_entities.find(_entity) > (size_t)-1) {
            m_entities.remove(index);
        }
    }
}

void Scene::Render()
{
    size_t i = 0;
    size_t size = m_entities.used();
    for (; i < size; i++) {
        m_entities[i]->Render();
    }
    if (m_overlay != NULL) {
        m_overlay->Render();
    }
}

void Scene::SetInterface(Interface *_interface)
{
    m_interface = _interface;
}

void Scene::SetOverlay(Scene *_overlay)
{
    m_overlay = _overlay;
}

void Scene::Update()
{
    size_t i = 0;
    size_t size = m_entities.used();
    for (; i < size; i++) {
        m_entities[i]->Update();
    }
    if (m_overlay != NULL) {
        m_overlay->Update();
    }
}
