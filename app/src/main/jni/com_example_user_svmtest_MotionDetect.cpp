//
// Created by user on 26/07/17.
//

#include <malloc.h>
#include "com_example_user_svmtest_MotionDetect.h"
#include "myfunc.h"
#include "svm.h"

JNIEXPORT jdoubleArray JNICALL Java_com_example_user_svmtest_MotionDetect_featureExtract
        (JNIEnv *env, jobject jobj, jobjectArray jarr) {

    int row = env->GetArrayLength(jarr);
    jarray arr0 = (jarray)env->GetObjectArrayElement(jarr, 0);
    int col = env->GetArrayLength(arr0);

    jdouble** data = (jdouble**)malloc(row*sizeof(jdouble*));
    for (int i = 0;i < row;i++) {
        data[i] = (jdouble*)malloc(col*sizeof(jdouble));
        jarray temp_arr = (jarray)env->GetObjectArrayElement(jarr, i);
        jdouble* temp_data = env->GetDoubleArrayElements((jdoubleArray)temp_arr, 0);
        for (int j = 0;j < col;j++) {
            data[i][j] = temp_data[j];
        }
        env->ReleaseDoubleArrayElements((jdoubleArray)temp_arr, temp_data, 0);
    }

	double* result;
    int result_len = featureExtract(result, data, row, col);
    jdoubleArray jresult = env->NewDoubleArray(result_len);
    env->SetDoubleArrayRegion(jresult, 0, result_len, result);

    return jresult;

}

JNIEXPORT jdouble JNICALL Java_com_example_user_svmtest_MotionDetect_predictMotion
        (JNIEnv *env, jobject jobj, jdoubleArray jarr) {

    int len = env->GetArrayLength(jarr);
    double* data = new double[len];
    env->GetDoubleArrayRegion(jarr, 0, len, data);

    double result = predict(data, len);
    return result;
}