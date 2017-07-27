//
// Created by user on 26/07/17.
//

#include "myfunc.h"
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_fft_real.h>
#include "svm.h"

static void set_svm_data(double* result, int& index, double* data, int len) {

    for (int i = 0;i < len;i++) {
        result[index+i] = data[i];
    }
    index += len;
    free(data);

}

int featureExtract(double*& result, double** data, int row, int size) {
    
    double* mean = (double*)malloc(row*sizeof(double));
    for (int i = 0;i < row;i++) {
        mean[i] = gsl_stats_mean(data[i], 1, size);
    }

    double* var = (double*)malloc(row*sizeof(double));
    for (int i = 0;i < row;i++) {
        var[i] = gsl_stats_variance(data[i], 1, size);
    }

    double* knew = (double*)malloc(row*sizeof(double));
    for (int i = 0;i < row;i++) {
        knew[i] = gsl_stats_skew(data[i], 1, size);
    }

    double* kurt = (double*)malloc(row*sizeof(double));
    for (int i = 0;i < row;i++) {
        kurt[i] = gsl_stats_kurtosis(data[i], i, size);
    }

    int covar_size = row*(row-1)/2;
    double* covar = (double*)malloc(covar_size*sizeof(double));
    int count = 0;
    for (int i = 0;i < row;i++) {
        for (int j = i+1;j < row;j++) {
            covar[count++] = gsl_stats_covariance(data[i], 1, data[j], 1, size);
        }
    }

    gsl_fft_real_wavetable* real;
    gsl_fft_real_workspace* work;

    work = gsl_fft_real_workspace_alloc(size);
    real = gsl_fft_real_wavetable_alloc(size);
    for (int i = 0;i < row;i++) {
        gsl_fft_real_transform(data[i], 1, size, real, work);
    }
    gsl_fft_real_wavetable_free(real);
    gsl_fft_real_workspace_free(work);

    int num_result = 4 * row + covar_size;
    result = (double*) malloc(num_result * sizeof(double));

    count = 0;
    set_svm_data(result, count, mean, row);
    // count += row;
    set_svm_data(result, count, var, row);    
    // count += row;
    set_svm_data(result, count, knew, row);    
    // count += row;
    set_svm_data(result, count, kurt, row);    
    // count += row;
    set_svm_data(result, count, covar, covar_size); 

    return num_result;
}

double predict(double* data, int len) {

    svm_node* svmData = new svm_node[len+1];
    for (int i = 0;i < len;i++) {
        svmData[i].index = i + 1;
        svmData[i].value = data[i];
    }
    svmData[len].index = -1;
    svmData[len].value = 0;

    svm_model* model = svm_load_model("sdcard/svm/model");
    double result = svm_predict(model, svmData);
    return result;
}