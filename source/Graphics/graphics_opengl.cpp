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

#ifdef ENABLE_OPENGL

#include "App/app.h"
#include "App/preferences.h"
#include "App/version.h"
#include "Graphics/font_opengl.h"
#include "Graphics/graphics_opengl.h"
#include "Graphics/opengl.h"

OpenGLGraphics::OpenGLGraphics()
 : Graphics(),
   m_sdlScreen(NULL)
{
    int retval = SDL_Init ( SDL_INIT_VIDEO );
    CrbReleaseAssert ( retval == 0 );
}

OpenGLGraphics::~OpenGLGraphics()
{
	size_t i;
    for ( i = 0; i < m_textures.size(); i++ )
    {
        if ( m_textures.valid(i) )
        {
            OpenGLTexture *tex = m_textures[i];
            m_textures.remove ( i );
            delete tex;
        }
    }
	m_fonts.flush();
    delete m_sdlScreen; m_sdlScreen = NULL;
    delete g_openGL;
    g_openGL = NULL;
    SDL_Quit ();
}

const char *OpenGLGraphics::RendererName()
{
	static char renderer[64] = {'\0'};
	if ( !strlen ( renderer ) )
	{
		sprintf ( renderer, "OpenGL 1.1 (engine v%d.%d)",
			m_rendererVersionMajor, m_rendererVersionMinor );
	}
	return renderer;
}

Uint32 OpenGLGraphics::CreateDisplayList()
{
	Uint32 ret = glGenLists(1);
	ASSERT_OPENGL_ERRORS;
	return ret;
}

void OpenGLGraphics::DestroyDisplayList(Uint32 _list)
{
	if (_list == 0) return;
	glDeleteLists(_list, 1);
	ASSERT_OPENGL_ERRORS;
}

void OpenGLGraphics::BeginDisplayList(Uint32 _list)
{
	if (_list == 0) return;
	glNewList(_list, GL_COMPILE_AND_EXECUTE);
	ASSERT_OPENGL_ERRORS;
}

void OpenGLGraphics::EndDisplayList(Uint32 _list)
{
	if (_list == 0) return;
	glEndList();
	ASSERT_OPENGL_ERRORS;
}

void OpenGLGraphics::CallDisplayList(Uint32 _list)
{
	if (_list == 0) return;
	CrbReleaseAssert(glIsList(_list));
	glCallLists(1, GL_UNSIGNED_INT, &_list);
	ASSERT_OPENGL_ERRORS;
}

Uint32 OpenGLGraphics::CreateFont(const char *_fontFace, int _height)
{
#ifdef ENABLE_FONTS
	char fontpath[512];
	MemMappedFile *file = NULL;

	sprintf(fontpath, "fonts/%s.ttf", _fontFace);
	file = g_app->m_resource->GetUncompressedFile(fontpath);

	if ( !file ) {
#ifdef TARGET_OS_WINDOWS
		char windir[128];
		GetWindowsDirectory(windir, 128);
		sprintf(fontpath, "%s/fonts/%s.ttf", windir, _fontFace);
#elif defined(TARGET_OS_MACOSX)
		sprintf(fontpath, "/Library/Fonts/%s.ttf", windir, _fontFace);
#endif
		file = g_app->m_resource->GetUncompressedFile(fontpath);
	}

	CoreAssert(file);

	OpenGLFont *font = new OpenGLFont(file->m_data, file->m_size);
	CoreAssert(font);

	font->SetFontSize(_height);

	return m_fonts.insert(font);
#else
	return 0;
#endif
}

void OpenGLGraphics::DrawText ( Uint32 _font, Uint16 _x, Uint16 _y, Uint32 _color, const char *_text )
{
#ifdef ENABLE_FONTS
	OpenGLFont *font = m_fonts[_font];
	CoreAssert ( font );

	font->Draw(_x, _y, _text, _color);
#endif
}

