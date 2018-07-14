/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidCallback.h
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

#include "common.h"
#include "IHidService.h" 
#include "IHidCallback.h"

//typedef void (*MsgCallbackFunc)(int channel, void * buf, int len);


namespace android{
	
class HidCallback: public BnHidCallback{  
	friend class BinderService<HidCallback>;

public:
	virtual int notifyCallback(void *buf,int len);
	virtual     status_t    onTransact(  
                                uint32_t code,  
                                const Parcel& data,  
                                Parcel* reply,  
                                uint32_t flags); 

	virtual void registerOnMessage(int channel,ndkCallbackFunc callback);

private:
	ndkCallbackFunc onMessageFunc;
	int	mChannel;
	
};


}  

