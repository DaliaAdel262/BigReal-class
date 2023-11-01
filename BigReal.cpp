

#include "BigReal.h"
#include <bits/stdc++.h>
using namespace std;

BigReal::BigReal(string realnumber){
    number = realnumber;
    int decimal_pos;
    for (int i = 0 ; i < size ; i++){
        if ( number[i] == '.' ){
            decimal_pos=i;
          break ;
        }
        integer += number[i] ;
    }
    for (int j=decimal_pos+1 ; j<size ; j++){
        fraction += number[j] ;
    }
}

bool BigReal::isvalid() {
    char point='.';
    char space =' ';
    if (count(number.begin(),number.end(),point)>1){
        return (false) ;
    }
    if (std::count(number.begin(), number.end(),space)>0){
        return (false) ;
    }
    if (number.front()+1 == '+' ||number.front()+1 == '-'  ){
        return (false) ;
    }
    return (true);
}
//void BigReal::set_decimal_point (string number){
//    for (int i=0;i<number.size();i++){
//        if (number[i]=='.'){
//            decimal_pos=i;
//        }
//    }
//}
void BigReal::print(){
    cout << sign;
    cout <<
}

