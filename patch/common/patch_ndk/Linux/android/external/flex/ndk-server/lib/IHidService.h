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
**			1. ����binder ����(Hid Service) �Ľӿ�
**			2. ����binder ����(Hid Service) ��ʵ����
**			3. ����binder ����(Hid Service) ��������
**			4. ����binder ����(Hid Service) ���з�����ö��ֵ
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

// ����Hid Service  �ӿ�IHidService
class IHidService : public IInterface
{			
public:
	// ������һЩ���룬����
	// ������ֶ�descriptor��
	// �����������Ա����asInterface��getInterfaceDescriptor
	// ����˹�������������
	DECLARE_META_INTERFACE(HidService);

	// �÷�������ṩ�Ĳ����ӿ�
	virtual int writeMessage(int id,void * buf,int length) = 0;			// ����ԭʼ����
	virtual int setCallback(const sp<IHidCallback>& callback) = 0;	// ���ûص�
	virtual String8 getVersion() = 0;
};


// ����IHidService	�ӿ����з�����ö��
enum
{
	POST_RAW_DATA_TRANSACTION = IBinder::FIRST_CALL_TRANSACTION,
	SET_CALLBACK_TRANSACTION,
	GET_VERSION_TRANSACTION,
};
			

// ����binder  �����ʵ����BnHidService, �̳�BnInterface  
class BnHidService: public BnInterface<IHidService>
{
public:
	virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply,uint32_t flags = 0);
};


// ����binder  �����������BpHidService, �̳�BpInterface
class BpHidService: public BpInterface<IHidService> {

public:
	BpHidService(const sp<IBinder>& impl);

	virtual int writeMessage(int id,void * buf,int len);
	virtual int setCallback(const sp<IHidCallback>& callback);
	virtual String8 getVersion();
};


}

#endif


