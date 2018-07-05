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
**			�ṩ����Ndk Server�Ľӿ�
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

	// ��ʼ��HidService  ����
	HidService::instantiate(role);
	
	// �����̳߳�
	ProcessState::self()->startThreadPool();
	
	// �ȴ��߳̽���
	IPCThreadState::self()->joinThreadPool();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}



}

	

