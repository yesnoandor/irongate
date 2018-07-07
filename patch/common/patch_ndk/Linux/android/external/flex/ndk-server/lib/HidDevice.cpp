/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidDevice.cpp
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


#include	"common.h" 

#include	"IHidService.h"
#include	"HidService.h"
//#include	"NdkThread.h"
//#include	"NdkTxThread.h"

#include	"HidDevice.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidDevice"
#include	<cutils/log.h>

using namespace std;

// ----------------- Macr Define -------------------------
namespace android {

//static const 成员跟static  成员一样在类外初始化（而不是在构造函数初始化列表中），记得加上关键字const
const string HidDevice::HMD_HID_DEVICE_NAME = "/dev/hidg0";
const string HidDevice::EPU_HID_DEVICE_NAME = "/dev/flxhmd";

HidDevice::HidDevice(sp<HidService> service,NDKRole role)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	if(role == EPU)
	{
		m_hid_name = EPU_HID_DEVICE_NAME;
	}
	else
	{
		m_hid_name = HMD_HID_DEVICE_NAME;
	}

	ALOGI("m_hid_name = %s\r\n",m_hid_name.c_str());

	mHidService = service;

	HidDevice::open_device();


	//mNdkTxThread = new NdkTxThread(this);
	//mNdkTxThread->start();

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

HidDevice::~HidDevice()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
	
bool HidDevice::open_device(string name)
{
	bool ret = true;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    m_hid_fd = open(name.c_str(),O_RDWR);
    if (m_hid_fd < 0){
        ALOGE("failed to open usb hid device(%s)",name.c_str());
        ret = false;
    }

    ALOGI("%s::---------------\r\n",__FUNCTION__);

    return ret;
}

void HidDevice::close_device()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	if(m_hid_fd > 0)
        close(m_hid_fd);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

bool HidDevice::set_feature_report(char * buf,int len)
{
	
#if 0
    if(m_hid_fd < 0)
        return false;
    uint8_t reportID = data[0];
    if(reportID == 0)
    {
        data++;
        length++;
    }
    int r = ioctl(fd, HIDIOCSETFEAURE(length),data);
    return (r>=0);
#endif

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
	return true;
}

bool HidDevice::get_feature_report(char * buf,int len)
{
#if 0
    if(fd<0)
        return false;
    int r = ioctl(fd, HIDIOCGETFEAURE(length),data);
    return (r>=0);
#endif

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return true;
}

bool HidDevice::write_hid_report(char * buf,int len)
{
	bool ret = false;
	ssize_t size = 0;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	if(m_hid_fd)
	{
		ALOGI("len = %d",len);
		for(int i=0;i<len;i++)
		{
			ALOGI("buf[%d] = 0x%x",i,buf[i]);
		}
	
		size = write(m_hid_fd,buf,len);
		if(size > 0)
		{
			ALOGI("len = %d",len);
    		ALOGI("size = %d",static_cast<int>(size));

    		ret = true;
		}
	}

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return (ret);
}

int HidDevice::read_hid_report(char * buf, int len)
{
	bool ret = false;
    ssize_t size = 0;

	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	if(m_hid_fd)
	{
		size = read(m_hid_fd,buf,len);
		if(size > 0)
		{
			ALOGI("len = %d",len);
			ALOGI("size = %d",static_cast<int>(size));

			ret = true;
		}
	}

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return	(size);
}




}



