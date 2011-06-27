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

Entity::Entity()
 :  m_active(true),
    m_border(false),
    m_boundingBox({0, 0, 0, 0, 0, 0}),
    m_vertices(NULL),
    m_numVertices(0),
    m_inputComponent(NULL),
    m_physicsComponent(NULL),
    m_renderComponent(NULL),
    m_textureComponent(NULL)
{
    BuildVertices();
}

Entity::Entity(float _x, float _y, float _w, float _h, Color32 _color)
 :  m_active(true),
    m_border(false),
    m_boundingBox({_x, _y, 0, _w, _h, 0}),
    m_color(_color),
    m_borderColor(Color32(255, 0, 255)),
    m_vertices(NULL),
    m_numVertices(0),
    m_inputComponent(NULL),
    m_physicsComponent(NULL),
    m_renderComponent(NULL),
    m_textureComponent(NULL)
{
    BuildVertices();
}

Entity::Entity(float _x, float _y, float _w, float _h, Color32 _color, const char *_textureFilename)
 :  m_active(true),
    m_border(false),
    m_boundingBox({_x, _y, 0, _w, _h, 0}),
    m_color(_color),
    m_borderColor(Color32(255, 0, 255)),
    m_vertices(NULL),
    m_numVertices(0),
    m_inputComponent(NULL),
    m_physicsComponent(NULL),
    m_renderComponent(NULL),
    m_textureComponent(NULL)
{
    TextureRegion textureRegion;
    textureRegion.textureId = g_graphics->LoadImage(_textureFilename);
    g_graphics->GetTexture(textureRegion.textureId)->Upload();
    textureRegion.x = 0;
    textureRegion.y = 0;
    textureRegion.w = g_graphics->GetTexture(textureRegion.textureId)->GetWidth();
    textureRegion.h = g_graphics->GetTexture(textureRegion.textureId)->GetHeight();
    m_textureComponent = new TextureComponent(this, textureRegion);
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
    if (m_textureComponent != NULL) {
        delete m_textureComponent;
        m_textureComponent = NULL;
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
    Vertex vert;
    TextureRegion *texReg = NULL;
    if (m_textureComponent != NULL) {
        texReg = &(m_textureComponent->GetTextureRegion());
    }
    vert.x = 0;
    vert.y = 0;
    vert.z = 0;
    vert.r = m_color.R();
    vert.g = m_color.G();
    vert.b = m_color.B();
    vert.a = m_color.A();
    vert.u = 0;
    vert.v = 0;
    for (; i < 4; i++) {
        switch(i) {
        case 0:
            vert.x = 0;
            vert.y = 0;
            vert.z = m_boundingBox.z;
            if (texReg != NULL) {
                vert.u = texReg->x;
                vert.v = texReg->y;
            }
            break;
        case 1:
            vert.x = m_boundingBox.w;
            vert.y = 0;
            vert.z = m_boundingBox.z;
            if (texReg != NULL) {
                vert.u = texReg->x + texReg->w;
                vert.v = texReg->y;
            }
            break;
        case 2:
            vert.x = m_boundingBox.w;
            vert.y = m_boundingBox.h;
            vert.z = m_boundingBox.z;
            if (texReg != NULL) {
                vert.u = texReg->x + texReg->w;
                vert.v = texReg->y + texReg->h;
            }
            break;
        case 3:
            vert.x = 0;
            vert.y = m_boundingBox.h;
            vert.z = m_boundingBox.z;
            if (texReg != NULL) {
                vert.u = texReg->x;
                vert.v = texReg->y + texReg->h;
            }
            break;
        }
        m_vertices[i] = vert;
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

TextureComponent *Entity::GetTextureComponent()
{
    return m_textureComponent;
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

void Entity::SetTextureComponent(TextureComponent *_textureComponent)
{
    m_textureComponent = _textureComponent;
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
