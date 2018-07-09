LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := \
	libutils \
	liblog  \
	libbinder

LOCAL_MODULE := libINdkBinder

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \

LOCAL_SRC_FILES:= \
	HidDevice.cpp \
	HidDaemonThread.cpp \
	HidTxThread.cpp \
	HidRxThread.cpp \
	HidService.cpp \
	IHidService.cpp \
	HidCallback.cpp \
	IHidCallback.cpp \
	NdkServer.cpp \
	NdkServerImpl.cpp \
	NdkClient.cpp \
	NdkClientImpl.cpp \
	
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
