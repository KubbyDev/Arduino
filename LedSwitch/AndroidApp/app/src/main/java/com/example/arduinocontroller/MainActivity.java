package com.example.arduinocontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.io.DataOutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void selectStateOn(View view) {
        sendHTTPRequest("?b=3");
    }

    public void selectStateOff(View view) {
        sendHTTPRequest("?b=");
    }

    private void sendHTTPRequest(String arguments) {

        // Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);
        String url = "http://localhost:4000/" + arguments;

        // Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                    }
                }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        System.out.println(error.getMessage());
                    }
                }
        );

        System.out.println("Sending Http Request");

        // Add the request to the RequestQueue.
        queue.add(stringRequest);
    }

    /*
    private void sendHTTPRequest(final String arguments) {

        new AsyncTask<Void, Void, Void>() {

            @Override
            protected Void doInBackground( final Void ... params ) {

                try {

                    //Init
                    //URL url = new URL("http://192.168.0.136:4200/");
                    URL url = new URL("http://localhost:4000/");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");

                    //Parametres
                    connection.setDoOutput(true);
                    DataOutputStream out = new DataOutputStream(connection.getOutputStream());
                    out.writeBytes(arguments);
                    out.flush();
                    out.close();

                    //Envoi
                    connection.setRequestProperty("Content-Type", "application/json");

                } catch (Exception e) { e.printStackTrace(); }

                return null;
            }

            @Override
            protected void onPostExecute( final Void result ) {
            }

        }.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, null);
    }
    */
}
