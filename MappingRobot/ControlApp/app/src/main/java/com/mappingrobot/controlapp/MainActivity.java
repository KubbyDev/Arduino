package com.mappingrobot.controlapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Network.init(this);

        // Starts a thread that calls update() every 200 milliseconds (2 seconds after startup)
        new Thread(new Runnable() {
            @Override
            public void run() {
                try { Thread.sleep(2000); } catch (InterruptedException e) { e.printStackTrace(); }
                while(true) {
                    RobotMap.requestNextChunk();
                    try { Thread.sleep(500); } catch (InterruptedException e) { e.printStackTrace(); }
                    RobotTransform.request();
                    try { Thread.sleep(500); } catch (InterruptedException e) { e.printStackTrace(); }
                    ((MapView)findViewById(R.id.mapview)).updateDisplay();
                }
            }
        }).start();
    }

    public void onClick(View view) {

    }
}
