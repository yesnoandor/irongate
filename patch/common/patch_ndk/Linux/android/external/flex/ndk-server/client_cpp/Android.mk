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

LOCAL_MODULE := hmd_ndk_client

LOCAL_SRC_FILES:= \
	HmdNdkClientDemo.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	liblog  \
	libbinder \
	libINdkBinder

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \

LOCAL_MODULE := epu_ndk_client

LOCAL_SRC_FILES:= \
	EpuNdkClientDemo.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
