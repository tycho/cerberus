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

#ifndef __included_preferences_h
#define __included_preferences_h

//! @cond
class PrefsItem
{
public:
    char        *m_key;

    enum
    {
        TypeString,
        TypeFloat,
        TypeInt
    };

    int            m_type;
    char          *m_str;
    union {
        int        m_int;
        float      m_float;
    };

    bool           m_hasBeenWritten;

    PrefsItem      ();
    PrefsItem      ( char *_line );
    PrefsItem      ( char const *_key, char const *_str );
    PrefsItem      ( char const *_key, float _float );
    PrefsItem      ( char const *_key, int _int );
    ~PrefsItem     ();
};
//! @endcond

//! The preferences manager.
class Preferences
{
private:
    Data::RedBlackTree <const char *, PrefsItem *>  m_items;
    Data::DArray<char *>                            m_fileText;
    char *m_filename;

    bool IsLineEmpty ( char const *_line );
    void SaveItem ( FILE *out, PrefsItem *_item );

    void CreateDefaultValues();

public:
    Preferences         ( char const *_filename );
    Preferences         ( std::string const &_filename );
    ~Preferences        ();

	//! Loads the preferences from a text file.
	/*!
		\param _filename The file to read from. If NULL, reads from the location specified in the constructor.
	 */
    void Load            (char const *_filename = NULL);

	//! Saves the preferences to a text file.
    void Save            ();

	//! Clears the preference list.
    void Clear           ();

	//! Retrieves the contents of a preference item with the specified name.
	/*!
		\param _key The name of the preference to retrieve.
		\param _default The default value to return if the preference isn't found.
		\return If a matching preference is found, the value is returned. Otherwise, _default is returned.
	 */
    const char *GetString( char const *_key, const char *_default = NULL ) const;

	//! Retrieves the contents of a preference item with the specified name.
	/*!
		\param _key The name of the preference to retrieve.
		\param _default The default value to return if the preference isn't found.
		\return If a matching preference is found, the value is returned. Otherwise, _default is returned.
	 */
    float GetFloat       ( char const *_key, float _default = -1.0f ) const;

	//! Retrieves the contents of a preference item with the specified name.
	/*!
		\param _key The name of the preference to retrieve.
		\param _default The default value to return if the preference isn't found.
		\return If a matching preference is found, the value is returned. Otherwise, _default is returned.
	 */
    int   GetInt         ( char const *_key, int _default = -1 ) const;

    //! Sets or updates a string preference with the specified name.
	/*!
		\param _key The name of the preference to set or alter.
		\param _string The value to set for the preference.
	 */
    void SetString       ( char const *_key, char const *_string );

	//! Sets or updates a floating-point preference with the specified name.
	/*!
		\param _key The name of the preference to set or alter.
		\param _val The value to set for the preference.
	 */
    void SetFloat        ( char const *_key, float _val );

	//! Sets or updates a integer preference with the specified name.
	/*!
		\param _key The name of the preference to set or alter.
		\param _val The value to set for the preference.
	 */
    void SetInt          ( char const *_key, int _val );

	//! Adds a line to the preferences file.
	/*!
		\param _line The text of the line to add.
		\param _overwrite If true, overrides the matching
		       preference. If false, doesn't alter the existing preference.
	 */
    void AddLine         ( char const *_line, bool _overwrite = false );

	//! Checks if a preference exists by the given name.
	/*!
		\param _key The name of the preference to check.
		\return True if a matching preference was found, false otherwise.
	 */
    bool DoesKeyExist    ( char const *_key );
};

extern Preferences *g_prefsManager;

#endif
