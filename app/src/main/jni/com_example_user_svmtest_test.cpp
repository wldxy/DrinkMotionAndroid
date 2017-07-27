//
// Created by user on 24/07/17.
//

#include "com_example_user_svmtest_test.h"
#include <jni.h>
#include <gsl/gsl_sf_bessel.h>

JNIEXPORT jdouble JNICALL Java_com_example_user_svmtest_testtry_test
        (JNIEnv *env, jobject jobject, jdouble num) {

    double y = gsl_sf_bessel_J0 (num);
//    printf ("J0(%g) = %.18e/n", x, y);
    return y;

}

JNIEXPORT jstring JNICALL Java_com_example_user_svmtest_testtry_check
        (JNIEnv *env, jobject jobj, jstring jstr) {

    return env->NewStringUTF("hahah");

}