/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		IHidCallback.cpp
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


#include "common.h"
#include "IHidCallback.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"IHidCallback"
#include	<cutils/log.h>

namespace android{

//-------------------------------------------
// ʵ��ICallback   �ӿ���������ĸ�������
// BpCallback �Ĺ��캯��
BpHidCallback::BpHidCallback(const sp<IBinder>& impl) :BpInterface<IHidCallback>(impl) {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	ALOGI("%s::---------------\r\n",__FUNCTION__);
}

// BpHidCallback ��notifyCallback	������ʵ��
// ��û��ʵ��notifyCallback �Ĺ���
// ���ǿ���̵���Binder  ʵ�����BnInterface��notifyCallback ����
int BpHidCallback::notifyCallback(void *buf,int len) {
	ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

	//Parcel data,reply;

		//data.writeInt32(a);
		//remote()->transact(NOTIFY_CALLBACK_TRANSACTION,data,&reply);


		Parcel data, reply;
		//data.writeInterfaceToken(ICallback::getInterfaceDescriptor());
		data.writeInt32(len);
		data.write(buf, len);
		remote()->transact(NOTIFY_CALLBACK_TRANSACTION,data,&reply);

		ALOGI("%s::---------------\r\n",__FUNCTION__);
				
		return reply.readInt32();
	}
	
	//-------------------------------------------
	// ʵ��IHidCallback	�ӿڵķ���
	IMPLEMENT_META_INTERFACE(HidCallback, "android.HidServer.IHidCallback");

 
	//-------------------------------------------
	// ʵ��ICallback  �ӿ�ʵ�����onTransact  ����
	status_t BnHidCallback::onTransact(uint32_t code, 
										const Parcel& data, 
										Parcel* reply, 
										uint32_t flags){

		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		ALOGI("code = %d\r\n",code);

		switch (code) {
			case NOTIFY_CALLBACK_TRANSACTION:{
				//CHECK_INTERFACE(Itestbinder, data, reply);  
				//reply->writeInt32(notifyCallback((int) data.readInt32()) );

				int32_t size;
                const void *buf;
				
				data.readInt32(&size);
				buf = data.readInplace(size);
				if (buf == NULL) {
					printf("get the error buf!(size = %d)\r\n",size);
					return BAD_VALUE;
				}

				notifyCallback((uint8_t *)buf,size);
				reply->writeInt32(0);
				
				return NO_ERROR;
			}
			break;

			default:{
				return BBinder::onTransact(code, data, reply, flags);
			}
		}
		
		ALOGI("%s::---------------\r\n",__FUNCTION__);
	}  
}  

