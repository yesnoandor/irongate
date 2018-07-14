/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkClientImpl.h
** 
**
**-----------------------------------------------------------------------------
** Created by:		David Xu
** Created date:	2018-07-02
** Version:		1.0
** Descriptions:	
**
**-----------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:
**
******************************************************************************/
#ifndef NDK_CLIENT_IMPL_H
#define NDK_CLIENT_IMPL_H
		
//#include "common.h"
#include	"NdkClient.h"

#include	"IHidService.h"	
		
namespace android
{



class NdkClientImpl : public RefBase
{
public:
	NdkClientImpl();
	~NdkClientImpl();

public:
	String8 getVersion();
	int writeMessage(int id,void * buf,int len);
	int registerOnMessage(int channel,ndkCallbackFunc onMessage);

private:
	sp<IHidService> mIHidService;

};
	
	
		
}
		
#endif
		

