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

LOCAL_MODULE := ndkServer

LOCAL_SRC_FILES:= \
	NdkServerDemo.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)

