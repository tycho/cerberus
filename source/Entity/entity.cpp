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

#include "Entity/behaviors.h"
#include "Entity/entity.h"

#include "Graphics/graphics.h"
#include "Graphics/vector.h"

Entity::Entity(unsigned int _id, const char *_name)
 : m_id(_id),
   m_name(newStr(_name))
{
}

Entity::~Entity()
{
    delete[] m_name;
    m_name = NULL;

    size_t propertyCount = m_properties.size();
    for (size_t i = 0; i < propertyCount; i++) {
        if (m_properties.valid(i)) {
            property_t *prop = m_properties[i];
            if (prop == NULL) {
                continue;
            }
            switch (prop->type) {
            case TYPE_STRING:
                delete[] (const char *)prop->value;
                break;
            case TYPE_NUMBER:
                delete (float *)prop->value;
                break;
            case TYPE_BOOLEAN:
                delete (bool *)prop->value;
                break;
            case TYPE_RECT:
                delete (Rect *)prop->value;
                break;
            case TYPE_VECTOR:
                delete (Vector *)prop->value;
                break;
            case TYPE_NONE:
                break;
            }
            delete prop;
        }
    }
}

unsigned int Entity::GetID() const
{
    return m_id;
}

const char *Entity::GetName() const
{
    return m_name;
}

/**
 * Behavior methods
 */

bool Entity::AddBehavior(const char *_name, behaviorFunc _func)
{
    if (unlikely(_name == NULL)) {
        return false;
    } else {
        behaviorFunc f = (_func == NULL) ? get_behavior(_name) : _func;
        if (f != NULL) {
            return m_behaviors.exists(_name) ^ m_behaviors.insert(_name, f);
        } else {
            return false;
        }
    }
}

bool Entity::RemoveBehavior(const char *_name)
{
    if (unlikely(_name == NULL)) {
        return false;
    } else {
        return m_behaviors.erase(_name);
    }
}

bool Entity::HasBehavior(const char *_name)
{
    return m_behaviors.exists(_name);
}

/**
 * Property methods
 */

bool Entity::SetProperty(const char *_name, property_type_t _type, void *_value)
{
    if (likely(_name != NULL)) {
        property_t *prop = m_properties.find(_name, NULL);
        bool overwritten = prop != NULL;
        bool sametype = overwritten;
        if (!overwritten) {
            prop = new property_t;
        } else if(prop->type != _type) {
            sametype = false;
            switch (prop->type) {
            case TYPE_STRING:
                delete[] (const char *)prop->value;
                prop->value = NULL;
                break;
            case TYPE_NUMBER:
                delete (float *)prop->value;
                prop->value = NULL;
                break;
            case TYPE_BOOLEAN:
                delete (bool *)prop->value;
                prop->value = NULL;
                break;
            case TYPE_RECT:
                delete (Rect *)prop->value;
                prop->value = NULL;
                break;
            case TYPE_VECTOR:
                delete (Vector *)prop->value;
                prop->value = NULL;
                break;
            case TYPE_NONE:
                break;
            }
        }
        prop->type = _type;
        switch (_type) {
        case TYPE_STRING:
            if (!(overwritten && sametype)) {
                prop->value = (void*)newStr((const char *)_value);
            } else {
                memmove(prop->value, _value, sizeof((const char *)_value));
            }
            break;
        case TYPE_NUMBER: {
            if (!(overwritten && sametype)) {
                prop->value = (void*)(new float);
            }
            memmove(prop->value, _value, sizeof(float));
            break;
        }
        case TYPE_BOOLEAN: {
            if (!(overwritten && sametype)) {
                prop->value = (void*)(new bool);
            }
            memmove(prop->value, _value, sizeof(bool));
            break;
        }
        case TYPE_RECT: {
            if (!(overwritten && sametype)) {
                prop->value = (void*)(new Rect);
            }
            memmove(prop->value, _value, sizeof(Rect));
            break;
        }
        case TYPE_VECTOR: {
            if (!(overwritten && sametype)) {
                prop->value = (void*)(new Vector);
            }
            memmove(prop->value, _value, sizeof(Vector));
            break;
        }
        case TYPE_NONE:
            break;
        }
        if (overwritten) {
            return false;
        } else {
            return m_properties.insert(_name, prop);
        }
    } else {
        return false;
    }
}

bool Entity::RemoveProperty(const char *_name)
{
    if (unlikely(_name == NULL)) {
        return false;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (prop == NULL) {
            return false;
        }
        switch (prop->type) {
        case TYPE_STRING:
            delete[] (const char *)prop->value;
            break;
        case TYPE_NUMBER:
            delete (float *)prop->value;
            break;
        case TYPE_BOOLEAN:
            delete (bool *)prop->value;
            break;
        case TYPE_RECT:
            delete (Rect *)prop->value;
            break;
        case TYPE_VECTOR:
            delete (Vector *)prop->value;
            break;
        case TYPE_NONE:
            break;
        }
        return m_properties.erase(_name);
    }
}

int Entity::GetProperty(const char *_name, const char *&_val)
{
    if (unlikely(_name == NULL)) {
        return 0;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (likely(prop != NULL && prop->type == TYPE_STRING)) {
            _val = (const char *)prop->value;
            return 1;
        } else {
            return 0;
        }
    }
}

int Entity::GetProperty(const char *_name, float &_val)
{
    if (unlikely(_name == NULL)) {
        return 0;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (likely(prop != NULL && prop->type == TYPE_NUMBER)) {
            memmove(&_val, prop->value, sizeof(float));
            return 1;
        } else {
            return 0;
        }
    }
}

int Entity::GetProperty(const char *_name, bool &_val)
{
    if (unlikely(_name == NULL)) {
        return 0;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (likely(prop != NULL && prop->type == TYPE_BOOLEAN)) {
            memmove(&_val, prop->value, sizeof(bool));
            return 1;
        } else {
            return 0;
        }
    }
}

int Entity::GetProperty(const char *_name, Rect *&_val)
{
    if (unlikely(_name == NULL)) {
        return 0;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (likely(prop != NULL && prop->type == TYPE_RECT)) {
            _val = (Rect*)prop->value;
            return 1;
        } else {
            return 0;
        }
    }
}

int Entity::GetProperty(const char *_name, Vector *&_val)
{
    if (unlikely(_name == NULL)) {
        return 0;
    } else {
        property_t *prop = m_properties.find(_name, NULL);
        if (likely(prop != NULL && prop->type == TYPE_VECTOR)) {
            _val = (Vector*)prop->value;
            return 1;
        } else {
            return 0;
        }
    }
}
bool Entity::HasProperty(const char *_name)
{
    if (unlikely(_name == NULL)) {
        return false;
    } else {
        return m_properties.exists(_name);
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

void Entity::AddChild(Entity *_child)
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
    size_t size = m_behaviors.size();
    behaviorFunc renderBehavior = m_behaviors.find("render", NULL);
    for (size_t i = 0; i < size; i++) {
        if (m_behaviors.valid(i)) {
            behaviorFunc f = m_behaviors[i];
            if (unlikely(f == renderBehavior)) {
                continue;
            } else {
                f(this, _delta);
            }
        }
    }
}

void Entity::Render(float _delta)
{
    behaviorFunc renderBehavior = m_behaviors.find("render", NULL);
    if (renderBehavior != NULL) {
        renderBehavior(this, _delta);
    }
}
