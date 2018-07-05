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

#include	"HidDaemonThread.h"
#include	"HidTxThread.h"
#include	"HidService.h"


// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidService"
#include	<cutils/log.h>


namespace android {

HidService::HidService():BnHidService()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);


		
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
	
HidService::~HidService()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

void HidService::instantiate(NDKRole role) {
	sp<HidService> server;
	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	server = new HidService();
	server->startServer(role);
	defaultServiceManager()->addService(String16("service.ndk"), server);
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

	
int HidService::writeMessage(int id,void * buf,int len)
{
	msg_t * item;
		
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("id = %d",id);
	ALOGI("len = %d",len);
				
	for(int i=0;i<len;i++)
	{
		ALOGI("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);
	}

	item = new msg_t;
	item->buf = new char[len];
	item->len = len;
		
	memcpy((char *)item->buf,buf,len);

	#if 0
	for(int i=0;i<16;i++)
	{
		ALOGI("item[%d] = 0x%x\r\n",i,((char *)item->buf)[i]);
	}
	#endif

	push_msg(item);
		
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return 0;
}


int HidService::setCallback(const sp<IHidCallback>& callback)
{
	ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

	mCallback.push_back(callback);

	ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

	return 0;
}

String8 HidService::getVersion()
{
	String8 version = String8("1.0");
		
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
		
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return version;
}


void HidService::startServer(NDKRole role){
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("role = %s",role ? "HMD" : "EPU");

	// 
	mHidDevice = new HidDevice(this,role);

	// 
	mHidDaemonThread = new HidDaemonThread(this,mHidDevice);
	mHidDaemonThread->start();

	// 
	mHidTxThread = new HidTxThread(this,mHidDevice);
	mHidTxThread->start();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}


void HidService::push_msg(msg_t * item)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	mHidTxQueue.push_back(item);
	mHidTxThread->notify();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

msg_t * HidService::pop_msg()
{
	msg_t * item;
	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	item = mHidTxQueue.front();
	mHidTxQueue.pop_front();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return item;
}


bool HidService::empty()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return mHidTxQueue.empty();
}

	
}

	