void OpenGLGraphics::DrawRect ( SDL_Rect *_destRect, Uint32 _color )
{
	CoreAssert ( _destRect );

	g_openGL->ActivateColour ( _color );
    g_openGL->DeactivateTextureRect ();
    g_openGL->VertexArrayStatePrimitive ();
    
    m_vertexArray[0] = _destRect->x;
    m_vertexArray[1] = _destRect->y;
    m_vertexArray[2] = _destRect->x + _destRect->w;
    m_vertexArray[3] = _destRect->y;
    m_vertexArray[4] = _destRect->x + _destRect->w;
    m_vertexArray[5] = _destRect->y + _destRect->h;
    m_vertexArray[6] = _destRect->x;
    m_vertexArray[7] = _destRect->y + _destRect->h;

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
	glEnable(GL_LINE_SMOOTH);
    ASSERT_OPENGL_ERRORS;
}

void OpenGLGraphics::ShowCursor ( bool _show )
{
    SDL_ShowCursor ( _show );
}

int OpenGLGraphics::SetSurfaceAlpha ( Uint32 _surfaceID, Uint8 alpha )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
    
    m_textures.get ( _surfaceID )->SetAlpha ( alpha );
    
    return 0;
}

void OpenGLGraphics::DrawLine ( Uint32 _surfaceID, Uint32 _color, int _startX, int _startY, int _stopX, int _stopY )
{
    CoreAssert ( _surfaceID == SCREEN_SURFACE_ID );

    g_openGL->VertexArrayStatePrimitive ();
    g_openGL->DeactivateTextureRect ();
    m_vertexArray[0] = _startX;
    m_vertexArray[1] = _startY;
    m_vertexArray[2] = _stopX;
    m_vertexArray[3] = _stopY;
    _color |= FULL_ALPHA;
    g_openGL->ActivateColour ( _color );
    glDrawArrays ( GL_LINES, 0, 2 );
    ASSERT_OPENGL_ERRORS;
}


Uint32 OpenGLGraphics::GetPixel ( Uint32 _surfaceID, int x, int y )
{
    OpenGLTexture *tex = m_textures.get ( _surfaceID );
    return tex->GetPixel ( x, y );
}

void OpenGLGraphics::SetPixel ( Uint32 _surfaceID, int x, int y, Uint32 _color )
{
    if ( _surfaceID == SCREEN_SURFACE_ID )
    {
        g_openGL->VertexArrayStatePrimitive ();
        g_openGL->DeactivateTextureRect ();
        glDisable ( GL_BLEND );
        ASSERT_OPENGL_ERRORS;
#ifndef TARGET_OS_WINDOWS
        m_vertexArray[0] = x;
        m_vertexArray[1] = y;
        _color |= FULL_ALPHA;
        g_openGL->ActivateColour ( _color );
        glDrawArrays ( GL_POINTS, 0, 1 );
#else
        glRasterPos2i ( x, y );
        ASSERT_OPENGL_ERRORS;
        glDrawPixels ( 1, 1, GL_RGBA, GL_UNSIGNED_INT, &_color );
        ASSERT_OPENGL_ERRORS;
#endif
        glEnable ( GL_BLEND );
        ASSERT_OPENGL_ERRORS;
    }
    else
    {
        CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
        OpenGLTexture *tex = m_textures.get ( _surfaceID );
        tex->SetPixel ( x, y, _color );
        tex->Damage();
    }
}

