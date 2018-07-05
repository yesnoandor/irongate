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


#include "common.h"
#include "IHidService.h"

// ----------------- Declaration Debug Zone ----------------
#ifdef 		LOG_TAG
#undef 		LOG_TAG
#endif

#define		LOG_NDEBUG 				1
#define		LOG_TAG 				"IHidService"
#include	<cutils/log.h>


namespace android
{

	//-------------------------------------------
	// 实现BpHidService  中的各个方法
	// BpNativeService 的构造函数
	BpHidService::BpHidService(const sp<IBinder>& impl) :BpInterface<IHidService>(impl) {
	
	}
	
	
	// BpHidService 的postRawData  方法的实现
	int BpHidService::writeMessage(int id,void * buf,int len){
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		ALOGI("id = %d\r\n",id);
		ALOGI("len = %d\r\n",len);

		Parcel data, reply;
		data.writeInterfaceToken(IHidService::getInterfaceDescriptor());
		data.writeInt32(id);
		data.writeInt32(len);
		data.write(buf, len);
				   
		remote()->transact(POST_RAW_DATA_TRANSACTION, data, &reply);
			
		ALOGI("get result %d\r\n", reply.readInt32());
			
		ALOGI("%s::---------------\r\n",__FUNCTION__);

		return 0;
	}


	// BpNativeService 的setCallback  方法的实现
	int BpHidService::setCallback(const sp<IHidCallback>& callback){  
		ALOGI("%s::+++++++++++++++\r\n",__FUNCTION__);

		Parcel data, reply;

		data.writeStrongBinder(IInterface::asBinder(callback));
		remote()->transact(SET_CALLBACK_TRANSACTION, data, &reply);

		ALOGI("%s::---------------\r\n",__FUNCTION__);

		return reply.readInt32();
	}
	

	// BpHidService 的getVersion 方法的实现
	String8 BpHidService::getVersion() {
		String8 version;
		
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);
	 
		Parcel data, reply;
		data.writeInterfaceToken(IHidService::getInterfaceDescriptor());
		remote()->transact(GET_VERSION_TRANSACTION, data, &reply);

		version = reply.readString8();
		
		ALOGI("ndk version : %s\r\n",version.string());
	
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);

		return version;
	}

	#if 0
	void BpHidService::setVersion(String8 version){
		ALOGI("%s:::%s::+++++++++++++++\r\n",__FILE__,__FUNCTION__);

	 	ALOGI("version = %s\r\n",version.string());

		Parcel data, reply;
		data.writeInterfaceToken(INativeService::getInterfaceDescriptor());
		data.writeString8(version);
		remote()->transact(SET_VERSION_TRANSACTION, data, &reply);
	
		ALOGI("%s:::%s::---------------\r\n",__FILE__,__FUNCTION__);
	}
	#endif

	//-------------------------------------------
	// 实现IHidService   接口的方法
	
	IMPLEMENT_META_INTERFACE(HidService, "android.HidServer.IHidService");

	
	
	
	//-------------------------------------------
	// 实现IHidService  实体类的onTransact  方法
	status_t BnHidService::onTransact(uint_t code, const Parcel& data,
		Parcel* reply, uint32_t flags) {
		switch (code) {

			case POST_RAW_DATA_TRANSACTION:{
					ALOGI("got the raw data!\n");
					CHECK_INTERFACE(INative, data, reply);

					int32_t id;
					int32_t size;
                	const void *buf;

					data.readInt32(&id);
					data.readInt32(&size);
					buf = data.readInplace(size);
					if (buf == NULL) {
						printf("get the error buf!(size = %d)\r\n",size);
						return BAD_VALUE;
					}
					
					writeMessage(id,(void *)buf,size);
					reply->writeInt32(0);
					
					return NO_ERROR;
				}
				break;
		

			case SET_CALLBACK_TRANSACTION:{
					ALOGI("set callback!\r\n");
					
					sp<IHidCallback> callback = interface_cast<IHidCallback>(data.readStrongBinder());
					reply->writeInt32(setCallback(callback));
					
					return NO_ERROR;
				}
				break;


			case GET_VERSION_TRANSACTION:{
					ALOGI("get version!\r\n");
					CHECK_INTERFACE(IHid, data, reply);

					reply->writeString8(getVersion());
					
					return NO_ERROR;
				}
				break;


				
			default:
        	    return BBinder::onTransact(code, data, reply, flags);	
				break;
		}
		
		return NO_ERROR;
	}
		
	
	

}



