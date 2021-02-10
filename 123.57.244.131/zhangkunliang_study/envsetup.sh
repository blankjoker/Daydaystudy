#!/bin/bash

base_path=$(pwd)
debug_lib_dir="/lib/Debug"
release_lib_dir="/lib/Release"
debug_lib_path=${base_path}${debug_lib_dir}
release_lib_path=${base_path}${release_lib_dir}
source_config=${base_path}/config/doip_server_config.xml
target_config="/tmp/doip_server_config.xml"

ipc_path="/tmp"

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
    cleanfile

    if [ $1 ]
    then
        ipc_path=$1
        if [ ! -d ${ipc_path} ]; then
          sudo mkdir -p -m 755 ${ipc_path}
          echo "sudo mkdir -p -m 777 ${ipc_path} done"
        fi
        echo "IPC user-confirmed path : ${ipc_path}"
    else
        read -p "please input socket ipc communication path. using default path: ${ipc_path}?" ipc_path
        if [ ! $ipc_path ]
        then
            ipc_path="/tmp"
        fi
        echo "IPC path: ${ipc_path}"
    fi

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

function linkto()
{
    if [ ! $1 ]
    then
        read -p "link to release or debug? default: debug?" var_linkto
        if [ ! $var_linkto ]
        then
            var_linkto="debug"
        fi
    else
        var_linkto=$1
    fi

    if [[ $var_linkto = "release" ]]
    then
        echo "link to release"
        export LD_LIBRARY_PATH=${release_lib_path}
        echo ${LD_LIBRARY_PATH}
    else
        if [[ $var_linkto = "debug" ]]
        then
            echo "link to debug"
            export LD_LIBRARY_PATH=${debug_lib_path}
            echo ${LD_LIBRARY_PATH}
        else
            echo "unknown input ${var_linkto}"
        fi
    fi
}
