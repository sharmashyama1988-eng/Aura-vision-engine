package com.aura.vision;

public class AuraEngine {
    static {
        System.loadLibrary("aura_engine");
    }

    public static native void init();
    public static native void processFrame(long framePointer);
    public static native void enhanceImage(long imagePointer); // ProVisual Enhancement
    public static native void connectToCamera(String packageName); // Connector Module
    public static native void shutdown();
}
