using System;
using UnityEngine;
using System.IO.Ports;

public class Inputs : MonoBehaviour
{
    public static int forward;
    public static int right;
    
    static SerialPort sp = new SerialPort("COM4", 9600);
 
    void Start () {
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
}
