/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidService.h
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

#ifndef HID_DEVICE_H
#define HID_DEVICE_H


//#include	"NdkThread.h"

//#include 	<string>

//using namespace std;

//#include	"INativeService.h"
//#include	"NativeService.h"

using namespace std;

namespace android {


class NdkThread;
class NdkTxThread;
class HidService;

typedef struct msg_t
{
    int id;
    void * buf;
    int len;
}msg_t;




class HidDevice : public RefBase
{
public:
	static const string HMD_HID_DEVICE_NAME;
	static const string EPU_HID_DEVICE_NAME;
	

public:
	//UsbHid();
	HidDevice(sp<HidService> service,NDKRole role);
	
	virtual ~HidDevice();

//private:
public:

	bool open_device(string name = "/dev/hidg0");
	void close_device();
	
	bool set_feature_report(char * buf,int len);
	bool get_feature_report(char * buf,int len);
	
	bool write_hid_report(char * buf,int len);
	int read_hid_report(char * buf,int len);

	bool query_device();

//private:
public:
	int m_hid_fd;
	string m_hid_name;

	//sp<NdkThread> mNdkThread;
	sp<HidService> mHidService;

	//sp<NdkTxThread> mNdkTxThread;
	//list<msg_t *> mNdkTxQueue;
};


}



#endif


