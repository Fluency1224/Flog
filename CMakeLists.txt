#编译链设置###################################################################
#告知当前使用的是交叉编译方式
#SET(CMAKE_SYSTEM_NAME Linux)

#SET(CMAKE_CROSS_TOOLS "")
#SET(CMAKE_CROSS_TOOLS "arm-linux-")
#指定c交叉编译器，必须配置
#或交叉编译器使用绝对地址
#SET(CMAKE_C_COMPILER ${CMAKE_CROSS_TOOLS}gcc)
#指定C++交叉编译器
#SET(CMAKE_CXX_COMPILER ${CMAKE_CROSS_TOOLS}g++)

#设置编译参数
#set(CMAKE_C_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS "-Wall")
#SET(CMAKE_C_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
#SET(CMAKE_C_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -DNDEBUG")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -DNDEBUG")

#设置编译版本
#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_BUILD_TYPE Release)

#1.cmake verson,指定cmake版本
#用来指定CMake的最低版本
cmake_minimum_required(VERSION 2.6)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT (EVENT_KEY)

#3.向当前工程添加一个需要构建的子目录，并且可以指定中间二进制文件和目标文件爱呢存放位置
ADD_SUBDIRECTORY(src/flog)
ADD_SUBDIRECTORY(src/main)


