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
#include "App/file_utils.h"
#include "App/preferences.h"
#include "Game/game.h"
#include "Graphics/graphics.h"
#include "Interface/interface.h"
#include "World/map.h"

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
#   pragma comment ( lib, "zlib.lib" )
#endif

// MEMO
// From: Alastair
// To: Steven
// NICE BYTESWAPPING, IDIOT >.>

// MEMO
// From: Steven
// To: Alastair
// THANKS.

Map::Map()
 : m_mapSurface(NULL)
{
    char temp[2048];
    memset ( &temp, 0, sizeof ( temp ) );

    memset ( &m_header, 0, sizeof ( MapHeader ) );
    memset ( &m_headerStrings, 0, sizeof ( MapHeaderStrings ) );
    memset ( &m_tileValues, 0, sizeof(m_tileValues) );
    memset ( &m_flagCounts, 0, sizeof(m_flagCounts) );
    memset ( &m_flagPoleCounts, 0, sizeof(m_flagPoleCounts) );
    memset ( &m_flagPole1, 0, sizeof ( m_flagPole1 ) );
    memset ( &m_flagPole2, 0, sizeof ( m_flagPole2 ) );
    memset ( &m_flagPole3, 0, sizeof ( m_flagPole3 ) );
    memset ( &m_flagPole4, 0, sizeof ( m_flagPole4 ) );
    memset ( &m_flagPole5, 0, sizeof ( m_flagPole5 ) );
    memset ( &m_switches, 0, sizeof ( m_switches ) );
    memset ( &m_mapData, 0, sizeof(m_mapData) );
    memset ( &m_sourceTileX, 0, sizeof ( m_sourceTileX ) );
    memset ( &m_sourceX, 0, sizeof ( m_sourceX ) );
    memset ( &m_sourceTileY, 0, sizeof ( m_sourceTileY ) );
    memset ( &m_sourceY, 0, sizeof ( m_sourceY ) );
    memset ( &m_animations, 0, sizeof ( m_animations ) );
    memset ( &m_animCount, 0, sizeof ( m_animCount ) );
    memset ( &m_animOffset, 0, sizeof ( m_animOffset ) );
    memset ( &m_tmpSX, 0, sizeof ( m_tmpSX ) );
    memset ( &m_tmpSY, 0, sizeof ( m_tmpSY ) );
    memset ( &m_roughTile, 0, sizeof(m_roughTile) );
    memset ( &m_collision, 0, sizeof ( m_collision ) );
    memset ( &m_sourceTile, 0, sizeof ( m_sourceTile ) );

    sprintf ( temp, "%s%s", g_app->GetResourcePath (), "data/rough.dat" );
    LoadRough ( temp );
}

Map::~Map()
{
    delete [] m_headerStrings.ExtendedName;
    m_headerStrings.ExtendedName = NULL;
    delete [] m_headerStrings.Description;
    m_headerStrings.Description = NULL;
	delete m_mapSurface; m_mapSurface = NULL;
}

short Map::GetAnimation ( int _index0, int _index1 )
{
    return m_animations[_index0][_index1];
}

short Map::GetCollision ( int _index0, int _index1 )
{
    return m_collision[_index0][_index1];
}

short Map::GetSourceTile ( int _index0, int _index1 )
{
    return m_sourceTile[_index0][_index1];
}

short Map::GetSourceTileX ( int _index0, int _index1 )
{
    return m_sourceTileX[_index0][_index1];
}

short Map::GetSourceTileY ( int _index0, int _index1 )
{
    return m_sourceTileY[_index0][_index1];
}

LegacyRect *Map::GetRoughTile ( int _index )
{
    return &m_roughTile[_index];
}

Uint32 Map::GetTileMapID()
{
    return m_tileTiledSurfaceID;
}

