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

#ifndef __entity_h_included
#define __entity_h_included

#include "universal_include.h"

#include "App/string_utils.h"

#include "Entity/behaviors.h"

#include "Graphics/rect.h"
#include "Graphics/vector.h"

typedef enum {
    TYPE_STRING,
    TYPE_NUMBER,
    TYPE_BOOLEAN,
    TYPE_RECT,
    TYPE_VECTOR,
    TYPE_NONE
} property_type_t;

typedef struct {
    property_type_t type;
    void *value;
} property_t;

class Entity { //tolua_export
protected:
    unsigned int m_id;
    const char *m_name;
    Data::HashTable<behaviorFunc> m_behaviors;
    Data::HashTable<property_t *> m_properties;
    Entity *m_parent;
    Data::LList<Entity *> m_children;
public:
    Entity(unsigned int _id, const char *_name);
    virtual ~Entity();

    unsigned int GetID() const; //tolua_export
    const char *GetName() const; //tolua_export

    /**
     * Behavior methods
     */
    bool AddBehavior(const char *_name, behaviorFunc _func = NULL);
    bool RemoveBehavior(const char *_name);
    bool HasBehavior(const char *_name); //tolua_export

    /**
     * Property methods
     */
    bool SetProperty(const char *_name, property_type_t _type, void *_value);
    bool RemoveProperty(const char *_name); //tolua_export
    int GetProperty(const char *_name, const char *&_val);
    int GetProperty(const char *_name, float &_val);
    int GetProperty(const char *_name, bool &_val);
    int GetProperty(const char *_name, Rect *&_val);
    int GetProperty(const char *_name, Vector *&_val);
    bool HasProperty(const char *_name); //tolua_export

    /**
     * Scene graph-ish methods
     */
    Entity *GetParent();
    Entity *GetChild(int _index);
    void AddChild(Entity *_child);
    void RemoveChild(Entity *_child);

    //tolua_end

    /**
     * Lifecycle methods
     */
    virtual void Update(float _delta);
    virtual void Render(float _delta);
}; //tolua_export

#endif
