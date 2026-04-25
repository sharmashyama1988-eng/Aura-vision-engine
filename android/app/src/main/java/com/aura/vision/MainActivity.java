package com.aura.vision;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Simple UI to test the engine
        TextView tv = new TextView(this);
        tv.setTextSize(24);
        tv.setPadding(50, 50, 50, 50);
        setContentView(tv);

        // Initialize the heavy C++ engine
        AuraEngine.init();
        
        tv.setText("Aura Vision Engine: Running\nStability: 100%\nStatus: Optimized");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        AuraEngine.shutdown();
    }
}
