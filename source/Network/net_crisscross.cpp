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

#ifdef USE_CRISSCROSS_NET

#include <crisscross/tcpsocket.h>
#include <crisscross/udpsocket.h>

#include "Network/net_crisscross.h"

#if defined ( TARGET_COMPILER_VC ) || defined ( TARGET_COMPILER_ICC )
#    pragma comment (lib, "ws2_32.lib")
#endif

using namespace CrissCross;
using namespace CrissCross::Network;

Net_CrissCross::Net_CrissCross()
 : m_udpDisabled(false), m_tcpSocket(NULL), m_udpSocket_out(NULL), m_udpSocket_in(NULL)
{
}

Net_CrissCross::~Net_CrissCross()
{
    delete m_tcpSocket; m_tcpSocket = NULL;
    delete m_udpSocket_in; m_udpSocket_in = NULL;
    delete m_udpSocket_out; m_udpSocket_out = NULL;
}

int
Net_CrissCross::Connect ( const char *_hostname, unsigned short _port )
{
    CrbReleaseAssert ( _hostname != NULL );
    int retval;

    if ( !m_udpSocket_out )
    {
        m_udpSocket_out = new UDPSocket();
        retval = m_udpSocket_out->Bind( _hostname, _port );
        if ( retval != CC_ERR_NONE )
        {
            g_console->WriteLine ( "Failed to bind to %s:%d: %d, '%s'",
                _hostname, _port, errno, CrissCross::GetErrorDescription ( retval ) );
            return retval;
        } else {
            g_console->WriteLine ( "UDP socket is ready to send data to %s:%d.", _hostname, _port );
        }
    }

    if ( !m_udpSocket_in )
    {
        m_udpSocket_in = new UDPSocket();
        retval = m_udpSocket_in->Listen ( _port + 5 );
        if ( retval != CC_ERR_NONE )
        {
            g_console->WriteLine ( "Failed to listen on UDP %d: %d, '%s'",
                _port, errno, CrissCross::GetErrorDescription ( retval ) );
            return retval;
        } else {
            g_console->WriteLine ( "UDP socket is waiting for data on port %d.", _port + 5 );
        }
    }

    if ( !m_tcpSocket )
    {
        m_tcpSocket = new TCPSocket();
        retval = m_tcpSocket->Connect ( _hostname, _port );
        if ( retval == CC_ERR_NONE )
        {
            g_console->WriteLine ( "Connection to %s:%d established!", _hostname, _port );
            return CC_ERR_NONE;
        }
        else if ( retval == CC_ERR_WOULD_BLOCK )
        {
            // We need to keep waiting.
            return CC_ERR_WOULD_BLOCK;
        }
        else
        {
            g_console->WriteLine ( "Failed to connect to %s:%d: %d, '%s'",
                _hostname, _port, retval, CrissCross::GetErrorDescription ( retval ) );
            return retval;
        }
    }
    else
    {
        switch ( m_tcpSocket->State() )
        {
        case SOCKET_STATE_CONNECTING:
            // We need to keep waiting.
            return CC_ERR_WOULD_BLOCK;

        case SOCKET_STATE_CONNECTED:
            // Our work here is done.
            g_console->WriteLine ( "Connection to %s:%d established!", _hostname, _port );
            return CC_ERR_NONE;

        case SOCKET_STATE_ERROR:
            // The connection failed.
            {
            int err = m_tcpSocket->GetError();
            if ( err != CC_ERR_NONE )
                return err;
            else
                return CC_ERR_INTERNAL;
            }

        }
    }

    CrbReleaseAbort ( "Defied physics." );
    return CC_ERR_INTERNAL;
}

int Net_CrissCross::ReceiveTCP ( int *_packetCount )
{
    static char readBuffer[NET_BUFFER_SIZE];
    static char *bufferOffset = readBuffer;
    static short bytesInBuffer = 0;

    CrbReleaseAssert ( _packetCount != NULL );
    *_packetCount = 0;

    while ( true )
    {
        unsigned int length;
        int retval;
        short packetSize;

        // Are we expecting a new packet, or do we have a partial?
        if ( !bytesInBuffer )
        {
            // We want to read the packet header.
            length = sizeof ( packetSize );

            // Get this packet's expected length
            retval = m_tcpSocket->Read ( bufferOffset, &length );

            // If we've got an error, we need to report it.
            if ( retval != CC_ERR_NONE && retval != CC_ERR_WOULD_BLOCK )
                return retval;

            // No data received, we're breaking the loop.
            if ( retval != CC_ERR_NONE || length == 0 )
                break;

            CrbDebugAssert ( length == sizeof ( packetSize ) );
            bytesInBuffer += length;
            bufferOffset += length;
        }

        // Figure out the expected packet size
        memcpy ( &packetSize, readBuffer, sizeof ( packetSize ) );

        // Is this a valid packet length?
        if ( packetSize < 1 || packetSize > (sizeof(readBuffer) - sizeof(packetSize)) )
            return CC_ERR_INVALID_BUFFER;

        length = packetSize - ( bytesInBuffer - sizeof(packetSize) );

        // Try to read the remainder of the packet.
        retval = m_tcpSocket->Read ( bufferOffset, &length );

        // If we've got an error, we need to report it.
        if ( retval != CC_ERR_NONE && retval != CC_ERR_WOULD_BLOCK )
            return retval;

        // No data received, we're breaking the loop.
        if ( retval != CC_ERR_NONE || length == 0 )
            break;

        CrbDebugAssert ( (short)length <= packetSize );
        bytesInBuffer += length;

        // We may only receive part of the remainder.
        if ( bytesInBuffer - (short)sizeof(packetSize) < packetSize )
            return CC_ERR_NONE;

        CrbDebugAssert ( bytesInBuffer - sizeof(packetSize) == packetSize );

        // Process the packet we have.
        Packet *packet = new Packet ( readBuffer + sizeof ( packetSize ), packetSize );
        m_packets.insert ( packet );
        packet = NULL;
        (*_packetCount)++;

        // Reset and prepare for the next packet.
        bytesInBuffer = 0;
        bufferOffset = readBuffer;

    }

    return CC_ERR_NONE;
}