void Map::Render ( short _x, short _y )
{
    char FrameChange[256][256];
    memset ( FrameChange, 0, sizeof(FrameChange) );
    short CenterSX = g_graphics->GetCenterX() - 16,
          CenterSY = g_graphics->GetCenterY() - 16;
    short ResX = g_graphics->GetScreenWidth(),
          ResY = g_graphics->GetScreenHeight();
    short MeX = _x - CenterSX,
          MeY = _y - CenterSY;
    short MapX = (MeX - (MeX % 16)) / 16,
          MapY = (MeY - (MeY % 16)) / 16;
    if ( MeY < 0 ) MapY--;
    if ( MeX < 0 ) MapX--;
    short Xdif = MeX - MapX * 16,
          Ydif = MeY - MapY * 16,
          ToX = ResX / 16 + 2,
          ToY = ResY / 16 + 2,
          I = MapX * 16 + Xdif,
          j = MapY * 16 + Ydif,
          d = I, C = j;
    SDL_Rect renderFrom, renderTo;
    renderFrom.x = d;
    renderFrom.y = C;
    d = ResX + d;
    C = ResY + C;
    renderFrom.w = d;
    renderFrom.h = C;
    renderTo.x = 0; renderTo.y = 0;
    renderTo.w = g_graphics->GetScreenWidth(); renderTo.h = g_graphics->GetScreenHeight();
	m_mapSurface->Render ( &renderFrom, g_graphics->GetScreen(), &renderTo );
	
    if ( renderFrom.w == 0 || renderFrom.h == 0 ) return;
    C = 0; d = 0;
    if ( MeY < 0 ) C = MapY;
    if ( MeX < 0 ) d = MapX;
    short xt, yt;
    short Xfind, Yfind, Xwdth, Ywdth,
            Xcoor, Ycoor, X, a, e;
    for ( short R = C; R < ToY; R++ )
    {
        for ( short I = d; I < ToX; I++ )
        {
            xt = I + MapX; yt = R + MapY;
            if ( yt > 255 || yt < 0 ) break;
            if ( xt > 255 || xt < 0 ) continue;
            Xfind = 0;
            if ( I == 0 ) Xfind += Xdif;
            Yfind = 0;
            if ( R == 0 ) Yfind += Ydif;
            Xwdth = 16;
            if ( I == 0 ) Xwdth -= Xdif;
            if ( I == ToX ) Xwdth = Xdif;
            Ywdth = 16;
            if ( R == 0 ) Ywdth -= Ydif;
            if ( R == ToY ) Ywdth = Ydif;

            Xcoor = I * 16;
            if ( I > 0 ) Xcoor -= Xdif;
            Ycoor = R * 16;
            if ( R > 0 ) Ycoor -= Ydif;

            X = m_animOffset[yt][xt];
            if ( X > 0 )
            {
                a = m_animations[yt][xt];
                if ( FrameChange[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] == 0 )
                {
                    if ( m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] < 0 )
                        m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] = 0;
                    if ( g_interface->GetAnimSpeed(a) == 0 ) g_interface->SetAnimSpeed(a,1);
                    m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] += g_game->GetGameSpeed() / (float)g_interface->GetAnimSpeed(a);
                    if ( m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] > g_interface->GetFrameCount(a) )
                        m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] = 0;
                }
                FrameChange[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)] = 1;
                e = (short)m_animCount[g_interface->GetFrameCount(a)][g_interface->GetAnimSpeed(a)];
                e = (e + X) % g_interface->GetFrameCount(a);
                SDL_Rect TileGet, ToRect;
                TileGet.y = g_interface->GetAnimFY(a,e) + Yfind;
                TileGet.h = Ywdth;
                TileGet.x = g_interface->GetAnimFX(a,e) + Xfind;
                TileGet.w = Xwdth;
                ToRect.x = Xcoor; ToRect.y = Ycoor; ToRect.w = TileGet.w; ToRect.h = TileGet.h;
                char temp[16]; sprintf ( temp, "anims%d", g_interface->GetAnimFS(a,0) );
                g_graphics->Blit ( g_interface->GetAnimSurfaceID(g_interface->GetAnimFS(a,0)), &TileGet, g_graphics->GetScreen(), &ToRect );
            }
        }
    }
}

