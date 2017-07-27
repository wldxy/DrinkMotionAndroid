package com.example.user.svmtest;

/**
 * Created by user on 24/07/17.
 */

public class testtry {

    static {
        System.loadLibrary("example");
    }

    public native double test(double x);

    public native String check(String str);
}