# cmake最低版本要求
cmake_minimum_required(VERSION 2.8)


# 项目信息
project(OtherLib)


# 搜索本目录搜索源码并赋值给变量
aux_source_directory(. DIR_LIB_SRCS)


# 添加库文件
add_library(other SHARED ${DIR_LIB_SRCS})