int Map::LoadAttribs ( const char *_file )
{
    ARCReleaseAssert ( _file );
    char tempPath[2048];

    ARCReleaseAssert ( _file != NULL );
    g_console->WriteLine ( "Loading map from %s...", _file );

    sprintf ( tempPath, "data/%s", _file );

    BinaryReader *attribs = g_app->m_resource->GetBinaryReader ( tempPath );
    if ( !attribs ) return -1;

    attribs->Seek ( 2, SEEK_SET );

    memset ( &m_tileValues, 0, sizeof(m_tileValues) );
    attribs->ReadBytes ( sizeof(m_tileValues), (unsigned char *)m_tileValues );

    g_console->WriteLine ( "Loaded %d bytes of data from %s.", attribs->GetSize(), tempPath );

    delete attribs;

    return 0;
}

int Map::GetFileSize ( const char *_file )
{
    char tempPath[2048];

    ARCReleaseAssert ( _file != NULL );
    g_console->WriteLine ( "Getting filesize of map %s...", _file );

    sprintf ( tempPath, "maps/%s", _file );

    BinaryReader *mapFile = g_app->m_resource->GetBinaryReader ( tempPath );
    if ( !mapFile ) return -1;

    int ret = mapFile->GetSize();

    delete mapFile; mapFile = NULL;

    return ret;
}

int Map::GetMapVersion ( const char *_file )
{
    char tempPath[2048];

    ARCReleaseAssert ( _file != NULL );
    g_console->WriteLine ( "Getting version of map %s...", _file );

    sprintf ( tempPath, "maps/%s", _file );

    BinaryReader *mapFile = g_app->m_resource->GetBinaryReader ( tempPath );
    if ( !mapFile ) return -1;

    MapHeader header;

    header.FormatID = (unsigned short)mapFile->ReadS16();

    if ( header.FormatID != 17016 )
        return -1;

    header.HeaderSize = (Uint16)mapFile->ReadS16();
    header.Version = (Uint8)mapFile->ReadS8();

    delete mapFile; mapFile = NULL;

    return header.Version;
}

