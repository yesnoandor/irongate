LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        $(call all-logtags-files-under, src)

LOCAL_MODULE := settings-logtags

include $(BUILD_STATIC_JAVA_LIBRARY)

# Build the Settings APK
include $(CLEAR_VARS)

LOCAL_JAVA_LIBRARIES := bouncycastle core-oj telephony-common ims-common telephony-ext
LOCAL_STATIC_JAVA_LIBRARIES := \
    android-support-v4 \
    android-support-v13 \
    android-support-v7-recyclerview \
    android-support-v7-preference \
    android-support-v7-appcompat \
    android-support-v14-preference \
    jsr305 \
    settings-logtags

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
        $(call all-java-files-under, src) \
        src/com/android/settings/EventLogTags.logtags
LOCAL_SRC_FILES += src/org/codeaurora/wfcservice/IWFCService.aidl \
                   src/org/codeaurora/wfcservice/IWFCServiceCB.aidl

#Flex :: java files overlay ++++++++++
ifeq ($(CODE_OVERLAY),true)

base_file_overlay_subdir := $(addprefix ../../../device/qcom/msm8998/overlay/, $(LOCAL_PATH)/)
$(warning $(base_file_overlay_subdir))
overlay_java_file = $(call all-java-files-under,$(base_file_overlay_subdir))
LOCAL_SRC_FILES += $(overlay_java_file)

empty :=
base_overlay_files := $(subst $(base_file_overlay_subdir),$(empty),$(overlay_java_file))
$(warning $(base_overlay_files))

LOCAL_SRC_FILES := $(filter-out $(base_overlay_files), $(LOCAL_SRC_FILES))
endif
#Flex :: java files overlay ----------

LOCAL_RESOURCE_DIR := $(LOCAL_PATH)/res \
    frameworks/support/v7/preference/res \
    frameworks/support/v14/preference/res \
    frameworks/support/v7/appcompat/res \
    frameworks/support/v7/recyclerview/res

LOCAL_PACKAGE_NAME := Settings
LOCAL_CERTIFICATE := platform
LOCAL_PRIVILEGED_MODULE := true

LOCAL_PROGUARD_FLAG_FILES := proguard.flags

LOCAL_AAPT_FLAGS := --auto-add-overlay \
    --extra-packages android.support.v7.preference:android.support.v14.preference:android.support.v17.preference:android.support.v7.appcompat:android.support.v7.recyclerview

ifneq ($(INCREMENTAL_BUILDS),)
    LOCAL_PROGUARD_ENABLED := disabled
    LOCAL_JACK_ENABLED := incremental
    LOCAL_DX_FLAGS := --multi-dex
    LOCAL_JACK_FLAGS := --multi-dex native
endif

include frameworks/opt/setupwizard/library/common-full-support.mk
include frameworks/base/packages/SettingsLib/common.mk

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
ifeq (,$(ONE_SHOT_MAKEFILE))
include $(call all-makefiles-under,$(LOCAL_PATH))
endif