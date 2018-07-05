#ifndef COMMON_H
#define COMMON_H

// C
#include <stdio.h>
#include <math.h>
#include <fcntl.h>


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
	CH_VENDOR_OUT = 1,
	CH_VENDOR_IN,
	CH_GESTURE_OUT,
	CH_GESTURE_IN
}NDKChannel;


typedef void (*flxndkMsgCallbackFunc)(void * buf, int len);


#endif
