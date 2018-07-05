/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		NdkClient.h
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
#ifndef NDK_CLIENT_H
#define NDK_CLIENT_H
		
#include "common.h"

namespace android
{

class 	NdkClientImpl;

class NdkClient : public RefBase
{
public:
	NdkClient();
	 virtual ~NdkClient();

public:
	String8 getVersion();
	int writeMessage(int id,void * buf,int len);
	int registerOnMessage(int channel,flxndkMsgCallbackFunc callback);
	

private:
	sp<NdkClientImpl> mNdkClientImpl;
};
	
	
		
}
		
#endif
		

