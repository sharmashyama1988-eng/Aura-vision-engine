#include <jni.h>
#include <string>
#include "Aura/Renderer/VisualEngine.hpp"
#include "Aura/Core/Base.hpp"
#include <android/log.h>
#include "Aura/Vision/ProVisualEngine.hpp"
#include "Aura/Network/AuraConnector.hpp"
#include "Aura/Core/AuraHandler.hpp"
#include "Aura/Camera/CameraEngineer.hpp"

#define LOG_TAG "AuraEngine-JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static aura::Scope<aura::renderer::VisualEngine> g_Engine;
static aura::vision::ProVisualEngine g_ProVisual;
static aura::network::AuraConnector g_Connector;
static aura::core::AuraHandler g_Handler;
static aura::camera::CameraEngineer g_Engineer_Hardware;

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_init(JNIEnv* env, jobject /* this */) {
    try {
        g_Engine = aura::CreateScope<aura::renderer::VisualEngine>();
        g_Engine->Initialize();
        g_Engineer_Hardware.AutoTuneHardware();
        g_Engineer_Hardware.OptimizeOptics();
        LOGI("Aura Engine initialized with CameraEngineer optimizations.");
    } catch (const std::exception& e) {
        LOGE("Engine Init Error: %s", e.what());
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_processFrame(JNIEnv* env, jobject /* this */, jlong framePointer) {
    (void)env; (void)framePointer;
    if (g_Engine) { /* g_Engine->ProcessFrame(...); */ }
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_enhanceImage(JNIEnv* env, jobject /* this */, jlong imagePointer) {
    (void)env; (void)imagePointer;
    g_Handler.GuardSystem();
    if (!g_Handler.IsSupercomputingSafe()) { return; }
    aura::camera::Frame dummyFrame; 
    g_ProVisual.EnhanceClarity(dummyFrame, dummyFrame);
    g_ProVisual.OptimizeColors(dummyFrame, dummyFrame);
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_connectToCamera(JNIEnv* env, jobject /* this */, jstring packageName) {
    const char* nativePackage = env->GetStringUTFChars(packageName, 0);
    g_Connector.EstablishConnection(nativePackage);
    env->ReleaseStringUTFChars(packageName, nativePackage);
}

extern "C" JNIEXPORT void JNICALL
Java_com_aura_vision_AuraEngine_shutdown(JNIEnv* env, jobject /* this */) {
    if (g_Engine) {
        g_Engine->Shutdown();
        g_Engine.reset();
        LOGI("Aura Engine shutdown safely.");
    }
}
