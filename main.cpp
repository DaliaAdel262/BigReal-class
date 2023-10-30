#include<iostream>
#include<bits/stdc++.h>
#include "BigReal.h"
#include "BigReal.cpp"

using namespace std;

int main() {
    string number;
    cin>>number;
    BigReal x(number);
    if (!x.isvalid()){
        cout << "not  a valid number";
    }
}
