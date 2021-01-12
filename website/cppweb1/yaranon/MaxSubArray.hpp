#ifndef MAXSUBARRAY_HPP
#define MAXSUBARRAY_HPP

#include <iostream>
#include <cmath>
#include <limits.h>

using namespace std;

int maxOfThree(int num1, int num2, int num3){
    if(num1 >= num2 && num1 >= num3){
        return num1;
    }
    else if(num2 >= num1 && num2 >= num3){
        return num2;
    }
    else if(num3 >= num1 && num3 >= num2){
        return num3;
    }
return 0;
}

int maxCrossingSubArray(int* arr, int low, int mid, int high){
    int left_sum = INT_MIN;
    int sum = 0;
    for(int i = mid; i >= low; i--){
        sum = sum + arr[i];
        if(sum > left_sum){
            left_sum = sum;
        }
    }
    int right_sum = INT_MIN;
    sum = 0;
    for(int j = mid + 1; j <= high; j++){
        sum = sum + arr[j];
        if(sum > right_sum){
            right_sum = sum;
        }
    }
 return maxOfThree(left_sum, right_sum, left_sum + right_sum);
}

int maxSubArray(int* arr, int low, int high){
    int left_low, left_high, left_sum;
    int right_low, right_high, right_sum;
    int cross_low, cross_high, cross_sum;
    if(low == high) // array size = 1;
        return arr[low];
    else{
        int mid = trunc((low+high)/2);
        left_sum = maxSubArray(arr, low, mid);
        right_sum = maxSubArray(arr, mid+1, high);
        cross_sum = maxCrossingSubArray(arr, low, mid, high);

        if(left_sum >= right_sum && left_sum >= cross_sum){
            return left_sum;
        }
        else if (right_sum >= left_sum && right_sum >= cross_sum){
            return right_sum;
        }
        else{
            return cross_sum;
        }
    }
return 0;
}


#endif
