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
#ifndef HID_SERVICE_H
#define HID_SERVICE_H

//#include "common.h"
#include "IHidService.h"
#include "IHidCallback.h"

#include "HidDevice.h"
//#include "HidDaemonThread.h"



namespace android {

class HidDaemonThread;
class HidTxThread;

class HidService : public BnHidService
{
	friend class BinderService<HidService>;
	
public:
	static void instantiate(NDKRole role);
	void startServer(NDKRole role);

	virtual int writeMessage(int id,void * buf,int len);
	virtual int setCallback(const int channel,const sp<IHidCallback>& callback);
	virtual String8 getVersion();

	void push_msg(msg_t * item);
	msg_t * pop_msg();
	bool empty();
	
public:
	HidService();

public:
	Vector<sp<IHidCallback>> mCallback;
	Vector<int> mChannel;
	list<msg_t *> mHidTxQueue;

private:
	String8 mVersion;		
	sp<HidDevice> mHidDevice;
	
	sp<HidDaemonThread> mHidDaemonThread;
	sp<HidTxThread> mHidTxThread;
    
private:
    virtual ~HidService();

};




}; // namespace android

#endif