int Map::Load ( const char *_file )
{
    char tempPath[2048];

    ARCReleaseAssert ( _file != NULL );
    g_console->WriteLine ( "Loading map from %s...", _file );

    sprintf ( tempPath, "maps/%s", _file );

    BinaryReader *mapFile = g_app->m_resource->GetBinaryReader ( tempPath );
    if ( !mapFile ) return -1;
    
    CoreAssert ( LoadAttribs ( "attribs.dat" ) == 0 );
    CoreAssert ( LoadRough ( "rough.dat" ) == 0 );

    m_header.FormatID = (unsigned short)mapFile->ReadS16();

    if ( m_header.FormatID != 17016 )
        return -1;

    m_header.HeaderSize = (Uint16)mapFile->ReadS16();
    m_header.Version = mapFile->ReadS8();
    m_header.Width = (Uint16)mapFile->ReadS16();
    m_header.Height = (Uint16)mapFile->ReadS16();
    m_header.MaxPlayers = mapFile->ReadS8();
    m_header.HoldingTime = mapFile->ReadS8();
    m_header.NumTeams = mapFile->ReadS8();
    ARCReleaseAssert ( m_header.NumTeams < 5 );
    m_header.GameObjective = mapFile->ReadS8();
    m_header.LaserDamage = mapFile->ReadS8();
    m_header.SpecialDamage = mapFile->ReadS8();
    m_header.Recharge = mapFile->ReadS8();
    m_header.MissEnabled = mapFile->ReadS8();
    m_header.MortEnabled = mapFile->ReadS8();
    m_header.BouncyEnabled = mapFile->ReadS8();
    m_header.PowerupPosCount = (Uint16)mapFile->ReadS16();
    m_header.SimulPowerups = mapFile->ReadS8();
    m_header.SwitchCount = mapFile->ReadS8();

#if defined ( DEBUGLOG_ENABLED ) && 0
    g_console->WriteLine ( "Map FormatID: %d", m_header.FormatID );
    g_console->WriteLine ( "Map Header Size: %d bytes", m_header.HeaderSize );
    g_console->WriteLine ( "Map Version: %d", m_header.Version );
    g_console->WriteLine ( "Map Width: %d", m_header.Width );
    g_console->WriteLine ( "Map Height: %d", m_header.Height );
    g_console->WriteLine ( "Map MaxPlayers: %d", m_header.MaxPlayers );
    g_console->WriteLine ( "Map HoldingTime: %d", m_header.HoldingTime );
    g_console->WriteLine ( "Map NumTeams: %d", m_header.NumTeams );
    g_console->WriteLine ( "Map GameObjective: %d", m_header.GameObjective );
    g_console->WriteLine ( "Map LaserDamage: %d", m_header.LaserDamage );
    g_console->WriteLine ( "Map SpecialDamage: %d", m_header.SpecialDamage );
    g_console->WriteLine ( "Map Recharge: %d", m_header.Recharge );
    g_console->WriteLine ( "Map MissEnabled: %d", m_header.MissEnabled );
    g_console->WriteLine ( "Map MortEnabled: %d", m_header.MortEnabled );
    g_console->WriteLine ( "Map BouncyEnabled: %d", m_header.BouncyEnabled );
    g_console->WriteLine ( "Map PowerupPosCount: %d", m_header.PowerupPosCount );
    g_console->WriteLine ( "Map SimulPowerups: %d", m_header.SimulPowerups );
    g_console->WriteLine ( "Map SwitchCount: %d", m_header.SwitchCount );
#endif

	Uint16 i;

    //get flag counts
    for ( i = 0; i < m_header.NumTeams; i++ )
    {
        m_flagCounts[i] = mapFile->ReadS8();
    }

    //get flag pole counts
    for ( i = 0; i < m_header.NumTeams; i++ )
    {
        m_flagPoleCounts[i] = mapFile->ReadS8();
    }
    
    for ( i = 0; i < m_header.NumTeams; i++ )
    {
        char t_flagPoleBase;
        if ( m_flagPoleCounts[i] > 0 )
        {
            for ( Uint16 j = 0; j < m_flagPoleCounts[i]; j++ )
            {
                t_flagPoleBase = mapFile->ReadS8();
                m_flagPoleBases[i].insert ( t_flagPoleBase, j );
            }
        }
    }

    Uint16 bytesToRead; char *newString = NULL;

    bytesToRead = (Uint16)mapFile->ReadS16();

    // Allocate space for our extended map name.
    newString = new char[bytesToRead + 1]; ARCReleaseAssert ( newString != NULL );
    memset ( newString, 0, bytesToRead + 1 );

    // Get the extended name and save it.
    mapFile->ReadBytes ( bytesToRead, (unsigned char *)newString );
    m_headerStrings.ExtendedName = newString;
    newString = NULL;

    bytesToRead = (Uint16)mapFile->ReadS16();

    // Allocate space for map description
    newString = new char[bytesToRead + 1]; ARCReleaseAssert ( newString != NULL );
    memset ( newString, 0, bytesToRead + 1 );

    // Save map description in RAM.
    mapFile->ReadBytes ( bytesToRead, (unsigned char *)newString );
    m_headerStrings.Description = newString;
    newString = NULL;

    g_console->WriteLine ( "Loading map '%s' data...", m_headerStrings.ExtendedName );
    g_console->WriteLine ( "Map desc: %s", m_headerStrings.Description );

    // Finally, read the map data.
    memset ( m_mapData, 0, sizeof ( m_mapData ) );
    mapFile->Seek ( m_header.HeaderSize + 2, SEEK_SET );
    int actualBytesRead = mapFile->ReadBytes ( 131072, m_mapData );
    g_console->WriteLine ( "Map data is %d bytes compressed.", actualBytesRead );

    delete mapFile;
    mapFile = NULL;

    int retval = DecompressMap ( m_mapData, 131072 );
    if ( retval != Z_OK )
    {
        ARCAbort ( "Map failed to decompress!" );
    }
    g_console->WriteLine ( "Map decompressed successfully." );

    CreateTileMap();

    return 0;

}

int Map::LoadRough ( const char *_file )
{
    char tempPath[2048];

    ARCReleaseAssert ( _file != NULL );
    g_console->WriteLine ( "Loading map from %s...", _file );

    sprintf ( tempPath, "data/%s", _file );

    BinaryReader *roughdat = g_app->m_resource->GetBinaryReader ( tempPath );
    if ( !roughdat ) return -1;

    roughdat->ReadBytes ( sizeof(m_roughTile), (unsigned char *)m_roughTile );


    g_console->WriteLine ( "Loaded %d bytes of data from %s.", roughdat->GetSize(), tempPath );

    delete roughdat;

    return 0;
}

