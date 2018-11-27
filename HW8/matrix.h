//
//  Header.h
//  HW8_1
//
//  Created by Li M on 15/10/31.
//  Copyright (c) 2015年 Li M. All rights reserved.
//

#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

using namespace std;

class Matrix{
private:
    int numRows;
    int numColumns;
    //helper functions - useful for finding the inverse
    void subtractRow(int i, int j);					//Subtracts row j from row i
    void swapRows(int i, int j);					//Swaps rows i and j
    void multiplyRow(int i, double d);				//Multiplies row i by constant d
    
    double** elements;								//the array
public:
    Matrix(const Matrix &m);						//copy constructor
    Matrix(int rows, int columns)				//constructor
    {
        elements = new double *[numRows];
        for (int i=0; i<numRows; ++i) {
            elements[i] = new double [numColumns];
        }
        // Initialize value for the matrix
        for (int i=0; i<numRows; ++i)
        {
            
            for (int j=0; j<numColumns; ++j)
            {
                elements[i][j]=0;
            }
        }

    }
    //Matrix();
    ~Matrix()
    {
        delete []elements;
    }//destructor
    
    Matrix& operator=(Matrix& m)				//assignment operator
    {
        if (this==&m)
            return *this;
        numColumns=m.numColumns;
        numRows=m.numRows;
        delete [] elements;
        double **elements = new double *[numRows];
        for (int i=0; i<numRows; ++i) {
            elements[i] = new double [numColumns];
        }
        // Initialize value for the matrix
        for (int i=0; i<numRows; ++i)
        {
            
            for (int j=0; j<numColumns; ++j)
            {
                elements[i][j]=m.elements[i][j];
            }
        }
        return *this;

    }
    friend Matrix& operator + (Matrix& h,Matrix& m)
    {
        assert(h.numRows==m.numRows&&h.numColumns==m.numColumns);
        for (int i=0; i<m.numRows; ++i)
        {
            
            for (int j=0; j<m.numColumns; ++j)
            {
                h.elements[i][j]+=m.elements[i][j];
            }
        }
        return h;
        
    }//addition operator
    friend Matrix operator *(Matrix& h,Matrix& m)
    {
        
//        double **temptr = new double *[h.numRows];
//        for (int i=0; i<h.numRows; ++i) {
//            temptr[i] = new double [m.numColumns];
//        }
//        for (int i=0; i<h.numRows; ++i)
//        {
//            
//            for (int j=0; j<m.numColumns; ++j)
//            {
//                temptr[i][j]=0;
//            }
//        }
//        
        Matrix temp(h.numRows,m.numColumns);
        //temp.numRows=h.numRows;temp.numColumns=m.numColumns;
        //temp.elements=temptr;
        assert(h.numColumns==m.numRows);
        for (int i=0; i<h.numRows; ++i)
        {
            
            for (int j=0; j<m.numColumns; ++j)
            {
                for (int k=0; k<h.numColumns; ++k)
                    temp[i][j]+=h.elements[i][k]*m.elements[k][j];
            }
        }
        
        return temp;
        
        
        
        
    }//matrix multiplication
    Matrix operator *(double d)
    {
        Matrix result(numRows,numColumns);
        
        for (int i=0; i<result.numRows; ++i)
        {
            
            for (int j=0; j<result.numColumns; ++j)
            {
                result.elements[i][j]=elements[i][j]*d;
            }
        }
        
        return result;

    }//multiplication by const
    double* operator[](int i)
    {
        assert(i>=0&&i<=numRows);
        return elements[i];
    }//overloaded operator [] - note the return type
    void subtractRow(int i, int j,double k) {
        for(int ii=0;ii<numColumns;ii++)elements[j][ii]-=k*elements[i][ii]; }
    void inverse() {
        if(numRows!=numColumns){
            cout<<"Error! numRow!=numColumns"<<endl; return ;
        }
        int n=numRows;
        Matrix ret(n,n);
        Matrix tmp(*this);
        for(int i=0;i<n;i++)for(int j=0;j<n;j++)ret[i][j]=(i==j);
        for(int i=0;i<n;i++) {
            int flag=-1; for(int j=i;j<n;j++) {
                if(tmp[j][i]!=0){flag=j;break;} }
            if(flag==-1){cout<<"Error! No inverse matrix."<<endl;return ;} tmp.swapRows(i,flag);
            ret.swapRows(i,flag);
            double t=1/tmp[i][i];
            tmp.multiplyRow(i,t); ret.multiplyRow(i,t); for(int j=0;j<n;j++)
            {
                if(i==j)continue; t=tmp[j][i]; tmp.subtractRow(i,j,t); ret.subtractRow(i,j,t);

            } //cout<<"turn"<<i<<endl; //cout<<tmp<<endl; //cout<<ret<<endl;
        } if(this!=&ret) {
            delete[] elements;
            elements=new double*[numRows];
            for(int i=0;i<numRows;i++)elements[i]=new double[numColumns];
            for(int i=0;i<numRows;i++)for(int
                                          j=0;j<numColumns;j++)elements[i][j]=ret.elements[i][j]; }
        return ; }
    Matrix transpose(Matrix &h)
    {
        Matrix temo(h.numColumns,h.numRows);
        for (int i=0; i<h.numColumns; ++i)
        {
            
            for (int j=0; j<h.numRows; ++j)
            {
                
                temo[i][j]=h[j][i];            }
        }
        return temo;

    }//returns a tranposed matrix
    void choleskyDecompose()
    {
        assert(numRows==numColumns);
        
            int j=0;
        int size=numColumns;
            elements[j][j]=pow(elements[j][j],0.5);
            for(int i=j+1;i<size;i++)
            {
                elements[i][j]=elements[i][j]/elements[j][j];
            }
            
            for(int j=1;j<size;j++)
            {
                int sum=0;
                for(int k=0;k<j;k++)
                {
                    sum+=pow(elements[j][k],2);
                }
                elements[j][j]=pow(elements[j][j]-sum,0.5);
                for(int i=j+1;i<size;i++)
                {
                    int sum1=0;
                    for(int k=0;k<j;k++)
                    {
                        sum1+=elements[i][k]*elements[j][k];
                    }
                    
                    elements[i][j]=elements[i][j]/elements[j][j]-sum1;
                }
            }
            
       

    }//finds and returns a Cholecky Decomposition of the matrix
    friend ostream& operator<<(ostream& os,const Matrix& m)
    {
        
        for (int i=0;i<m.numRows;i++)
        {for (int j=0;j<m.numColumns;j++)
            {os<<m.elements[i][j]<<" ";}
            os<<std::endl;
        }
        return os;
        
        
        
        

    }//Stream "<<" overloading
    friend istream& operator>>(istream& is, Matrix& m)
    {
        for (int i=0;i<m.numRows;i++)
        {for (int j=0;j<m.numColumns;j++)
        {is>>m.elements[i][j];}
            
        }
        return is;
    }
};

