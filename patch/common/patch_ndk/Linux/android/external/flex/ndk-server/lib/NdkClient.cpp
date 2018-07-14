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
#include	"NdkClientImpl.h"
#include	"NdkClient.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkClient"
#include	<cutils/log.h>

namespace android
{

NdkClient::NdkClient()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	mNdkClientImpl = new NdkClientImpl();
		
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
	
NdkClient::~NdkClient()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

String8 NdkClient::getVersion()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return mNdkClientImpl->getVersion();
}

int NdkClient::writeMessage(int id,void * buf,int len)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return mNdkClientImpl->writeMessage(id,buf,len);
}


int NdkClient::registerOnMessage(int channel,ndkCallbackFunc callback)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return mNdkClientImpl->registerOnMessage(channel,callback);
}

}
