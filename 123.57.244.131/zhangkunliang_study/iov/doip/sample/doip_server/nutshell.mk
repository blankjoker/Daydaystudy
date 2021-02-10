# Copyright @ 2019 iAuto (Shanghai) Co., Ltd.
# All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are NOT permitted except as agreed by
# iAuto (Shanghai) Co., Ltd.
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.


LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    main.c \

LOCAL_C_INCLUDES := \
    system/iov/doip/include \

LOCAL_MODULE:= doip_server

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := -O2

LOCAL_SHARED_LIBRARIES := \
                    libnedoipstackserver \

LOCAL_LDFLAGS := -lpthread -lrt -ldl

include $(BUILD_EXECUTABLE)