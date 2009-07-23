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

#ifndef __included_opengl_h
#define __included_opengl_h

#if defined(_DEBUG)
#define CATCH_OPENGL_ERRORS
#endif

#ifdef CATCH_OPENGL_ERRORS
#define ASSERT_OPENGL_ERRORS { \
        GLenum errval = glGetError(); \
        if ( errval != GL_NO_ERROR ) \
        { \
            g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY ); \
            g_console->WriteLine ( "ERROR: glGetError() returned 0x%04x.", errval ); \
            g_console->SetColour (); \
        } \
        CrbReleaseAssert ( errval == GL_NO_ERROR ); \
    }
#else
#define ASSERT_OPENGL_ERRORS
#endif

// these were at one point set to -1 and -2
// however, surface IDs are unsigned
#define INVALID_SURFACE_ID 0xFFFFFFFF
#define SCREEN_SURFACE_ID  0xFFFFFFFE

typedef enum
{
    OPENGL_USE_TEXTURE_RECTANGLES,
    OPENGL_TEX_ALLOW_NPOT,
    OPENGL_TEX_S3_COMPRESSION,
    OPENGL_TEX_3DFX_COMPRESSION,
    OPENGL_TEX_FORCE_SQUARE
} openglSetting;

typedef enum
{
    RENDER_PATH_VERTEX_ARRAY = 0
} renderPath;

class OpenGL
{
private:
    Uint16                              m_version[8];
    bool                                m_textureEnabled;
    char                               *m_extensionsString;
    char                               *m_versionString;
    char                               *m_vendorString;
    char                               *m_rendererString;
    Data::AVLTree<const char *, char>   m_extensions;
    Data::AVLTree<openglSetting, bool>  m_settings;
    Data::DStack<GLuint>                m_freeTextures;
    bool                                m_vboEnabled;

    renderPath                          m_renderPath;

    GLuint                              m_boundTexture;

    bool m_clientStateVertexArray;
    bool m_clientStateTexCoordArray;

    void FillTextureStack();
    void SetupExtensions();
    void SetupVersion();

public:
    OpenGL();
    ~OpenGL();

    void ActivateTextureRect();
    void DeactivateTextureRect();

    void ActivateWhiteWithAlpha ( Uint8 alpha );
    void ActivateColour ( Uint32 col );

    void VertexArrayStatePrimitive();
    void VertexArrayStateTexture();
    void VertexArrayStateOff();

    bool IsTextureBound ( GLuint _textureID ) const;
    void BindTexture ( GLuint _textureID );

    bool ExtensionIsSupported ( const char *_extension );
    const char *GetVendor() const;
    const char *GetRenderer() const;
    const char *GetVersion() const;
    Uint16 GetVersionMajor() const;
    Uint16 GetVersionMinor() const;

    Uint16 GetMaximumTextureSize() const;

    renderPath GetRenderPath() const;

    bool GetSetting ( openglSetting _setting, bool _default ) const;
    void SetSetting ( openglSetting _setting, bool _value );

    GLenum GetTextureTarget() const;
    GLint  GetInternalFormat24() const;
    GLint  GetInternalFormat32() const;

    GLuint GetFreeTexture ();
    void   FreeTexture ( GLuint _texture );

};

extern OpenGL *g_openGL;

#endif
