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
#include "Graphics/Animation/fade.h"

Fade::Fade(float _start, float _end, float _rate)
 : m_widget(NULL), m_alpha(_start), m_end(_end), m_rate(_rate)
{
    m_dir = (_start > _end) ? -1 : 1;
}

Fade::Fade(Widget *_widget, float _start, float _end, float _rate)
 : m_widget(_widget), m_alpha(_start), m_end(_end), m_rate(_rate)
{
    m_dir = (_start > _end) ? -1 : 1;
}

Fade::~Fade()
{
}

void Fade::Update()
{
	m_alpha += (float)m_dir * m_rate * 0.1f * (float)g_app->Speed();
	if (m_dir < 0 && m_alpha <= m_end) {
		m_alpha = m_end;
	}
	if (m_dir > 0 && m_alpha >= m_end) {
		m_alpha = m_end;
	}
	if (m_widget != NULL) {
	    m_widget->SetAlpha(m_alpha);
	}
}

void Fade::Begin()
{
    if (m_widget == NULL) {
        /*
         * Basically, we want to use diffuse lighting (which is the only type of lighting
         * which cares about the alpha value) to make the object become transparent. To do
         * so, we set glColor to only set the ambient color (via glColorMaterial), and let
         * the lighting manage the alpha value.
         */
        GLfloat global_ambient[] = {0.7f, 0.7f, 0.7f, m_alpha};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, global_ambient);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);
    } else {
        m_widget->SetAlpha(m_alpha);
    }
}

void Fade::End()
{
    if (m_widget == NULL) {
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
    } else {
        m_widget->SetAlpha(m_end);
    }
}
