#include <jni.h>
#include <android/log.h>

#define LOG_TAG "Fifa11Port"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT void JNICALL
Java_com_fifa11_port_MainActivity_initResolution(JNIEnv *env, jobject thiz, jint width, jint height) {
    LOGI("¡Motor inicializado con éxito, boludo! Resolución recibida desde Java: %dx%d XD", (int)width, (int)height);
    
    // Acá más adelante metemos la configuración del viewport de OpenGL ES:
    // glViewport(0, 0, width, height);
}

}