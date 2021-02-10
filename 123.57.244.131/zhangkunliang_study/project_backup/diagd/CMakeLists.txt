CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(diagd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -pthread")

INCLUDE_DIRECTORIES(
include
../core/include
../iov/doip/include
)

AUX_SOURCE_DIRECTORY(src DTSERVICE_SRC_FILES)

add_executable(diagd ${DTSERVICE_SRC_FILES})

target_link_libraries(diagd ncore socket nedoipstackserver)

install(TARGETS diagd
        RUNTIME
        DESTINATION /usr/bin
)
