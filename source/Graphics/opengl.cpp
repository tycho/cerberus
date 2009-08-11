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

#include "App/preferences.h"
#include "Graphics/opengl.h"

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
#    pragma comment (lib, "opengl32.lib")
#endif

#ifndef GL_TEXTURE_RECTANGLE_ARB
#    define GL_TEXTURE_RECTANGLE_ARB            0x84F5
#endif

OpenGL *g_openGL = NULL;

OpenGL::OpenGL()
:  m_renderPath(RENDER_PATH_VERTEX_ARRAY),
   m_boundTexture(0)
{
    CrbReleaseAssert ( g_openGL == NULL );
    m_vendorString     = cc_strdup((const char *)glGetString ( GL_VENDOR     ));
    m_rendererString   = cc_strdup((const char *)glGetString ( GL_RENDERER   ));
    m_versionString    = cc_strdup((const char *)glGetString ( GL_VERSION    ));
    m_extensionsString = cc_strdup((const char *)glGetString ( GL_EXTENSIONS ));
    SetupExtensions();
    SetupVersion();
}

OpenGL::~OpenGL()
{
    while ( m_freeTextures.count() )
    {
        GLuint texid = m_freeTextures.pop();
        glDeleteTextures ( 1, &texid );
    }
    free ( m_vendorString );     m_vendorString     = NULL;
    free ( m_rendererString );   m_rendererString   = NULL;
    free ( m_versionString );    m_versionString    = NULL;
    free ( m_extensionsString ); m_extensionsString = NULL;
}

void OpenGL::SetupVersion()
{
	CrbDebugAssert ( this );
    Uint16 index = 0;
    memset ( m_version, 0, sizeof ( m_version ) );
    char *tmp = cc_strdup(m_versionString);
    char *ptr = strtok ( tmp, "." );
    do
    {
        if ( !ptr ) break;
        m_version[index++] = atoi ( ptr );
    } while ( index < 8 && ( ptr = strtok ( NULL, "." ) ) != NULL );
    free ( tmp );
}

void OpenGL::SetupExtensions()
{
	CrbDebugAssert ( this );
    //
    // Find the actual extensions and add them to the tree.
    char *ptr = strtok ( m_extensionsString, " " );
    do
    {
        m_extensions.insert ( ptr, 1 );
    } while ( ( ptr = strtok ( NULL, " " ) ) != NULL );

    if ( g_prefsManager->GetInt ( "DumpOpenGLInfo", 0 ) != 0 )
    {
        //
        // We want to print out an OpenGL extension list along with
        // graphics card information.

        g_console->Write ( "Saving OpenGL information... " );

        FILE *file = fopen ( "opengl-info.txt", "wt" );
        if ( !file ) {
            g_console->WriteLine ( "FAILED" );
            return;
        }
        fprintf ( file, "OpenGL Vendor: %s\nOpenGL Renderer: %s\nOpenGL Version: %s\n\n"
            "Supported OpenGL Extensions\n\n",
            m_vendorString, m_rendererString, m_versionString );

        //
        // Convert to DArray because the spec does not require that
        // the extension list be given sorted, and we want the output
        // to be sorted.
        Data::DArray<const char *> *data = m_extensions.ConvertIndexToDArray();
        for ( size_t i = 0; i < data->size(); i++ )
        {
            if ( !data->valid ( i ) ) continue;
            fprintf ( file, "%s\n", data->get ( i ) );
        }
        delete data;

        fclose ( file );
        g_console->WriteLine ( "OK" );
    }

    int renderPreference = g_prefsManager->GetInt ( "RenderMode", 0 );
    if ( renderPreference < m_renderPath && renderPreference >= 0 )
    {
        m_renderPath = (renderPath)renderPreference;
    }
}

bool OpenGL::ExtensionIsSupported ( const char *_extension )
{
	CrbDebugAssert ( this );
    return m_extensions.exists ( _extension );
}

void OpenGL::FillTextureStack ()
{
	CrbDebugAssert ( this );
    GLuint textures[64];
    glGenTextures ( 64, textures );
    ASSERT_OPENGL_ERRORS;
    for ( int i = 0; i < 64; i++ )
        m_freeTextures.push ( textures[i] );
}

