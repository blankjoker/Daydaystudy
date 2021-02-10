
LOCAL_PATH :=$(call my-dir)

################aidl##################
include $(CLEAR_VARS)
LOCAL_LDLIBS    := -lm -llog

LOCAL_CFLAGS := -Wall -Werror
LOCAL_CLANG := true
LOCAL_MODULE := libdoipmanageraidl
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
        libbinder \
        libutils

LOCAL_AIDL_INCLUDES := $(LOCAL_PATH)/include/binder/
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/include \

LOCAL_SRC_FILES := include/binder/nesat/IDoipManagerService.aidl \
                   include/binder/nesat/IDoipManagerListener.aidl \


include $(BUILD_SHARED_LIBRARY)

##################################doipmanager############################
include $(CLEAR_VARS)

LOCAL_MODULE       	:= diagd
LOCAL_INIT_RC       := diagd.rc
LOCAL_MODULE_TAGS   := optional
LOCAL_C_INCLUDES := frameworks/native/include \
                    $(LOCAL_BASE_PATH)/include \
                    frameworks/core/include \
                    $(LOCAL_BASE_PATH)/servicebase \
                    $(LOCAL_BASE_PATH)/include/servicebase \
                    $(LOCAL_BASE_PATH)/include/sysctrlmanager \
                    $(LOCAL_BASE_PATH)/sysctrlmanager \
                    $(LOCAL_BASE_PATH)/sysctrlmanager/src \
                    $(LOCAL_BASE_PATH)/sysctrlmanager/binder \
                    hardware/libhardware/include/hardware \
                    system/core/include/utils \
                    system/core/include/cutils \
                    $(LOCAL_PATH)/doipmanager/include \
                    $(LOCAL_PATH)/doipmanager/src \
                    frameworks/services/networkmanager/include \
                    frameworks/services/networkmanager/include/binder \
                    frameworks/services/ucomservice/include \
                    frameworks/services/ucomservice/include/binder \
                    externals/libxml2/include \
                    externals/icu4c/common \
                    external/icu/icu4c/source/common \
                    system/extras/libpagemap/include/pagemap \
                    system/core/storaged \
                    frameworks/services/dtservice/include \
                    system/iov/doip/include \
                    $(TARGET_OUT_HEADERS)


LOCAL_SRC_FILES :=  main.cpp \
                    diagd.cpp \
                    doipmanager/src/DoipManager.cpp \

LOCAL_STATIC_LIBRARIES := libxml2

LOCAL_SHARED_LIBRARIES := libservicebase \
                          libbinder  \
                          libcutils  \
                          libutils  \
                          liblog  \
                          libsysctrlaidl  \
                          libnetworkmanageraidl \
                          libdoipmanageraidl \
                          libicuuc \
                          libpagemap \
                          libhardware \
                          libstoragedinfoaidl \
                          libdtlib \
                          libstcbase \
                          libnedoipstackserver \
#                           libucomdiagaidl \
#                           libucommaidl \

include $(BUILD_EXECUTABLE)

##################################TestClient############################
include $(CLEAR_VARS)

LOCAL_MODULE        := DoipManagerTest
LOCAL_MODULE_TAGS   := eng

LOCAL_C_INCLUDES := $(LOCAL_PATH)


LOCAL_SRC_FILES :=  test/DoipManagerTest.cpp


LOCAL_SHARED_LIBRARIES := libservicebase libbinder libcutils libutils liblog libtimemanageraidl libstcbase

include $(BUILD_EXECUTABLE)
