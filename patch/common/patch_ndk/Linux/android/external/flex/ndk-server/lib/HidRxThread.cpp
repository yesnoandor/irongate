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
#include 	"common.h"

#include	"HidDevice.h"
#include	"HidService.h"

#include	"HidRxThread.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidRxThread"
#include	<cutils/log.h>

using namespace std;

namespace android {  
  
HidRxThread::HidRxThread(const sp<HidService> service,const sp<HidDevice> device) : Thread(false)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	mHidDevice = device;
	mHidService = service;
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
  
HidRxThread::~HidRxThread()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

bool HidRxThread::threadLoop() {	
	int i;

	int ret;
	ssize_t size;
	
	//uint8_t buf[1024];
	
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	//mUsbHid->open_device();
	
	while(!exitPending())
	{
		if(!mHidService->rx_empty())
		{			
			msg_t * item;

			item = mHidService->pop_rx_msg();
			ALOGI("id = %d",item->id);
			
			sp<IHidCallback> c = mHidService->mCallback[item->id];
    		c->notifyCallback(item->buf,item->len);

    		delete [] (char *)item->buf; 
			delete item;
		}
		else
		{
			Mutex::Autolock lock(mHidRxMutex);
			mHidRxCondition.waitRelative(mHidRxMutex,seconds(5));
		}

	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void HidRxThread::notify()
{  	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	Mutex::Autolock lock(mHidRxMutex);
	mHidRxCondition.signal();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

status_t HidRxThread::start() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    status_t res;
    res = run("HidTxThread");
    if (res != OK)
	{
        ALOGE("Unable to start hid rx thread:(%s)",strerror(res));
    }
	else
	{
    	ALOGI("start hid rx thread OK!");
    }

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t HidRxThread::stop()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}


