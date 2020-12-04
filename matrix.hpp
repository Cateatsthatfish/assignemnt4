#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
class Matrix{
private:
    int _Row,_Column,_Total;
    // _Total = _Row * _Column;
    float * _Matrix;
    //float * _Matrix = new float[_Total + 1];
    // +1: 这个位置用来存放refcount
    int * refcount;
    //refcount: 引用计数
    //refcount = (int*)(_Matirx + _Total);
    //*refcount = 1; // 最开始创建的时候，记录被引用了一次  

public:
    Matrix();//默认构造
    Matrix(int r,int c);//构造r行、c列的矩阵, 里面元素为随机数
    Matrix(int r,int c,const float init);//构造r行、c列的矩阵, 里面元素为init
    Matrix(const Matrix&B); // 拷贝构造
    ~Matrix();

    //A(i,j)
    float& operator()(int i,int j){return _Matrix[i*(_Column)+j];}
    //B(i,j)
    const float operator()(int i,int j)const{return _Matrix[i*(_Column)+j];}
    // =
    Matrix & operator = (const Matrix & B);
    // << 
    friend std::ostream & operator << (std::ostream & os, const Matrix & B);
    // >>
    friend void operator >> (std::istream & is, Matrix & B);
    // C = A*B
    // 条件 ： A._Column = B._Row
    Matrix operator * (const Matrix & B) const;
    // C = A*b
    Matrix operator * (const float b) const;
    // C = a*B
    friend Matrix operator * (float a, const Matrix & B);
    // C = A + B
    // 条件： A._Column = B._Column A._Row = B._Row
    Matrix operator + (const Matrix & B) const;
    // C = A - B
    // 条件： A._Column = B._Column A._Row = B._Row
    Matrix operator -(const Matrix & B) const;
    // ==
    // 大小和值相等就可以
    int operator == (const Matrix & B)const;
    // !=
    // 大小不等 或者 值不相等
    int operator !=(const Matrix & B) const;
    // ~ 
    // 转置
    friend Matrix operator ~ (const Matrix &B);

};
#endif