void Map::CreateTileMap ()
{
	System::Stopwatch sw;
    long countd = 0; int xt, yt, lastSYbound = 0;
    short f, stx, sty; SDL_Rect temprect, temprect1;
    int ubfp12 = 0; int ubfp22 = 0;
    int ubfp32 = 0; int ubfp42 = 0;
    int ubfp52 = 0;    int ubs2 = 0;

    g_console->Write ( "Creating tile map..." );
	sw.Start();
    m_tileTiledSurfaceID = g_graphics->CreateSurface ( 640, 480 );

    short SrcTile[65538];
    memcpy ( SrcTile, m_mapData, sizeof ( m_mapData ) );
    
#ifdef TARGET_BIG_ENDIAN
    for (unsigned i = 0; i < 65538; i++)
    {
        SrcTile[i] = SDL_SwapLE16(SrcTile[i]);
    }
#endif
    
    for ( int i = 0; i < 256; i++ )
    {
        for ( int j = 0; j < 256; j++ )
        {
            xt = (SrcTile[countd] % 40) * 16;
            yt = (SrcTile[countd] - (SrcTile[countd] % 40)) / 40 * 16;
            m_sourceX[i][j] = xt; m_sourceY[i][j] = yt;
            if ( SrcTile[countd] > -1 && SrcTile[countd] <= 4255 )
                m_collision[i][j] = m_tileValues[SrcTile[countd]];
            else
                SrcTile[countd] = 0;
            m_sourceTile[i][j] = SrcTile[countd];
            m_animations[i][j] = -1;
            if ( m_mapData[countd * 2 + 1] > 127 )
            {
                m_animations[i][j] = m_mapData[countd * 2];

                m_collision[i][j] = m_tileValues[4000 + m_animations[i][j]];
                if ( m_animations[i][j] != 158 )
                {
                    m_animOffset[i][j] = ((m_mapData[countd * 2 + 1] - 128) %
                        g_interface->GetFrameCount(m_animations[i][j])) + 1;
                } else {
                    m_animOffset[i][j] = m_mapData[countd * 2 + 1] - 128;
                }
                m_sourceX[i][j] = -1;
                m_sourceY[i][j] = 0;
            }
            
            if ( m_sourceX[i][j] == 0 && m_sourceY[i][j] == 112 )
            {
                m_sourceX[i][j] = -1;
                if ( m_animations[i][j] == -1 )
                {
                    m_collision[i][j] = 2;
                    m_animations[i][j] = -2;
                }
                countd++;
                continue;
            }
            m_tmpSX[0] = 1; m_tmpSY[0] = 1;
            for ( int k = 1; k <= lastSYbound + 1; k++ )
            {
                if ( k > lastSYbound )
                {
                    lastSYbound++;
                    m_tmpSX[k] = m_sourceX[i][j];
                    m_tmpSY[k] = m_sourceY[i][j];
                    f = (k - 1) * 16;
                    stx = ( f % 640 ) & -16;
                    sty = ( f - (f % 640)) / 640 * 16;
                    m_sourceTileX[i][j] = stx;
                    m_sourceTileY[i][j] = sty;
                    temprect.x = m_sourceX[i][j]; temprect.w = 16;
                    temprect.y = m_sourceY[i][j]; temprect.h = 16;
                    temprect1.x = stx; temprect1.w = 16;
                    temprect1.y = sty; temprect1.h = 16;
                    //TODO: Add tiles surface to Map
                    g_graphics->Blit ( g_interface->GetTileSurfaceID(), &temprect, m_tileTiledSurfaceID, &temprect1 );
                    break;
                }
                if ( m_sourceX[i][j] == m_tmpSX[k] && m_sourceY[i][j] == m_tmpSY[k] )
                {
                    f = (k - 1) * 16;
                    stx = ( f % 640 ) & -16;
                    sty = ( f - ( f % 640) ) / 640 * 16;
                    m_sourceTileX[i][j] = stx;
                    m_sourceTileY[i][j] = sty;
                    break;
                }
            }
            if (( m_animations[i][j] > 23 && m_animations[i][j] < 29) || m_animations[i][j] == 128 )
            {
                ubfp12++;
                m_flagPole1[0][ubfp12] = j * 16;
                m_flagPole1[1][ubfp12] = i * 16;
                if (m_animations[i][j] == 28) 
                    m_animations[i][j] = 24;
            } else if ( m_animations[i][j] == 37 || m_animations[i][j] == 35 || m_animations[i][j] == 34 || m_animations[i][j] == 32 || m_animations[i][j] == 129 ) {
                ubfp22++;
                m_flagPole2[0][ubfp22] = j * 16;
                m_flagPole2[1][ubfp22] = i * 16;
                if (m_animations[i][j] == 37)
                    m_animations[i][j] = 33;
            } else if ( m_animations[i][j] == 46 || m_animations[i][j] == 43 || m_animations[i][j] == 41 || m_animations[i][j] == 40 || m_animations[i][j] == 130 ) {
                ubfp32++;
                m_flagPole3[0][ubfp32] = j * 16;
                m_flagPole3[1][ubfp32] = i * 16;
                if (m_animations[i][j] == 46)
                    m_animations[i][j] = 42;
            } else if ( m_animations[i][j] == 65 || m_animations[i][j] == 60 || m_animations[i][j] == 59 || m_animations[i][j] == 58 || m_animations[i][j] == 131 ) {
                ubfp42++;
                m_flagPole4[0][ubfp42] = j * 16;
                m_flagPole4[1][ubfp42] = i * 16;
                if (m_animations[i][j] == 65)
                    m_animations[i][j] = 65;
            } else if ( m_animations[i][j] == 140 ) {
                ubfp52++;
                m_flagPole5[0][ubfp52] = j * 16;
                m_flagPole5[1][ubfp52] = i * 16;
                m_animations[i][j] = 136;
            } else if ( m_animations[i][j] == 123 ) {
                ubs2++;
                m_switches[0][ubs2] = j * 16;
                m_switches[1][ubs2] = i * 16;
            }
            countd++;
        }
    }
	sw.Stop();
    g_console->WriteLine ( "%0.3fs", sw.Elapsed() );
    BlitEntireMap();
}

