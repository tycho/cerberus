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

#ifndef __sprite_h_included
#define __sprite_h_included

#include <universal_include.h>

class Texture;

class Sprite : public Entity { //tolua_export
protected:
    Texture *m_texture; // Sprite's texture object

public:
    Sprite();
    Sprite(float _x, float _y, float _w, float _h);
    Sprite(float _x, float _y, float _z, float _w, float _h, float _d);
    Sprite(Rect &_position);
    Sprite(Rect &_position, Vertex _vertices[], int _numVertices);
    Sprite(Rect &_position, Vertex _vertices[], int _numVertices, const char *_textureFilename);
    
    virtual ~Sprite();

    /**
     * Getters
     */

    //tolua_begin

    //tolua_end

    virtual Texture *GetTexture();

    /**
     * Setters
     */

    //tolua_begin

    //tolua_end

    virtual Uint32 SetTextureBitmap(const char *_filename);

    /**
     * Lifecycle functions
     */
    virtual void Render(float _delta);

    virtual void Update(float _delta);
}; //tolua_export

#include "Graphics/texture.h"

#endif
