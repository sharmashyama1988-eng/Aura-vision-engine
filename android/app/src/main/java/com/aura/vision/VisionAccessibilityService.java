package com.aura.vision;

import android.accessibilityservice.AccessibilityService;
import android.content.Intent;
import android.view.accessibility.AccessibilityEvent;
import android.util.Log;

public class VisionAccessibilityService extends AccessibilityService {
    private static final String TAG = "AuraVisionService";

    @Override
    public void onAccessibilityEvent(AccessibilityEvent event) {
        if (event.getEventType() == AccessibilityEvent.TYPE_WINDOW_STATE_CHANGED) {
            String packageName = event.getPackageName() != null ? event.getPackageName().toString() : "";
            Log.d(TAG, "Window changed: " + packageName);
            
            if (isCameraApp(packageName)) {
                Log.d(TAG, "Camera app detected: " + packageName);
                
                // Use the Connector Engine to bridge with the camera app
                AuraEngine.connectToCamera(packageName);
                
                Log.d(TAG, "Starting Aura Engine Service...");
                Intent intent = new Intent(this, AuraEngineService.class);
                intent.setAction("START_ENGINE");
                startService(intent);
            }
        }
    }

    private boolean isCameraApp(String pkg) {
        return pkg.toLowerCase().contains("camera");
    }

    @Override
    public void onInterrupt() {
    }
}
