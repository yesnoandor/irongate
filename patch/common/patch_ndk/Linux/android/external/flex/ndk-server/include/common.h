#ifndef COMMON_H
#define COMMON_H

// C
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>



// C++
#include <iostream>
#include <fstream>
#include <string>
#include <list>


// Binder
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/BinderService.h>
#include <binder/IMemory.h>

// Typedef
typedef enum
{
	EPU = 0,
	HMD = 1
}NDKRole;


typedef enum
{
	CHANNEL_VENDOR = 1,
	CHANNEL_GESTURE,
	CHANNEL_SENSOR,
	CHANNEL_FISHEYE,
	CHANNEL_ANDROID,
	CHANNEL_HID,
}NDKChannel;




typedef void (*ndkCallbackFunc)(void * buf, int len);


#endif
