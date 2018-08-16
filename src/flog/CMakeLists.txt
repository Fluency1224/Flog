#1.指定头文件目录
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

#2.指定源文件目录，并查找当前目录下所有源文件，将名称保存到SRC_FILE变量中
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} SRC_FILLE)

#3.指定生成动态库，参数SHARED,floga.so,静态库和动态库名称不能一样


#4.指定生成静态库，参数STATIC,floga.a
ADD_LIBRARY(floga STATIC ${SRC_FILLE})
SET_TARGET_PROPERTIES(floga PROPERTIES VERSION 1.2 SOVERSION 1)
SET_TARGET_PROPERTIES(floga PROPERTIES OUTPUT_NAME flog)

#5.将生成的目标文件存放到源码目录下的dist下
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

#6.生成可执行文件
#7.将生成的可执行文件存放到dist目录下

