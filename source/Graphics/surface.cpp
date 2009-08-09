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

#include "Graphics/graphics.h"
#include "Graphics/surface.h"

/*

            COST-BENEFIT ANALYSIS OF N-WAY SPLITTING

            LEGEND
            ---------
            N: Split N ways.
            A: Split into AxA sections.
            B: Split into BxB pixel sections.
            C: Split into CxC tile sections.

                P O S S I B L E  V A L U E S
            N     (  AxA  ):    BxB    (   CxC   )
            --------------------------------------
            1     (  1x1  ): 4096x4096 ( 256x256 )
            4     (  2x2  ): 2048x2048 ( 128x128 )
            16    (  4x4  ): 1024x1024 (  64x64  )
            64    (  8x8  ):  512x512  (  32x32  )
            256   ( 16x16 ):  256x256  (  16x16  )
            1024  ( 32x32 ):  128x128  (   8x8   )
            4096  ( 64x64 ):   64x64   (   4x4   )
            16384 (128x128):   32x32   (   2x2   )
            65536 (256x256):   16x16   (   1x1   )

    LOW N-VALUE
        PROS
            - Fewer individual blits to render the scene.
        CONS
            - Breaks compatibility with certain hardware.
            - Low map optimization for empty areas.
            - High memory usage.
	    - Large textures reduce compatibility.

*/

Surface::Surface ( Uint16 _sizeX, Uint16 _sizeY, Uint16 _splitSections )
{
    if ( _splitSections > 64 ) _splitSections = 64;

    m_sizeXY = cc_max ( nearestPowerOfTwo ( _sizeX ), nearestPowerOfTwo ( _sizeY ) );
    m_sqrtN = _splitSections;

    CrbDebugAssert ( isPowerOfTwo ( _splitSections ) );
    if ( !isPowerOfTwo ( _splitSections ) )
    {
        _splitSections = nearestPowerOfTwo ( _splitSections );
        m_nWays = _splitSections * _splitSections;
        m_sqrtN = _splitSections;
    }

    // We want to force it to use the nicest texture size possible without
    // compromising performance.
    Uint16 maxTexSize = cc_min ( g_graphics->GetMaximumTextureSize() / 2, 1024 );

    m_pixelWH = m_sizeXY / m_sqrtN;
    while ( m_pixelWH > maxTexSize )
    {
        m_sqrtN *= 2;
        m_pixelWH = m_sizeXY / m_sqrtN;
    }
    m_nWays = m_sqrtN * m_sqrtN;

    m_sectionIDs.setSize ( m_nWays );
	m_srcRects = new SDL_Rect[m_nWays];
	m_destRects = new SDL_Rect[m_nWays];
}

Surface::~Surface()
{
	delete [] m_srcRects; m_srcRects = NULL;
	delete [] m_destRects; m_destRects = NULL;

    for ( size_t i = 0; i < m_sectionIDs.size(); i++ )
    {
        if ( !m_sectionIDs.valid ( i ) ) continue;
        g_graphics->DeleteSurface ( m_sectionIDs.get(i) );
        m_sectionIDs.remove ( i );
    }
}

