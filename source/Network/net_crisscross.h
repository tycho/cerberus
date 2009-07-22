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

#ifndef __included_net_crisscross_h
#define __included_net_crisscross_h

#include "Network/net.h"
#include "Network/packet.h"

#ifdef USE_CRISSCROSS_NET

class Net_CrissCross : public Net
{
protected:
    bool m_udpDisabled;

    CrissCross::Network::TCPSocket *m_tcpSocket;
    CrissCross::Network::UDPSocket *m_udpSocket_out;
    CrissCross::Network::UDPSocket *m_udpSocket_in;

    virtual int ReceiveTCP ( int *_packetCount );
    virtual int ReceiveUDP ( int *_packetCount );

public:
    Net_CrissCross();
    virtual ~Net_CrissCross();

    virtual void                  DisableUDP();
    virtual int                   Connect ( const char *_hostname, unsigned short _port );
    virtual int                   Receive ( int *_packetCount );
    virtual int                   Send ( const Packet *_buffer, bool _criticalData );
    virtual Network::socketState  State () const;
};

#endif

#endif
