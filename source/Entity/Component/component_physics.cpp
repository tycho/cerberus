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

#include <universal_include.h>

#include "Entity/Component/component_physics.h"

#include "Graphics/graphics.h"

PhysicsComponent::PhysicsComponent(Entity *_entity)
 : Component(_entity)
{
}

void PhysicsComponent::Update(float _delta)
{

    float x = m_entity->GetX();
    float y = m_entity->GetY();
/*
    m_xVelocity += m_xAcceleration * _delta;
    m_yVelocity += m_yAcceleration * _delta;

    if (m_xAcceleration == 0.0f) {
        m_xVelocity = 0.0f;
    }
    if (m_yAcceleration == 0.0f) {
        m_yVelocity = 0.0f;
    }

    if (m_xVelocity > 40.0f) {
        m_xVelocity = 40.0f;
    } else if (m_xVelocity < -40.0f) {
        m_xVelocity = -40.0f;
    }
    if (m_yVelocity > 40.0f) {
        m_yVelocity = 40.0f;
    } else if (m_yVelocity < -40.0f) {
        m_yVelocity = -40.0f;
    }

    x += m_xVelocity * _delta;
    y += m_yVelocity * _delta;
*/

    x += m_xAcceleration * _delta;
    y += m_yAcceleration * _delta;

    m_entity->SetX(x);
    m_entity->SetY(y);
}

void PhysicsComponent::SetCollisionType(int _collisionType)
{
    m_collisionType = _collisionType;
}

void PhysicsComponent::SetGravity(int _accDueToGravity)
{
    m_gravity = _accDueToGravity;
}
