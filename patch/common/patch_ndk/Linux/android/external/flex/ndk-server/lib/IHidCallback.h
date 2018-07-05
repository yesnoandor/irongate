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

// ����callback  �ӿ�IHidCallback
class IHidCallback : public IInterface{
public:
	// ������һЩ���룬����
	// ������ֶ�descriptor��
	// �����������Ա����asInterface��getInterfaceDescriptor
	// ����˹�������������
	DECLARE_META_INTERFACE(HidCallback);

	// �ýӿڶ����ṩ�Ĳ����ӿ�
	virtual int notifyCallback(void *buf,int len) = 0;
};

// ����ö��IHidCallback	�ӿڵ����з���
enum {
	NOTIFY_CALLBACK_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
};

// ����IHidCallback   �ӿڵ�ʵ����BnHidCallback, �̳�BnInterface
class BnHidCallback : public BnInterface<IHidCallback>{
public:
	virtual status_t    onTransact( uint32_t code,  
                                    const Parcel& data,  
                                    Parcel* reply,  
                                    uint32_t flags = 0);
};

// ����IHidCallback  �ӿڵ�������BpHidCallback, �̳�BpInterface
class BpHidCallback: public BpInterface<IHidCallback> {
public:
	BpHidCallback(const sp<IBinder>& impl);
	virtual int notifyCallback(void *buf,int len);
};



}


#endif
