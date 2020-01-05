package com.example.androidcontroller;

import androidx.appcompat.app.AppCompatActivity;
import androidx.arch.core.executor.DefaultTaskExecutor;

import android.os.AsyncTask;
import android.os.Bundle;

import com.android.volley.RequestQueue;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.concurrent.Executor;

import io.github.controlwear.virtual.joystick.android.JoystickView;

public class MainActivity extends AppCompatActivity {

    private static int angle = 0;
    private static int strength = 0;

    //Les valeurs envoyees a la requette precedente
    private static int lastAngle = 0;
    private static int lastStrength = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JoystickView joystick = findViewById(R.id.joystickView);
        joystick.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                MainActivity.angle = angle;
                MainActivity.strength = strength;
            }
        });

        new Thread() {
            @Override
            public void run() {

                while(true) {

                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) { e.printStackTrace(); }

                    sendHTTPRequest(angle + "&" + strength);
                }
            }
        }.start();
    }

    private void sendHTTPRequest(String arguments) {

        //Si les valeurs n'ont pas change depuis la derniere requette on n'envoie rien
        if(angle == lastAngle && strength == lastStrength)
            return;

        lastAngle = angle;
        lastStrength = strength;

        // Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);
        String url = "http://192.168.0.111:4000/" + arguments;

        // Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(com.android.volley.Request.Method.GET, url,
                new com.android.volley.Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        System.out.println(response);
                    }
                }, new com.android.volley.Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                System.out.println(error.getMessage());
            }
        }
        );

        System.out.println("Sending Http Request " + url);

        // Add the request to the RequestQueue.
        queue.add(stringRequest);
    }
}
