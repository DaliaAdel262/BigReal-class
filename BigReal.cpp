

#include "BigReal.h"
#include <bits/stdc++.h>
using namespace std;

BigReal::BigReal(string realnumber){
    number = realnumber;
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

