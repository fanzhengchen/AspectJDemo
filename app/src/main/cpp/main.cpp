//
// Created by Administrator on 2017/9/22 0022.
//

#include <cstdlib>
#include <jni.h>
#include <assert.h>
#include <android/log.h>
#include <cstdio>
#include <string>

#define TAG "MAIN_CPP"
#define JNI_CLASS "xgn/com/aspectjdemo/Check"
#define LOGV(...) \
    (__android_log_print(ANDROID_LOG_ERROR,TAG, __VA_ARGS__))

void checkout(JNIEnv *env, jobject instance, jobject context);

JNINativeMethod methods[] = {
        {"check", "(Ljava/lang/Object;)V", (void *) checkout},
};

bool registerNatives(JNIEnv *env) {
    int len = sizeof(methods) / sizeof(methods[0]);
    jclass clazz = env->FindClass(JNI_CLASS);
    if (clazz == NULL) {
        return false;
    }
    int result = env->RegisterNatives(clazz, methods, len);
    return result >= 0;
}

void checkout(JNIEnv *env, jobject instance, jobject context) {
    jclass ctx = env->FindClass("android/content/Context");
    bool isContext = env->IsInstanceOf(context, ctx);
    if (isContext) {
        jmethodID package_managerId = env->GetMethodID(ctx, "getPackageManager",
                                                       "()Landroid/content/pm/PackageManager;");
        jobject package_manager_obj = env->CallObjectMethod(context, package_managerId);
        jclass package_manager_cls = env->GetObjectClass(package_manager_obj);

        jmethodID package_name_id = env->GetMethodID(ctx, "getPackageName", "()Ljava/lang/String;");
        jobject package_name_obj = env->CallObjectMethod(context, package_name_id);

        jmethodID package_info_id = env->GetMethodID(package_manager_cls, "getPackageInfo",
                                                     "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
        jobject package_info_obj = env->CallObjectMethod(package_manager_obj, package_info_id,
                                                         package_name_obj, 64);
        jclass package_info_cls = env->GetObjectClass(package_info_obj);

        jfieldID fieldId = env->GetFieldID(package_info_cls, "signatures",
                                           "[Landroid/content/pm/Signature;");

        jobjectArray signature_object_array = (jobjectArray) env->GetObjectField(package_info_obj,
                                                                                 fieldId);
        jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);

        jclass signature_class = env->GetObjectClass(signature_object);

        jmethodID methodId = env->GetMethodID(signature_class, "toCharsString",
                                              "()Ljava/lang/String;");
        jstring signature_string = (jstring) env->CallObjectMethod(signature_object, methodId);
        const char *signature_text = env->GetStringUTFChars(signature_string, NULL);
        std::string text = std::string(signature_text);
        LOGV("PPP%sPPPP\n", signature_text);
        LOGV("PPP%sPPP\n", text.c_str());
        env->DeleteLocalRef(package_info_obj);
        env->DeleteLocalRef(package_info_cls);
        env->DeleteLocalRef(package_name_obj);
        env->DeleteLocalRef(package_manager_obj);
        env->DeleteLocalRef(package_manager_cls);
        env->DeleteLocalRef(signature_class);
        env->DeleteLocalRef(signature_object);
        env->DeleteLocalRef(signature_object_array);
        env->DeleteLocalRef(signature_string);
    }
}

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;

    LOGV("jni %s %d", __FUNCTION__, __LINE__);
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) ^ JNI_OK) {
        return -1;
    }

    assert(env != NULL);

    if (!registerNatives(env)) {//注册
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
