//
//  main.cpp
//  HW3_2
//
//  Created by Li M on 15/9/22.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include <iostream>
using namespace std;
void myBubbleSort(double* arr, int size)
{
    int j = 0;
    int tmp;
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        j++;
        for (int i = 0; i < size - j; i++)
        {
            if (*(arr+i) > arr[i + 1])
            {
                tmp = *(arr+i);
                *(arr+i) = arr[i + 1];
                *(arr+i+1) = tmp;
                swapped = true;
            }
        }
    }
}

