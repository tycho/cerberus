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

#ifndef __included_scene_h
#define __included_scene_h

#include "Entity/entity.h"

class Interface;

class Scene
{
protected:
    Scene *m_overlay;
    Data::LList<Entity *> m_entities;

    Interface *m_interface;

    bool m_showing;
public:
    Scene();
    Scene(Scene *_overlay);
    Scene(Interface *_interface);
    Scene(Scene *_overlay, Interface *_interface);
    virtual ~Scene();

    virtual void AddEntity(Entity *_entity);
    bool IsShowing();
    Interface *GetInterface();
    Scene *GetOverlay();
    virtual void RemoveEntity(Entity *_entity);
    virtual void Render(float _delta);
    void SetInterface(Interface *_interface);
    void SetOverlay(Scene *_overlay);
    void SetShowing(bool _showing);
    virtual void Update(float _delta);
};

#include "Interface/interface.h"

#endif