Uint32 OpenGLGraphics::LoadImage ( const char *_filename, bool _isColorKeyed )
{
    
    CrbReleaseAssert ( _filename != NULL );

    // Load the image from RAM.
    SDL_Surface* src = g_app->m_resource->GetImage ( _filename ); // use SDL_Image to load the image
    CrbReleaseAssert ( src != NULL );
    Uint32 oldWidth = 0, oldHeight = 0;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    Uint32 targetW = src->w, targetH = src->h;

    if ( !g_openGL->GetSetting ( OPENGL_TEX_ALLOW_NPOT, false ) )
    {
        oldWidth = targetW, oldHeight = targetH;
        if ( !isPowerOfTwo ( targetW ) )
            targetW = nearestPowerOfTwo ( targetW );
        if ( !isPowerOfTwo ( targetH ) )
            targetH = nearestPowerOfTwo ( targetH );
        CrbReleaseAssert ( isPowerOfTwo ( targetW * targetH ) );
    }
    if ( g_openGL->GetSetting ( OPENGL_TEX_FORCE_SQUARE, false ) )
	{
		targetH = targetW = cc_max ( targetW, targetH );
	}

    OpenGLTexture *tex = new OpenGLTexture();
    Uint32 ret = m_textures.insert ( tex );

    tex->Dispose();
    tex->Create ( targetW, targetH, _isColorKeyed );

    CrbReleaseAssert ( tex->m_sdlSurface != NULL );

	if ( _isColorKeyed && m_colorKeySet )
    {
		SDL_FillRect ( tex->m_sdlSurface, NULL, ZERO_ALPHA & m_colorKey );
        SDL_SetColorKey ( tex->m_sdlSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, m_colorKey );
    }
    SDL_SetAlpha ( tex->m_sdlSurface, 0, SDL_ALPHA_OPAQUE );

    SDL_BlitSurface ( src, NULL, tex->m_sdlSurface, NULL );
    SDL_FreeSurface ( src );

    tex->Damage();

    return ret;
}

int OpenGLGraphics::DeleteSurface ( Uint32 _surfaceID )
{
    if ( !m_textures.valid ( _surfaceID ) ) return -1;
    
    OpenGLTexture *tex = m_textures.get ( _surfaceID );
    CrbReleaseAssert ( tex != NULL );
    delete tex;
    m_textures.remove ( _surfaceID );

    return 0;
}

Uint32 OpenGLGraphics::CreateSurface ( Uint32 _width, Uint32 _height, bool _isColorKeyed )
{
    OpenGLTexture *tex = new OpenGLTexture();
    tex->Create ( _width, _height, _isColorKeyed );
    
    Uint32 ret = m_textures.insert ( tex );
    
    return ret;
}

Uint16 OpenGLGraphics::GetMaximumTextureSize()
{
    return g_openGL->GetMaximumTextureSize();
}

int OpenGLGraphics::SetColorKey ( Uint32 _color )
{    
    CrbReleaseAssert ( m_sdlScreen != NULL );

    m_colorKey = _color;
    m_colorKeySet = true;
    
    return 0;
}

void OpenGLGraphics::ApplyColorKey ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

	OpenGLTexture *surface = m_textures.get ( _surfaceID );
	SDL_SetColorKey ( surface->m_sdlSurface, SDL_SRCCOLORKEY | SDL_RLEACCEL, m_colorKey );
}

int OpenGLGraphics::FillRect ( Uint32 _surfaceID, SDL_Rect *_destRect, Uint32 _color )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );

    if ( _color == m_colorKey )
        _color = m_colorKey & ZERO_ALPHA;
    
    if (_surfaceID == SCREEN_SURFACE_ID)
    {
        // fill a rectangle on screen
        g_openGL->ActivateColour ( _color );
        g_openGL->DeactivateTextureRect ();
        g_openGL->VertexArrayStatePrimitive ();
    
        if ( _destRect )
        {
            m_vertexArray[0] = _destRect->x;
            m_vertexArray[1] = _destRect->y;
            m_vertexArray[2] = _destRect->x + _destRect->w;
            m_vertexArray[3] = _destRect->y;
            m_vertexArray[4] = _destRect->x;
            m_vertexArray[5] = _destRect->y + _destRect->h;
            m_vertexArray[6] = _destRect->x + _destRect->w;
            m_vertexArray[7] = _destRect->y + _destRect->h;
        } else {
            m_vertexArray[0] = 0;
            m_vertexArray[1] = 0;
            m_vertexArray[2] = m_sdlScreen->m_sdlSurface->w;
            m_vertexArray[3] = 0;
            m_vertexArray[4] = 0;
            m_vertexArray[5] = m_sdlScreen->m_sdlSurface->h;
            m_vertexArray[6] = m_sdlScreen->m_sdlSurface->w;
            m_vertexArray[7] = m_sdlScreen->m_sdlSurface->h;
        }

        glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
        ASSERT_OPENGL_ERRORS;
        
        return 0;
    }
    else
    {
        CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
        OpenGLTexture *tex = m_textures.get ( _surfaceID );
        CrbReleaseAssert ( tex != NULL );

        int r = SDL_FillRect ( tex->m_sdlSurface, _destRect, _color );
        
        tex->Damage ();

        return r;
    }
}

