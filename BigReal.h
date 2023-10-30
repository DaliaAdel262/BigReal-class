//
// Created by DELL on 10/28/2023.
//

#ifndef A2_GROUPB_S8_20220516_20220424_BIGREAL_H
#define A2_GROUPB_S8_20220516_20220424_BIGREAL_H

#include <bits/stdc++.h>
using namespace std;
class BigReal {
private:
    string number;
public:
    BigReal(string realnumber);
    bool isvalid();
    void set_sign();
    char sign=number[0];
    int size=number.size();
};


#endif //A2_GROUPB_S8_20220516_20220424_BIGREAL_H