void Surface::CalculateRectangles ( SDL_Rect *sourceRects, SDL_Rect *destRects,
		                            const SDL_Rect *_sourceRect, const SDL_Rect *_destRect )
{
	CrbReleaseAssert ( sourceRects );
	CrbReleaseAssert ( destRects );
	CrbReleaseAssert ( _sourceRect );
	CrbReleaseAssert ( _destRect );

    Uint32 xoff = _destRect->x % m_pixelWH,
           yoff = _destRect->y % m_pixelWH;

    for ( Uint16 destX = _destRect->x - xoff,
                 srcX  = _sourceRect->x - xoff;
          destX < _destRect->x + _sourceRect->w + m_pixelWH;
          destX += m_pixelWH,
          srcX  += m_pixelWH)
    {
        for ( Uint16 destY = _destRect->y - yoff,
                     srcY  = _sourceRect->y - yoff;
              destY < _destRect->y + _sourceRect->h + m_pixelWH;
              destY += m_pixelWH,
              srcY  += m_pixelWH)
        {
			SDL_Rect srcRect, dstRect;

			dstRect.x = destX;
			dstRect.y = destY;
			srcRect.x = srcX;
			srcRect.y = srcY;
			srcRect.w = m_pixelWH;
			srcRect.h = m_pixelWH;

			// The actual X is a bit right of this.
			if ( dstRect.x < _destRect->x )
			{
				Uint16 diff = _destRect->x - dstRect.x;
				CrbDebugAssert ( diff == xoff );
				dstRect.x += diff;
				srcRect.x += diff;
				srcRect.w -= diff;
			}

			// The actual Y is a bit down of this.
			if ( dstRect.y < _destRect->y )
			{
				Uint16 diff = _destRect->y - dstRect.y;
				CrbDebugAssert ( diff == yoff );
				dstRect.y += diff;
				srcRect.y += diff;
				srcRect.h -= diff;
			}

			// Trim to destination rectangle boundaries
			if ( dstRect.x + srcRect.w > _destRect->x + _sourceRect->w )
			{
				Uint16 diff = (dstRect.x + srcRect.w) - (_destRect->x + _sourceRect->w);
				srcRect.w -= diff;
			}
			if ( dstRect.y + srcRect.h > _destRect->y + _sourceRect->h )
			{
				Uint16 diff = (dstRect.y + srcRect.h) - (_destRect->y + _sourceRect->h);
				srcRect.h -= diff;
			}

			// Let's not waste a BlitNoOverlap call.
			if ( (Sint16)srcRect.h <= 0 ) continue;
			if ( (Sint16)srcRect.w <= 0 ) continue;

			if ( sourceRects )
			{
				memcpy ( sourceRects, &srcRect, sizeof(SDL_Rect) );
				sourceRects++;
			}
			if ( destRects )
			{
				memcpy ( destRects, &dstRect, sizeof(SDL_Rect) );
				destRects++;
			}
        }
    }
}

void Surface::CalculateDestinationRectangles ( SDL_Rect *destRects, const SDL_Rect *_destRect )
{
	CrbReleaseAssert ( destRects );
	CrbReleaseAssert ( _destRect );
    Uint32 xoff = _destRect->x % m_pixelWH,
           yoff = _destRect->y % m_pixelWH;

    for ( Uint16 destX = _destRect->x - xoff;
          destX < _destRect->x + _destRect->w + m_pixelWH;
          destX += m_pixelWH )
    {
        for ( Uint16 destY = _destRect->y - yoff;
              destY < _destRect->y + _destRect->h + m_pixelWH;
              destY += m_pixelWH )
        {
			SDL_Rect dstRect;

			dstRect.x = destX;
			dstRect.y = destY;
			dstRect.w = m_pixelWH;
			dstRect.h = m_pixelWH;

			// The actual X is a bit right of this.
			if ( dstRect.x < _destRect->x )
			{
				Uint16 diff = _destRect->x - dstRect.x;
				CrbDebugAssert ( diff == xoff );
				dstRect.x += diff;
			}

			// The actual Y is a bit down of this.
			if ( dstRect.y < _destRect->y )
			{
				Uint16 diff = _destRect->y - dstRect.y;
				CrbDebugAssert ( diff == yoff );
				dstRect.y += diff;
			}

			// Trim to destination rectangle boundaries
			if ( dstRect.x + dstRect.w > _destRect->x + _destRect->w )
			{
				Uint16 diff = (dstRect.x + dstRect.w) - (_destRect->x + _destRect->w);
				dstRect.w -= diff;
			}
			if ( dstRect.y + dstRect.h > _destRect->y + _destRect->h )
			{
				Uint16 diff = (dstRect.y + dstRect.h) - (_destRect->y + _destRect->h);
				dstRect.h -= diff;
			}

			// Let's not waste a BlitNoOverlap call.
			if ( (Sint16)dstRect.h <= 0 ) continue;
			if ( (Sint16)dstRect.w <= 0 ) continue;

			if ( destRects )
			{
				memcpy ( destRects, &dstRect, sizeof(SDL_Rect) );
				destRects++;
			}
        }
    }
}

void Surface::Blit ( Uint32 _sourceSurfaceID, const SDL_Rect *_sourceRect, const SDL_Rect *_destRect )
{

    // If no rects are provided, do a default blit.
    SDL_Rect internalSrcRect, internalDstRect;
    if ( !_sourceRect )
    {
        _sourceRect = &internalSrcRect;
        internalSrcRect.x = internalSrcRect.y = 0;
        internalSrcRect.w = g_graphics->GetSurfaceWidth ( _sourceSurfaceID );
        internalSrcRect.h = g_graphics->GetSurfaceHeight ( _sourceSurfaceID );
    }
    if ( !_destRect )
    {
        _destRect = &internalDstRect;
        internalDstRect.x = internalDstRect.y = 0;
        internalDstRect.w = _sourceRect->w;
        internalDstRect.h = _sourceRect->h;
    }

	memset ( m_srcRects, 0, sizeof(SDL_Rect) * m_nWays );
	memset ( m_destRects, 0, sizeof(SDL_Rect) * m_nWays );

	CalculateRectangles ( m_srcRects, m_destRects, _sourceRect, _destRect );

	SDL_Rect *dest = m_destRects;
	SDL_Rect *src = m_srcRects;
	for ( size_t i = 0; i < m_nWays; i++ )
	{
		if ( src->w == 0 ) break;
		Uint32 surfaceID;
		FindLocalSurfaceRect ( dest, surfaceID );
		g_graphics->Blit ( _sourceSurfaceID, src, surfaceID, dest );
		src++; dest++;
	}
}

