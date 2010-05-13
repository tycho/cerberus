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

#ifndef __included_databuffer_h
#define __included_databuffer_h

//! A sort of basic string class, but can hold other types of data as well.
class DataBuffer
{
    protected:
        //! Indicates whether or not the DataBuffer was set to contain a string.
        bool m_isString;

        //! The internal memory buffer which contains the data.
        char *m_buffer;

        //! The size of the internal buffer.
        size_t m_size;

    public:
        //! The default constructor.
        DataBuffer ();

        /*!
            \param _initialCapacity Amount of memory to allocate for the internal buffer.
         */
        DataBuffer ( size_t _initialCapacity );

        /*!
            \param _initialString A string to put into the buffer.
         */
        DataBuffer ( const char *_initialString );

        /*!
            \param _initialData A pointer to the data which should be inside the buffer.
            \param _size The size of the data to be copied (in bytes).
         */
        DataBuffer ( const void *_initialData, size_t _size );

        //! The copy constructor.
        DataBuffer ( const DataBuffer &_initialData );

        //! The destructor.
        virtual ~DataBuffer ();

        //! Resize the data buffer while preserving the contents.
        virtual void resize ( size_t _capacity );

        //! Resize the data buffer, dropping existing contents.
        virtual void setSize ( size_t _capacity );

        //! Set the data buffer contents.
        virtual int setData ( const void *_newData, size_t _size );

        //! Set the data buffer contents.
        virtual int setDataString ( const char *_newData );

        //! Returns a pointer to the internal data buffer.
        virtual const char *getData() const;

        //! Returns the current buffer size, in bytes.
        virtual size_t getSize() const;

        virtual bool isString() const;

        //! Implicit assignment operator.
        DataBuffer &operator=  ( const DataBuffer &_buffer );

        bool operator>  ( const DataBuffer &_buffer ) const;
        bool operator>= ( const DataBuffer &_buffer ) const;

        bool operator<  ( const DataBuffer &_buffer ) const;
        bool operator<= ( const DataBuffer &_buffer ) const;

        bool operator== ( const DataBuffer &_buffer ) const;
        bool operator!= ( const DataBuffer &_buffer ) const;

        /*!
            \return Returns 'true' if the data buffer has been allocated.
         */
        inline bool operator! () const { return ( m_buffer == NULL ); }

        //! Returns a pointer to a given location in the data buffer.
        /*!
            \param _index The index of the data requested.
         */
        inline char &operator[] ( unsigned int _index ) {
                static char c = '\x0';
                if ( m_buffer && m_size > _index )
                    return m_buffer[_index];
                else
                    return c;
        }

        //! Returns a pointer to a given location in the data buffer.
        /*!
            \param _index The index of the data requested.
         */
        inline const char &operator[] ( unsigned int _index ) const {
                static const char c = '\x0';
                if ( m_buffer && m_size > _index )
                    return m_buffer[_index];
                else
                    return c;
        }
};

#endif
