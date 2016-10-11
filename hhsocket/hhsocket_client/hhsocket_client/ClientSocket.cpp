// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "HHLog.hpp"

ClientSocket::ClientSocket()
{
}

void ClientSocket::Demo(char* pData)
{
    char* temp = new char[100];
    pData = temp;
}

ClientSocket::ClientSocket ( std::string host, int port )
{
    if ( ! Socket::create() )
    {
        throw SocketException ( "Could not create client socket." );
    }
    
    if ( ! Socket::connect ( host, port ) )
    {
        throw SocketException ( "Could not bind to port." );
    }
    send_packet_index = 0;
}

ClientSocket:: ~ClientSocket()
{
}

const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
    if ( ! Socket::send ( s ) )
    {
        throw SocketException ( "Could not write to socket." );
    }
    
    return *this;
    
}

const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
    if ( ! Socket::recv ( s ) )
    {
        throw SocketException ( "Could not read from socket." );
    }
    
    return *this;
}


char* ClientSocket::FetchPicture(std::string camera, int &length, PictureType type){
    
    FetchPictureCommandPacket packet;
    HHHeader header;
    
    FetchPictureCommand command;
    strcpy(command.sCamera, camera.c_str());
    char cPicType = '0';
    strcpy(&command.iPicType, &cPicType);
    
    std::string flag = ".msg";
    strcpy(header.flag, flag.c_str());
    memcpy(header.number, intToBytes2(send_packet_index), 4);
    memcpy(header.msg_length, intToBytes2(sizeof(command)), sizeof(header.msg_length));
    // 类型 3 为 客户端请求图片数据
    byte* command_type = hexStringToByte("01000003");
    memcpy(header.type, command_type, 4);
    memcpy(header.error_code, intToBytes2(0), 4);
    
    packet.header = header;
    packet.body = command;
    
    if ( ! Socket::send ( &packet, sizeof(packet) ) )
    {
        LOG("failed to send fetch picture command...");
        return NULL;
    }
    else
    {
        // success to send packet, increase the local index
        send_packet_index++;
        
        // receive the packet from the server
        HHHeader backHeader;
        if(!Socket::recv(&backHeader, sizeof(HHHeader)))
        {
            LOG("failed to recv fetch picture header...");
            return NULL;
        }
        
        // if the error_code != 0; failed to fetch picture,
        if(bytesToInt2(backHeader.error_code, 0) != 0)
        {
            return NULL;
        }
  
        int iFileLen = bytesToInt2(backHeader.msg_length, 0);
        if(iFileLen > 0)
        {
            int iReadTotal = 0;
            int iRead = 0;
            char* szData = new char[iFileLen];
            while (iReadTotal < iFileLen)
            {
                iRead = iFileLen - iReadTotal;
                if (iRead > 100)
                {
                    iRead = 100;
                }
                if(!Socket::recv(szData + iReadTotal, iRead))
                {
                    break;
                }
                iReadTotal += iRead;
            }
            
            length = iFileLen - 25;
            return szData + 25;
        }
        
        if(command_type)
        {
            delete command_type;
        }
        //picture = received_packet.body;
        
        return NULL;
    }
    

}

bool ClientSocket::ControlVideo(std::string camera, int iDecodeFlag, std::string camera_name, bool bPlay)
{
    VideoControlCommandPacket packet;
    HHHeader header;
    
    VideoControlCommand command;
    strcpy(command.sCamera, camera.c_str());
    strcpy(command.sCameraName, camera_name.c_str());
    command.iDecodeFlag = htonl(iDecodeFlag);
    command.bPlay = bPlay;
    
    std::string flag = ".msg";
    strcpy(header.flag, flag.c_str());
    
    memcpy(header.number, intToBytes2(send_packet_index), 4);
    memcpy(header.msg_length, intToBytes2(sizeof(command)), 4);
    // 类型 2 为 客户端 control the video
    byte* command_type = hexStringToByte("01000002");
    memcpy(header.type, command_type, 4);
    memcpy(header.error_code, intToBytes2(0), 4);
    
    packet.header = header;
    packet.body = command;
    
    
    if ( ! Socket::send ( &packet, sizeof(packet) ) )
    {
        return false;
    }
    send_packet_index++;
    
    // receive the packet from the server
    HHHeader backHeader;
    if(!Socket::recv(&backHeader, sizeof(HHHeader)))
    {
        LOG("failed to recv control video header...");
        return false;
    }
    
    // if the error_code != 0; failed to control video,
    if(bytesToInt2(backHeader.error_code, 0) != 0)
    {
        return false;
    }
    
    if(command_type)
    {
        delete command_type;
    }
    return true;
}


