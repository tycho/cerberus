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

Entity::Entity()
 :  m_active(true),
    m_boundingBox({0, 0, 0, 0, 0, 0}),
    m_vertices(NULL),
    m_numVertices(0),
    m_inputComponent(NULL),
    m_physicsComponent(NULL),
    m_renderComponent(NULL)
{
    BuildVertices();
}

Entity::Entity(float _x, float _y, float _w, float _h, Color32 _color)
 :  m_active(true),
    m_border(false),
    m_boundingBox({_x, _y, 0, _w, _h, 0}),
    m_color(_color),
    m_borderColor(_color),
    m_vertices(NULL),
    m_numVertices(0),
    m_inputComponent(NULL),
    m_physicsComponent(NULL),
    m_renderComponent(NULL)
{
    BuildVertices();
}

Entity::~Entity()
{
    if (m_vertices != NULL) {
        free(m_vertices);
        m_vertices = NULL;
    }
    if (m_inputComponent != NULL) {
        delete m_inputComponent;
        m_inputComponent = NULL;
    }
    if (m_physicsComponent != NULL) {
        delete m_physicsComponent;
        m_physicsComponent = NULL;
    }
    if (m_renderComponent != NULL) {
        delete m_renderComponent;
        m_renderComponent = NULL;
    }
}

/* Build each of the (currently 4) vertices for this entity */
void Entity::BuildVertices()
{
    if (m_vertices != NULL) {
        free(m_vertices);
        m_vertices = NULL;
    }
    m_vertices = (Vertex *)calloc(sizeof(Vertex), 4);
    int i = 0;
    Vertex v;
    for (; i < 4; i++) {
        float x, y, z, r, g, b, a, u, v;
        r = m_color.R();
        g = m_color.G();
        b = m_color.B();
        a = m_color.A();
        switch(i) {
        case 0:
            x = 0;
            y = 0;
            z = m_boundingBox.z;
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        }
        m_vertices[i] = v;
    }
}

bool Entity::IsActive()
{
    return m_active;
}

bool Entity::IsBorderEnabled()
{
    return m_border;
}

float Entity::GetX()
{
    return m_boundingBox.x;
}

float Entity::GetY()
{
    return m_boundingBox.y;
}

float Entity::GetZ()
{
    return m_boundingBox.z;
}

float Entity::GetWidth()
{
    return m_boundingBox.w;
}

float Entity::GetHeight()
{
    return m_boundingBox.h;
}

float Entity::GetDepth()
{
    return m_boundingBox.d;
}

Color32 &Entity::GetColor()
{
    return m_color;
}

Color32 &Entity::GetBorderColor()
{
    return m_borderColor;
}

Visibility Entity::GetVisibility()
{
    return m_visibility;
}

Vertex *Entity::GetVertices()
{
    return m_vertices;
}

int Entity::GetNumVertices()
{
    return m_numVertices;
}

InputComponent *Entity::GetInputComponent()
{
    return m_inputComponent;
}

PhysicsComponent *Entity::GetPhysicsComponent()
{
    return m_physicsComponent;
}

RenderComponent *Entity::GetRenderComponent()
{
    return m_renderComponent;
}

void Entity::SetActive(bool _isActive)
{
    m_active = _isActive;
}

void Entity::SetBorderEnabled(bool _isBorderEnabled)
{
    m_border = _isBorderEnabled;
}

void Entity::SetX(float _x)
{
    m_boundingBox.x = _x;
}

void Entity::SetY(float _y)
{
    m_boundingBox.y = _y;
}

void Entity::SetZ(float _z)
{
    m_boundingBox.z = _z;
}

void Entity::SetWidth(float _w)
{
    m_boundingBox.w = _w;
}

void Entity::SetHeight(float _h)
{
    m_boundingBox.h = _h;
}

void Entity::SetDepth(float _d)
{
    m_boundingBox.d = _d;
}

void Entity::SetColor(Color32 _color)
{
    m_color = _color;
}

void Entity::SetBorderColor(Color32 _borderColor)
{
    m_borderColor = _borderColor;
}

void Entity::SetVisibility(Visibility _visibility)
{
    m_visibility = _visibility;
}

void Entity::SetVertices(Vertex _vertices[], int _count)
{
    if (_vertices != NULL) {
        if (m_vertices != NULL) {
            free(m_vertices);
            m_vertices = NULL;
        }
        m_vertices = (Vertex *)calloc(sizeof(Vertex), _count);
        for (int i = 0; i < _count; i++) {
            m_vertices[i] = _vertices[i];
        }
        m_numVertices = _count;
        if (m_renderComponent == NULL) {
            m_renderComponent = new RenderComponent(this);
        }
    }
}

void Entity::SetInputComponent(InputComponent *_inputComponent)
{
    m_inputComponent = _inputComponent;
}

void Entity::SetPhysicsComponent(PhysicsComponent *_physicsComponent)
{
    m_physicsComponent = _physicsComponent;
}

void Entity::SetRenderComponent(RenderComponent *_renderComponent)
{
    m_renderComponent = _renderComponent;
}

void Entity::Render(float _delta)
{
    if (m_renderComponent != NULL) {
        m_renderComponent->Update(_delta);
    }
}

void Entity::Update(float _delta)
{
    if (m_inputComponent != NULL) {
        m_inputComponent->Update(_delta);
    }
    if (m_physicsComponent != NULL) {
        m_physicsComponent->Update(_delta);
    }
}
