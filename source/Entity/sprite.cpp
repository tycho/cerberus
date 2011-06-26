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
#include "Entity/sprite.h"

class Texture;

Sprite::Sprite()
 :  Entity(),
    m_texture(NULL)
{
}

Sprite::Sprite(float _x, float _y, float _w, float _h)
 :  Entity(_x, _y, _w, _h),
    m_texture(NULL)
{
}

Sprite::Sprite(float _x, float _y, float _z, float _w, float _h, float _d)
 :  Entity(_x, _y, _z, _w, _h, _d),
    m_texture(NULL)
{
}

Sprite::Sprite(Rect &_position)
 :  Entity(_position),
    m_texture(NULL)
{
}

Sprite::Sprite(Rect &_position, Vertex _vertices[], int _numVertices)
 :  Entity(_position, _vertices, _numVertices),
    m_texture(NULL)
{
}

Sprite::Sprite(Rect &_position, Vertex _vertices[], int _numVertices, const char *_textureFilename)
 :  Entity(_position, _vertices, _numVertices),
    m_texture(NULL)
{
    SetTextureBitmap(_textureFilename);
}

Sprite::~Sprite()
{
    if (m_texture != NULL) {
        m_texture->Dispose();
        m_texture = NULL;
    }
}

Texture *Sprite::GetTexture()
{
    return m_texture;
}

Uint32 Sprite::SetTextureBitmap(const char *_filename)
{
    Uint32 offset = g_graphics->LoadImage(_filename);
    m_texture = g_graphics->GetTexture(offset);
    m_texture->Upload();
    return offset;
}

void Sprite::Render(float _delta)
{
    Entity::Render(_delta);
}

void Sprite::Update(float _delta)
{
    Entity::Update(_delta);
}

#include "Graphics/texture.h"
