package android.util;

import java.text.SimpleDateFormat; 
import java.util.Date;

/** @hide */
public abstract class CommonFunction {

/** @hide */
public static String getFileLineMethod() { 
	StackTraceElement traceElement = ((new Exception()).getStackTrace())[1]; 
	StringBuffer toStringBuffer = new StringBuffer("[").append( 
	traceElement.getFileName()).append(" | ").append( 
	traceElement.getLineNumber()).append(" | ").append(
	traceElement.getMethodName()).append("]");

	return toStringBuffer.toString();
}

/** @hide */
public static String _FILE_() { 
	StackTraceElement traceElement = ((new Exception()).getStackTrace())[1]; 
	return traceElement.getFileName(); 
}

/** @hide */
public static String _FUNC_() { 
	StackTraceElement traceElement = ((new Exception()).getStackTrace())[1]; 
	return traceElement.getMethodName(); 
}

/** @hide */
public static int _LINE_() { 
	StackTraceElement traceElement = ((new Exception()).getStackTrace())[1]; 
	return traceElement.getLineNumber(); 
}

/** @hide */
public static String _TIME_() { 
	Date now = new Date(); 
	SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS"); 
	return sdf.format(now); 
}

//Usage:
//Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::+++++++++++++++");
//Slog.i(TAG,CommonFunction._FILE_() + ":::" + CommonFunction._FUNC_() + "::---------------");
		
 
} 
