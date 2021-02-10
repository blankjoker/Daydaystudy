LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := udsserver
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := sample/uds_server.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES := libnedoipstackclient

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := udsclient
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := sample/uds_client.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES := libnedoipstackclient
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := doipdaemon
LOCAL_MODULE_TAGS := eng
LOCAL_SRC_FILES := sample/doip_daemon.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SHARED_LIBRARIES := libnedoipstackserver
include $(BUILD_EXECUTABLE)
