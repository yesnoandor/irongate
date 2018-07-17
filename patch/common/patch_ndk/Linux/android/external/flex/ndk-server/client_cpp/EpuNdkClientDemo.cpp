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
#include 	"common.h"
#include 	"NdkClient.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"NdkClientDemo"
#include	<cutils/log.h>

using namespace android;



void onVendorMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}


void onGestureMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}

void onSensorMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}

void onFishEyeMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}

void onAndroidMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}



// 实现client   
int main() {
	String8 version;
	char buf[32];

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	sp<NdkClient> client = new NdkClient();

	// 得到版本号
	version = client->getVersion();
	printf("version = %s\r\n",version.string());

	// 注册不同通道的处理函数
	printf("register onVendorMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_VENDOR,onVendorMessage);

	printf("register onGestureMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_GESTURE,onGestureMessage);

	printf("register onSensorMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_SENSOR,onSensorMessage);

	printf("register onFishEyeMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_FISHEYE,onFishEyeMessage);

	printf("register onAndroidMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_ANDROID,onAndroidMessage);

	// 调用写数据方法
	printf("write data into hmd...\r\n");
	
	do{
		// 测试GESTURE OUT  通道
		memset(buf,0x00,sizeof(buf));
		for(unsigned int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i+3;		// report id = 3,channel --> gesture out
		}
	
		client->writeMessage(CHANNEL_GESTURE,(void *)buf,sizeof(buf));
		sleep(10);

		// 测试SENSOR OUT  通道
		memset(buf,0x00,sizeof(buf));
		for(unsigned int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i+5;		// report id = 5,channel --> sensor out
		}
	
		client->writeMessage(CHANNEL_SENSOR,(void *)buf,sizeof(buf));
		sleep(10);

		// 测试FISHEYE OUT  通道
		memset(buf,0x00,sizeof(buf));
		for(unsigned int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i+7;		// report id = 7,channel --> fisheye out
		}
	
		client->writeMessage(CHANNEL_FISHEYE,(void *)buf,sizeof(buf));
		sleep(10);

		// 测试ANDROID OUT  通道
		memset(buf,0x00,sizeof(buf));
		for(unsigned int i=0;i<sizeof(buf);i++)
		{
			buf[i] = 3*i+9;		// report id = 9,channel --> android out
		}
	
		client->writeMessage(CHANNEL_ANDROID,(void *)buf,sizeof(buf));
		sleep(10);

	}while(1);
	
	printf("%s::---------------\r\n",__FUNCTION__);
	
	return 0;
}



