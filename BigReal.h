

#ifndef LETS_TRY_BIGREAL_H
#define LETS_TRY_BIGREAL_H

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <deque>
#include <map>
#include <set>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <regex>
using namespace std;


class BigReal{
private:
    string number;
    char signNumber;
    bool checkValidInput(string input);

public:
    bool operator < (const BigReal& anotherDec);
    bool operator > (const BigReal& anotherDec);
    bool operator == (const BigReal anotherDec);
    BigReal& operator = (BigReal anotherDec);
    BigReal operator + (BigReal number2);
    BigReal operator - (BigReal anotherDec);
    friend ostream &operator << (ostream &out, BigReal num);
    int size();
    int sign();
    void setNumber(string num);
    string getNumber(){
        return number;
    }

    BigReal(){}
    BigReal(string num)
    {
        setNumber(num);
    }

};



#endif //LETS_TRY_BIGREAL_H
