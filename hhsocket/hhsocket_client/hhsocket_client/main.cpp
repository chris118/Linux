//
//  main.cpp
//  hhsocket_client
//
//  Created by xiaopeng on 16/9/5.
//  Copyright © 2016年 hh. All rights reserved.
//
#include "ClientSocket.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "HHLog.hpp"

int main(int argc, const char * argv[])
{
    try
    {
        
        // test purpose:"127.0.0.1", "30000"
        LOG("main starting.... ");
        
        ClientSocket client_socket1;
        char* p = NULL;
        client_socket1.Demo(p);
        
        
        const char* ip = argv[1];
        int port = atoi(argv[2]);
        const char* sCamera = argv[3];
        
        cout << "ip: " << ip << endl;
        cout << "port: " << port << endl;
        cout << "sCamera: " << sCamera << endl;
        
        LOG2("ip address", ip);
        LOG2("port", port);
        LOG2("sCamera", sCamera);
        
        ClientSocket client_socket ( ip, port );
        
        try
        {
            // start video
            if(client_socket.ControlVideo(sCamera, 150, "", true) == false)
            {
                LOG("failed to start video...");
                return SERVERERROR;
            }
            
            sleep(1);
            
            while(true)
            {
                LOG("try to fetch picture...");
                
                int length = 0;
                char* picture  = client_socket.FetchPicture(sCamera, length);
                
                // if the picture data is null, continue the next fetch procedure
                if(picture)
                {
                    LOG("success to get picture...");
                    
                    time_t timep;
                    time(&timep); /*获取time_t类型的当前时间*/
                    std::string filename(asctime(gmtime(&timep)));
                    filename = filename.append(".bmp");

                    
                    ofstream fout(filename, ios::binary);
                    fout.write(picture, length);
                    fout.close();
                    
//                    cout << "length:" << length << "data: " << picture << endl;
                }
                else
                {
                    continue;
                    LOG("can't get the picture...");
                }
            }
        }
        catch ( SocketException& ) {}        
    }
    catch ( SocketException& e )
    {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }
    
    return 0;
}

