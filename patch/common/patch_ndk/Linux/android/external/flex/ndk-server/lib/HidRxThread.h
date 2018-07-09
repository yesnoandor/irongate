/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidService
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
#pragma once


//#include	"HidDevice.h"

//using namespace std;

namespace android {

class 	HidRxThread : public Thread
{
public:
    HidRxThread(const sp<HidService> service,const sp<HidDevice> device);
	
private:
    virtual  ~HidRxThread();

public:	
    virtual bool threadLoop();



public:	
	status_t start();
	status_t stop();
	void notify();

private:
    sp<HidRxThread> mHidRxThread;
	
	mutable Mutex mHidRxMutex;
	Condition mHidRxCondition;

	sp<HidDevice> mHidDevice;
	sp<HidService> mHidService;

  
};

}

