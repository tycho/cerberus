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

#ifndef __included_binary_stream_readers_h
#define __included_binary_stream_readers_h

//! Abstract binary data reader.
class BinaryReader
{
protected:
    bool                      m_eof;
    char                      m_filename[256];

public:
    BinaryReader              ();
    virtual ~BinaryReader     ();

	//! Indicates whether the file is open.
	/*!
		\return True if the file is open, false otherwise.
	 */
    virtual bool              IsOpen      () = 0;

	//! Gets the file's extension (i.e. 'exe', 'png', etc)
	/*!
		\return The file extension.
	 */
    virtual const char       *GetFileType () = 0;

	//! Reads a signed 8-bit integer from the file stream.
	/*!
		\return The next signed 8-bit integer in the file stream.
	 */
    virtual signed char       ReadS8      () = 0;

	//! Reads a signed 16-bit integer from the file stream.
	/*!
		\return The next signed 16-bit integer in the file stream.
	 */
    virtual short             ReadS16     () = 0;

	//! Reads a signed 32-bit integer from the file stream.
	/*!
		\return The next signed 32-bit integer in the file stream.
	 */
    virtual int               ReadS32     () = 0;

	//! Reads the specified number of bytes into a buffer.
	/*!
		\param _count The number of bytes to read.
		\param _buffer The buffer to read into.
		\return The number of bytes actually read. Can be less than the number
		        specified by _count (end of file condition).
		\warning The buffer specified by _buffer must have space for _count bytes or more!
	 */
    virtual size_t            ReadBytes   ( unsigned int _count, unsigned char *_buffer ) = 0;

	//! Moves the file pointer to the specified location.
	/*!
		Sets the position indicator associated with the stream to a new position defined by adding offset to a reference position specified by origin.
		\param _offset The number of bytes to shift the position by, relative to _origin.
		\param _origin The origin from which to shift the buffer. Must be one of
		               SEEK_SET (move relative to beginning of file),
					   SEEK_CUR (move relative to current cursor position), or
					   SEEK_END (move relative to the end of the file).
        \return Zero on success, non-zero on failure.
	 */
    virtual int               Seek        ( int _offset, int _origin ) = 0;

	//! Returns the current value of the position indicator of the stream.
	/*!
		\return On success, the current value of the position indicator is returned.
	 */
    virtual int               Tell        () = 0;

	//! Gets the size of the file
	/*!
        \return The size of the file in bytes.
	 */
    size_t                    GetSize     ();
};

//! Binary file reader.
class BinaryFileReader: public BinaryReader
{
protected:
    FILE                      *m_file;

public:
    BinaryFileReader          ( char const *_filename );
    ~BinaryFileReader         ();

	//! Indicates whether the file is open.
	/*!
		\return True if the file is open, false otherwise.
	 */
    bool                      IsOpen      ();

	//! Gets the file's extension (i.e. 'exe', 'png', etc)
	/*!
		\return The file extension.
	 */
    const char *              GetFileType ();

	//! Reads a signed 8-bit integer from the file stream.
	/*!
		\return The next signed 8-bit integer in the file stream.
	 */
    signed char               ReadS8      ();

	//! Reads a signed 16-bit integer from the file stream.
	/*!
		\return The next signed 16-bit integer in the file stream.
	 */
    short                     ReadS16     ();

	//! Reads a signed 32-bit integer from the file stream.
	/*!
		\return The next signed 32-bit integer in the file stream.
	 */
    int                       ReadS32     ();

	//! Reads the specified number of bytes into a buffer.
	/*!
		\param _count The number of bytes to read.
		\param _buffer The buffer to read into.
		\return The number of bytes actually read. Can be less than the number
		        specified by _count (end of file condition).
		\warning The buffer specified by _buffer must have space for _count bytes or more!
	 */
    size_t                    ReadBytes   ( unsigned int _count, unsigned char *_buffer );

	//! Moves the file pointer to the specified location.
	/*!
		Sets the position indicator associated with the stream to a new position defined by adding offset to a reference position specified by origin.
		\param _offset The number of bytes to shift the position by, relative to _origin.
		\param _origin The origin from which to shift the buffer. Must be one of
		               SEEK_SET (move relative to beginning of file),
					   SEEK_CUR (move relative to current cursor position), or
					   SEEK_END (move relative to the end of the file).
        \return Zero on success, non-zero on failure.
	 */
    int                       Seek        ( int _offset, int _origin );

	//! Returns the current value of the position indicator of the stream.
	/*!
		\return On success, the current value of the position indicator is returned.
	 */
    int                       Tell        ();
};

//! Binary memory-mapped file reader.
class BinaryDataReader: public BinaryReader
{
protected:
    unsigned int              m_offset;

    unsigned char const      *m_data;
    unsigned int              m_dataSize;

public:
    BinaryDataReader          ( unsigned char const *_data, unsigned int _dataSize, char const *_filename );
    ~BinaryDataReader         ();

	//! Indicates whether the file is open.
	/*!
		\return True if the file is open, false otherwise.
	 */
    bool                      IsOpen      ();

	//! Gets the file's extension (i.e. 'exe', 'png', etc)
	/*!
		\return The file extension.
	 */
    const char *              GetFileType ();

	//! Reads a signed 8-bit integer from the file stream.
	/*!
		\return The next signed 8-bit integer in the file stream.
	 */
    signed char               ReadS8      ();

	//! Reads a signed 16-bit integer from the file stream.
	/*!
		\return The next signed 16-bit integer in the file stream.
	 */
    short                     ReadS16     ();

	//! Reads a signed 32-bit integer from the file stream.
	/*!
		\return The next signed 32-bit integer in the file stream.
	 */
    int                       ReadS32     ();

	//! Reads the specified number of bytes into a buffer.
	/*!
		\param _count The number of bytes to read.
		\param _buffer The buffer to read into.
		\return The number of bytes actually read. Can be less than the number
		        specified by _count (end of file condition).
		\warning The buffer specified by _buffer must have space for _count bytes or more!
	 */
    size_t                    ReadBytes   ( unsigned int _count, unsigned char *_buffer );

	//! Moves the file pointer to the specified location.
	/*!
		Sets the position indicator associated with the stream to a new position defined by adding offset to a reference position specified by origin.
		\param _offset The number of bytes to shift the position by, relative to _origin.
		\param _origin The origin from which to shift the buffer. Must be one of
		               SEEK_SET (move relative to beginning of file),
					   SEEK_CUR (move relative to current cursor position), or
					   SEEK_END (move relative to the end of the file).
        \return Zero on success, non-zero on failure.
	 */
    int                       Seek        ( int _offset, int _origin );

	//! Returns the current value of the position indicator of the stream.
	/*!
		\return On success, the current value of the position indicator is returned.
	 */
    int                       Tell        ();
};


#endif
