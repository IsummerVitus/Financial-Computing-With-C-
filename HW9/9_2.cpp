#include <iostream>
using namespace std;


template<class T>
class sharedptr
{
private:
    T* inner;
    int * counter;
public:
    sharedptr() { }
    
    sharedptr(T* objectPtr_) :inner(objectPtr_), counter(new int(1))
    {}
    
    
    sharedptr(sharedptr<T>& m)
    {
        inner = m.inner;
        counter= m.counter;
        (*counter)++;
    }
    
    
    sharedptr& operator=(const sharedptr<T>& rhs)
    {
        if(this!=&rhs)
        {
            --(*counter);
            if(!*counter) {
                delete counter;
                delete inner;
            }
            inner=rhs.inner; counter=rhs.counter; ++(*counter);
        }
        return *this;
    }
    
    
    ~sharedptr()
    {
        if (--(*counter) == 0) {
            delete inner;
            delete counter;
        }
    }
    
    
    T& operator *()
    {
        return *inner;
    }
    
    
    T* operator ->()
    {
        return inner;
    }
    
    
    T* get()
    {
        return inner;
    }
    
    
    void exchange(sharedptr<T> &rhs)
    {
        T* temp = rhs.inner;
        rhs.inner = inner;
        inner = temp;
        
        int * counter_temp = rhs.counter;
        rhs.counter = counter;
        counter = counter_temp;
        
    }
    
    
    void reset()
    {
        if (--(*counter) == 0) {
            delete inner;
            delete counter;
        }
        inner = NULL;
    }
    
    void reset(sharedptr<T>& qtr)
    {
        
        if (--(*counter) == 0) {
            delete inner;
            delete counter;
        }
        inner = NULL;
        inner = qtr.inner;
        ++*(qtr.counter);
    }
    
    void print()
    {
        cout <<"It contains "<< (*counter) << " copies of " << *inner << endl;
    }
    
};


int main() {
    int *a=new int(22);
    double *p=new double(2.71);
    sharedptr<int> aptr(a);
    aptr.print();
    sharedptr<double> bptr(p);
    bptr.print();
    sharedptr<int> cptr1=aptr;
    cptr1.print();
    sharedptr<int> cptr2=aptr;
    cptr2.print();
    int *d=new int(2);
    sharedptr<int> dptr(d);
    dptr.reset(aptr);
    aptr.print();
    dptr.print();
    dptr.exchange(aptr);
    aptr.print();
    dptr.print();
    
    
    
    
}