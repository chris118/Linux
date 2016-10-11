//
//  Utility.h
//  hhsocket_client
//
//  Created by xiaopeng on 16/9/11.
//  Copyright © 2016年 hh. All rights reserved.
//

#ifndef Utility_h
#define Utility_h

#define btye char

/**
 * 将int数值转换为占四个字节的byte数组，本方法适用于(低位在前，高位在后)的顺序。 和bytesToInt（）配套使用
 * @param value
 *            要转换的int值
 * @return byte数组
 */
btye* intToBytes( int value);
/**
 * 将int数值转换为占四个字节的byte数组，本方法适用于(高位在前，低位在后)的顺序。  和bytesToInt2（）配套使用
 */
btye* intToBytes2(int value);

#endif /* Utility_h */
