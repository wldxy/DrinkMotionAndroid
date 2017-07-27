cmake_minimum_required(VERSION 3.4.1)

include_directories(. include/)

# link_directories(/home/user/Lab/javacpp-presets/gsl/cppbuild/android-arm/lib/)
# find_library(gsl gslcblas)

# add_library(gslcblas SHARED IMPORTED)
# set_target_properties(gslcblas PROPERTIES IMPORTED_LOCATION /home/user/AndroidStudioProjects/SVMTest/app/src/main/jniLibs/armeabi-v7a/libgslcblas.so)

# add_library(gsl SHARED IMPORTED)
# set_target_properties(gsl PROPERTIES IMPORTED_LOCATION /home/user/AndroidStudioProjects/SVMTest/app/src/main/jniLibs/armeabi-v7a/libgsl.so)

add_library(gslcblas STATIC IMPORTED)
set_target_properties(gslcblas PROPERTIES IMPORTED_LOCATION /home/user/AndroidStudioProjects/SVMTest/app/src/main/jniLibs/armeabi-v7a/libgslcblas.a)

add_library(gsl STATIC IMPORTED)
set_target_properties(gsl PROPERTIES IMPORTED_LOCATION /home/user/AndroidStudioProjects/SVMTest/app/src/main/jniLibs/armeabi-v7a/libgsl.a)

# add_library(b SHARED btest.cpp)

add_library(example SHARED com_example_user_svmtest_test.cpp)
target_link_libraries(example gsl gslcblas)

add_library(motion SHARED com_example_user_svmtest_MotionDetect.cpp myfunc.cpp svm.cpp)
target_link_libraries(motion gsl gslcblas)