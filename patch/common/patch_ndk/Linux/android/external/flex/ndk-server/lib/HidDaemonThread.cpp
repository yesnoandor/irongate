/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		HidDaemonThread.cpp
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


#include 	"common.h"

#include	"HidDevice.h"
#include	"HidService.h"
#include	"IHidCallback.h"

#include	"HidDaemonThread.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"HidDaemonThread"
#include	<cutils/log.h>

using namespace std;

namespace android {  
  
HidDaemonThread::HidDaemonThread(const sp<HidService> service,const sp<HidDevice> device) : Thread(false)
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	mHidService = service;
	mHidDevice = device;
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}
  
HidDaemonThread::~HidDaemonThread()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  

bool HidDaemonThread::threadLoop() {

	fd_set readfds;
	
	int i;
	int maxfd,fd;
	int ret;
	int size;
	
	char buf[MAX_HID_BUFFER_SIZE];
	
    ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
	while(!exitPending())
	{
		size = 0;
		maxfd = 0;
		maxfd = fd = mHidDevice->m_hid_fd;

		FD_ZERO(&readfds);
		
		FD_SET(fd, &readfds);

		ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
		switch(ret)
		{
			case -1:
				//exit = 1;
				ALOGE("usb hid select failed!(err = %s)\r\n",strerror(errno));
				break;
				
			case 0:
				ALOGW("usb hid select timeout!\r\n");
				break;
		
			default:
				ALOGI("get data event!\r\n");
				if (FD_ISSET(fd, &readfds))
				{
					size = mHidDevice->read_hid_report(buf, MAX_HID_BUFFER_SIZE);
					if(size < 0)
					{	
						ALOGE("socket (%d) recv failed!(size = %d,err = %s)\r\n",i,size,strerror(errno));
						break;
					}
					else if(size == 0)
					{
						ALOGW("socket(%d) disconnect\r\n",i);
						continue;
					}
					else	
					{
						ssize_t len = 0;

						ALOGI("size = %d\r\n",(int)size);
						for(i=0;i<size;i++)
						{
							ALOGI("buf[%d] = 0x%x\r\n",i,buf[i]);
						}

						ALOGI("mCallback size = %d\r\n",(int)mHidService->mCallback.size());
						ALOGI("mChannel size = %d\r\n",(int)mHidService->mChannel.size());

						for(i=0;i<(int)mHidService->mCallback.size();i++)
						{
    						sp<IHidCallback> c = mHidService->mCallback[i];
    						int channel = mHidService->mChannel[i];

    						ALOGI("filter channel = %d",channel);
    						ALOGI("real channel = %d",((char *)buf)[0]);

    						if(channel == ((char *)buf)[0])
							{
								msg_t * item;
								
								item = new msg_t;
								item->buf = new char[size];
								item->len = size;
								item->id = i;

								memcpy((char *)item->buf,buf,item->len);
								mHidService->push_rx_msg(item);
								//c->notifyCallback(buf,size);
    						}
    					}
					}		
				}
				break;
		}
 
		
	}
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);

    return true;
}  


void HidDaemonThread::notify()
{  	
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	Mutex::Autolock lock(mHidDaemonMutex);
	mHidDaemonCondition.signal();
	
	ALOGI("%s::---------------\r\n",__FUNCTION__);
}  



status_t HidDaemonThread::start() {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);
	
    status_t res;
    res = run("HidDaemonThread");
    if (res != OK)
	{
        ALOGE("Unable to start hid daemon thread:(%s)",strerror(res));
    }
	else
	{
    	ALOGI("start hid daemon thread OK!");
    }

	ALOGI("%s::---------------\r\n",__FUNCTION__);
	
    return res;
}

status_t HidDaemonThread::stop()
{
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

    requestExitAndWait();

	ALOGI("%s::---------------\r\n",__FUNCTION__);

	return OK;
}


  
}


