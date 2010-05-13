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

#ifndef __included_arc_version_h
#define __included_arc_version_h

namespace Cerberus
{
	namespace Version
	{
		//! The short version string.
		/*!
		 * The short version format is %d.%d.%d (<major>.<minor>.<revision>).
		 * \return The version number of the CrissCross library.
		 */
		const char *ShortVersion();

		//! The long version string.
		/*!
		 * The long version can currently be in a couple different forms, and
		 * the formats may change across versions, so don't make much effort to
		 * parse these out:
		 *    %d.%d.%d-%d-g%07x (<major>.<minor>.<revision>-<build>-g<commit id>)
		 *    %d.%d.%d-rc%d-%d-g%07x (<major>.<minor>.<revision>-rc<rc number>-<build>-g<commit id>)
		 * \return The version number of the CrissCross library.
		 */
		const char *LongVersion();

		/*!
		 * \return The major version number (i.e. in v1.2.3.4, it would be '1').
		 */
		int Major();

		/*!
		 * \return The minor version number (i.e. in v1.2.3.4, it would be '2').
		 */
		int Minor();

		/*!
		 * \return The revision version number (i.e. in v1.2.3.4, it would be '3').
		 */
		int Revision();

		/*!
		 * \return The build number (i.e. in v1.2.3.4, it would be '4').
		 */
		int Build();
	}
}

#endif
