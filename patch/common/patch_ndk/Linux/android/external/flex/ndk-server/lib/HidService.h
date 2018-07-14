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


typedef enum
{
	CH_VENDOR_OUT = 1,		// EPU --> HMD
	CH_VENDOR_IN,			// HMD --> EPU
	CH_GESTURE_OUT,			// EPU --> HMD
	CH_GESTURE_IN,			// HMD --> EPU
	CH_END,
}NDKReportID;


class HidDaemonThread;
class HidTxThread;
class HidRxThread;

class HidService : public BnHidService
{
	friend class BinderService<HidService>;
	
public:
	static void instantiate(NDKRole role);
	void startServer(NDKRole role);

	virtual int writeMessage(int id,void * buf,int len);
	virtual int setCallback(const int channel,const sp<IHidCallback>& callback);
	virtual String8 getVersion();

	void push_tx_msg(msg_t * item);
	msg_t * pop_tx_msg();
	bool tx_empty();


	void push_rx_msg(msg_t * item);
	msg_t * pop_rx_msg();
	bool rx_empty();
	
public:
	HidService();

public:
	NDKRole mRole;
	Vector<sp<IHidCallback>> mCallback;
	Vector<int> mChannel;
	list<msg_t *> mHidTxQueue;
	list<msg_t *> mHidRxQueue;

private:
	String8 mVersion;		
	sp<HidDevice> mHidDevice;
	
	sp<HidDaemonThread> mHidDaemonThread;
	sp<HidTxThread> mHidTxThread;
	sp<HidRxThread> mHidRxThread;
    
private:
    virtual ~HidService();

};




}; // namespace android

#endif

