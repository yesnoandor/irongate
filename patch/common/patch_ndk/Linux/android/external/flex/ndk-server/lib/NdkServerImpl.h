/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkServerImpl.h
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

#ifndef NDK_SERVER_IMPL_H
#define NDK_SERVER_IMPL_H

#include	"common.h"
#include	"NdkServer.h"

namespace android
{

class NdkServerImpl : public NdkServer
{
public:
    NdkServerImpl();
    virtual ~NdkServerImpl();
	virtual void startServer(NDKRole role);
private:
	int a;
};


	
}
	
#endif
	

