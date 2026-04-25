#include <jni.h>
#include <string>
#include "Aura/Renderer/VisualEngine.hpp"
#include "Aura/Core/Base.hpp"
#include <android/log.h>

#define LOG_TAG "AuraEngine-JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static aura::Scope<aura::renderer::VisualEngine> g_Engine;

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_init(JNIEnv* env, jobject /* this */) {
    (void)env;
    try {
        g_Engine = aura::CreateScope<aura::renderer::VisualEngine>();
        g_Engine->Initialize();
        LOGI("Aura Engine initialized successfully for Android.");
    } catch (const std::exception& e) {
        LOGE("Engine Init Error: %s", e.what());
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_processFrame(JNIEnv* env, jobject /* this */, jlong framePointer) {
    (void)env;
    (void)framePointer;
    // In a production app, we pass the pointer to the raw camera buffer
    // For now, we simulate processing to ensure stability
    if (g_Engine) {
        // g_Engine->ProcessFrame(...);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_shutdown(JNIEnv* env, jobject /* this */) {
    (void)env;
    if (g_Engine) {
        g_Engine->Shutdown();
        g_Engine.reset();
        LOGI("Aura Engine shutdown safely.");
    }
}
