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

#ifndef __included_text_stream_readers_h
#define __included_text_stream_readers_h

// This is an ABSTRACT BASE class. If you want to actually tokenise some text,
// I recommend either TextFileReader or TextDataReader.
class TextReader
{
protected:
    char           m_seperatorChars[16];
    char           m_filename[256];

    int            m_offsetIndex;
    int            m_fileEncrypted;    // -1 means we don't know yet. 0 means no. 1 means yes.

    void           DoubleMaxLineLen();
    void           CleanLine();            // Decrypt, strip comments and scan for conflict markers

public:
    int            m_tokenIndex;
    char          *m_line;
    unsigned int   m_maxLineLen;        // Doesn't include '\0' - m_line points to an array one byte larger than this
    unsigned int   m_lineNum;

    TextReader         ();
    virtual ~TextReader();

    virtual bool IsOpen          () = 0;
    virtual bool ReadLine        () = 0;    // Returns false on EOF, true otherwise
    bool         TokenAvailable  ();
    char        *GetNextToken    ();
    char        *GetRestOfLine   ();

    char const  *GetFilename     ();

    void SetSeperatorChars       ( char const *_seperatorChars );
    void SetDefaultSeperatorChars();
};


class TextFileReader: public TextReader
{
protected:
    FILE            *m_file;

public:
    TextFileReader                (char const *_filename);
    TextFileReader                (std::string const &_filename);
    ~TextFileReader               ();

    bool IsOpen                   ();
    bool ReadLine                 ();
};


class TextDataReader: public TextReader
{
protected:
    char const         *m_data;
    unsigned int        m_dataSize;
    unsigned int        m_offset;

public:
    TextDataReader              (char const *_data, unsigned int _dataSize, char const *_filename);

    bool IsOpen                 ();
    bool ReadLine               ();
};


#endif
