/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkServerImpl.cpp
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
#include	"HidService.h"
#include	"NdkServerImpl.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkServerImpl"
#include	<cutils/log.h>


namespace android
{

NdkServerImpl::NdkServerImpl():NdkServer()
{

}

NdkServerImpl::~NdkServerImpl()
{

}

// 
void NdkServerImpl::startServer(NDKRole role)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	sp <ProcessState> proc(ProcessState::self());

	// 初始化HidService  单例
	HidService::instantiate(role);
	
	// 启动线程池
	ProcessState::self()->startThreadPool();
	
	// 等待线程结束
	IPCThreadState::self()->joinThreadPool();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}



}

	

