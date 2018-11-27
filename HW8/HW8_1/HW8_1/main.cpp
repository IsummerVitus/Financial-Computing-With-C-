//
//  main.cpp
//  HW8_1
//
//  Created by Li M on 15/10/31.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

//#include "matrix.h"
//
//int main() {
//
//        Matrix m1(4,5);
//    cout<<"haha";
//    cout<<"m1 is:"<<endl<<m1;;
//    cout<<"please input m1";
////    cin>> m1;
////    cout<< m1;
//        Matrix m2=m1;
//        cout<<"m2 is:"<<m2;
//
//
//
//        Matrix m3(5,4);
//    cin>>m3;
//        cout<<"m3 is:"<<m3;
//
//
//        cout<<"m2*m3 is::"<<m2*m3;
//
//    cout <<"m1+m2 is::"<<m1+m2;
//
//
//
//
//}


#include <iostream>
using namespace std;

int main()
{
    int arr[] = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    sort(arr, arr+n);
    
    cout << "\nArray after sorting using "
    "default sort is : \n";
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    
    return 0;
}

