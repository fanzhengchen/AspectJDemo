package xgn.com.aspectjdemo;

import android.app.Application;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Log;

/**
 * Created by Administrator on 2017/9/22 0022.
 */

public class App extends Application {
    private static final Check CHECK = new Check();

    @Override
    public void onCreate() {
        super.onCreate();

        ApplicationInfo info = getApplicationInfo();

        try {
            PackageManager packageManager = getPackageManager();
            PackageInfo packageInfo = packageManager.getPackageInfo(getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signatures = packageInfo.signatures;
            Log.d("wwwwwwwwwwwww", "" + signatures[0].toCharsString() + " " + signatures[0].toCharsString().length());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
