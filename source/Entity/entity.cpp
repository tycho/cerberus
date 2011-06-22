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

class Texture;

Entity::Entity()
 :  m_active(true),
    m_X(0),
    m_Y(0),
    m_Z(0),
    m_vertices(NULL),
    m_numVertices(0),
    m_texture(NULL),
    m_renderComponent(NULL)
{
}

Entity::Entity(int _X, int _Y, int _Z)
 :  m_active(true),
    m_X(_X),
    m_Y(_Y),
    m_Z(_Z),
    m_vertices(NULL),
    m_numVertices(0),
    m_texture(NULL),
    m_renderComponent(NULL)
{
}

Entity::Entity(int _X, int _Y, int _Z, Vertex _vertices[], int _numVertices)
 :  m_active(true),
    m_X(_X),
    m_Y(_Y),
    m_Z(_Z),
    m_vertices(NULL),
    m_numVertices(0),
    m_texture(NULL),
    m_renderComponent(NULL)
{
    SetVertices(_vertices, _numVertices);
}

Entity::Entity(int _X, int _Y, int _Z, Vertex _vertices[], int _numVertices, const char *_textureFilename)
 :  m_active(true),
    m_X(_X),
    m_Y(_Y),
    m_Z(_Z),
    m_vertices(NULL),
    m_numVertices(0),
    m_texture(NULL),
    m_renderComponent(NULL)
{
    SetVertices(_vertices, _numVertices);
    SetTextureBitmap(_textureFilename);
}

Entity::~Entity()
{
    if (m_vertices != NULL) {
        free(m_vertices);
        m_vertices = NULL;
    }
    if (m_texture != NULL) {
        m_texture->Dispose();
        m_texture = NULL;
    }
    if (m_renderComponent != NULL) {
        delete m_renderComponent;
        m_renderComponent = NULL;
    }
}

bool Entity::IsActive()
{
    return m_active;
}

int Entity::GetX()
{
    return m_X;
}

int Entity::GetY()
{
    return m_Y;
}

int Entity::GetZ()
{
    return m_Z;
}

Vertex *Entity::GetVertices()
{
    return m_vertices;
}

int Entity::GetNumVertices()
{
    return m_numVertices;
}

Texture *Entity::GetTexture()
{
    return m_texture;
}

InputComponent *Entity::GetInputComponent()
{
    return m_inputComponent;
}

RenderComponent *Entity::GetRenderComponent()
{
    return m_renderComponent;
}

void Entity::SetX(int _x)
{
    m_X = _x;
}

void Entity::SetY(int _y)
{
    m_Y = _y;
}

void Entity::SetZ(int _z)
{
    m_Z = _z;
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
            m_renderComponent = new RenderComponent();
        }
    }
}

Uint32 Entity::SetTextureBitmap(const char *_filename)
{
    Uint32 offset = g_graphics->LoadImage(_filename);
    m_texture = g_graphics->GetTexture(offset);
    m_texture->Upload();
    return offset;
}

void Entity::SetInputComponent(InputComponent *_inputComponent)
{
    m_inputComponent = _inputComponent;
}

void Entity::SetRenderComponent(RenderComponent *_renderComponent)
{
    m_renderComponent = _renderComponent;
}

void Entity::Render()
{
    if (m_renderComponent != NULL) {
        m_renderComponent->Update(this);
    }
}

void Entity::Update()
{
}

#include "Graphics/texture.h"