int Net_CrissCross::ReceiveUDP ( int *_packetCount )
{
    short packetSize, remainingBytes;
    static char readBuffer[NET_BUFFER_SIZE];
    static char *bufferOffset = readBuffer;
    unsigned int length;

    CrbReleaseAssert ( _packetCount != NULL );

    *_packetCount = 0;

    length = sizeof ( readBuffer );

    // Read into the beginning of the buffer.
    int retval = m_udpSocket_in->Read ( bufferOffset, &length );

    // If we've got an error, we need to report it.
    if ( retval != CC_ERR_NONE && retval != CC_ERR_WOULD_BLOCK )
    {
        return retval;
    }

    // No data received, we're breaking the loop.
    if ( retval != 0 || length == 0 )
    {
        return CC_ERR_NONE;
    }

    // Get the expected packet size.
    memcpy ( &packetSize, bufferOffset, sizeof ( packetSize ) );
    bufferOffset += sizeof ( packetSize );

    // Make sure this is a valid size, otherwise bomb out.
    if ( packetSize < 0 || packetSize > 16384 )
        return CC_ERR_INVALID_BUFFER;

    // Calculate how many bytes we're missing.
    remainingBytes = packetSize - ( length - sizeof ( packetSize ) );

    // UDP doesn't have partial packets, it seems.
    if ( remainingBytes != 0 )
    {
        g_console->SetColour ( IO::Console::FG_YELLOW | IO::Console::FG_INTENSITY );
        g_console->WriteLine ( "UDP WARNING: An invalid UDP packet was received." );
        g_console->SetColour ();

        // Clear the buffer and hope this wasn't an attack.
        bufferOffset = readBuffer;
        memset ( readBuffer, 0, sizeof ( readBuffer ) );

        // TODO: Determine if this condition should be fatal.
        return CC_ERR_NONE;
    }

    if ( remainingBytes == 0 )
    {
        // Deserialize this packet.
        Packet *packet = new Packet ( readBuffer + sizeof ( packetSize ), packetSize );
        m_packets.insert ( packet );
        packet = NULL;
        memset ( readBuffer, 0, sizeof ( packetSize ) + packetSize );
        bufferOffset = readBuffer;
    }

    *_packetCount = 1;

    return CC_ERR_NONE;
}

int Net_CrissCross::Receive ( int *_packetCount )
{
    CrbReleaseAssert ( _packetCount );

    int TCPcount = 0, UDPcount = 0, ret = 0;

    ret = ReceiveTCP ( &TCPcount );
    if ( ret )
        return ret;

    ret = ReceiveUDP ( &UDPcount );
    if ( ret )
        return ret;

    *_packetCount = TCPcount + UDPcount;

    return CC_ERR_NONE;
}

void Net_CrissCross::DisableUDP ()
{
    m_udpDisabled = true;
}

int Net_CrissCross::Send ( const Packet *_buffer, bool _criticalData )
{
    CrbReleaseAssert ( _buffer != NULL );

    // We send with UDP only if we're able to (server can receive it) and the data is not critical.
    CoreSocket *socket = ( _criticalData || m_udpDisabled ?
        dynamic_cast<CoreSocket *>(m_tcpSocket) :
        dynamic_cast<CoreSocket *>(m_udpSocket_out) );

    // Prep the packet for transmission.
    const char *serializedData = NULL; size_t serializedDataSize;
    _buffer->Serialize ( serializedData, serializedDataSize );

    // Loop a bit if the socket is pending a transmission.
    while ( !socket->IsWritable() )
    {
        // Are we in an error state?
        if ( socket->State() == SOCKET_STATE_ERROR )
        {
            // Nuts. We are.
            return socket->GetError();
        }
    }

    // Send it.
    int dataSent = socket->Send ( serializedData, serializedDataSize );

    // Handle the error cases.
    if ( dataSent == -1 )
    {
        int err = socket->GetError();
        g_console->WriteLine ( "Data send failure, error #%d (%s)", err, GetErrorDescription(err) );
    }

    CrbReleaseAssert ( dataSent == (int)serializedDataSize );

    return 0;
}

socketState Net_CrissCross::State () const
{
    if ( m_tcpSocket )
        return m_tcpSocket->State();
    else
        return SOCKET_STATE_NOT_CREATED;
}

#endif
