#include		<common.h>

// Created by tom on 17-11-24.
//

#include "flx_ndk_intf.h"
#include <sys/types.h>
#include <chrono>
#include <thread>
#include <android/log.h>
#include <unistd.h>
#define  LOG_TAG    "hmd"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#define WBUF_SIZ    1000//255
#define RBUF_SIZ    1000//255
uint8_t wbuf[WBUF_SIZ] = {0x04,'h','m','d','t','e','s','t',0x0};
uint8_t rbuf[RBUF_SIZ] = {0,};

FLXNDK_DEVICE hmd_deviceID = NULL;

#ifdef USING_THREAD
pthread_t main_thread ;
bool main_thread_quit = false;
//pthread_cond_t main_cond;
pthread_mutex_t main_mutex;
#endif


//typedef enum
//{	EPU =0,
//    HMD =1
//} HIDRole;

void OnPowerState(int evtid, void *evtData, int datalen)
{
    LOGD("%s",__FUNCTION__);
}


void onMessage(void *userdata, int msgid, void *msgData, int datalen)
{
    char *p = static_cast<char*>(msgData);
    if(msgid==MSG_WRITE_HID)
        LOGD("%s MSG_WRITE_HID reportID[%d]len[%d]data[%s]",__FUNCTION__,*p,datalen,p+1);
    if(msgid==MSG_READ_HID)
        LOGD("%s MSG_READ_HID reportID[%d]len[%d]data[%s]",__FUNCTION__,*p,datalen,p+1);
}

#ifdef USING_THREAD
void* main_thread_func(void*) {
    while (!main_thread_quit) {
        flxndkWriteDeviceMsg(hmd_deviceID,MSG_WRITE_HID,wbuf,sizeof(wbuf));
        flxndkWriteDeviceMsg(hmd_deviceID,MSG_READ_HID,rbuf,sizeof(rbuf));
    };
    LOGD("%s Exit",__func__);
    return NULL;
}
#endif

int flex_ndk_hmd_sample()
{
    LOGD("%s",__FUNCTION__);

    FLXNDK_INSTANCE hmd_instance  = flxndkInit(OnPowerState,HMD);

    if(!hmd_instance)
        return -1;

    FLXNDK_DEVICE_TYPE  device_type = FLXNDK_DEVICE_TYPE_HID;

    int device_count = flxndkQueryDeviceCount(FLXNDK_DEVICE_TYPE_HID);

    const char* deviceID= flxndkGetDeviceId(device_type,0);

    hmd_deviceID = flxndkOpenDevice(deviceID);

    if(!hmd_deviceID)
        LOGE("Failed open %p",hmd_deviceID);

    flxndkRegisterMsgCallbackFunction(hmd_deviceID,onMessage,NULL);
    for (int i = 0; i < 58; i++) {
        LOGD("%s writing ndk message", __FUNCTION__);
        memset(wbuf,0x00,WBUF_SIZ);
        wbuf[1] = wbuf[2] = wbuf[3] = wbuf[4] = wbuf[5] = wbuf[6] = wbuf[7] =
                (uint8_t)('A' + i);
        flxndkWriteDeviceMsg(hmd_deviceID, MSG_WRITE_HID, wbuf, sizeof(wbuf));
        //flxndkWriteDeviceMsg(hmd_deviceID, MSG_READ_HID, rbuf, sizeof(rbuf));
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // 200 FPS
    };

    LOGD("%s Exit", __func__);

#ifdef USING_THREAD
    if(!pthread_create(&main_thread, NULL, main_thread_func, NULL))
        pthread_setname_np(main_thread, "hmd_main_thread");
#endif

    flxndkCloseDevice(hmd_deviceID);
    flxndkDeinit(hmd_instance);

    return 1;
}


void flex_ndk_hmd_send_sample()
{
	char buf[32];

	memset(buf,0x00,sizeof(buf));
	for(unsigned int i=0;i<sizeof(buf);i++)
	{
		buf[i] = 3*i+4;
	}

	flxndkWriteDeviceMsg(hmd_deviceID, MSG_WRITE_HID, buf, sizeof(buf));
}

// 实现server  端的应用程序
int main() {
	printf("%s::+++++++++++++++\r\n",__FUNCTION__);

	flex_ndk_hmd_sample();

	do{
		sleep(10);

		flex_ndk_hmd_send_sample();
	}while(1);

	printf("%s::---------------\r\n",__FUNCTION__);
	
	return 0;
}