int OpenGLGraphics::Blit ( Uint32 _sourceSurfaceID, SDL_Rect const *_sourceRect,
                           Uint32 _destSurfaceID,   SDL_Rect const *_destRect )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
        
    OpenGLTexture *fromSurface = NULL;
    OpenGLTexture *toSurface = NULL;

    SDL_Rect *sourceRect = NULL;
    SDL_Rect *destRect = NULL;

    if ( _sourceSurfaceID == SCREEN_SURFACE_ID )
    {
        // trying to blit from screen?
        // not at the moment, sadly
        return -1;
    }

    // Get the SDL surface for the source surface.
    CrbReleaseAssert ( m_textures.valid ( _sourceSurfaceID ) );
    fromSurface = m_textures.get ( _sourceSurfaceID );
    CrbReleaseAssert ( fromSurface != NULL );

    // Get the SDL surface for the destination surface.
    if ( _destSurfaceID != SCREEN_SURFACE_ID )
    {
        CrbReleaseAssert ( m_textures.valid ( _destSurfaceID ) );
        toSurface = m_textures.get ( _destSurfaceID );
        CrbReleaseAssert ( toSurface != NULL );
    } else {
        toSurface = m_sdlScreen;
    }

    // With SDL, you can have a NULL destination rectangle if you are just
    // writing to 0,0 and the max possible WxH on the surface.
    SDL_Rect nullDestRect;
    if ( !_destRect )
    {
        nullDestRect.x = 0; nullDestRect.y = 0;
        nullDestRect.w = m_sdlScreen->m_sdlSurface->w;
        nullDestRect.h = m_sdlScreen->m_sdlSurface->h;
        destRect = &nullDestRect;
    } else {
        memcpy ( &nullDestRect, _destRect, sizeof(SDL_Rect) );
        destRect = &nullDestRect;
    }

    // With SDL, you can have a NULL source rectangle if you are just
    // reading from 0,0 and the max possible WxH on the surface.
    SDL_Rect nullSourceRect;
    if ( !_sourceRect )
    {
        nullSourceRect.x = 0; nullSourceRect.y = 0;
        if ( g_openGL->GetSetting ( OPENGL_TEX_ALLOW_NPOT, false ) ) {
            nullSourceRect.w = fromSurface->m_sdlSurface->w;
            nullSourceRect.h = fromSurface->m_sdlSurface->h;
        } else {
            nullSourceRect.w = fromSurface->m_originalWidth;
            nullSourceRect.h = fromSurface->m_originalHeight;
        }
        sourceRect = &nullSourceRect;
    } else {
        memcpy ( &nullSourceRect, _sourceRect, sizeof(SDL_Rect) );
        sourceRect = &nullSourceRect;
    }

    if ( destRect->x > toSurface->m_sdlSurface->w ) {
        // This blit is completely off the surface.
        return 1;
    }
    if ( destRect->y > toSurface->m_sdlSurface->h ) {
        // This blit is completely off the surface.
        return 1;
    }

    // Is this blit is going to be partially off the surface?
    if ( destRect->x + sourceRect->w > toSurface->m_sdlSurface->w )
        sourceRect->w = toSurface->m_sdlSurface->w - destRect->x;
    if ( destRect->y + sourceRect->h > toSurface->m_sdlSurface->h )
        sourceRect->h = toSurface->m_sdlSurface->h - destRect->y;

    // With SDL, you don't have to specify the dest width/height. With OpenGL, we do.
    destRect->w = sourceRect->w;
    destRect->h = sourceRect->h;
    
    // Now we need to do the actual blit!
    if ( _destSurfaceID == SCREEN_SURFACE_ID )
    {
        fromSurface->Upload();

        // draw from sourceSurfaceID
        g_openGL->ActivateTextureRect();
        fromSurface->Bind();
        g_openGL->ActivateWhiteWithAlpha ( fromSurface->m_alpha );
        g_openGL->VertexArrayStateTexture ();

        short *vertexArray = m_vertexArray, *texCoordArrayi = m_texCoordArrayi;
        float *texCoordArrayf = m_texCoordArrayf;
        vertexArray = m_vertexArray;

        vertexArray[0] = destRect->x;
        vertexArray[1] = destRect->y;
        vertexArray[2] = destRect->x + destRect->w;
        vertexArray[3] = destRect->y;
        vertexArray[4] = destRect->x;
        vertexArray[5] = destRect->y + destRect->h;
        vertexArray[6] = destRect->x + destRect->w;
        vertexArray[7] = destRect->y + destRect->h;

        if ( g_openGL->GetSetting ( OPENGL_USE_TEXTURE_RECTANGLES, false ) )
        {
            texCoordArrayi[0] = sourceRect->x;
            texCoordArrayi[1] = sourceRect->y;
            texCoordArrayi[2] = sourceRect->x + sourceRect->w;
            texCoordArrayi[3] = sourceRect->y;
            texCoordArrayi[4] = sourceRect->x;
            texCoordArrayi[5] = sourceRect->y + sourceRect->h;
            texCoordArrayi[6] = sourceRect->x + sourceRect->w;
            texCoordArrayi[7] = sourceRect->y + sourceRect->h;
        }
        else
        {
            float w = (float)fromSurface->m_sdlSurface->w,
                  h = (float)fromSurface->m_sdlSurface->h;
            float x = (float)sourceRect->x,
                  y = (float)sourceRect->y;
            texCoordArrayf[0] = x / w;
            texCoordArrayf[1] = y / h;
            texCoordArrayf[2] = x / w + (float)sourceRect->w / w;
            texCoordArrayf[3] = y / h;
            texCoordArrayf[4] = x / w;
            texCoordArrayf[5] = y / h + (float)sourceRect->h / h;
            texCoordArrayf[6] = x / w + (float)sourceRect->w / w;
            texCoordArrayf[7] = y / h + (float)sourceRect->h / h;
        }
        
        glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );
        ASSERT_OPENGL_ERRORS;
        
        return 0;
    }
    else
    {

        // This is a very hackish way to do it, but the alpha settings
        // aren't preserved across blits for some reason, so this is
        // necessary!

        // Fill with fully opaque colour key.
        //SDL_FillRect ( toSurface->m_sdlSurface, destRect, FULL_ALPHA | m_colorKey );
        
        // Blit
        int res = SDL_BlitSurface ( fromSurface->m_sdlSurface, sourceRect, toSurface->m_sdlSurface, destRect );

        // Replace the fully opaque colour key with a fully transparent
        // colour key.
        //ReplaceColour ( _destSurfaceID, destRect, FULL_ALPHA | m_colorKey, ZERO_ALPHA & m_colorKey );
        
        // We want to upload the textures to graphics memory
        // later in order to make things fast.
        toSurface->Damage();
        
        return res;
    }

}

