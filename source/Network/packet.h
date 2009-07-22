/*
 * Copyright (c) 2009 Steven Noonan <steven@uplinklabs.net>
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

#ifndef __included_packet_h
#define __included_packet_h

#include <crisscross/darray.h>

#include "App/databuffer.h"

class Packet
{
private:
    // TODO: Make this one long char array. This method's too slow.
    CrissCross::Data::DArray<DataBuffer *> m_buffer;
    mutable int m_bufferIndex;
    mutable int m_size;
    mutable int m_serializedSize;
    mutable char *m_serializedBuffer;

    inline void CacheDamaged ();
    void Deserialize ();

public:
    Packet();
    Packet ( const char *_serializedData, size_t _dataLength ); // Deserializes a stream of data.
    ~Packet();

    void AddBufferData ( const void *_data, size_t _length );
    void AddBufferString ( const char *_string );
    int GetBufferData ( void *_data, size_t _length ) const;
    int GetBufferString ( char *&_string, size_t &_length ) const;

    void Serialize ( const char *&_data, size_t &_dataSize ) const;
    inline size_t SerializedSize () const;
    inline size_t Size () const;

};

#endif
