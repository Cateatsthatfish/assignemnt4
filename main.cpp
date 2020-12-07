#include <iostream>
#include <chrono> 
#include "matrix.hpp"
// 随机数
#include <cstdlib>
#include <ctime>

#pragma GCC optimize(3, "Ofast", "inline")

const int n = 1000;
const size_t N2 = 10000;
const size_t N1 = 1000;
using namespace std;

int main(){
    /* --------- test block -------
    Matrix A(N1,N2,1),B(N2,N1,2);
    cout << A ;
    cout << B ;
    Matrix C = A.multi_block(B);
    cout << C;
    */

    /* --------- test speed ------- */
    srand((int)time(0));
    Matrix A(N1,N2),B(N2,N1);
    //Matrix A(n,n),B(n,n);

    cout << "multi_block:   " ;
    cout << endl;
    for(int i = 0; i<10;i++){
    //cout << i << ": ";
    auto t1=std::chrono::steady_clock::now(); 

    Matrix C1 = A.multi_block(B);
    auto t2=std::chrono::steady_clock::now(); //结束时间
    double time1=std::chrono::duration<double,std::milli>(t2-t1).count();
    //cout << "(time: " << time1 << "ms)" << endl;
    cout << time1 << endl;
    }    
    
    /*
    srand((int)time(0));
    Matrix A(4,8,2),B(8,3,0.8);
    cout << "----  A  ----" << endl;
    cout << A;
    cout << "----  B  ----" << endl;
    cout << B ;

    Matrix C = A*B;
    cout << "---- A*B ---" << endl;
    cout << C;
      
    Matrix D = 2*A;
    cout << "---- 2*A ---" << endl;
    cout << D;
    Matrix E = B*5;
    cout << "---- B*5 ---" << endl;
    cout << E;
    
    cout.setf(ios_base::fixed,ios_base::floatfield);
    cout.precision(6);

    cout << "- cin >> A -" << endl;
    cin >> A;
    cout << "----  A  ----" << endl;
    cout << A;
    cout << "---- ~A ----" << endl;
    cout << (~A); 

    
    Matrix F(2,2),G(2,2);
    cout << "----  F  ----" << endl;
    cout << F;
    cout << "----  G  ----" << endl;
    cout << G ;
    cout << "--- F==G? ---" << endl;
    cout << ((F==G)? "true":"false") << endl;
    cout << "--- F!=G? ---" << endl;
    cout << ((F!=G)? "true":"false") << endl;   
    Matrix H = F+G;
    cout << "---- F+G ---" << endl;
    cout << H;
    Matrix I = F-G;
    cout << "---- F-G ---" << endl;
    cout << I; 
    */
    return 0;
}
