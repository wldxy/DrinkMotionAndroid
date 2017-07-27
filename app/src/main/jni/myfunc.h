//
// Created by user on 26/07/17.
//

#ifndef SVMTEST_MYFUNC_H
#define SVMTEST_MYFUNC_H

int featureExtract(double*& result, double** data, int row, int size);

double predict(double* data, int len);

#endif //SVMTEST_MYFUNC_H