SDL_PixelFormat *Surface::GetPixelFormat()
{
	size_t i = 0;
	while ( !m_sectionIDs.valid ( i ) ) i++;
	return g_graphics->GetPixelFormat ( i );
}

Color32 Surface::GetPixel ( int _x, int _y )
{
	SDL_Rect destRect;
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = destRect.h = 1;

	memset ( m_destRects, 0, sizeof(SDL_Rect) * m_nWays );

	CalculateDestinationRectangles ( m_destRects, &destRect );

	SDL_Rect *dest = m_destRects;

	Uint32 surfaceID;

	FindLocalSurfaceRect ( dest, surfaceID );

	return g_graphics->GetPixel ( surfaceID, dest->x, dest->y );
}

void Surface::SetPixel ( int _x, int _y, Color32 _colour )
{
	SDL_Rect destRect;
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = destRect.h = 1;

	memset ( m_destRects, 0, sizeof(SDL_Rect) * m_nWays );

	CalculateDestinationRectangles ( m_destRects, &destRect );

	SDL_Rect *dest = m_destRects;

	Uint32 surfaceID;

	FindLocalSurfaceRect ( dest, surfaceID );

	g_graphics->SetPixel ( surfaceID, dest->x, dest->y, _colour );
}

void Surface::FillRect ( SDL_Rect *_destRect, Color32 _colour )
{
	memset ( m_destRects, 0, sizeof(SDL_Rect) * m_nWays );

	CalculateDestinationRectangles ( m_destRects, _destRect );

	SDL_Rect *dest = m_destRects;
	for ( size_t i = 0; i < m_nWays; i++ )
	{
		if ( dest->w == 0 ) break;
		Uint32 surfaceID;
		FindLocalSurfaceRect ( dest, surfaceID );
		g_graphics->FillRect ( surfaceID, dest, _colour );
		dest++;
	}
}

void Surface::ReplaceColour ( SDL_Rect *_destRect, Color32 _findColour, Color32 _replaceColour )
{
	SDL_Rect internalDstRect;
    if ( !_destRect )
    {
        _destRect = &internalDstRect;
        internalDstRect.x = internalDstRect.y = 0;
        internalDstRect.w = internalDstRect.h = m_sizeXY;
    }

	memset ( m_destRects, 0, sizeof(SDL_Rect) * m_nWays );

	CalculateDestinationRectangles ( m_destRects, _destRect );

	SDL_Rect *dest = m_destRects;
	for ( size_t i = 0; i < m_nWays; i++ )
	{
		if ( dest->w == 0 ) break;
		Uint32 surfaceID;
		FindLocalSurfaceRect ( dest, surfaceID );
		g_graphics->ReplaceColour ( surfaceID, dest, _findColour, _replaceColour );
		dest++;
	}
}

void Surface::FindLocalSurfaceRect ( SDL_Rect *_destRect, Uint32 &_surfaceID )
{
    CrbReleaseAssert ( _destRect );

    SDL_Rect dstRect;

    // Find out what the index of this surface should be.
    Uint32 row = _destRect->y / m_pixelWH, column = _destRect->x / m_pixelWH;
    Uint32 surfaceIndex = row * m_sqrtN + column;

    // Calculate the offset.
    dstRect.x = _destRect->x % m_pixelWH;
    dstRect.y = _destRect->y % m_pixelWH;
	dstRect.w = _destRect->w;
	dstRect.h = _destRect->h;

    // Does the surface exist?
    if ( !m_sectionIDs.valid ( surfaceIndex ) )
    {
        // Not yet. Create it.
        m_sectionIDs.insert ( g_graphics->CreateSurface ( m_pixelWH, m_pixelWH, true ), surfaceIndex );
    }

	memcpy ( _destRect, &dstRect, sizeof(SDL_Rect) );

    // Get the surface.
    _surfaceID = m_sectionIDs.get ( surfaceIndex );
}

