//
// Created by tom on 17-11-23.
//
#include 	"common.h"
#include 	"NdkClient.h"
#include 	"flx_ndk_intf.h"


#include <sys/types.h>
#include <android/log.h>
#define  LOG_TAG    "FlexNDKapi"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#define USER_MSG_BUFFER_SIZE   0xFF

//composite_dev *g_dev_instance;
bool m_quit = false;
uint8_t g_Dev = 0x00;
flxndkEventCallbackFunc g_flxndkEventCallbackFunc = NULL;
flxndkMsgCallbackFunc g_hidMsgCallbackFunc = NULL;
//pthread_t *event_thread = NULL;
//pthread_t msg_thread ;
//pthread_cond_t msg_cond;
//pthread_mutex_t msg_mutex;
//msg_t userMsgBuffer[USER_MSG_BUFFER_SIZE];
uint32_t userMsgBufferIndex = 0;


using namespace android;


static sp<NdkClient> g_dev_instance;

//void hid_msg_handler(const msg_t *clientMsg)
void hid_msg_handler(void)
{
#if 0
    int id = clientMsg->msg_id;
    bool ret = false;

    if(id == MSG_READ_HID)
    {
        LOGD("%s MSG_READ_HID len(%d)",__FUNCTION__,static_cast<uint32_t >(clientMsg->datalen));
        if(g_dev_instance->PollHidPackage(1))
            ret= g_dev_instance->RecvPackage(static_cast<uint8_t* >(clientMsg->msg_data), static_cast<uint32_t >(clientMsg->datalen));
    }

    if(id == MSG_WRITE_HID)
    {
        LOGD("%s MSG_WRITE_HID len(%d)",__FUNCTION__,static_cast<uint32_t >(clientMsg->datalen));
        ret= g_dev_instance->SendPackage(static_cast<uint8_t* >(clientMsg->msg_data), static_cast<uint32_t >(clientMsg->datalen));
    }

    if(ret)
        g_hidMsgCallbackFunc(NULL, clientMsg->msg_id, clientMsg->msg_data, clientMsg->datalen);
    else
        g_hidMsgCallbackFunc(NULL, MSG_HID_ERROR, NULL, 0);
#endif        
}

void* msg_thread_func(void*)
{
#if 0
    while (!m_quit) {
        pthread_mutex_lock(&msg_mutex);
        if(g_dev_instance->userMsgQueue.empty())
            pthread_cond_wait(&msg_cond, &msg_mutex);
        else{
            //handle client msg
            msg_t *clientMsg = g_dev_instance->userMsgQueue.pop_front();
            uint8_t *deviceType = static_cast<uint8_t *>(clientMsg->device);
            if((*deviceType) & 0x1<<FLXNDK_DEVICE_TYPE_HID)
                hid_msg_handler(clientMsg);
        }
        pthread_mutex_unlock(&msg_mutex);
    };
    LOGD("%s Exit",__func__);
#endif    
    return NULL;
}



FLX_API FLXNDK_INSTANCE flxndkInit(flxndkEventCallbackFunc callback, int evtMask)
{
#if 0
    LOGD("%s",__FUNCTION__);
    pthread_mutex_init(&msg_mutex, NULL);
    pthread_cond_init(&msg_cond, NULL);
    if(evtMask==EPU)
        g_dev_instance = new composite_dev(EPU);

    if(evtMask==HMD)
        g_dev_instance = new composite_dev(HMD);

    if (g_dev_instance == NULL)
        return NULL;

    if (callback != NULL) {
        g_flxndkEventCallbackFunc = callback;
        if(!pthread_create(&msg_thread, NULL, msg_thread_func, NULL)){
            pthread_setname_np(msg_thread, "flexndk_msg_thread");
        }
    }

    return (void *)g_dev_instance
#endif    
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
    

    g_dev_instance = new NdkClient();


	printf("%s::---------------\r\n",__FUNCTION__);
	
    return (FLXNDK_INSTANCE)&g_dev_instance;
}


FLX_API bool flxndkDeinit(FLXNDK_INSTANCE instance)
{
#if 0
    m_quit = true;
    pthread_join(msg_thread, NULL);

    if(instance != NULL){
        instance = NULL;
        delete g_dev_instance;
    }
#endif
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	printf("%s::---------------\r\n",__FUNCTION__);
	
    return true;
}


