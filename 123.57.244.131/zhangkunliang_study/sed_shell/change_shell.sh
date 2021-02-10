#!/bin/bash

ipc_path="/home/kun/zhang"

line_code="CFLAGS += -D NE_DOIP_IPC_PATH=\\\\\"${ipc_path}\\\\\""

# sed -i '/DEFINE_YUQIANG/{n;d}' makefile
# sed -i "N;46a $line_code" makefiles
# sed -i '/^DEFINE_YUQIANG/line_code/' makefile

sed -i "/^CFLAGS += -D NE_DOIP_IPC_PATH/c$line_code" makefile
sync


