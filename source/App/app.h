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

#ifndef __app_h_included
#define __app_h_included

#include "App/resource.h"

//! The application class.
/*!
	The App class handles some of the basic things needed to run
	an application cross-platform, especially in relation to file
	and resource management.
 */
class App {

protected:
    char *m_appPath;
    char *m_appSupportPath;
    char *m_resourcePath;

public:
    Resource                      *m_resource;

public:
    App ();
    virtual ~App();

	//! Create a directory at the specified path.
	/*!
		Non-recursively creates a directory.
		\param _path The path of the directory to create.
	 */
    virtual void                   CreateDirectory ( const char *_path );

	//! Gets the application's resource directory.
	/*!
		\return The location where application resources are stored.
	 */
    virtual const char            *GetResourcePath ();

	//! Gets the application executable's directory.
	/*!
		\return The location where the application's executable is.
	 */
    virtual const char            *GetApplicationPath ();

	//! Gets the application support directory.
	/*!
		\return The location where any new application resources should be stored.
	 */
    virtual const char            *GetApplicationSupportPath ();

};

extern App *g_app;

#endif
