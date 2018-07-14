LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog  \
	libbinder \
	libINdkBinder \
	libflex_ndk_api

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \

LOCAL_MODULE := ndk_legacy_client

LOCAL_SRC_FILES:= \
	native-lib.cpp 

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
