# Copyright @ 2013 - 2015 Suntec Software(Shanghai) Co., Ltd.
# All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are NOT permitted except as agreed by
# Suntec Software(Shanghai) Co., Ltd.
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

LOCAL_PATH := $(call my-dir)

##################################################
# libnedoipstackclient.so

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/ne_doip_util.c \
	src/ne_doip_connection.c \
	src/ne_doip_os.c \
	src/ne_doip_event_loop.c \
	src/ne_doip_thread.c \
	src/ne_doip_timer.c \
	src/ne_doip_client.c \
	src/ne_doip_node.c \
	src/ne_doip_client_manager.c \
	src/ne_doip_node_manager.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_MODULE := libnedoipstackclient

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS :=	-fvisibility=hidden -Wall -Werror

LOCAL_CPPFLAGS :=

LOCAL_SHARED_LIBRARIES := liblog

LOCAL_LDFLAGS := -lpthread

include $(BUILD_SHARED_LIBRARY)

##################################################
# libnedoipstackserver.so

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	src/ne_doip_util.c \
	src/ne_doip_connection.c \
	src/ne_doip_os.c \
	src/ne_doip_event_loop.c \
	src/ne_doip_thread.c \
	src/ne_doip_timer.c \
	src/ne_doip_server.c \
	src/ne_doip_server_manager.c \
	src/ne_doip_config.c \
	src/ne_doip_data_queue.c \
	src/ne_doip_select.c \
	src/ne_doip_threadpool.c \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_MODULE := libnedoipstackserver

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS :=	-fvisibility=hidden -Wall -Werror

LOCAL_CPPFLAGS :=

LOCAL_SHARED_LIBRARIES := liblog

LOCAL_LDFLAGS := -lpthread

include $(BUILD_SHARED_LIBRARY)
include $(call first-makefiles-under,$(LOCAL_PATH))