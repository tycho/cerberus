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

#include "Entity/component.h"

struct MessageObserver {
    const char *type;
    Component *observer;
};

class Entity { //tolua_export
protected:
    const char *m_name;
    Data::HashTable<Behavior *> m_behaviors;
    Data::HashTable<Attribute *> m_attributes;
    Data::HashTable<MessageObserver> m_messageObservers;
    Entity *m_parent;
    Data::LList<Entity *> m_children;
public:
    Entity(const char *_name);
    virtual ~Entity();

    //tolua_begin

    const char *GetName();

    /**
     * Behavior methods
     */
    bool HasBehavior(const char *_name);
    //tolua_end
    template<typename B>
    B *GetBehavior(const char *_name) { return dynamic_cast<B*>(m_behaviors.find(_name)); }
    //tolua_begin
    bool AddBehavior(const char *_name, Behavior *_behavior);
    bool RemoveBehavior(const char *_name);

    /**
     * Attribute methods
     */
    bool HasAttribute(const char *_name);
    //tolua_end
    template<typename A>
    A *GetAttribute(const char *_name) { return dynamic_cast<A*>(m_attributes.find(_name)); }
    //tolua_begin
    bool AddAttribute(const char *_name, Attribute *_attribute);
    bool RemoveAttribute(const char *_name);

    /**
     * Messaging
     */
    void SendMessage(const char * _type, void *_data);
    void RegisterMessageObserver(const char *_type, Component *_observer);

    /**
     * Scene graph methods
     */
    Entity *GetParent();
    Entity *GetChild(int _index);
    void AttachChild(Entity *_child);
    void RemoveChild(Entity *_child);

    //tolua_end

    /**
     * Lifecycle methods
     */
    virtual void Update(float _delta);
    virtual void Render(float _delta);
}; //tolua_export

#endif
