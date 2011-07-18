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

#include "Entity/Attributes/attribute_position.h"
#include "Entity/Behaviors/behavior_physics.h"

#include "Entity/entity.h"
PhysicsBehavior::PhysicsBehavior(Entity *_entity)
 : Behavior(Behavior::Names[PHYSICS], _entity),
   m_gravity(0.0f),
   m_collidable(false)
{
}

bool PhysicsBehavior::IsCollidable()
{
    return m_collidable;
}

float PhysicsBehavior::GetGravity()
{
    return m_gravity;
}

Vector &PhysicsBehavior::GetVelocity()
{
    return m_velocity;
}

Vector &PhysicsBehavior::GetAcceleration()
{
    return m_acceleration;
}

void PhysicsBehavior::SetCollidable(bool _collidable)
{
    m_collidable = _collidable;
}

void PhysicsBehavior::SetGravity(float _gravity)
{
    m_gravity = _gravity;
}

void PhysicsBehavior::SetVelocity(Vector &_velocity)
{
    m_velocity = _velocity;
}

void PhysicsBehavior::SetAcceleration(Vector &_acceleration)
{
    m_acceleration = _acceleration;
}

void PhysicsBehavior::Update(float _delta)
{
    /* Make gravity act on the acceleration */
    m_acceleration.y += m_gravity * _delta;

    /* Accelerate */
    m_velocity.x += m_acceleration.x * _delta;
    m_velocity.y += m_acceleration.y * _delta;
    m_velocity.z += m_acceleration.z * _delta;

    /* Update entity position (if it has one, which it should) */
    PositionAttribute *posAttr = m_entity->GetAttribute<PositionAttribute>(Attribute::Names[POSITION]);
    if (posAttr != NULL) {
        Rect tmp = posAttr->GetPosition();
        tmp.x += m_velocity.x * _delta;
        tmp.y += m_velocity.y * _delta;
        tmp.z += m_velocity.z * _delta;
        posAttr->SetPosition(tmp);
    }
}
