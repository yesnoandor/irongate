
package com.android.server;

import android.content.Context;

import com.android.server.lights.Light;
import com.android.server.lights.LightsManager;

import android.os.IFlexService;
import android.util.Slog;
import android.util.CommonFunction;

public class FlexService extends IFlexService.Stub {
	private static final String TAG = "FlexService";
	private LightsManager mLightsManager;
	private Light mLight;
	
	FlexService() {	
		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
		
		//init_native();
		mLightsManager = LocalServices.getService(LightsManager.class);

		mLight = mLightsManager.getLight(LightsManager.LIGHT_ID_BATTERY);

		//mBatteryLowARGB = context.getResources().getInteger(
		//					com.android.internal.R.integer.config_notificationsBatteryFullARGB);
		// Green Led lights
		mLight.setColor(0xFF00FF00);
		
		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
	}

	
	public void ledSetBrightness(int brightness)
	{
		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
		
    	if(mLight != null){
			mLight.setBrightness(brightness);
		}

		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
	}
	
    public void ledSetBrightness(int brightness, int brightnessMode)
    {
    	Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
		
    	if(mLight != null){
			mLight.setBrightness(brightness,brightnessMode);
		}

		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
    }
	
    public void ledSetColor(int color)
    {
    	Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
		
    	if(mLight != null){
			mLight.setColor(color);
		}

		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
    }
	
    public void ledSetFlashing(int color, int mode, int onMS, int offMS)
    {
    	Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
				
    	if(mLight != null){
			mLight.setFlashing(color,mode,onMS,offMS);
		}

		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
		
    }
	public  void ledTurnOff()
    {
    	Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
		
    	if(mLight != null){
			mLight.turnOff();
		}

		Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
    }
    
    
};
