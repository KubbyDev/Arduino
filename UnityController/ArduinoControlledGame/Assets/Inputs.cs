using System;
using UnityEngine;
using System.Net;
using System.Threading.Tasks;

public class Inputs : MonoBehaviour
{
    public static float forward;
    public static float right;

    //static SerialPort sp = new SerialPort("COM4", 9600);
    private static int angle;
    private static int strength;

    /*
     
     Passer en .NET 3.5 dans ProjectSettings dans Unity pour utiliser ca
     
    public static void InitArduinoReader()
    {
        sp.Open ();
        sp.ReadTimeout = 1;
    }
    
    public static void ReadFromArduino() 
    {
        try
        {
            string line = sp.ReadLine();

            //0 => negatif, 1 => neutre, 2 => positif
            //Donc on fait -1 pour avoir un truc plus facile a utiliser
            if (line[0] == 'F')
                forward = int.Parse(line[1].ToString()) -1;
            if (line[0] == 'R')
                right = int.Parse(line[1].ToString()) -1;
            
            Debug.Log(line);
        }
        catch(Exception) {}
    }
    */

    public static void InitHttpReader()
    {
        Task.Run(() =>
        {
            HttpListener listener = new HttpListener();
            listener.Prefixes.Add("http://192.168.0.111:4000/");
            listener.Start();

            while (true)
            {
                Debug.Log("Listening...");

                HttpListenerContext context = listener.GetContext(); //Blocking
                Debug.Log(context.Request.RawUrl);

                string[] numbers = context.Request.RawUrl.Substring(1).Split('&');
                angle = int.Parse(numbers[0]);
                strength = int.Parse(numbers[1]);
            }
        });
    }
    
    public static void ReadFromHttpRequest()
    {
        forward = (float) Math.Sin(angle*Math.PI/180) * strength / 100;
        right = (float) Math.Cos(angle*Math.PI/180) * strength / 100;
    }
}
