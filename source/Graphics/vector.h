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
 
#ifndef __vector_h_included
#define __vector_h_included

#include <universal_include.h>

class Vector {
public:
    float i, j, k;

    Vector()
     : i(0),
       j(0),
       k(0)
    {
    }

    Vector(float _i, float _j)
     : i(_i),
       j(_j),
       k(0)
    {
    }

    Vector(float _i, float _j, float _k)
     : i(_i),
       j(_j),
       k(_k)
    {
    }
};

// Multiplies a vector by a scalar value
inline Vector multv(Vector const &v, float s)
{
    return Vector(s * v.i, s * v.j, s * v.k);
}

// Returns magnitude of a given vector
inline float magv(Vector const &v)
{
    return sqrt(v.i * v.i + v.j * v.j + v.k * v.k);
}

// Normalizes a vector
inline Vector normalizev(Vector const &v)
{
    return multv(v, (1.0 / magv(v)));
}

// Returns dot product of two given vectors
inline float dotv(Vector const &u, Vector const &v)
{
    return u.i * v.i + u.j * v.j + u.k * v.k;
}

// Returns dot product of two vectors given their magnitude and angle (in degrees) between them
inline float dotv(float magu, float magv, float angle)
{
    return magu * magv * cos(TORADIANS(angle));
}

// Vector Projection of u onto v
inline Vector projectionv(Vector const &u, Vector const &v)
{
    return multv(v, dotv(u, v) / dotv(v, v));
}

// Scalar projection of u onto v (magnitude of projection vector)
inline float projections(Vector const &u, Vector const &v)
{
    return magv(projectionv(u, v));
}

// Returns cross product of two vectors
inline Vector crossv(Vector const &u, Vector const &v)
{
    return Vector(  u.j * v.k - u.k * v.j,
                    -(u.i * v.k - u.k * v.i),
                    u.i * v.j - u.j * v.i);
}

// Returns vector perpendicular to a given vector
inline Vector perpendicularv(Vector const &u)
{
    return Vector(-u.j, u.i, u.k);
}

// Returns vector perpendicular to u and v (cross product alias)
inline Vector perpendicularv(Vector const &u, Vector const &v)
{
    return crossv(u, v);
}

// Returns angle between two vectors, in degrees
inline float anglev(Vector const &u, Vector const &v)
{
    return TODEGREES(acos(dotv(u, v) / (magv(u) * magv(v))));
}
#endif
