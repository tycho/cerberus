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

#ifndef __included_map_h
#define __included_map_h

#include "Graphics/surface.h"

#define MAX_FLAGPOLES 32
#define MAX_SWITCHES 64

struct LegacyRect {
        char aTop;
        char bBottom;
        char cLeft;
        char dRight;
};

struct MapHeader {
    unsigned short   FormatID;
    unsigned short   HeaderSize;
    unsigned char    Version;
    unsigned short   Width;
    unsigned short   Height;
    unsigned char    MaxPlayers;
    unsigned char    HoldingTime;
    unsigned char    NumTeams;
    unsigned char    GameObjective;
    unsigned char    LaserDamage;
    unsigned char    SpecialDamage;
    unsigned char    Recharge;
    char             MissEnabled;
    char             MortEnabled;
    char             BouncyEnabled;
    unsigned short   PowerupPosCount;
    unsigned char    SimulPowerups;
    unsigned char    SwitchCount;
};

struct MapHeaderStrings
{
    char *ExtendedName;
    char *Description;
};

struct FlagPole {
    unsigned short x;
    unsigned short y;
};

class Map
{
public:
    short                       m_animations[256][256];
    short                       m_flagPosition1[2][MAX_FLAGPOLES]; // [x or y][index]
    short                       m_flagPosition2[2][MAX_FLAGPOLES]; // [x or y][index]
    short                       m_flagPosition3[2][MAX_FLAGPOLES]; // [x or y][index]
    short                       m_flagPosition4[2][MAX_FLAGPOLES]; // [x or y][index]
    short                       m_flagPosition5[2][MAX_FLAGPOLES]; // [x or y][index]

    // TODO: These could probably be reduced to 'char'
    short                       m_flagCarry1[MAX_FLAGPOLES];
    short                       m_flagCarry2[MAX_FLAGPOLES];
    short                       m_flagCarry3[MAX_FLAGPOLES];
    short                       m_flagCarry4[MAX_FLAGPOLES];
    short                       m_flagCarry5[MAX_FLAGPOLES];

private:
    struct MapHeader            m_header;
    struct MapHeaderStrings     m_headerStrings;

    char                        m_tileValues[4255];

    char                        m_flagCounts[4];
    char                        m_flagPoleCounts[4];

    Data::DArray<char>          m_flagPoleBases[4];

    short                       m_flagPole1[MAX_FLAGPOLES][MAX_FLAGPOLES];
    short                       m_flagPole2[MAX_FLAGPOLES][MAX_FLAGPOLES];
    short                       m_flagPole3[MAX_FLAGPOLES][MAX_FLAGPOLES];
    short                       m_flagPole4[MAX_FLAGPOLES][MAX_FLAGPOLES];
    short                       m_flagPole5[MAX_FLAGPOLES][MAX_FLAGPOLES];
    short                       m_switches[MAX_SWITCHES][MAX_SWITCHES];

    unsigned char               m_mapData[131072];

    short                       m_sourceTileX[256][256];
    short                       m_sourceX[256][256];

    short                       m_sourceTileY[256][256];
    short                       m_sourceY[256][256];

    double                      m_animCount[256][256];
    short                       m_animOffset[256][256];
    short                       m_tmpSX[256];
    short                       m_tmpSY[256];
    LegacyRect                  m_roughTile[4001];
    short                       m_collision[256][256];
    short                       m_sourceTile[256][256];

    Surface                    *m_mapSurface;
    Uint32                      m_tileTiledSurfaceID;

protected:
    virtual void CreateTileMap ();
    virtual int LoadRough ( const char *_file );
    virtual int LoadAttribs ( const char *_file );
    virtual int DecompressMap ( unsigned char *_data, int _origSize );

public:
    Map();
    virtual ~Map();
    virtual void BlitEntireMap ();
    virtual void Render ( short _x, short _y );
    virtual int Load ( const char *_file );
    virtual short GetAnimation ( int _index0, int _index1 );
    virtual short GetCollision ( int _index0, int _index1 );
    virtual short GetSourceTile ( int _index0, int _index1 );
    virtual short GetSourceTileX ( int _index0, int _index1 );
    virtual short GetSourceTileY ( int _index0, int _index1 );
    virtual Uint32 GetTileMapID ();
    virtual LegacyRect *GetRoughTile ( int _index );

    static int GetFileSize ( const char *_file );
    static int GetMapVersion ( const char *_file );
};

#endif
