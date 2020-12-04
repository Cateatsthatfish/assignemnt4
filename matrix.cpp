#include <iostream>
// 随机数
#include <cstdlib>
#include <ctime>
//getline
#include <string> 
#include "matrix.hpp"

const int a = -1;
const int b = 1;

using namespace std;

bool isValid_int(string in);


Matrix::Matrix():_Row(0),_Column(0),_Total(0){
    _Matrix = new float [1];
    refcount = (int*)_Matrix;
    *refcount = 1;
}

Matrix::Matrix(int r,int c):_Row(r),_Column(c),_Total(r*c){
    _Matrix = new float [_Total+1];
    //srand((int)time(0));
    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = a + rand()%(b-a) + rand()/double(RAND_MAX);
        //_Matrix[i] = i;
    }
    refcount = (int*) (_Matrix+_Total);
    *refcount = 1; 
}

Matrix::Matrix(int r,int c, const float init):_Row(r),_Column(c),_Total(r*c){
    _Matrix = new float [_Total+1];
    for(int i = 0 ; i<_Total;i++){
        _Matrix[i] = init;
        //_Matrix[i] = i;
    }
    refcount = (int*) (_Matrix+_Total);
    *refcount = 1; 

}

//拷贝构造(指针指向同一片数据)
Matrix::Matrix(const Matrix& B){
    _Row = B._Row;
    _Column = B._Column;
    _Total = B._Total;
    _Matrix = B._Matrix;
    refcount = B.refcount;
    ++ * refcount;   
}

Matrix::~Matrix(){
    *refcount = *refcount -1;
    if(*refcount == 0){
        delete [] _Matrix;
    } 
}

// = 
Matrix & Matrix :: operator = (const Matrix & B){
    _Row = B._Row;
    _Column = B._Column;
    _Total = B._Total;

    *refcount = * refcount - 1;
    if(*refcount == 0){
        delete [] _Matrix;
    }

    _Matrix = B._Matrix;
    refcount = B.refcount;
    *refcount = *refcount + 1;
    return *this;
}

// <<
ostream & operator << (ostream & os, const Matrix & B){
    for(int i = 0; i< B._Row;i++){
        for(int j =0 ; j < B._Column ; j++){
        os << B(i,j) << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}
// >>
void operator >> (std::istream & is, Matrix & B){
    string n1_in, m1_in; 
    int n1,m1;
    //cout << "initialize a m*n matrix:(m,n are positive integers)" << endl;
    cout << "#row = ";
    getline(cin,m1_in);
    while(!isValid_int(m1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "#row = ";
    getline(cin,m1_in);    
        }

    cout << "#column = ";
    getline(cin,n1_in);
    while(!isValid_int(n1_in)){
    cout << "Invalid input! please try again! "<<endl;
    cout << "#column = ";
    getline(cin,n1_in);      
        }

    m1 = atoi(m1_in.c_str());
    n1 = atoi(n1_in.c_str());

    Matrix temp(m1,n1); //里面的值是随机数
    B = temp;

}

bool isValid_int(string in){
    bool len = true;
    if(in.length()==0){
        len = false;
    
    }
    // 不允许第一位是0的情况,与不允许输入0
    if(in[0]=='0'){
        len = false;
    }
    for(int i = 0 ; i< in.length();i++){
        if(in[i]>'9'||in[i]<'0')
        {
            len = false;
            break;
        }
    }    
    return len;
}

// C = A*B
Matrix Matrix :: operator * (const Matrix & B)const{
    int m(_Row),n(_Column),p(B._Column);
    if(n = B._Row)
    {
    Matrix temp(m,p,0);
    for(int i = 0; i < m; i++ ){
        for(int j = 0; j < p; j++ ){
            float c = 0; 
            for (int k = 0; k< n; k++){
                c += (*this)(i,k) * B(k,j);                
                }
            temp(i,j) = c;
        }
    }
    return temp; 
    }else{
        cout << "sizes don't match!" << endl;
        return *this;
    }

}
// C = A*b
Matrix Matrix :: operator * (const float b)const{
    Matrix temp(_Row,_Column,0);
    for(int i = 0; i<_Total; i++){
        temp._Matrix[i] = b*(_Matrix[i]);
    }
    return temp;
}
// C = a*B
Matrix operator * (float a, const Matrix &B){
    Matrix temp(B._Row,B._Column,0);
    for(int i = 0; i<B._Total; i++){
        temp._Matrix[i] = a*(B._Matrix[i]);
    }
    return temp;
}

//A+B
Matrix Matrix::operator + (const Matrix & B) const {
    if(_Column == B._Column && _Row == B._Row){
        Matrix temp(_Row,_Column,0);
        for(int i = 0; i<_Total;i++){
            temp._Matrix[i] = _Matrix[i]+B._Matrix[i];
        }
        return temp;
    }else{
        cout << "sizes don't match !" << endl;
        return *this;
    }
}
//A-B
Matrix Matrix::operator - (const Matrix & B) const {
    if(_Column == B._Column && _Row == B._Row){
        Matrix temp(_Row,_Column,0);
        for(int i = 0; i<_Total;i++){
            temp._Matrix[i] = _Matrix[i]-B._Matrix[i];
        }
        return temp;
    }else{
        cout << "sizes don't match !" << endl;
        return *this;
    }
}
//A==B
int Matrix::operator == (const Matrix & B) const{
    int tf = 1;
    if(!(_Column == B._Column && _Row == B._Row)){
        tf = 0;
    }
    for(int i = 0; i<_Total;i++){
        if(_Matrix[i]!=B._Matrix[i]){
            tf = 0;
            break;
        }
    }
    return tf;
    
}
//A!=B
int Matrix::operator != (const Matrix & B) const{
    return !(*this==B);
    //cout << "afer return" << endl;
}
// ~
Matrix operator ~ (const Matrix & B){
    Matrix temp(B._Column,B._Row,0);
    for(int i = 0; i<B._Row;i++){
        for(int j = 0; j<B._Column;j++){
            temp(j,i) = B(i,j);
        }
    }
    return temp;
}

