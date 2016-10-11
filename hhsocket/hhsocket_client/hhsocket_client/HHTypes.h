//
//  HHTypes.h
//  hhsocket_client
//
//  Created by xiaopeng on 16/9/11.
//  Copyright © 2016年 hh. All rights reserved.
//

#ifndef HHTypes_h
#define HHTypes_h

enum PictureType{
    BMP,
    JPG
};

enum ErrorCode{
    SUCCESS,
    WRONGPARAMETER,
    SERVERERROR,
    NOTPLAYERROR
};

#pragma pack(1)

typedef struct HHHeader
{
    char flag[4];
    char number[4];
    char msg_length[4];
    char type[4];
    char error_code[4];
    
}HHHeader;

typedef struct VideoControlCommand
{
    char sCamera[20];
    int  iDecodeFlag;
    char sCameraName[256];
    char bPlay;//0停止，1 播放
}VideoControlCommand;

typedef struct FetchPictureCommand
{
    char sCamera[20];
    char iPicType;//0 BMP，1 JPG 目前支持BMP
}FetchPictureCommand;

typedef struct Picture
{
    char sCamera[20];
    char iPicType;//0 BMP，1 JPG 目前支持BMP
    int  iFileLen;
    //char *pFileData;//图片文件长度的二进制数据
}Picture;

// packets
typedef struct FetchPictureCommandPacket
{
    HHHeader header;
    FetchPictureCommand body;
    
}FetchPictureCommandPacket;

typedef struct VideoControlCommandPacket
{
    HHHeader header;
    VideoControlCommand body;
    
}VideoControlCommandPacket;

typedef struct PicturePacket
{
    HHHeader header;
    Picture body;
    
}PicturePacket;

#pragma pack()


#endif /* HHTypes_h */
