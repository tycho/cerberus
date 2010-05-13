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

#ifndef __included_surface_h
#define __included_surface_h

class Surface
{
protected:
	Uint32 m_sizeXY;
	Uint32 m_nWays;
	Uint32 m_sqrtN;
	Uint32 m_pixelWH;
	Data::DArray<Uint32> m_sectionIDs;

	SDL_Rect *m_srcRects;
	SDL_Rect *m_destRects;

	virtual void FindLocalSurfaceRect ( SDL_Rect *_destRect, Uint32 &_surfaceID );
	virtual void CalculateDestinationRectangles ( SDL_Rect *destRects, const SDL_Rect *_destRect );
	virtual void CalculateRectangles ( SDL_Rect *sourceRects, SDL_Rect *destRects,
		                               const SDL_Rect *_sourceRect, const SDL_Rect *_destRect );

public:
	Surface                                      ( Uint16 _sizeX, Uint16 _sizeY, Uint16 _splitSections = 16 );
	virtual ~Surface                             ();
    virtual Color32            GetPixel          ( int x, int y );
    virtual void               SetPixel          ( int x, int y, Color32 _colour );
    virtual SDL_PixelFormat   *GetPixelFormat    ();
    virtual void               ReplaceColour     ( SDL_Rect *_destRect, Color32 _findColour, Color32 _replaceColour );
    virtual void               FillRect          ( SDL_Rect *_destRect, Color32 _colour );
    virtual void               Blit              ( Uint32 _sourceSurfaceID, const SDL_Rect *_sourceRect, const SDL_Rect *_destRect );
    virtual void               Render            ( SDL_Rect *_sourceRect, Uint32 _destSurfaceID, SDL_Rect *_destRect ) const;
    virtual void               PrintStatistics   () const;
};

#endif
