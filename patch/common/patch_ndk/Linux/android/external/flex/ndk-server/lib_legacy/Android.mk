LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog  \
	libbinder \
	libINdkBinder

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \

LOCAL_MODULE := libflex_ndk_api

LOCAL_SRC_FILES:= \
	flex_ndk_api.cpp 

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)


