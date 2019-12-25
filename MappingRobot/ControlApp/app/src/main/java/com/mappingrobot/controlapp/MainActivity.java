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
                    update();
                    try { Thread.sleep(200); } catch (InterruptedException e) { e.printStackTrace(); }
                }
            }
        }).start();
    }

    public void onClick(View view) {

    }

    public void update() {
        RobotMap.requestNextChunk();
        RobotTransform.request();
        ((MapView)findViewById(R.id.mapview)).updateDisplay();
    }
}
