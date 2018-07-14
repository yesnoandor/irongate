/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidTxThread.cpp
** 
**
**-----------------------------------------------------------------------------
** Created by:		David Xu
** Created date:	2018-07-02
** Version:		1.0
** Descriptions:	
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

#include	"HidTxThread.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidTxThread"
#include	<cutils/log.h>

using namespace std;

namespace android {  
  
HidTxThread::HidTxThread(const sp<HidService> service,const sp<HidDevice> device) : Thread(false)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	mHidDevice = device;
	mHidService = service;
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
  
HidTxThread::~HidTxThread()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

bool HidTxThread::threadLoop() {	
	int ret;
	ssize_t size;
	
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	while(!exitPending()){
		if(!mHidService->tx_empty())
		{			
			msg_t * item;

			item = mHidService->pop_tx_msg();
			mHidDevice->write_hid_report((char *)item->buf,item->len);

			delete [] (char *)item->buf; 
			delete item;
		}
		else
		{
			Mutex::Autolock lock(mHidTxMutex);
			mHidTxCondition.wait(mHidTxMutex);
			//mHidTxCondition.waitRelative(mHidTxMutex,seconds(5));
		}
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void HidTxThread::notify()
{  	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	Mutex::Autolock lock(mHidTxMutex);
	mHidTxCondition.signal();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

status_t HidTxThread::start() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    status_t res;
    res = run("HidTxThread");
    if (res != OK)
	{
        ALOGE("Unable to start hid tx thread:(%s)",strerror(res));
    }
	else
	{
    	ALOGI("start hid tx thread OK!");
    }

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t HidTxThread::stop()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}