int Map::DecompressMap ( unsigned char *_data, int _origSize )
{
    unsigned long szBuffer = 132394;
    int result; unsigned char TempBuffer[132394];
    memset ( TempBuffer, 0, sizeof(TempBuffer) );
    result = uncompress ( TempBuffer, &szBuffer, _data, (unsigned long)_origSize );
    ARCReleaseAssert ( szBuffer == 131072 );
    memcpy ( _data, TempBuffer, szBuffer );
    return result;
}

void Map::BlitEntireMap()
{
    System::Stopwatch sw; 
    short x; short y;

    // Allocate our map surface
    g_console->Write ( "Creating map surface... " );
    sw.Start();
	delete m_mapSurface;
    m_mapSurface = new Surface ( 4096, 4096, g_prefsManager->GetInt ( "SurfaceSplitFactor", 32 ) );
    sw.Stop();
    g_console->WriteLine ( "%0.3lfs", sw.Elapsed() );

    // Finally blit the entire thing.
    g_console->WriteLine ( "Blitting entire map..." );
    sw.Start();

    for ( y = 0; y < 256; y++ )
    {
        for ( x = 0; x < 256; x++ )
        {
            if ( m_sourceX[y][x] != -1 )
            {
                SDL_Rect TileGet, TileDest;
                TileGet.w = TileGet.h = TileDest.w = TileDest.h = 16;
                TileGet.x = m_sourceTileX[y][x];
                TileGet.y = m_sourceTileY[y][x];
                TileDest.x = x * 16;
                TileDest.y = y * 16;
				m_mapSurface->Blit ( m_tileTiledSurfaceID, &TileGet, &TileDest );
            }
        }
	}

    sw.Stop();
    g_console->WriteLine ( "Map prerender took %0.3lfs", sw.Elapsed() );

    m_mapSurface->PrintStatistics();
}
