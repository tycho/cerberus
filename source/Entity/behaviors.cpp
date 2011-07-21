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

#include "Entity/behaviors.h"
#include "Entity/entity.h"
#include "Graphics/graphics.h"

int register_behavior(const char *_name, behaviorFunc _func) {
    if (unlikely(behavior_map.find(_name, NULL) != NULL)) {
        return 0;
    } else {
        behavior_map.insert(_name, _func);
        return 1;
    }
}

behaviorFunc get_behavior(const char *_name) {
    return behavior_map.find(_name, NULL);
}

int unregister_behavior(const char *_name) {
    return behavior_map.erase(_name);
}

void behavior_moveable(Entity *_entity, float _delta) {
    Vector *position, *velocity, *acceleration;
    if (_entity->GetProperty("position", position)) {
        if (_entity->GetProperty("velocity", velocity)) {
            if (_entity->GetProperty("acceleration", acceleration)) {
                velocity->x += acceleration->x * _delta;
                velocity->y += acceleration->y * _delta;
                velocity->z += acceleration->z * _delta;
                _entity->SetProperty("velocity", TYPE_VECTOR, (void*)velocity);
            }
            position->x += velocity->x * _delta;
            position->y += velocity->y * _delta;
            position->z += velocity->z * _delta;
            _entity->SetProperty("position", TYPE_VECTOR, (void*)position);
        }
    }
}

void behavior_physics(Entity *_entity, float _delta) {
}

void behavior_render(Entity *_entity, float _delta) {
    g_graphics->DrawEntity(_entity);
}