FLX_API FLXNDK_DEVICE flxndkOpenDevice(const char* deviceId)
{
    uint8_t *dev = NULL;
    
#if 0    
    LOGD("%s",__FUNCTION__);
    if(g_dev_instance != NULL)
    {
        if(!strcmp(deviceId,"hid") && g_dev_instance->openSubDev(deviceId))
        {
            g_Dev |= 0x1<<FLXNDK_DEVICE_TYPE_HID;
            dev = &g_Dev;
        }
    }
#endif

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	printf("%s::---------------\r\n",__FUNCTION__);
	
    return static_cast<void*>(dev);
}

FLX_API int flxndkQueryDeviceCount(FLXNDK_DEVICE_TYPE type)
{
#if 0
    if(type == FLXNDK_DEVICE_TYPE_HID){
        return g_dev_instance->QueryDeviceCount(composite_dev::FLXNDK_DEVICE_TYPE::FLXNDK_DEVICE_TYPE_HID);
    }
#endif

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	printf("%s::---------------\r\n",__FUNCTION__);
	
    return 0;
}

FLX_API const char * flxndkGetDeviceId(FLXNDK_DEVICE_TYPE type, int index)
{
    static char deviceId[16];

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
   
    if(type==FLXNDK_DEVICE_TYPE_HID)
    {
        strcpy(deviceId,"hid");
    }

	printf("%s::---------------\r\n",__FUNCTION__);
	
    return deviceId;
}

void onMessage(void * buf, int len)
{	
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	for(int i=0;i<len;i++)
	{
		printf("buf[%d] = 0x%x\r\n",i,((char *)buf)[i]);	
	}

	g_hidMsgCallbackFunc(NULL, 0x01 << 3, buf, len);
	
	printf("%s::---------------\r\n",__FUNCTION__);
}

FLX_API void flxndkRegisterMsgCallbackFunction(FLXNDK_DEVICE device,flxndkMsgCallbackFunc callback, void *userdata)
{
#if 0
    uint8_t *dev = static_cast<uint8_t*>(device);
    if(*dev & 0x1<<FLXNDK_DEVICE_TYPE_HID)
        g_hidMsgCallbackFunc = callback;
#endif

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	g_hidMsgCallbackFunc = callback;
	g_dev_instance->registerOnMessage(CHANNEL_HID,onMessage);

	printf("%s::---------------\r\n",__FUNCTION__);
}


FLX_API void flxndkWriteDeviceMsg(FLXNDK_DEVICE device, int msgid, void *msgData, int len)
{
#if 0
    LOGD("%s tid(%d) In: index[%d]:msgid[%d]",__FUNCTION__,pthread_gettid_np(pthread_self()),userMsgBufferIndex,msgid);

    pthread_mutex_lock(&msg_mutex);
    if(userMsgBufferIndex >= USER_MSG_BUFFER_SIZE)
        userMsgBufferIndex = 0;
    msg_t *msg = (userMsgBuffer + userMsgBufferIndex);
    userMsgBufferIndex++;
    msg->device = device;
    msg->msg_id = msgid;
    msg->msg_data = msgData;
    msg->datalen = len;
    g_dev_instance->userMsgQueue.push_back(msg);
    pthread_mutex_unlock(&msg_mutex);

    LOGD("%s tid(%d) Out: index[%d]:msgid[%d]",__FUNCTION__,pthread_gettid_np(pthread_self()),userMsgBufferIndex,msgid);
    pthread_cond_signal(&msg_cond);
#endif

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	g_dev_instance->writeMessage(CHANNEL_HID,(void *)msgData,len);

	printf("%s::---------------\r\n",__FUNCTION__);
}


FLX_API void flxndkCloseDevice(FLXNDK_DEVICE device)
{
#if 0
    char *deviceId = (char*)device;
    if(g_dev_instance!=NULL)
        g_dev_instance->closeSubDev(deviceId);
    LOGD("%s",__FUNCTION__);
#endif    

	printf("%s::+++++++++++++++\r\n",__FUNCTION__);
	printf("%s::---------------\r\n",__FUNCTION__);

}