void Surface::Render ( SDL_Rect *_sourceRect, Uint32 _destSurfaceID, SDL_Rect *_destRect ) const
{
    // If no rects are provided, do a default blit.
    SDL_Rect internalSrcRect, internalDstRect;
    if ( !_sourceRect )
    {
        _sourceRect = &internalSrcRect;
        internalSrcRect.x = internalSrcRect.y = 0;
        internalSrcRect.w = g_graphics->GetSurfaceWidth ( _destSurfaceID );
        internalSrcRect.h = g_graphics->GetSurfaceHeight ( _destSurfaceID );
    }
    if ( !_destRect )
    {
        _destRect = &internalDstRect;
        internalDstRect.x = internalDstRect.y = 0;
        internalDstRect.w = _sourceRect->w;
        internalDstRect.h = _sourceRect->h;
    }

    // Source rectangles and destination rectangles VERY rarely
    // happen to coincide with the m_pixelWH boundary. Modulus
    // obtains the offset.
    Uint32 xoff = (_sourceRect->x + _destRect->x) % m_pixelWH,
           yoff = (_sourceRect->y + _destRect->y) % m_pixelWH;

    // This loop looks grotesque, but it actually only ends up being
    // 7 or 8 iterations if the texture threshhold is properly set.
    for ( Uint16 destX = _destRect->x,
                 srcX = _sourceRect->x;
          destX < _destRect->x + _sourceRect->w + m_pixelWH;
          destX += m_pixelWH,
          srcX  += m_pixelWH)
    {
        for ( Uint16 destY = _destRect->y,
                     srcY  = _sourceRect->y;
              destY < _destRect->y + _sourceRect->h + m_pixelWH;
              destY += m_pixelWH,
              srcY  += m_pixelWH)
        {
            Uint32 row    = ( srcY + _destRect->y ) / m_pixelWH,
                   column = ( srcX + _destRect->x ) / m_pixelWH;
            Uint32 surfaceIndex = row * m_sqrtN + column;

            // The surface doesn't exist. No need for a blit.
            if ( !m_sectionIDs.valid ( surfaceIndex ) )    continue;

            SDL_Rect dstRect, srcRect;

            srcRect.x = srcRect.y = 0;
            srcRect.w = srcRect.h = m_pixelWH;

            dstRect.x = destX - xoff;
            dstRect.y = destY - yoff;

            // Trim left.
            if ( dstRect.x < _destRect->x )
            {
                srcRect.x += ( _destRect->x - dstRect.x );
                srcRect.w -= ( _destRect->x - dstRect.x );
                dstRect.x = _destRect->x;
            }

            // Trim top.
            if ( dstRect.y < _destRect->y )
            {
                srcRect.y += ( _destRect->y - dstRect.y );
                srcRect.h -= ( _destRect->y - dstRect.y );
                dstRect.y = _destRect->y;
            }

			// Trim to destination rectangle boundaries
			if ( dstRect.x + srcRect.w > _destRect->x + _sourceRect->w )
			{
				Uint16 diff = (dstRect.x + srcRect.w) - (_destRect->x + _sourceRect->w);
				srcRect.w -= diff;
			}
			if ( dstRect.y + srcRect.h > _destRect->y + _sourceRect->h )
			{
				Uint16 diff = (dstRect.y + srcRect.h) - (_destRect->y + _sourceRect->h);
				srcRect.h -= diff;
			}

            if ( dstRect.x > _destRect->x + _sourceRect->w ) continue;
            if ( dstRect.y > _destRect->y + _sourceRect->h ) continue;
			if ( (Sint16)srcRect.h <= 0 ) continue;
			if ( (Sint16)srcRect.w <= 0 ) continue;

            // Get the surface.
            Uint32 srcSurfaceID = m_sectionIDs.get ( surfaceIndex );

            g_graphics->Blit ( srcSurfaceID, &srcRect, _destSurfaceID, &dstRect );
        }
    }
}

void Surface::PrintStatistics() const
{
	double percent = 1.0 - ((double)m_sectionIDs.used() / (double)m_sectionIDs.size());

	// X * Y * pixelsize = size in bytes / 1024 / 1024 = size in MB
	double totalmb = (double)(m_sizeXY * m_sizeXY * sizeof(Uint32)) / 1024.0 / 1024.0;

    g_console->WriteLine ( "Surface class saved %0.2lf%% (%0.2lfMB) of texture memory",
        100.0 * percent, percent * totalmb  );
}
