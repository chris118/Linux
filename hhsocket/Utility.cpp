//
//  Utility.cpp
//  hhsocket_client
//
//  Created by xiaopeng on 16/9/11.
//  Copyright © 2016年 hh. All rights reserved.
//

#include <stdio.h>
#include "Utility.h"

btye*  intToBytes( int value )
{
    btye* src = new btye[4];
    src[3] =  (btye) ((value>>24) & 0xFF);
    src[2] =  (btye) ((value>>16) & 0xFF);
    src[1] =  (btye) ((value>>8) & 0xFF);
    src[0] =  (btye) (value & 0xFF);
    
    return src;
}

btye* intToBytes2(int value)
{
    btye* src = new btye[4];
    src[0] = (btye) ((value>>24) & 0xFF);
    src[1] = (btye) ((value>>16)& 0xFF);
    src[2] = (btye) ((value>>8)&0xFF);
    src[3] = (btye) (value & 0xFF);
    return src;
}