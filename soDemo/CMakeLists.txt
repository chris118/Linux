# 搜索本目录搜索源码并赋值给变量
# cmake最低版本要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project(DynamicLibDemon)

# 搜索本目录搜索源码并赋值给变量
aux_source_directory(. PROJECT_SOURCE_DIR)


LINK_DIRECTORIES(./Math ./Other)

# 添加库文件
add_executable(Demon ${PROJECT_SOURCE_DIR})

# 链接动态库
target_link_libraries(Demon mymath other)
