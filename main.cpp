#include <iostream>
#include"matrix.hpp"
// 随机数
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    
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


              



    return 0;
}
