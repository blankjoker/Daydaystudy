#!/bin/bash


base_path=$(pwd)


function makefile()
{
    echo "************makefile************"

    cd ${base_path}
    if [ $? -eq 0 ]; then
        make
    else
        echo "fail to cd ${base_path}"
    fi
    echo ""
}


function cleanfile()
{
    echo "************cleanfile************"

    cd ${base_path}
    if [ $? -eq 0 ]; then
        make clean
    else
        echo "fail to cd ${base_path}"
    fi
    echo ""
}