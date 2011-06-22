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

#include <universal_include.h>

#include "Graphics/vertex.h"

class Component;
class InputComponent;
class RenderComponent;
class Texture;

class Entity
{
protected:
    bool m_active;

    int m_X;
    int m_Y;
    int m_Z;

    Vertex *m_vertices;
    int m_numVertices;

    Texture *m_texture;

    InputComponent *m_inputComponent;
    RenderComponent *m_renderComponent;

public:
    Entity();
    Entity(int _X, int _Y, int _Z);
    Entity(int _X, int _Y, int _Z, Vertex _vertices[], int _numVertices);
    Entity(int _X, int _Y, int _Z, Vertex _vertices[], int _numVertices, const char *_textureFilename);
    
    virtual ~Entity();

    virtual bool IsActive();

    virtual int GetX();
    virtual int GetY();
    virtual int GetZ();

    virtual Vertex *GetVertices();
    virtual int GetNumVertices();
    virtual Texture *GetTexture();

    virtual InputComponent *GetInputComponent();
    virtual RenderComponent *GetRenderComponent();

    virtual void SetX(int _x);
    virtual void SetY(int _y);
    virtual void SetZ(int _z);

    virtual void SetVertices(Vertex _vertices[], int _count);
    virtual Uint32 SetTextureBitmap(const char *_filename);

    virtual void SetInputComponent(InputComponent *_inputComponent);
    virtual void SetRenderComponent(RenderComponent *_renderComponent);

    virtual void Render();

    virtual void Update();
};

#include "Entity/Component/component.h"
#include "Graphics/texture.h"

#endif