void OpenGLGraphics::ReplaceColour ( Uint32 _surfaceID, SDL_Rect *_destRect, Uint32 findcolor, Uint32 replacecolor )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    CrbReleaseAssert ( _surfaceID != SCREEN_SURFACE_ID );
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    m_textures.get ( _surfaceID )->ReplaceColour ( _destRect, findcolor, replacecolor );

}

SDL_PixelFormat *OpenGLGraphics::GetPixelFormat ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    
    if (_surfaceID == SCREEN_SURFACE_ID)
        return m_sdlScreen->m_sdlSurface->format;
    
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );
    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->format;
}

Uint32 OpenGLGraphics::GetSurfaceHeight ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    
    if ( _surfaceID == SCREEN_SURFACE_ID )
        return GetScreenHeight();
    
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->h;
}

Uint32 OpenGLGraphics::GetSurfaceWidth ( Uint32 _surfaceID )
{
    CrbReleaseAssert ( m_sdlScreen != NULL );
    
    if (_surfaceID == SCREEN_SURFACE_ID)
        return GetScreenWidth();
    
    CrbReleaseAssert ( m_textures.valid ( _surfaceID ) );

    SDL_Surface *surface = m_textures.get ( _surfaceID )->m_sdlSurface;
    CrbReleaseAssert ( surface != NULL );

    return surface->w;
}

