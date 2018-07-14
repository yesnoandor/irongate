/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkServerDemo.cpp
** 
**
**-----------------------------------------------------------------------------
** Created by:		David Xu
** Created date:	2018-07-02
** Version:		1.0
** Descriptions:	
**			���� Ndk Server ��Ӧ�ó��� (ͨ��libINdkBinder.so�Ľӿ�)
**-----------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:
**
******************************************************************************/
#include "common.h"
#include "NdkServer.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkServiceDemo"
#include	<cutils/log.h>

using namespace android;

// ʵ��server  �˵�Ӧ�ó���
int main() {
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	//sleep(30);
	
	sp<NdkServer> server = NdkServer::create();
	server->startServer(EPU);

	printf("%s::---------------\r\n",__FUNCTION__);
	
	return 0;
}

