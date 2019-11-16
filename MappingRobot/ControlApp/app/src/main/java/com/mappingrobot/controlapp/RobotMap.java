package com.mappingrobot.controlapp;

// Contains and manages the values of the intern map of the robot (gets and stores them)
public class RobotMap {

    public static int SIZE = 72;
    private static boolean[] values = new boolean[SIZE * SIZE];

    public static void fill(boolean val) {
        for(int i = 0; i < SIZE*SIZE; i++)
            values[i] = val;
    }

    public static boolean get(int x, int y) {
        return values[y*SIZE + x];
    }

    public static void set(int x, int y, boolean val) {
        values[y*SIZE + x] = val;
    }
}
