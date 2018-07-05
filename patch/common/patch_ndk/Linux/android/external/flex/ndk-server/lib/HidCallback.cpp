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

#include	"common.h"
#include	"HidCallback.h"


// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidCallback"
#include	<cutils/log.h>
  
namespace android{

void HidCallback::registerOnMessage(int channel,flxndkMsgCallbackFunc callback)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	onMessageFunc = callback;
	mChannel = channel;

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

int HidCallback::notifyCallback(void * buf,int len)
{
	int i;
		
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("len = %d\r\n",len);

	for(i=0;i<len;i++)
	{
		ALOGI("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);
	}

	ALOGI("report id = %d\r\n",((char *)buf)[0]);
	ALOGI("mChannel = %d\r\n",mChannel);
	
	if(((char *)buf)[0] == mChannel)
	{	
		onMessageFunc(buf,len);
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
		
	return 0;
}

status_t HidCallback::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags){
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);
		
	return BnHidCallback::onTransact(code, data, reply, flags);
}
	
} 
