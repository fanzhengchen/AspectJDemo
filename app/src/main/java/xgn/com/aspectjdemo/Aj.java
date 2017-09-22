package xgn.com.aspectjdemo;

import android.content.Context;
import android.util.Log;
import android.view.MotionEvent;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;

/**
 * Created by Administrator on 2017/9/12 0012.
 */

@Aspect
public class Aj {
    private static final Check CHECK = new Check();
    private static final String TAG = "Aj";

    @Before("execution(* xgn.com.aspectjdemo.MainActivity.onCreate(android.os.Bundle))")
    public void onActivityMethodBefore(JoinPoint joinPoint) throws Exception {
        String key = joinPoint.getSignature().toString();
        Log.d(TAG, "onActivityMethodBefore: " + key);
    }

    @After("execution(* xgn.com.aspectjdemo.MainActivity.onStart(..))")
    public void onActivityMethod(JoinPoint joinPoint) {
        String key = joinPoint.getSignature().toString();
        Log.d(TAG, "onActivityMethodAfter: " + key);
    }

    @Around(value = "execution(* xgn.com.aspectjdemo.MainActivity.onTouchEvent(android.view.MotionEvent))")
    public Object onActivityTouchEvent(ProceedingJoinPoint joinPoint) throws Throwable {
        Object retVal = joinPoint.proceed();
        Log.d(TAG, "onActivityTouchEvent: " + joinPoint + " " + retVal);
        return retVal;
    }

    @After(value = "execution(* xgn.com.aspectjdemo.App.onCreate(..))")
    public void onApplicationCreate(JoinPoint joinPoint) {
        Log.d(TAG, "Application on Create " + joinPoint.getThis());
        CHECK.check(joinPoint.getThis());
    }
}