Uint32 OpenGLGraphics::GetScreen ()
{
    return SCREEN_SURFACE_ID;
}

int OpenGLGraphics::SetWindowMode ( bool _windowed, Sint16 _width, Sint16 _height, Uint8 _colorDepth )
{
    CrbReleaseAssert ( m_sdlScreen == NULL );

#ifdef ENFORCE_RESOLUTION
    if ( _width < 640 || _width > 800 || _height < 480 || _height > 600 )
    {
        _width = 800;
        _height = 600;
    }
#endif

    if ( _colorDepth < 16 || _colorDepth > 32 ) _colorDepth = 16;

    m_windowed = _windowed;

    m_screenX = _width;
    m_screenY = _height;

    m_centerX = m_screenX / 2;
    m_centerY = m_screenY / 2;

    g_console->WriteLine ( "Setting up variables for OpenGL" );

    const SDL_VideoInfo* info = NULL;
    info = SDL_GetVideoInfo ();
    CrbReleaseAssert ( info != NULL );

    m_colorDepth = _colorDepth; 

    g_console->WriteLine ( "The requested color depth is %d, and we're using %d.", _colorDepth, m_colorDepth );
    g_console->WriteLine ( "Setting display mode of %dx%dx%d...", _width, _height, m_colorDepth );

    Uint32 flags = SDL_HWSURFACE | SDL_OPENGL;

    if ( !m_windowed ) flags |= SDL_FULLSCREEN;

    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute ( SDL_GL_SWAP_CONTROL, g_prefsManager->GetInt ( "WaitVerticalRetrace", 1 ) );
    SDL_GL_SetAttribute ( SDL_GL_RED_SIZE, m_colorDepth / 4 );
    SDL_GL_SetAttribute ( SDL_GL_GREEN_SIZE, m_colorDepth / 4 );
    SDL_GL_SetAttribute ( SDL_GL_BLUE_SIZE, m_colorDepth / 4 );
    SDL_GL_SetAttribute ( SDL_GL_ALPHA_SIZE, m_colorDepth / 4 );

    m_sdlScreen = new OpenGLTexture ( SDL_SetVideoMode ( _width, _height, m_colorDepth, flags ) );
    
    if ( !m_sdlScreen || !m_sdlScreen->m_sdlSurface )
    {
        g_console->WriteLine ( "SDL couldn't initialise properly: %s", SDL_GetError() );
        return -1;
    }

    m_sdlScreen->m_textureID = SCREEN_SURFACE_ID;

    char windowTitle[512];
	sprintf(windowTitle, "%s v%s", APP_NAME, Cerberus::Version::LongVersion());
    SDL_WM_SetCaption ( windowTitle, NULL );
#ifdef TARGET_OS_WINDOWS
    if ( _windowed )
    {
        HWND hwnd = FindWindow ( NULL, windowTitle );
        RECT workArea, window;
        GetWindowRect ( hwnd, &window ); 
        SystemParametersInfo ( SPI_GETWORKAREA, 0, &workArea, 0 );
        Uint32 left = workArea.right - (window.right - window.left) - 20;
        Uint32 top =  ( (workArea.top + workArea.bottom) - (window.bottom - window.top) ) / 2;
        SetWindowPos ( hwnd, HWND_TOP, left, top, 0, 0, SWP_NOSIZE );
    }
#endif

    info = SDL_GetVideoInfo();
    
    g_console->WriteLine ( "Display mode set successfully (%dx%dx%d).", info->current_w, info->current_h, info->vfmt->BitsPerPixel );
    g_console->WriteLine ();

    if ( !g_openGL )
        g_openGL = new OpenGL();
    CrbReleaseAssert ( g_openGL );

    bool testsPassed = true;

    g_console->Write ( "OpenGL vendor: " );
    g_console->SetColour ( IO::Console::FG_CYAN | IO::Console::FG_INTENSITY );
    g_console->WriteLine ( "%s", g_openGL->GetVendor() );
    g_console->SetColour ();
    g_console->Write ( "OpenGL renderer: " );
    g_console->SetColour ( IO::Console::FG_CYAN | IO::Console::FG_INTENSITY );
    g_console->WriteLine ( "%s", g_openGL->GetRenderer() );
    g_console->SetColour ();
    g_console->Write ( "OpenGL version: " );
    g_console->SetColour ( IO::Console::FG_CYAN | IO::Console::FG_INTENSITY );
    g_console->WriteLine ( "%s", g_openGL->GetVersion() );
    g_console->SetColour ();

    g_console->WriteLine ();

    g_console->Write ( "Supports OpenGL v1.1? " );

    bool ogl11Support = false;
    if ( g_openGL->GetVersionMajor() == 1 ) {
        if ( g_openGL->GetVersionMinor() >= 1 ) {
            ogl11Support = true;
        } else {
            ogl11Support = false;
        }
    } else if ( g_openGL->GetVersionMajor() > 1 ) {
        ogl11Support = true;
    } else {
        ogl11Support = false;
    }

    if ( ogl11Support )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
    }
    else
    {
        g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        testsPassed = false;
    }

    bool extensionIsSupported = false;

    g_console->Write ( "Supports texture rectangles? " );

    if ( g_openGL->ExtensionIsSupported ( "GL_EXT_texture_rectangle" ) ||
         g_openGL->ExtensionIsSupported ( "GL_ARB_texture_rectangle" ) ||
         g_openGL->ExtensionIsSupported ( "GL_NV_texture_rectangle" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        extensionIsSupported = true;
    }
    else
    {
        g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        extensionIsSupported = false;
    }
    
    if ( g_prefsManager->GetInt ( "TextureRectangles", 1 ) && extensionIsSupported )
    {
        g_openGL->SetSetting ( OPENGL_TEX_ALLOW_NPOT, true );
        g_openGL->SetSetting ( OPENGL_USE_TEXTURE_RECTANGLES, true );
        //m_textureType = GL_TEXTURE_RECTANGLE_ARB;
    } else {
        g_openGL->SetSetting ( OPENGL_TEX_ALLOW_NPOT, false );
        g_openGL->SetSetting ( OPENGL_USE_TEXTURE_RECTANGLES, false );
        //m_textureType = GL_TEXTURE_2D;
    }

    g_console->Write ( "Supports sufficiently sized textures? " );
    if ( GetMaximumTextureSize() >= 1024 )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
    } else {
        g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->WriteLine ( "ERROR: OpenGL engine needs support for large texture sizes." );
        g_console->SetColour ();
        testsPassed = false;
	}

	// Support for this on ATI hardware seems dodgy at best.
    g_console->Write ( "Supports non power-of-two textures? " );
    if ( g_openGL->ExtensionIsSupported ( "ARB_texture_non_power_of_two" ) &&
        !strstr ( g_openGL->GetVendor(), "ATI" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        g_openGL->SetSetting ( OPENGL_TEX_ALLOW_NPOT, true );
    } else {
        g_console->SetColour ( IO::Console::FG_RED | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        g_openGL->SetSetting ( OPENGL_TEX_ALLOW_NPOT, false );
	}

    g_console->Write ( "Supports 3DFX texture compression? " );
    if ( g_openGL->ExtensionIsSupported ( "GL_3DFX_texture_compression_FXT1" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        extensionIsSupported = true;
    } else {
        g_console->SetColour ( IO::Console::FG_RED |IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        extensionIsSupported = false;
    }

    if ( g_prefsManager->GetInt ( "TextureCompression", 0 ) && extensionIsSupported )
    {
        g_openGL->SetSetting ( OPENGL_TEX_3DFX_COMPRESSION, true );
    } else {
        g_openGL->SetSetting ( OPENGL_TEX_3DFX_COMPRESSION, false );
    }
	
    g_console->Write ( "Supports S3 texture compression? " );
    if ( g_openGL->ExtensionIsSupported ( "GL_EXT_texture_compression_s3tc" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        extensionIsSupported = true;
    } else {
        g_console->SetColour ( IO::Console::FG_RED |IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        extensionIsSupported = false;
    }

    if ( g_prefsManager->GetInt ( "TextureCompression", 0 ) && extensionIsSupported )
    {
        g_openGL->SetSetting ( OPENGL_TEX_S3_COMPRESSION, true );
    } else {
        g_openGL->SetSetting ( OPENGL_TEX_S3_COMPRESSION, false );
    }

    g_console->Write ( "Supports compiled vertex arrays? " );
    if ( g_openGL->ExtensionIsSupported ( "GL_EXT_compiled_vertex_array" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        extensionIsSupported = true;
    } else {
        g_console->SetColour ( IO::Console::FG_RED |IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        extensionIsSupported = false;
    }

    g_console->Write ( "Supports vertex buffer objects? " );
    if ( g_openGL->ExtensionIsSupported ( "GL_ARB_vertex_buffer_object" ) )
    {
        g_console->SetColour ( IO::Console::FG_GREEN | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "Yes" );
        g_console->SetColour ();
        extensionIsSupported = true;
    } else {
        g_console->SetColour ( IO::Console::FG_RED |IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "No" );
        g_console->SetColour ();
        extensionIsSupported = false;
    }

    if ( !testsPassed ) return -1;

    g_openGL->SetSetting ( OPENGL_TEX_FORCE_SQUARE, false );

	m_defaultFont = CreateFont("Arial", 12);

    glDisable ( GL_CULL_FACE );
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_DITHER );
    glDisable ( GL_FOG );
    glDisable ( GL_LIGHTING );
    glDisable ( GL_LOGIC_OP );
    glDisable ( GL_POINT_SMOOTH );
    glDisable ( GL_STENCIL_TEST );
    glDisable ( GL_SCISSOR_TEST );
    glDisable ( GL_TEXTURE_1D );
    glDisable ( GL_TEXTURE_2D );
    
    // Alpha blending setup code
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    ASSERT_OPENGL_ERRORS;
    glEnable ( GL_ALPHA_TEST );
    glAlphaFunc ( GL_GREATER, 0.1f );

    // We set this to GL_MODULATE to make the alpha blended textures render properly
    glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    ASSERT_OPENGL_ERRORS;

    // Lasers should be smooth. Trust me. They look crap without this.
    glEnable ( GL_LINE_SMOOTH );
    glHint ( GL_LINE_SMOOTH_HINT, GL_NICEST );
    
    // We need to reset the OpenGL projection matrix.
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity (); // use an identity matrix for the projection matrix
    glOrtho ( 0.0, (double)m_screenX, (double)m_screenY, 0.0, -1.0, 1.0 ); // use a 2D orthographic matrix
    
    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity (); // load an identity to clear the modelview matrix
    ASSERT_OPENGL_ERRORS;

    glVertexPointer ( 2, GL_SHORT, 0, (GLvoid*)m_vertexArray );
    ASSERT_OPENGL_ERRORS;

    if ( g_openGL->GetSetting ( OPENGL_USE_TEXTURE_RECTANGLES, false ) )
        glTexCoordPointer ( 2, GL_SHORT, 0, (GLvoid*)m_texCoordArrayi );
    else
        glTexCoordPointer ( 2, GL_FLOAT, 0, (GLvoid*)m_texCoordArrayf );
    ASSERT_OPENGL_ERRORS;

    return 0;
}

bool OpenGLGraphics::Flip()
{
    SDL_GL_SwapBuffers ();
	return true;
}

#endif
