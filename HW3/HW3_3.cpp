//
//  main.cpp
//  HW3_3
//
//  Created by Li M on 15/9/22.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#ifndef QUICKSORT_H
#define QUICKSORT_H
void quickSort(double *a,int p,int r);
#endif

#include<cstdlib>
#include<ctime>
#include "HW3_3.h"
#include<iostream>
using namespace std;
void quickSort(double *a,int p,int r)   //r在第一次迭代中取length（a)-1,p取1
{
    
    double pivot=a[p];
    int i=p;
    int j=r;
    while(i<j)
    {
        while (i<j&&a[j]>=pivot)
            
            j--;a[i]=a[j];
        
        while (i<j&&a[i]<=pivot)
            
            i++;a[j]=a[i];
        
    }
    a[i]=pivot;
    if(p<i-1)
        quickSort(a,p,i-1);
    if (r>i+1)
        quickSort(a,i+1,r);
    return 0;
}
int main()
{
    srand(time(NULL));
    double ia[10];
    for(int i=0;i<10;i++)
    {
        ia[i]=rand()/(static_cast<double>(RAND_MAX));
    }
    cout<<"the random arry is:"<<endl;
    for(int i=0;i<10;i++)
        cout<<ia[i]<<" ";
    cout<<endl;
    quickSort(ia,0,9);
    cout<<"the sort result is:"<<endl;
    for(int i=0;i<10;i++)
        cout<<ia[i]<<" ";
    cout<<endl;
    return 0;
}

//int main()
//{
    
//  srand(time(NULL));
//    int N;
//    cout<<"please input the size of array"<<endl;
//    cin>>N;
//    double *ia=new double[N];
//    for(int i=0;i<N;i++)
//    {
//        ia[i]=rand();
//    }
//    quicksort(ia,0,N-1)；  //r在第一次迭代中取length（a)-1,p取0
//}
