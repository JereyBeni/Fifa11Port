package com.fifa11.port;

import android.app.Activity;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends Activity {

    private static final String TAG = "Fifa11Port";

    // Cargar la librería nativa de C++
    static {
        System.loadLibrary("fifa11_core");
    }

    // Declaración del método nativo que recibe la resolución desde Java
    public native void initResolution(int width, int height);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // 1. Detectar versión de Android para definir la resolución óptima
        int sdkVersion = Build.VERSION.SDK_INT;
        int targetWidth, targetHeight;

        if (sdkVersion <= Build.VERSION_CODES.O_MR1) { 
            // Android 5 a 8.1 (Perfil de 32 bits optimizado para rendimiento)
            targetWidth = 640;
            targetHeight = 360;
            Log.i(TAG, "Perfil Android 5-8 (32-bit): Resolución a 640x360");
        } else if (sdkVersion <= Build.VERSION_CODES.VANILLA_ICE_CREAM) { 
            // Android 9 a 14 (Perfil intermedio 720p/1080p)
            targetWidth = 1280;
            targetHeight = 720;
            Log.i(TAG, "Perfil Android 9-14: Resolución a 720p HD");
        } else { 
            // Android 15+ (Perfil moderno de 64 bits en 1080p)
            targetWidth = 1920;
            targetHeight = 1080;
            Log.i(TAG, "Perfil Android 15+ (64-bit): Resolución a 1080p Full HD");
        }

        // 2. Enviar la resolución calculada al motor nativo (C++) vía JNI
        initResolution(targetWidth, targetHeight);

        // Pantalla base por ahora
        View gameView = new View(this);
        setContentView(gameView);
    }
}