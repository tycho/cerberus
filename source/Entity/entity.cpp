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

#include "Entity/entity.h"

#include "Graphics/graphics.h"

Entity::Entity(const char *_name)
 : m_name(newStr(_name))
{
}

Entity::~Entity()
{
    delete m_name;
    m_name = NULL;
}

const char *Entity::GetName()
{
    return m_name;
}

/**
 * Behavior methods
 */

bool Entity::HasBehavior(const char *_name)
{
    return m_behaviors.exists(_name);
}

Behavior *Entity::GetBehavior(const char *_name)
{
    return m_behaviors.find(_name);
}

bool Entity::AddBehavior(const char *_name, Behavior *_behavior)
{
    return (int)m_behaviors.insert(_name, _behavior) > -1;
}

class Behavior;

bool Entity::RemoveBehavior(const char *_name)
{
    if (m_behaviors.exists(_name)) {
        delete m_behaviors.find(_name);
        return m_behaviors.erase(_name);
    } else {
        return false;
    }
}

/**
 * Attribute methods
 */

bool Entity::HasAttribute(const char *_name)
{
    return m_attributes.exists(_name);
}

Attribute *Entity::GetAttribute(const char *_name)
{
    return m_attributes.find(_name);
}

bool Entity::AddAttribute(const char *_name, Attribute *_attribute)
{
    return (int)m_attributes.insert(_name, _attribute) > -1;
}

bool Entity::RemoveAttribute(const char *_name)
{
    if (m_attributes.exists(_name)) {
        delete m_attributes.find(_name);
        return m_attributes.erase(_name);
    } else {
        return false;
    }
}

/**
 * Scene graph methods
 */

Entity *Entity::GetParent()
{
    return m_parent;
}

Entity *Entity::GetChild(int _index)
{
    return m_children.get(_index);
}

void Entity::AttachChild(Entity *_child)
{
    m_children.insert(_child);
}

void Entity::RemoveChild(Entity *_child)
{
    int index = (int)m_children.find(_child);
    if (index > -1) {
        m_children.remove(index);
    }
}

/**
 * Lifecycle methods
 */

void Entity::Update(float _delta)
{
    size_t behaviorCount = m_behaviors.used();
    for (size_t i = 0; i < behaviorCount; i++) {
        if (strcmp(m_behaviors[i]->GetName(), Behavior::Names[RENDER]) == 0) {
            continue;
        } else {
            m_behaviors[i]->Update(_delta);
        }
    }
}

void Entity::Render(float _delta)
{
    Behavior *renderBehavior = m_behaviors.find(Behavior::Names[RENDER]);
    if (renderBehavior != NULL) {
        renderBehavior->Update(_delta);
    }
}
