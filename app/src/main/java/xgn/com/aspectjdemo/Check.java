package xgn.com.aspectjdemo;

import android.content.Context;

/**
 * Created by Administrator on 2017/9/22 0022.
 */

public class Check {

    static {
        System.loadLibrary("check");
    }

    public native void check(Object object);
}
