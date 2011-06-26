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
 
#ifndef __included_color32_h
#define __included_color32_h

#include <universal_include.h> //tolua_export
#include <crisscross/platform_detect.h>

class Color32 { //tolua_export
private:
    union {
        Uint32 rgba;
        struct {
#ifdef TARGET_LITTLE_ENDIAN
            Uint8 a;
            Uint8 b;
            Uint8 g;
            Uint8 r;
#else
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;
#endif
        } c;
    };
public:
    //tolua_begin
    float R() const { return (float)c.r / 255.0f; }
    float G() const { return (float)c.g / 255.0f; }
    float B() const { return (float)c.b / 255.0f; }
    float A() const { return (float)c.a / 255.0f; }

	Color32()
	{
		rgba = 0;
	}

	Color32(Uint32 _rgba)
	{
		rgba = _rgba;
	}

    Color32(Uint8 _r, Uint8 _g, Uint8 _b, int _a = 255)
    {
        Set(_r,_g,_b,_a);
    }

	Color32(Color32 const &_copy)
	{
		rgba = _copy.rgba;
	}

    void Set(Uint8 _r, Uint8 _g, Uint8 _b, int _a = 255)
    {
        c.r = _r;
        c.g = _g;
        c.b = _b;
        c.a = (Uint8)_a;
    }

    void SetR(Uint8 _r)
    {
        c.r = _r;
    }

    void SetB(Uint8 _b)
    {
        c.b = _b;
    }

    void SetG(Uint8 _g)
    {
        c.g = _g;
    }

    void SetA(Uint8 _a)
    {
        c.a = _a;
    }

    Uint32 GetRGBA()
    {
        return rgba;
    }
//tolua_end
	Color32 const &operator = (Color32 const &_rhs)
	{
		rgba = _rhs.rgba;
		return *this;
	}

	Color32 const &operator = (Uint32 const &_rhs)
	{
		rgba = _rhs;
		return *this;
	}

	Color32 const &operator = (Sint32 const &_rhs)
	{
		rgba = _rhs;
		return *this;
	}
//tolua_begin
	bool operator==(Color32 const &_rhs) const
	{
		return _rhs.rgba == rgba;
	}
	//tolua_end
}; //tolua_export
#endif
