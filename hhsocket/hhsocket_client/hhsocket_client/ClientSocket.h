// Definition of the ClientSocket class

#ifndef ClientSocket_class
#define ClientSocket_class

#include "Socket.h"
#include "HHTypes.h"
#include "Utility.h"
#include "SocketException.h"



class ClientSocket : private Socket
{
public:
    
    ClientSocket ( std::string host, int port );
    ClientSocket();
    virtual ~ClientSocket();
    
    const ClientSocket& operator << ( const std::string& ) const;
    const ClientSocket& operator >> ( std::string& ) const;
    
    const ClientSocket& operator << ( void* ) const;
    const ClientSocket& operator >> ( void* ) const;
    
    char* FetchPicture(std::string camera, int &length, PictureType type = BMP);
    bool ControlVideo(std::string camera, int  iDecodeFlag, std::string camera_name, bool bPlay);
    void Demo(char* pData);
private:
    int send_packet_index;
    
};


#endif
