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



void onMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}
	
	printf("%s::---------------\r\n",__FUNCTION__);
}


// ʵ��client   
int main() {
	String8 version;
	char buf[32];

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	sp<NdkClient> client = new NdkClient();

	// �õ��汾��
	version = client->getVersion();
	printf("version = %s\r\n",version.string());

	// ע�᲻ͬͨ���Ĵ�����
	printf("register onMessage callback function...\r\n");
	client->registerOnMessage(CHANNEL_GESTURE,onMessage);

	// ����д���ݷ���
	printf("write data into epu...\r\n");
	memset(buf,0x00,sizeof(buf));
	for(unsigned int i=0;i<sizeof(buf);i++)
	{
		buf[i] = 3*i+3;
	}
	
	do{
		client->writeMessage(CHANNEL_GESTURE,(void *)buf,sizeof(buf));
		sleep(20);
	}while(1);
	
	printf("%s::---------------\r\n",__FUNCTION__);
	
	return 0;
}



