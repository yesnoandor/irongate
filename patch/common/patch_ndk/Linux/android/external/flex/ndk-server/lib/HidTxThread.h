/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidTxThread.h
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

class 	HidTxThread : public Thread
{
public:
    HidTxThread(const sp<HidService> service,const sp<HidDevice> device);
	
private:
    virtual  ~HidTxThread();

public:	
    virtual bool threadLoop();



public:	
	status_t start();
	status_t stop();
	void notify();

private:
    sp<HidTxThread> mHidTxThread;
	
	mutable Mutex mHidTxMutex;
	Condition mHidTxCondition;

	sp<HidDevice> mHidDevice;
	sp<HidService> mHidService;

  
};

}
