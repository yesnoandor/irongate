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

#ifndef NDK_SERVICE_H
#define NDK_SERVICE_H
	
#include "common.h"


namespace android
{

class NdkServer : public RefBase
{
public:
	//static sp<NdkServer> create();

	//static sp<NdkServer> create()
	//{
	//	return sp<NdkServer>(new NdkServerImpl());
		//new NdkServerImpl();
	//}
	static sp<NdkServer> create();

public:
	//NdkServer();
	//virtual ~NdkServer();
	virtual void startServer(NDKRole role) = 0;

	
};


	
}
	
#endif
	

