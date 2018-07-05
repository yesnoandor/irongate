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

LOCAL_MODULE := ndkClient

LOCAL_SRC_FILES:= \
	NdkClientDemo.cpp \

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)



