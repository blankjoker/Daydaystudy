#!/bin/bash

base_path=$(pwd)
debug_lib_dir="/lib/Debug"
release_lib_dir="/lib/Release"
debug_lib_path=${base_path}${debug_lib_dir}
release_lib_path=${base_path}${release_lib_dir}
source_config=${base_path}/config/doip_server_config.xml
target_config="/tmp/doip_server_config.xml"

ipc_path="/tmp"
# ipc_path_line_code="CFLAGS = -DNE_DOIP_IPC_PATH=\\\\\"${ipc_path}\\\\\""

if [[ $1 = "release" ]]
then
    echo "makefile is release"
    export LD_LIBRARY_PATH=${release_lib_path}
else
    echo "makefile is debug"
    export LD_LIBRARY_PATH=${debug_lib_path}
fi
echo ${LD_LIBRARY_PATH}

if [ $2 ]
then
    ipc_path=$2
    echo "IPC user-confirmed path : ${ipc_path}"
else
    echo "IPC use default path : ${ipc_path}"
fi


function cleanfile()
{
    echo "************cleanfile************"

    cd ${base_path}/src
    if [ $? -eq 0 ]; then
        make clean
    else
        echo "fail to cd ${base_path}/src"
    fi

    cd ${base_path}/sample/doip_daemon
    if [ $? -eq 0 ]; then
        make clean
    else
        echo "fail to ${base_path}/sample/doip_daemon"
    fi

    cd ${base_path}/sample/uds_server
    if [ $? -eq 0 ]; then
        make clean
    else
        echo "fail to ${base_path}/sample/uds_server"
    fi

    cd ${base_path}/sample/uds_client
    if [ $? -eq 0 ]; then
        make clean
    else
        echo "fail to ${base_path}/sample/uds_client"
    fi

    echo "rm -rf ${base_path}/bin/*"
    rm -rf ${base_path}/bin/*

    echo "rm -rf ${base_path}/lib/*"
    rm -rf ${base_path}/lib/*

    echo "rm -rf ${base_path}/src/obj"
    rm -rf ${base_path}/src/obj

    echo "rm -rf ${base_path}/sample/doip_daemon/obj"
    rm -rf ${base_path}/sample/doip_daemon/obj

    echo "rm -rf ${base_path}/sample/uds_server/obj"
    rm -rf ${base_path}/sample/uds_server/obj

    echo "rm -rf ${base_path}/sample/uds_client/obj"
    rm -rf ${base_path}/sample/uds_client/obj

    cd ${base_path}
    echo ""
}

function makefile()
{
    echo "************makefile************"

    # sed -i "/^CFLAGS = -DNE_DOIP_IPC_PATH/c${ipc_path_line_code}" ${base_path}/src/makefile

    cd ${base_path}/src
    if [ $? -eq 0 ]; then
        make IPC_PATH=${ipc_path}
    else
        echo "fail to cd ${base_path}/src"
    fi

    cd ${base_path}/sample/doip_daemon
    if [ $? -eq 0 ]; then
        make 
    else
        echo "fail to cd ${base_path}/sample/doip_daemon"
    fi

    cd ${base_path}/sample/uds_server
    if [ $? -eq 0 ]; then
        make 
    else
        echo "fail to cd ${base_path}/sample/uds_server"
    fi

    cd ${base_path}/sample/uds_client
    if [ $? -eq 0 ]; then
        make 
    else
        echo "fail to cd ${base_path}/sample/uds_client"
    fi

    cd ${base_path}
    echo ""
}

function cpconfig()
{
    echo "************cpconfig************"

    echo "cp ${source_config} ${target_config}"
    cp ${source_config} ${target_config}

    echo ""
}
