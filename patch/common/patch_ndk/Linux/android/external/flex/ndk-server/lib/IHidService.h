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
** Descriptions:
**			1. 声明binder 服务(Hid Service) 的接口
**			2. 声明binder 服务(Hid Service) 的实体类
**			3. 声明binder 服务(Hid Service) 的引用类
**			4. 声明binder 服务(Hid Service) 所有方法的枚举值
**
**-----------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:
**
******************************************************************************/


#ifndef IHID_SERVICE_H
#define IHID_SERVICE_H

#include "common.h"
#include "IHidCallback.h"

//using namespace android;
//using namespace std;


namespace android
{

// 申明Hid Service  接口IHidService
class IHidService : public IInterface
{			
public:
	// 申明了一些代码，包括
	// 添加了字段descriptor，
	// 添加了两个成员函数asInterface，getInterfaceDescriptor
	// 添加了构造器和析构器
	DECLARE_META_INTERFACE(HidService);

	// 该服务对外提供的操作接口
	virtual int writeMessage(int id,void * buf,int length) = 0;			// 传输原始数据
	virtual int setCallback(const sp<IHidCallback>& callback) = 0;	// 设置回调
	virtual String8 getVersion() = 0;
};


// 声明IHidService	接口所有方法的枚举
enum
{
	POST_RAW_DATA_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
	SET_CALLBACK_TRANSACTION,
	GET_VERSION_TRANSACTION,
};
			

// 声明binder  服务的实体类BnHidService, 继承BnInterface  
class BnHidService: public BnInterface<IHidService>
{
public:
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,uint32_t flags = 0);
};


// 声明binder  服务的引用类BpHidService, 继承BpInterface
class BpHidService: public BpInterface<IHidService> {

public:
	BpHidService(const sp<IBinder>& impl);

	virtual int writeMessage(int id,void * buf,int len);
	virtual int setCallback(const sp<IHidCallback>& callback);
	virtual String8 getVersion();
};


}

#endif


