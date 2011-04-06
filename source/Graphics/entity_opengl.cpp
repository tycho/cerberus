/*
 * Copyright (c) 2010 Steven Noonan <steven@uplinklabs.net>
 *                and Miah Clayton <miah@ferrousmoon.com>
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

#include "Graphics/entity.h"

OpenGLEntity::OpenGLEntity()
 : Entity()
{
}

OpenGLEntity::OpenGLEntity(int _width, int _height)
 : Entity(_width, _height)
{
}

OpenGLEntity::OpenGLEntity(int _width, int _height, int _X, int _Y, int _Z)
 : Entity(_width, _height, _X, _Y, _Z)
{
}

OpenGLEntity::~OpenGLEntity()
{
}

void OpenGLEntity::CreateVBO()
{
}

void OpenGLEntity::LoadVBO()
{
}

void OpenGLEntity::DestroyVBO()
{
}

void OpenGLEntity::LoadVertices(GLfloat *_vertices)
{
    m_vertices = _vertices;
}

void OpenGLEntity::LoadColors(GLfloat *_colors)
{
    m_colors = _colors;
}

void OpenGLEntity::LoadTextureCoords(GLfloat *_textureCoords)
{
    m_textureCoords = _textureCoords;
}

void OpenGLEntity::LoadIndices(GLfloat *_indices)
{
    m_indices = _indices;
}

void OpenGLEntity::Upload()
{
    CreateVBO();
    LoadVBO();
}