//const Matrix EMPTY_MATRIX(0, 0);//empty matrix- in case of error

Matrix::Matrix(const Matrix &m)
{
    numRows=m.numRows;
    numColumns=m.numColumns;
    double **elements = new double *[numRows];
    for (int i=0; i<numRows; ++i) {
        elements[i] = new double [numColumns];
    }
    // Initialize value for the matrix
    for (int i=0; i<numRows; ++i)
    {
        
        for (int j=0; j<numColumns; ++j)
        {
            elements[i][j]=m.elements[i][j];
        }
    }
}//copy constructor


void Matrix::subtractRow(int i, int j)
{
    for(int k=0;i<numColumns;k++)
    {
        elements[i][k]-=elements[j][k];
    }
}//Subtracts row j from row i
void Matrix::swapRows(int i, int j)
{
    for(int k=0;i<numColumns;k++)
    {
        double num1=0;
        num1=elements[j][k];
        elements[j][k]=elements[i][k];
        elements[i][k]=num1;
        

    }
}//Swaps rows i and j
void Matrix::multiplyRow(int i, double d)
{
    for(int k=0;i<numColumns;k++)
    {
        elements[i][k]=d*elements[i][k];
    }
}//Multiplies row i by constant d

//Matrix Matrix::operator + (const Matrix& m)
//{

//    for (int i=0; i<numRows; ++i)
//    {
//        
//        for (int j=0; j<numColumns; ++j)
//        {
//            elements[i][j]+=m.elements[i][j];
//        }
//    }
//    return *this;
//
//}//addition operator


#endif