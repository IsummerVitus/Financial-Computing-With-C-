//
//  Matrix.h
//  
//
//  Created by Li M on 15/11/10.
//
//

#ifndef _Matrix_h
#define _Matrix_h
#include <iostream>
#include <ctime>
#include <assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>

using namespace std;

class Matrix{
private:
    int numRows;
    int numColumns;
    //helper functions - useful for finding the inverse
    void subtractRow(int i, int j);					//Subtracts row j from row i
    void swapRows(int i, int j);					//Swaps rows i and j
    void multiplyRow(int i, double d);				//Multiplies row i by constant d
    vector<vector<double> > elements;
    
public:
    Matrix(const Matrix &m)						//copy constructor
    {
        numRows = m.numRows; numColumns = m.numColumns;
        elements.resize(numRows);
        for (int i = 0; i < numRows; i++) {
            elements[i].resize(numColumns,0);
        }
        for (int i = 0; i < numRows; i++){
            for (int j = 0; j < numColumns; j++)
                elements[i][j] = m.elements[i][j];
        }
    }
    Matrix(int rows, int columns):numRows(rows),numColumns(columns)				//constructor
    {
        elements.resize(numRows);
        for (int i = 0; i < numRows; i++) {
            elements[i].resize(numColumns, 0);
        }
    }
    friend Matrix operator *(Matrix& ,Matrix& );
//    ~Matrix()										//destructor
//    {
//        for (int i = 0; i < numRows; ++i) {
//            elements[i].clear();
//            elements[i].shrink_to_fit();
//        }
//        elements.clear();
//        elements.shrink_to_fit();
//    }
    Matrix& operator=(Matrix& m)				//assignment operator
    {
        if (this != &m) {
            for (int i = 0; i < numRows; ++i) {
                elements[i].clear();
                elements[i].shrink_to_fit();}
        }
            elements.clear();
            elements.shrink_to_fit();
        numRows = m.numRows; numColumns = m.numColumns;
        elements.resize(numRows);
        for (int i = 0; i < numRows; i++) {
            elements[i].resize(numColumns,0);
        }
        for (int i = 0; i < numRows; i++){
            for (int j = 0; j < numColumns; j++)
                elements[i][j] = m.elements[i][j];
        }
        return *this;
    }

    friend Matrix& operator + (Matrix& ,Matrix& );
    
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
        
    }
    void transforRow(int i, int j, double d)           //row[i]-row[j]*d
    {
        double *temp=new double[numColumns];
        
        for (int k = 0; k < numColumns; k++) {
            temp[k] = elements[j][k]*d;
        }
        for (int k = 0; k < numColumns; k++) {
            elements[i][k] -= temp[k];
        }
    }//multiplication by const
    double* operator[](int i)
    {
        double *row = &elements[i][0];
        return row;
    }//overloaded operator [] - note the return type
    void subtractRow(int i, int j,double k) {
        for(int ii=0;ii<numColumns;ii++)
            elements[j][ii]-=k*elements[i][ii];
    }
    void inverse() {
        
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
            elements.resize(numRows);
            for (int i = 0; i < numRows; i++) {
                elements[i].resize(numColumns,0);
            }
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
    friend ostream& operator<<(ostream& ,const Matrix&);//Stream "<<" overloading
    friend std::istream& operator >>(std::istream&, Matrix& );
    void LUDecompose();
    void GaussSeidel(vector<double> b,  int iter);
    
};

//const Matrix EMPTY_MATRIX(0, 0);//empty matrix- in case of error
Matrix& operator + (Matrix& h,Matrix& m)
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
 Matrix operator *(Matrix& h,Matrix& m)
{
    
    Matrix temp(h.numRows,m.numColumns);
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
void Matrix::subtractRow(int i, int j)
{
    for(int k=0;i<numColumns;k++)
    {
        elements[i][k]-=elements[j][k];
    }
}//Subtracts row j from row i
void Matrix::swapRows(int i, int j)
{
    assert(i >= 0 && i <= numRows&&j >= 0 && j <= numRows);
    double *tem = new double[numColumns];
    for (int k = 0; k < numColumns; ++k)
        tem[k] = elements[i][k];
    for (int k = 0; k < numColumns; ++k)
        elements[i][k] = elements[j][k];
    for (int k = 0; k < numColumns; ++k)
        elements[j][k] = tem[k];
    delete[]tem;
}//Swaps rows i and j
void Matrix::multiplyRow(int i, double d)
{
    assert(i >= 0 && i < numRows);
    for (int k = 0; k < numColumns; ++k)
        elements[i][k] *= d;}//Multiplies row i by constant d

void Matrix::LUDecompose()
{
    assert(numRows == numColumns);
    Matrix temp(*this);                   //construct new matrix
    //cout << temp;
    if (elements[0][0] == 0) {
        for (int i = 0; i < numRows; i++) {
            if (elements[i][0] != 0) temp.swapRows(i, 0);
        }
    }
    for (int i = 0; i <numRows; i++) {
        for (int j = i + 1; j < numRows; j++) {
            temp.transforRow(j, i, 1 / temp.elements[i][i] * temp.elements[j][i]);
        }
    }
    cout << "By LU decompose we get U:" << endl;
    cout << temp;
    cout << "L:" << endl;
    temp.inverse();
    cout << temp;
   
    return;
    
}
void Matrix::GaussSeidel(vector<double> b,  int iter)
{
    assert(numColumns == b.size());
    vector<double> x(numColumns,0);
    for (int iteration = 0; iteration < iter; iteration++)
    {
        for (int i = 0; i < numColumns; i++)
        {
            x[i] = 0;
            double sum1 = 0;
            for (int j = 0; j < i; j++) {
                sum1 += elements[i][j] * x[j];
            }
            
            for (int j = i + 1; j < numColumns; j++) {
                sum1 += elements[i][j] * x[j];
            }
            x[i] = 1 / elements[i][i] * (b[i] - sum1);
            
        }
    }
    
    for (int i = 0; i < numColumns;i++)
        cout << x[i]<<endl;
    
    return ;
}
ostream& operator<<(ostream& os,const Matrix& m)
{
    
    for (int i=0;i<m.numRows;i++)
    {for (int j=0;j<m.numColumns;j++)
    {os<<m.elements[i][j]<<" ";}
        os<<std::endl;
    }
    return os;
    
    
    
    
    
}//Stream "<<" overloading
istream& operator>>(istream& is, Matrix& m)
{
    for (int i=0;i<m.numRows;i++)
    {for (int j=0;j<m.numColumns;j++)
    {is>>m.elements[i][j];}
        
    }
    return is;
}

#endif


