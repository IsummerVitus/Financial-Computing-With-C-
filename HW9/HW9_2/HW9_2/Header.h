//
//  Header.h
//  HW9_2
//
//  Created by Li M on 15/11/11.
//  Copyright (c) 2015年 Li M. All rights reserved.
//
#include<iostream>
using namespace std;


template<class T>
class innerobject {
protected:
    T  data;
public:
    innerobject() {};
    innerobject(T data_) :data(data_)
    {}
    void showed() {
        cout<<"This class contains "<<data<<endl; }
    T getdata() { return data; }
    ~innerobject() {}
};



template<class T>
class Wrapper {
private:
    innerobject<T>* innerQtr;
    int * ref_c;
public:
    Wrapper(innerobject<T>* innerobjectPtr_):innerQtr(innerobjectPtr_),ref_c(new int(1))
    {}
    Wrapper(Wrapper<T>& other):innerQtr(other.innerQtr),ref_c(other.ref_c)
    {
        (*ref_c)++;
    }
    Wrapper& operator=(const Wrapper& rhs);
    ~Wrapper();
    void showed(){innerQtr->showed();}
    void show()
    {
        cout << "We've got " << *ref_c << " copies " <<innerQtr->getdata()<< endl;
    }
    
};

template<class T>
Wrapper<T>:: ~Wrapper()
{
    if (--(*ref_c) == 0) {
        delete innerQtr;
        delete ref_c;
    }
}

template<class T>
Wrapper<T>& Wrapper<T>::operator=(const Wrapper<T>& rhs)
{
    ++*rhs.ref_c;
    if (--(*ref_c) == 0)
    {
        delete innerQtr;
        delete ref_c;
    }
    innerQtr = rhs.innerQtr;
    ref_c = rhs.ref_c;
    return *this;
}



int main()
{
    innerobject<int> *aint=new innerobject<int>(5);
    innerobject<double> *bdouble=new innerobject<double>(2.4);
    Wrapper<int> a(aint);
    Wrapper<double> b(bdouble);
    
    Wrapper<int> c = a;
    Wrapper<int> d(a);
    
    
    a.showed();
    b.showed();
    c.showed();
    d.showed();
    d.show();
    a.show();
    b.show();
    c.show();
    
    cin.get();
    return 0;
    
}