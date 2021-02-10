
cmake_minimum_required (VERSION 2.8)

# project (testcmake)

# add_executable(testcmake main.cpp)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

ADD_LIBRARY(mymain SHARED /root/zhangkunliang_study/Cmake/mymain.cpp /root/zhangkunliang_study/Cmake/mymain.h)
