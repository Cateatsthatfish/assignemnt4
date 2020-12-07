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
    //std::cout << "Copy!" << endl;
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
      // std:: cout << "destroyed!" << std::endl;
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

Matrix Matrix::multi_block(const Matrix &B){
    int M(_Row), N(_Column),P(B._Column);
    Matrix temp(M,P,0);
    float * tmpB = new float[4*N];
    int n1(N),n2(2*N),n3(3*N);
    
    for(int j = 0; j < P; j+=4){
        for(int k = 0; k < N ; k++){
            tmpB[k] =  B(k,j);
            tmpB[k+n1] = B(k,j+1);
            tmpB[k+n2] = B(k,j+2);
            tmpB[k+n3] = B(k,j+3);
        }
        /*
        for(int l = 0; l<4*N;l++){
            cout << tmpB[l] << " ";
        }
        */
        for(int i = 0; i < M; i+=4){
            kernel(temp,_Matrix,tmpB,i,j);            
        }
    }

    delete [] tmpB;
    return temp;   
}

void Matrix::kernel(Matrix& c, float *a , float*b, int row, int col){
    int N(_Column);
    int n0(N*row),n1(N*(row+1)),n2(N*(row+2)),n3(N*(row+3));
    /*
    Matrix c : temp 
    float *a : this._Matrix
    float *b : tmpB 
    int row = i
    int col = j

    c(j,i) -> c(j+3,i+3)
    t0,  t1,  t2,  t3
    t4,  t5,  t6,  t7
    t8,  t9,  t10, t11
    t12, t13, t14, t15
    */
    register double t0(0),t1(0),t2(0),t3(0),t4(0),t5(0),t6(0),t7(0),
                    t8(0),t9(0),t10(0),t11(0),t12(0),t13(0),t14(0),t15(0);
    

    float *a0(a+n0),*a1(a+n1),*a2(a+n2),*a3(a+n3),
            *b0(b),*b1(b+N),*b2(b+2*N),*b3(b+3*N),
            *end=b0+N;
            //cout << *a0 << " " << *a1 << " " << *a2 << " " << *a3 << endl;
            

    do{
        t0+=*(a0)**(b0);
        t1+=*(a0)**(b1);
        t2+=*(a0)**(b2);
        t3+=*(a0++)**(b3);            

        t4+=*(a1)**(b0);
        t5+=*(a1)**(b1);
        t6+=*(a1)**(b2);
        t7+=*(a1++)**(b3);

        t8+=*(a2)**(b0);
        t9+=*(a2)**(b1);
        t10+=*(a2)**(b2);
        t11+=*(a2++)**(b3);

        t12+=*(a3)**(b0++);
        t13+=*(a3)**(b1++);
        t14+=*(a3)**(b2++);
        t15+=*(a3++)**(b3++);
            
    }while(b0!=end);

    c(col,row) = t0;
    c(col,row+1) = t1;
    c(col,row+2) = t2;
    c(col,row+3) = t3;

    c(col+1,row) = t4;
    c(col+1,row+1) = t5;
    c(col+1,row+2) = t6;
    c(col+1,row+3) = t7;

    c(col+2,row) = t8;
    c(col+2,row+1) = t9;
    c(col+2,row+2) = t10;
    c(col+2,row+3) = t11;

    c(col+3,row) = t12;
    c(col+3,row+1) = t13;
    c(col+3,row+2) = t14;
    c(col+3,row+3) = t15;


}