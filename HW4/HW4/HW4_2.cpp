//
//  main.cpp
//  HW4_2
//
//  Created by Li M on 15/9/27.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
template <class T>
void merge(T *ia, T low, T high, T mid)
{
    int size=0;
    while (*(ia++)!='\0')
        size++;
    ia-=size+1;
    T *c=new T[size];
    int i, j, k;
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (ia[i] < ia[j])
        {
            c[k] = ia[i];
            i++;
        }
        else
        {
            c[k] = ia[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        c[k] = ia[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = ia[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        ia[i] = c[i];
    }
}
template <class U>
void mergesort(U *a, U low, U high)
{
    U mid;
    if (low < high)
    {
        mid=(low+high)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a,low,high,mid);
    }
    return;
}

int main()
{
    int a[10];
    cout<<"enter  the elements:\n";
    for (int i = 0; i <10; i++)
    {
        cin>>a[i];
    }
    mergesort(a, 0, 10);
    cout<<"sorted array:\n";
    for (int i = 0; i < 10; i++)
    {
        cout<<" "<<a[i];
    }
    cin.get();
    return 0;
}