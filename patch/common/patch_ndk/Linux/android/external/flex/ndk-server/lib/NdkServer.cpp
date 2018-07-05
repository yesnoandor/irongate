/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkService.cpp
** 
**
**-----------------------------------------------------------------------------
** Created by:		David Xu
** Created date:	2018-07-02
** Version:		1.0
** Descriptions:	
**			提供启动Ndk Server的接口
**
**-----------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:
**
******************************************************************************/

#include	"common.h"
#include	"NdkServer.h"
#include	"NdkServerImpl.h"
#include	"NdkClientImpl.h"


// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkServer"
#include	<cutils/log.h>


namespace android
{


sp<NdkServer> NdkServer::create()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return sp<NdkServer>(new NdkServerImpl());
}

//NdkServer::NdkServer() {
//}

//NdkServer::~NdkServer() {
//}




}

	
