

#ifndef A2_GROUPB_S8_20220516_20220424_BIGREAL_H
#define A2_GROUPB_S8_20220516_20220424_BIGREAL_H

#include <bits/stdc++.h>
using namespace std;
class BigReal {
private:
    string number;
    char sign=number[0];
    int size=number.size();
    string integer;
    string fraction;
    char decimal = '.';
public:
    BigReal(string realnumber);
    bool isvalid();
    void set_sign();
    BigReal operator= (BigReal& other);
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    bool operator< (BigReal& other);
    bool operator> (BigReal& other);
    void print();
};


#endif //A2_GROUPB_S8_20220516_20220424_BIGREAL_H
