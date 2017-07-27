package com.example.user.svmtest;
import java.io.IOException;

import libsvm.*;

/**
 * Created by user on 26/07/17.
 */

public class MotionDetect {
    static {
        System.loadLibrary("motion");
        try {
            model = svm.svm_load_model("/sdcard/svm/model");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static svm_model model;

    public native double[] featureExtract(double[][] data);

    public native double predictMotion(double[] data);

    public double predictMotionbyJava(double[] data) {

        svm_node[] svmNodes = new svm_node[data.length+1];
        for (int i = 0;i < data.length;i++) {
            svmNodes[i] = new svm_node();
            svmNodes[i].index = i + 1;
            svmNodes[i].value = data[i];
        }
        svmNodes[data.length] = new svm_node();
        svmNodes[data.length].index = -1;
        double result = svm.svm_predict(model, svmNodes);

        return result;
    }

}
