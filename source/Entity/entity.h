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

//tolua_begin
enum Visibility {
    VISIBLE, // Draw this entity and it's border (if it's enabled)
    INVISIBLE, // Only draw this entity's border if it's enabled
    GONE // Don't draw the entity or the border
};
//tolua_end

class Component;
class InputComponent;
class PhysicsComponent;
class RenderComponent;
class TextureComponent;

class Entity { //tolua_export
protected:
    bool m_active; // Is the entity active?
    bool m_border; // Should we enable this entity's border?

    Rect m_boundingBox; // Entity's position and dimensions

    Color32 m_color; // Base color of the entity
    Color32 m_borderColor; // Border color

    Visibility m_visibility; // See Visibility enum

    Vertex *m_vertices; // Entity vertex data
    int m_numVertices; // Number of Vertex objects in m_vertices

    InputComponent *m_inputComponent; // Entity's InputComponent
    PhysicsComponent *m_physicsComponent; // Entity's PhysicsComponent
    RenderComponent *m_renderComponent; // Entity's RenderComponent
    TextureComponent *m_textureComponent; // Entity's TextureComponent

    virtual void BuildVertices();

public:
    Entity();
    Entity(float _x, float _y, float _w, float _h, Color32 _color);
    Entity(float _x, float _y, float _w, float _h, Color32 _color, const char *_textureFilename);
    
    virtual ~Entity();

    /**
     * Getters
     */

    //tolua_begin

    virtual bool IsActive();
    virtual bool IsBorderEnabled();

    virtual float GetX();
    virtual float GetY();
    virtual float GetZ();

    virtual float GetWidth();
    virtual float GetHeight();
    virtual float GetDepth();

    virtual Color32 &GetColor();
    virtual Color32 &GetBorderColor();

    virtual Visibility GetVisibility();

    //tolua_end

    virtual Vertex *GetVertices();
    virtual int GetNumVertices();

    virtual InputComponent *GetInputComponent();
    virtual PhysicsComponent *GetPhysicsComponent();
    virtual RenderComponent *GetRenderComponent();
    virtual TextureComponent *GetTextureComponent();

    /**
     * Setters
     */

    //tolua_begin
    virtual void SetActive(bool _isActive);
    virtual void SetBorderEnabled(bool _isBorderEnabled);

    virtual void SetX(float _x);
    virtual void SetY(float _y);
    virtual void SetZ(float _z);

    virtual void SetWidth(float _x);
    virtual void SetHeight(float _y);
    virtual void SetDepth(float _z);

    virtual void SetColor(Color32 _color);
    virtual void SetBorderColor(Color32 _borderColor);

    virtual void SetVisibility(Visibility _visibility);

    //tolua_end

    virtual void SetInputComponent(InputComponent *_inputComponent);
    virtual void SetPhysicsComponent(PhysicsComponent *_physicsComponent);
    virtual void SetRenderComponent(RenderComponent *_renderComponent);
    virtual void SetTextureComponent(TextureComponent *_textureComponent);

    /**
     * Lifecycle functions
     */
    virtual void Render(float _delta);

    virtual void Update(float _delta);
}; //tolua_export

#include "Entity/Component/component.h"

#endif
