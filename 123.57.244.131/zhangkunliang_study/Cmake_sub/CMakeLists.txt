
cmake_minimum_required (VERSION 2.8)

project (testcmake)
ADD_SUBDIRECTORY(src)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)  
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
add_executable(testcmake ${DIR_SRCS})
include_directories(src)
TARGET_LINK_LIBRARIES(testcmake mymain)


# include_directories ([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
# 将指定目录添加到编译器的头文件搜索路径之下，指定的目录被解释成当前源码路径的相对路径。
# include_directories(sub) #与上个场景不同的地方在于此处
# URL:https://www.jianshu.com/p/e7de3de1b0fa