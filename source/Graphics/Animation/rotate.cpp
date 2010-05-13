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

#include "App/app.h"
#include "Graphics/Animation/rotate.h"

Rotate::Rotate(SDL_Rect *_pivot, float _start, float _end, float _rate)
: m_rot(_start), m_end(_end), m_rate(_rate), m_pivot(_pivot)
{
    m_dir = (_start > _end) ? -1 : 1;
}

Rotate::~Rotate()
{
}

void Rotate::Update()
{
	if ((m_dir > 0 && m_rot >= m_end) || (m_dir < 0 && m_rot <= m_end)) {
		m_rot = m_end;
	} else {
		m_rot += (float)m_dir * m_rate * g_app->Speed();
	}
}

void Rotate::Begin()
{
	glPushMatrix();
	glTranslatef(m_pivot->x + (m_pivot->w / 2), m_pivot->y + (m_pivot->h / 2), 0.0f);
	glRotatef(m_rot, 0.0f, 0.0f, 1.0f);
	glTranslatef(-(m_pivot->x + (m_pivot->w / 2)), -(m_pivot->y + (m_pivot->h / 2)), 0.0f);
}

void Rotate::End()
{
	glPopMatrix();
}