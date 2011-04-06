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

Entity::Entity()
 : m_static(false),
   m_visible(true),
   m_width(0),
   m_height(0),
   m_X(0),
   m_Y(0),
   m_Z(0),
   m_Xvel(0),
   m_Yvel(0),
   m_Zvel(0)
{
}

Entity::Entity(int _width, int _height)
 : m_static(false),
   m_visible(true),
   m_width(_width),
   m_height(_height),
   m_X(0),
   m_Y(0),
   m_Z(0),
   m_Xvel(0),
   m_Yvel(0),
   m_Zvel(0)
{
}

Entity::Entity(int _width, int _height, int _X, int _Y, int _Z)
 : m_static(false),
   m_visible(true),
   m_width(_width),
   m_height(_height),
   m_X(_X),
   m_Y(_Y),
   m_Z(_Z),
   m_Xvel(0),
   m_Yvel(0),
   m_Zvel(0)
{
}

Entity::~Entity()
{
}

void Entity::setWidth(int _width)
{
    m_width = _width;
}

void Entity::setHeight(int _height)
{
    m_height = _height;
}

void Entity::setPositionX(int _X)
{
    m_X = _X;
}

void Entity::setPositionY(int _Y)
{
    m_Y = _Y;
}

void Entity::setPositionZ(int _Z)
{
    m_Z = _Z;
}

void Entity::setPosition(int _X, int _Y, int _Z)
{
    m_X = _X;
    m_Y = _Y;
    m_Z = _Z;
}

void Entity::setVelocityX(int _Xvel)
{
    m_Xvel = _Xvel;
}

void Entity::setVelocityY(int _Yvel)
{
    m_Yvel = _Yvel;
}

void Entity::setVelocityZ(int _Zvel)
{
    m_Zvel = _Zvel;
}

void Entity::setVelocity(int _Xvel, int _Yvel, int _Zvel)
{
    m_Xvel = _Xvel;
    m_Yvel = _Yvel;
    m_Zvel = _Zvel;
}
