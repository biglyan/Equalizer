
/* Copyright (c) 2005, Stefan Eilemann <eile@equalizergraphics.com> 
   All rights reserved. */

#include "socketConnection.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace eqNet;
using namespace std;

SocketConnection::~SocketConnection()
{
    close();
}

//----------------------------------------------------------------------
// connect
//----------------------------------------------------------------------
bool SocketConnection::connect()
{
    if( _state != STATE_CLOSED )
        return false;

    _state = STATE_CONNECTING;

    _createSocket();

    // TODO: execute launch command

    sockaddr_in socketAddress;
    _parseAddress( socketAddress );

    const bool connected = (::connect( _readFD, (sockaddr*)&socketAddress, 
            sizeof(socketAddress)) == 0);

    if( connected )
        _state = STATE_CONNECTED;
    else
    {
        WARN( "Could not connect socket: %s\n", strerror( errno ));
        close();
    }
    
    return connected;
}

void SocketConnection::_createSocket()
{
    const int fd = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if( fd == -1 )
    {
        string error = strerror( errno );
        throw connection_error("Could not create socket: " + error);
    }

    const int on = 1;
    setsockopt( fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on) );

    _readFD  = fd;
    _writeFD = fd; // TCP/IP sockets are bidirectional
    return;
}

void SocketConnection::close()
{
    if( _readFD == -1 )
        return;

    const bool closed = ( ::close(_readFD) == 0 );
    if( !closed )
        WARN( "Could not close socket: %s\n", strerror( errno ));

    _readFD  = -1;
    _writeFD = -1;
    _state   = STATE_CLOSED;
}

void SocketConnection::_parseAddress( sockaddr_in& socketAddress )
{
    uint32_t ip = INADDR_ANY;
    short port = DEFAULT_PORT;

    if( _description.TCPIP.address != NULL )
    {
        char *ipName = strdup( _description.TCPIP.address );
	const size_t len = strlen( ipName );
	
	for( size_t i=0; i<len; i++ )
	{
            if( ipName[i] == ':' )
            {
                ipName[i] = '\0';
                const char *portName = &ipName[i+1];

                if( portName != NULL )
                {
                    port = (short)atoi( portName );
                    if( port == 0 ) port = DEFAULT_PORT;
                }

                break;
            }
        }

        if( strlen( ipName ) > 0 )
            ip = atoi( ipName );

        free( ipName );
    }

    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = htonl( ip );
    socketAddress.sin_port = htons( port );
}

//----------------------------------------------------------------------
// listen
//----------------------------------------------------------------------
bool SocketConnection::listen()
{
    if( _state != STATE_CLOSED )
        return false;

    _state = STATE_CONNECTING;

    _createSocket();

    sockaddr_in socketAddress;
    _parseAddress( socketAddress ); //XXX restrict IP unimplemented

    const bool bound = (::bind( _readFD, (sockaddr *)&socketAddress,
            sizeof(socketAddress) ) == 0);

    if( !bound )
    {
        WARN( "Could not bind socket: %s\n", strerror( errno ));
        close();
        return false;
    }

    const bool listening = (::listen( _readFD, 10 ) == 0);
        
    if( listening )
        _state = STATE_LISTENING;
    else
    {
        WARN( "Could not listen on socket: %s\n", strerror( errno ));
        close();
    }

    return listening;
}

//----------------------------------------------------------------------
// accept
//----------------------------------------------------------------------
Connection* SocketConnection::accept()
{
    if( _state != STATE_LISTENING )
        return NULL;

    sockaddr_in newAddress;
    socklen_t   newAddressLen = sizeof( newAddress );
    int fd;

    do
        fd = ::accept( _readFD, (sockaddr*)&newAddress, &newAddressLen );
    while( fd == -1 && errno == EINTR );

    if( fd == -1 )
    {
        WARN( "accept failed: %s\n", strerror( errno ));
        return NULL;
    }

    SocketConnection* newConnection = new SocketConnection();
    newConnection->_readFD  = fd;
    newConnection->_writeFD = fd;
    newConnection->_state   = STATE_CONNECTED;

    return newConnection;
}
