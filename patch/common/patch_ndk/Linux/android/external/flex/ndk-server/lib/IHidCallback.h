/******************************************************************************
** Copyright (C), 2017-2018, Flex Co. Ltd 
** All rights reserved.
** 
** File name: 		IHidCallback.h
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
#ifndef IHID_CALLBACK_H    
#define IHID_CALLBACK_H

//using namespace android;

namespace android{

// 申明callback  接口IHidCallback
class IHidCallback : public IInterface{
public:
	// 申明了一些代码，包括
	// 添加了字段descriptor，
	// 添加了两个成员函数asInterface，getInterfaceDescriptor
	// 添加了构造器和析构器
	DECLARE_META_INTERFACE(HidCallback);

	// 该接口对外提供的操作接口
	virtual int notifyCallback(void *buf,int len) = 0;
};

// 声明枚举IHidCallback	接口的所有方法
enum {
	NOTIFY_CALLBACK_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
};

// 声明IHidCallback   接口的实体类BnHidCallback, 继承BnInterface
class BnHidCallback : public BnInterface<IHidCallback>{
public:
	virtual status_t    onTransact( uint32_t code,  
                                    const Parcel& data,  
                                    Parcel* reply,  
                                    uint32_t flags = 0);
};

// 声明IHidCallback  接口的引用类BpHidCallback, 继承BpInterface
class BpHidCallback: public BpInterface<IHidCallback> {
public:
	BpHidCallback(const sp<IBinder>& impl);
	virtual int notifyCallback(void *buf,int len);
};



}


#endif
