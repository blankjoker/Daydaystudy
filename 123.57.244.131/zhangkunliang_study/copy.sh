#!/bin/sh
exe="./doip_clent"
des="/home/zhang/zhangkunliang_study/DoIP_Client"

deplist=$(ldd $exe | awk '{if (match($3,"/")){ printf("%s "),$3 } }')

cp $deplist $des
