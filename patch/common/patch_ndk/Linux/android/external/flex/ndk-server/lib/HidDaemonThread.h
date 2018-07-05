/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidDaemonThread.h
** 
**
**-----------------------------------------------------------------------------
** Created by:		David Xu
** Created date:	2018-07-02
** Version:		1.0
** Descriptions:	The original version
**
**-----------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:
**
******************************************************************************/

#include	"HidDevice.h"

using namespace std;

namespace android {

class HidDaemonThread : public Thread
{
public:
    HidDaemonThread(const sp<HidService> service,const sp<HidDevice> device);
    virtual  ~HidDaemonThread();

public:
    virtual bool threadLoop();
    //virtual void     requestExit();
    //void requestLock();


public:	
	status_t start();
	status_t stop();

	void notify();

//private:
	

private:
    sp<HidDaemonThread> mHidDaemonThread;
	
	mutable Mutex mHidDaemonMutex;
	Condition mHidDaemonCondition;

	sp<HidDevice> mHidDevice;
	sp<HidService> mHidService;

};

}

