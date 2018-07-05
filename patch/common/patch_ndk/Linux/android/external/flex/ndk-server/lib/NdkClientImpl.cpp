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
#include "HidCallback.h"
#include "NdkClientImpl.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkClientImpl"
#include	<cutils/log.h>

namespace android
{

NdkClientImpl::NdkClientImpl()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	// 获取service manager 引用
	sp <IServiceManager> sm = defaultServiceManager();
	// 获取ndk  的binder  接口对象
	sp <IBinder> binder = sm->getService(String16("service.ndk"));
	// 转为sp <IHidService>
	mIHidService = interface_cast <IHidService> (binder);

	ProcessState::self()->startThreadPool();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
	
NdkClientImpl::~NdkClientImpl()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

String8 NdkClientImpl::getVersion()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return mIHidService->getVersion();
}

int NdkClientImpl::writeMessage(int id,void * buf,int len)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return mIHidService->writeMessage(id,buf,len);
}

int NdkClientImpl::registerOnMessage(int channel,flxndkMsgCallbackFunc onMessage)
{
	int ret;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	sp<HidCallback> callback = new HidCallback();
	callback->registerOnMessage(channel,onMessage);
	
	ret = mIHidService->setCallback(callback);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return ret;
}




}