GLuint OpenGL::GetFreeTexture ()
{
	CrbDebugAssert ( this );
    if ( !m_freeTextures.count() )
        FillTextureStack();
    CrbReleaseAssert ( m_freeTextures.count() );
    return m_freeTextures.pop();
}

void OpenGL::FreeTexture ( GLuint _texture )
{
	CrbDebugAssert ( this );
    m_freeTextures.push ( _texture );
}

Uint16 OpenGL::GetVersionMajor() const
{
	CrbDebugAssert ( this );
    return m_version[0];
}

Uint16 OpenGL::GetVersionMinor() const
{
	CrbDebugAssert ( this );
    return m_version[1];
}

const char *OpenGL::GetRenderer() const
{
	CrbDebugAssert ( this );
    return m_rendererString;
}

const char *OpenGL::GetVersion() const
{
    return m_versionString;
}

const char *OpenGL::GetVendor() const
{
	CrbDebugAssert ( this );
    return m_vendorString;
}

Uint16 OpenGL::GetMaximumTextureSize() const
{
	CrbDebugAssert ( this );
    static GLint maxTextureSize = -1;
    if ( maxTextureSize == -1 )
    {
        glGetIntegerv ( GL_MAX_TEXTURE_SIZE, &maxTextureSize );
        ASSERT_OPENGL_ERRORS;
    }
    return maxTextureSize;
}

renderPath OpenGL::GetRenderPath() const
{
	CrbDebugAssert ( this );
    return m_renderPath;
}

void OpenGL::VertexArrayStatePrimitive ()
{
	CrbDebugAssert ( this );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
}

void OpenGL::VertexArrayStateTexture ()
{
	CrbDebugAssert ( this );
    glEnableClientState ( GL_VERTEX_ARRAY );
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
}

void OpenGL::VertexArrayStateOff ()
{
	CrbDebugAssert ( this );
    glDisableClientState ( GL_VERTEX_ARRAY );
    glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
}

void OpenGL::BindTexture ( GLuint _textureID )
{
	CrbDebugAssert ( this );
    CrbReleaseAssert ( _textureID != SCREEN_SURFACE_ID );
    CrbReleaseAssert ( _textureID != INVALID_SURFACE_ID );
    CrbReleaseAssert ( _textureID != 0 );
    glBindTexture ( GetTextureTarget(), _textureID );
}

GLenum OpenGL::GetTextureTarget() const
{
	CrbDebugAssert ( this );
    if ( GetSetting ( OPENGL_USE_TEXTURE_RECTANGLES, false ) )
        return GL_TEXTURE_RECTANGLE_ARB;
    else
        return GL_TEXTURE_2D;
}

GLint OpenGL::GetInternalFormat24() const
{
	CrbDebugAssert ( this );
    if ( GetSetting ( OPENGL_TEX_S3_COMPRESSION, false ) )
        return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    if ( GetSetting ( OPENGL_TEX_3DFX_COMPRESSION, false ) )
        return GL_COMPRESSED_RGB_FXT1_3DFX;
    return GL_RGB;
}

GLint OpenGL::GetInternalFormat32() const
{
	CrbDebugAssert ( this );
    if ( GetSetting ( OPENGL_TEX_S3_COMPRESSION, false ) )
        return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    if ( GetSetting ( OPENGL_TEX_3DFX_COMPRESSION, false ) )
        return GL_COMPRESSED_RGBA_FXT1_3DFX;
    return GL_RGBA;
}

void OpenGL::SetSetting ( openglSetting _setting, bool _value )
{
	CrbDebugAssert ( this );
    if ( m_settings.exists ( _setting ) )
        m_settings.replace ( _setting, _value );
    else
        m_settings.insert ( _setting, _value );
}

bool OpenGL::GetSetting ( openglSetting _setting, bool _default ) const
{
	CrbDebugAssert ( this );
    bool item = m_settings.find ( _setting, _default );
    return item;
}
