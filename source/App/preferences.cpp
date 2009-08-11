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

#include "universal_include.h"

#include "App/app.h"
#include "App/preferences.h"
#include "App/resource.h"
#include "App/string_utils.h"
#include "App/text_stream_readers.h"

Preferences *g_prefsManager = NULL;

PrefsItem::PrefsItem()
:   m_key(NULL),
    m_str(NULL),
    m_int(0)
{
}

PrefsItem::PrefsItem(char *_line)
:    m_str(NULL)
{
    // Get key
    char *key = _line;
    while (!isalnum(*key) && *key != '\0')        // Skip leading whitespace
    {
        key++;
    }
    char *c = key;
    while (isalnum(*c))                            // Find the end of the key word
    {
        c++;
    }
    *c = '\0';
    m_key = newStr(key);

    // Get value
    char *value = c + 1;
    while (isspace(*value) || *value == '=')
    {
        if (value == '\0') break;
        value++;
    }

    // Is value a number?
    if (value[0] == '-' || isdigit(value[0]))
    {
        // Guess that number is an int
        m_type = TypeInt;

        // Verify that guess
        c = value;
        int numDots = 0;
        while (*c != '\0')
        {
            if (*c == '.')
            {
                ++numDots;
            }
            ++c;
        }
        if( numDots == 1 ) m_type = TypeFloat;
        else if(  numDots > 1 ) m_type = TypeString;


        // Convert string into a real number
        if      (m_type == TypeFloat)        m_float = (float)atof(value);
        else if (m_type == TypeString)      m_str = newStr(value);
        else                                m_int = atoi(value);
    }
    else
    {
        m_type = TypeString;
        m_str = newStr(value);
    }
}

PrefsItem::PrefsItem(char const *_key, char const *_str)
:   m_type(TypeString)
{
    m_key = newStr(_key);
    m_str = newStr(_str);
}

PrefsItem::PrefsItem(char const *_key, float _float)
:   m_type(TypeFloat),
    m_str(NULL),
    m_float(_float)
{
    m_key = newStr(_key);
}

PrefsItem::PrefsItem(char const *_key, int _int)
:    m_type(TypeInt),
    m_str(NULL),
    m_int(_int)
{
    m_key = newStr(_key);
}

PrefsItem::~PrefsItem()
{
    delete [] m_key; m_key = NULL;
    delete [] m_str; m_str = NULL;
}


Preferences::Preferences(char const *_filename)
{
    m_filename = newStr(_filename);

    Load();

}

Preferences::Preferences(std::string const &_filename)
{
    m_filename = newStr(_filename.c_str());

    Load();
}

Preferences::~Preferences()
{
    delete [] m_filename; m_filename = NULL;
    Clear();
}

bool Preferences::IsLineEmpty(char const *_line)
{
    while (_line[0] != '\0')
    {
        if (_line[0] == '#') return true;
        if (isalnum(_line[0])) return false;
        ++_line;
    }

    return true;
}

void Preferences::CreateDefaultValues()
{

    // We default to the best possible preferences for performance and
    // so forth on the latest-and-greatest machines.

    AddLine( "TextureCompression = 0" );
    AddLine( "TextureRectangles = 0" );
	// AddLine ( "RenderMode = 0" );

    AddLine( "\n" );

	AddLine ( "IgnoreDataFiles = 0" );
	AddLine ( "DumpOpenGLInfo = 0" );

	AddLine ( "\n" );

#ifdef INTERNAL_BUILD
    AddLine( "ScreenWindowed = 1" );
#else
    AddLine( "ScreenWindowed = 0" );
#endif
    AddLine( "ScreenWidth = 0" );
    AddLine( "ScreenHeight = 0" );
    AddLine( "ScreenColourDepth = 32" );
    AddLine( "WaitVerticalRetrace = 1" );

	AddLine( "\n" );

	// AddLine( "SurfaceSplitFactor = 32" );

    // AddLine( "\n" );

    AddLine( "SoundChannels = 32" );
    AddLine( "SoundMixFreq = 22050" );
    AddLine( "SoundBufferSize = 512" );

    AddLine( "\n" );

    // Override the defaults above with stuff from a default preferences file
    if ( g_app && g_app->m_resource )
    {
        TextReader *reader = g_app->m_resource->GetTextReader( "default_preferences.txt" );
        if ( reader && reader->IsOpen() )
        {
            while ( reader->ReadLine() )
            {
                AddLine( reader->GetRestOfLine(), true );
            }
        }
        delete reader;
    }

}

void Preferences::Load(char const *_filename)
{
    if (!_filename) _filename = m_filename;

    Data::DArray<PrefsItem *> *items = m_items.ConvertToDArray();
    for ( size_t i = 0; i < items->size(); i++ )
        if ( items->valid(i) )
            delete items->get(i);
    delete items;
    m_items.empty();

    // Try to read preferences if they exist
    FILE *in = fopen(_filename, "r");

    if( !in )
    {
        // Probably first time running the game
        CreateDefaultValues();
    }
    else
    {
        char line[256];
        while (fgets(line, 256, in) != NULL)
        {
            AddLine( line );
        }
        fclose(in);
    }

    if ( m_items.size() < 1 ) CreateDefaultValues();

#ifdef DEMOBUILD
    AddLine( OTHER_DIFFICULTY " = 1", true );
#endif
}

void Preferences::SaveItem(FILE *out, PrefsItem *_item)
{
    switch (_item->m_type)
    {
        case PrefsItem::TypeFloat:
            fprintf(out, "%s = %.2f\n", _item->m_key, _item->m_float);
            break;
        case PrefsItem::TypeInt:
            fprintf(out, "%s = %d\n", _item->m_key, _item->m_int);
            break;
        case PrefsItem::TypeString:
            fprintf(out, "%s = %s\n", _item->m_key, _item->m_str);
            break;
    }
    _item->m_hasBeenWritten = true;
}

