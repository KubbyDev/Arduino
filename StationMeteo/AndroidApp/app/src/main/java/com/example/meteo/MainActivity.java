package com.example.meteo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.TextView;

import com.android.volley.RequestQueue;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        main();
    }

    private static MainActivity app;

    private void main() {

        app = this;
        new Updater().execute();
    }

    private static class Updater extends AsyncTask {

        @Override
        protected Object doInBackground(Object[] objects) {

            while(true) {

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {e.printStackTrace(); break;}

                app.updateValues();
            }

            return new Object();
        }
    }

    private void updateDisplay(String rawData) {

        int[] values = new int[8];
        String[] data = rawData.split(",");
        for(int i = 0; i < 8; i++)
            values[i] = Integer.parseInt(data[i]);

        ((TextView)findViewById(R.id.sound)).setText(String.valueOf(values[0]));
        ((TextView)findViewById(R.id.humidity)).setText(String.valueOf(values[1]));
        ((TextView)findViewById(R.id.pressure)).setText(String.valueOf(values[2]));
        ((TextView)findViewById(R.id.altitude)).setText(String.valueOf(values[3]));
        ((TextView)findViewById(R.id.smoke)).setText(String.valueOf(values[4]));
        ((TextView)findViewById(R.id.luminosity)).setText(String.valueOf(values[5]));
        ((TextView)findViewById(R.id.temperature)).setText(String.valueOf(values[6]));
        ((TextView)findViewById(R.id.water)).setText(String.valueOf(values[7]));

    }

    private void updateValues() {

        // Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);
        String url = "http://192.168.1.28:4300/";

        // Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(com.android.volley.Request.Method.GET, url,
            new com.android.volley.Response.Listener<String>() {
                @Override
                public void onResponse(String response) {
                    System.out.println("\nResponse : " + response);
                    updateDisplay(response);
                }
            },
            new com.android.volley.Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    System.out.println("\nError" + error.getMessage());
                }
            }
        );

        System.out.println("Sending Http Request");

        // Add the request to the RequestQueue.
        queue.add(stringRequest);
    }
}
