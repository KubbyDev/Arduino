package com.mappingrobot.controlapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RobotMap.fill(false);
        RobotMap.set(0,0,true);
        RobotMap.set(2,2,true);
        RobotMap.set(50,42,true);
        RobotMap.set(71,71,true);
    }

    public void onClick(View view) {


        ((MapView)findViewById(R.id.mapview)).updateDisplay();
    }
}