void Preferences::Save()
{
    // We've got a copy of the plain text from the prefs file that we initially
    // loaded in the variable m_fileText. We use that file as a template with
    // which to create the new save file. Updated prefs items values are looked up
    // as it their turn to be output comes around. When we've finished we then
    // write out all the new prefs items because they didn't exist in m_fileText.

	size_t i;

    // First clear the "has been written" flags on all the items
    Data::DArray<PrefsItem *> *items = m_items.ConvertToDArray();
    for ( i = 0; i < items->size(); ++i )
    {
        if ( items->valid ( i ) )
        {
            items->get(i)->m_hasBeenWritten = false;
        }
    }
    delete items;

    // Now use m_fileText as a template to write most of the items
    FILE *out = fopen(m_filename, "w");

    // If we couldn't open the prefs file for writing then just silently fail -
    // it's better than crashing.
    if (!out)
    {
        return;
    }

    for ( i = 0; i < m_fileText.size(); ++i )
    {
        if ( !m_fileText.valid ( i ) ) continue;
        char const *line = m_fileText[i];
        if (IsLineEmpty(line))
        {
            fprintf(out, "%s", line);
        }
        else
        {
            char const *c = line;
            char const *keyStart = NULL;
            char const *keyEnd = NULL;
            while (*c != '=')
            {
                if (keyStart)
                {
                    if (!isalnum(c[0]))
                    {
                        keyEnd = c;
                    }
                }
                else
                {
                    if (isalnum(c[0]))
                    {
                        keyStart = c;
                    }
                }
                ++c;
            }
            char key[128];
            int keyLen = keyEnd - keyStart;
            strncpy(key, keyStart, keyLen);
            key[keyLen] = '\0';
            PrefsItem *item = m_items.find(key, NULL);
			CrbReleaseAssert ( item != NULL );
            SaveItem(out, item);
        }
    }


    // Finally output any items that haven't already been written
    items = m_items.ConvertToDArray();
    for ( i = 0; i < items->size(); ++i )
    {
        if ( items->valid ( i ) )
        {
            PrefsItem *item = items->get ( i );
            if ( !item->m_hasBeenWritten )
            {
                SaveItem(out, item);
            }
        }
    }
    delete items;

    fclose(out);
}

void Preferences::Clear()
{
    Data::DArray<PrefsItem *> *items = m_items.ConvertToDArray();
	size_t i;
    for ( i = 0; i < items->size(); i++ )
        if ( items->valid(i) )
            delete items->get(i);
    delete items;
    m_items.empty();
    for ( i = 0; i < m_fileText.size(); i++ )
        if ( m_fileText.valid ( i ) )
            delete m_fileText.get ( i );
}

float Preferences::GetFloat(char const *_key, float _default) const
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item ) return _default;
    if (item->m_type != PrefsItem::TypeFloat) return _default;
    return item->m_float;
}

int Preferences::GetInt(char const *_key, int _default) const
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item ) return _default;
    if (item->m_type != PrefsItem::TypeInt) return _default;
    return item->m_int;
}

const char *Preferences::GetString(char const *_key, const char *_default) const
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item ) return _default;
    if (item->m_type != PrefsItem::TypeString) return _default;
    return item->m_str;
}

void Preferences::SetString(char const *_key, char const *_string)
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item )
    {
        item = new PrefsItem(_key, _string);
        m_items.insert ( item->m_key, item );
    }
    else
    {
        CrbDebugAssert ( item->m_type == PrefsItem::TypeString );
        char *newString = newStr(_string);
        delete [] item->m_str; item->m_str = NULL;
        // Note by Chris:
        // The incoming value of _string might also be item->m_str
        // So it is essential to copy _string before freeing item->m_str
        item->m_str = newString;
    }
}

void Preferences::SetFloat(char const *_key, float _float)
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item )
    {
        item = new PrefsItem ( _key, _float );
        m_items.insert ( item->m_key, item );
    }
    else
    {
        CrbDebugAssert ( item->m_type == PrefsItem::TypeFloat );
        item->m_float = _float;
    }
}

void Preferences::SetInt(char const *_key, int _int)
{
	PrefsItem *item = m_items.find ( _key, NULL );
    if ( !item )
    {
        item = new PrefsItem(_key, _int);
        m_items.insert ( item->m_key, item );
    }
    else
    {
        CrbDebugAssert ( item->m_type == PrefsItem::TypeInt );
        item->m_int = _int;
    }
}

void Preferences::AddLine(char const*_line, bool _overwrite)
{
    if ( !_line )
        return;

    bool saveLine = true;

    if (!IsLineEmpty(_line))                // Skip comment lines and blank lines
    {
        char *localCopy = newStr( _line );
        char *c = strchr(localCopy, '\n');
        if (c)
            *c = '\0';

        PrefsItem *item = new PrefsItem(localCopy);

		PrefsItem *idx = m_items.find ( item->m_key, NULL );
        if ( _overwrite && idx ) {
            delete idx;
            m_items.erase ( item->m_key );
            saveLine = false;
        }

        m_items.insert ( item->m_key, item );
        delete [] localCopy; localCopy = NULL;
    }

    if ( saveLine ) {
        char *lineCopy = newStr(_line);
        m_fileText.insert ( lineCopy );
    }
}

bool Preferences::DoesKeyExist(char const *_key)
{
    return m_items.exists ( _key );
}
