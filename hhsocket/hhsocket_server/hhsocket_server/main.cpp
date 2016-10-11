#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "HHTypes.h"

int main(int argc, const char * argv[])
{
    std::cout << "running....\n";
    
    try
    {
        // Create the socket
        ServerSocket server ( 30000 );
        
        while ( true )
        {
            
            ServerSocket new_sock;
            server.accept ( new_sock );
            
            try
            {
                while ( true )
                {
//                    std::string data;
//                    new_sock >> data;
//                    std::cout << "We received from the client:\n\"" << data << "\"\n";
//                    new_sock << data;
                    
                    FetchPictureCommandPacket packet;
                    new_sock.recv(&packet, sizeof(packet));
                    
                    FetchPictureCommand body = packet.body;
                    std::cout << body.sCamera <<  "\"\n";
                    
//                    VideoControlCommandPacket packet;
//                    new_sock.recv(&packet, sizeof(packet));
//
//                    VideoControlCommand body = packet.body;
//                    std::cout << body.sCameraName <<  "\"\n";
                }
            }
            catch ( SocketException& ) {}
            
        }
    }
    catch ( SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    
    return 0;
}
