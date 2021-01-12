#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <iostream>
#include <cmath>
#include <limits.h>
#include <vector>
#include "json.h"
#include "crow_all.h"


void maxHeapify(int* arr, int i, int size){
    int leftChild = (2*i + 1);
    int rightChild = (2*i + 2);
    int largest;
    if(leftChild < size && arr[leftChild] > arr[i]){
        largest = leftChild;
    }
    else{
        largest = i;
    }
    if(rightChild < size && arr[rightChild] > arr[largest]){
        largest = rightChild;
    }
    if(largest != i){
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        maxHeapify(arr, largest, size);
    }
}

void buildMaxHeap(int* arr, int size){
    for(int i = trunc((size / 2)); i >= 0; i--){
        maxHeapify(arr, i, size);
    }
}

nlohmann::json heapSort(int* arr, int size){
    nlohmann::json x;
    buildMaxHeap(arr, size);
    for(int i = size - 1; i >= 0; i--){
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        maxHeapify(arr, 0, i);
    }
    std::vector<int> nums;
    for(int i = 0; i < size; i++){
        nums.push_back(arr[i]);
    }
    x["sort"] = nums;
    return x;
}

#endif
