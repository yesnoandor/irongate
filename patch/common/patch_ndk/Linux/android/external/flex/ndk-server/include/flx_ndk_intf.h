/************************************************************************************
Filename    :   flx_ndk_intf.h
Content     :	Flex AR NDK interface implement. 

Copyright   :   Copyright 2017 Flex, Inc. All Rights reserved.
************************************************************************************/
#ifndef FLX_NDK_INTF_H
#define FLX_NDK_INTF_H

#ifdef WINVER // windows
#ifdef STATICLIB
#define FLX_API
#else
#ifdef FLEX_SHARED_LIBRARY // dll export
#define FLX_API __declspec(dllexport)
#else // dll import for windows
#define FLX_API	 __declspec(dllimport)
#endif // FLEX_SHARED_LIBRARY
#endif // STATICLIB
#else // non window platform
#define FLX_API // no need to do declaration for android/linux
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void * FLXNDK_INSTANCE;
typedef void * FLXNDK_DEVICE;

#define FLXNDK_MAKE_VERSION(major, minor, rev) ((major&0xff)|((minor&0xff)<<8)|(rev<<16))

// call back function types
typedef void (*flxndkEventCallbackFunc)(int evtid, void *evtData, int datalen);
typedef void (*flxndkMsgCallbackFunc)(void *userdata, int msgid, void *msgData, int datalen);

typedef void * FLXNDK_DEVICE;

typedef enum {
    MSG_READ_HID = 0x1,
    MSG_WRITE_HID = 0x1<<1,
    MSG_HID_ERROR,
}MSG_TYPE;

typedef enum {
	FLXNDK_DEVICE_TYPE_IMU=0,
	FLXNDK_DEVICE_TYPE_STEREO_RGB_CAM=1,
	FLXNDK_DEVICE_TYPE_DEPTH_CAM=2,
	FLXNDK_DEVICE_TYPE_HID=3,
	FLXNDK_DEVICE_TYPE_NONE
} FLXNDK_DEVICE_TYPE;


typedef enum {
	FLXNDK_EVENT_TYPE_SLEEP=0,
	FLXNDK_EVENT_TYPE_WAKEUP=1,
	FLXNDK_EVENT_TYPE_VOICEWAKEUP=2,
} FLXNDK_EVENT_TYPE;


typedef void * FLXNDK_DEVICE_ENUMERATOR;

#define FLXNDK_EVENT_TYPE_WAKEUP	0x0001
#define FLXNDK_EVENT_TYPE_6DOF		0x0002

//-----------------------------------------------------------------
// peripheral interface version information
//-----------------------------------------------------------------
FLX_API int flxndkGetVersion(); // must return FLXNDK_MAKE_VERSION(1,0,0)
FLX_API int flxndkGetRuntimeVersion(); // currently return FLXNDK_MAKE_VERSION(1,0,0)

//-----------------------------------------------------------------
// peripheral interface initialization
//-----------------------------------------------------------------
FLX_API FLXNDK_INSTANCE flxndkInit(flxndkEventCallbackFunc callback, int evtMask);
FLX_API bool flxndkDeinit(FLXNDK_INSTANCE instance);

//-----------------------------------------------------------------
// peripheral device control
//-----------------------------------------------------------------

// query device count
FLX_API int flxndkQueryDeviceCount(FLXNDK_DEVICE_TYPE type);
// get device id
FLX_API const char * flxndkGetDeviceId(FLXNDK_DEVICE_TYPE type, int index);
// open device
FLX_API FLXNDK_DEVICE flxndkOpenDevice(const char* deviceId);
// close device
FLX_API void flxndkCloseDevice(FLXNDK_DEVICE device);

// register message callback function
FLX_API void flxndkRegisterMsgCallbackFunction(FLXNDK_DEVICE device, flxndkMsgCallbackFunc callback, void *userdata);
// write message data to device
FLX_API void flxndkWriteDeviceMsg(FLXNDK_DEVICE device, int msgid, void *msgData, int datalen);


//
// EPU
// event:
// system wakeup/sleep event, including voice wakeup source(broadcase as a standart android intent).
// 6dof data
//
// IMU device: imu sensor raw data, configuration(calibration data)
// Stereo camera device: stereo raw data, configuration(calibration data)
// Depth camera device: depth sensor raw data, configuration(calibration data)
// Gesture algorithm device: gesture msg, use protocol buffer, gesture data and hand data, 
//							commands msg, configuration
// Display device: commands(brightness, color calibration, porch vaule...)
// voice recongnition device: customized voice wakeup command configuration
//

// HMD
// event:
// system wakeup/sleep event, including voice wakeup source(broadcase as a standart android intent).
// 6dof data
//
// IMU device: imu sensor raw data, configuration
// Stereo camera device: stereo raw data, configuration
// Depth camera device: depth sensor raw data, configuration
// Gesture output device: gesture, use protocol buffer, gesture data and hand data
//						  multi-touch message for touching.

#ifdef __cplusplus
}
#endif
#endif //FLX_NDK_INTF_H
