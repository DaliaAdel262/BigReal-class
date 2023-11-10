
#include <iostream>
#include <string>
#include <map>
#include <istream>
#include <ostream>
#include <math.h>
#include <regex>
#include <vector>
#include <iostream>
#include <fstream>
#include <deque>
#include <set>
#include <cmath>
#include <algorithm>
#include "BigReal.h"
using namespace std;

/////////////////////////////////////////////////////////////////////
class helper
{
public:


    helper();
    helper(double realNumber);
    helper (string realNumber);
    helper (BigReal bigInteger);
    helper(const helper& other);
    helper (helper&& other);
    helper& operator= (helper& other);
    helper& operator= (helper&& other);
    helper operator+ (const helper& other);
    helper operator- (const helper& other);
    bool operator == (helper& anotherReal);
    bool operator < (helper& anotherReal);
    bool operator > (helper& anotherReal);
    int size();
    int sign();
    friend ostream& operator << (ostream& out,const helper& num);
    friend istream& operator >> (istream& out, helper& num);

    void setNumber( string num);



private:

    int Number;
    BigReal whole;
    string fraction;
    string number;
    char signNumber;
    bool checkValidInput(string input);
};

/////////////////////////////////////////////////////////////////////

bool helper :: checkValidInput (string input)
{
    return (regex_match (number, regex("[+-]?\\d*\\.?\\d*")));
}

helper::helper()
{
    number = "";
    signNumber = '+';
}

helper ::helper(double realNumber) {
    realNumber = 0.0;
}

helper::helper(string number)
{
    setNumber(number);

}

helper::helper(BigReal bigInteger)
{
    number = bigInteger.getNumber();
}

helper::helper(const helper &other) {
    this->Number = other.Number  ;
    this->signNumber = other.signNumber ;
}

helper::helper(helper &&other) {
    Number = other.Number ;
    signNumber = other.signNumber ;

    other.Number = 0;
    other.signNumber = '\0' ;
}

helper &helper::operator=(helper &&other) {
    if (&other != this){
        this->Number = other.Number  ;
        this->signNumber = other.signNumber ;

        other.Number = 0;
        other.signNumber = '\0';
    }

    return *this;
}

helper& helper::operator=(helper& other)
{
    if (&other != this){
        this->Number = other.Number  ;
        this->signNumber = other.signNumber ;
    }

    return *this;
}
void helper :: setNumber(string num)
{

    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            signNumber = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            signNumber = '-';
        }
        else
        {
            signNumber = '+';
        }

        int pose = num.find('.') ;
        if(pose>=1)
        {
            string numm;
            fraction=num.substr(pose+1);
            numm=num.substr(0,pose);
            BigReal whl(numm);
            whole=whl;
        }
        else
        {
            BigReal whl(num);
            whole=whl;
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(0);
    }

}

void  matchzeros(string &f1, string& f2)
{
    if (f1.size()>f2.size())
    {
        for(int i =f2.size() ; i<f1.size();i++)
        {
            f2+='0';
        }
    }
    else if(f1.size()<f2.size())
    {
        for(int i =f1.size() ; i<f2.size();i++)
        {
            f1+='0';
        }
    }
}

void subcarry(string& r,string& carry){
    char s;
    if(r[0] == '-'){
        s = r[0];
        r.erase(0,1);
        while (r.length() > carry.length()) {
            carry.insert(carry.begin(), '0');
        }
        BigReal c1(r),c2(carry),c3;
        c3 = c1 - c2;
        r = c3.getNumber();
        r.insert(r.begin(),s);
    }
    else{
        while (r.length() > carry.length()) {
            carry.insert(carry.begin(), '0');
        }
        BigReal c1(r),c2(carry),c3;
        c3 = c1 - c2;
        r = c3.getNumber();
    }

}
void addcarry(string& r,string& carry){
    char s;

    if(r[0] == '-'){
        s = r[0];
        r.erase(0,1);
        while (r.length() > carry.length()) {
            carry.insert(carry.begin(), '0');
        }
        BigReal c1(r),c2(carry),c3;
        c3 = c1 + c2;
        r = c3.getNumber();
        r.insert(r.begin(),s);
    }
    else{
        while (r.length() > carry.length()) {
            carry.insert(carry.begin(), '0');
        }
        BigReal c1(r),c2(carry),c3;
        c3 = c1 + c2;
        r = c3.getNumber();
    }

}

helper helper::operator+(const helper& number2) {
    int check,count=0;
    string Carry = "1", r, f1 = fraction, f2 = number2.fraction;
    helper FinalResult;
    BigReal r1 = whole + number2.whole;
    r = r1.getNumber();
    matchzeros(f1, f2);

    for (int i = 0; i < f1.length(); ++i) {
        if ((int) f1[i] > (int) f2[i]) {
            check = 1;
            break;
        } else if ((int) f1[i] < (int) f2[i]) {
            check = 2;
            break;
        }
        else{
            count++;
        }
    }
    if(f1.length() == count){
        check = 3;
    }
    if (signNumber == '-' && number2.signNumber == '+') {

        if (check == 1) {
            if(r == "0"){
                r = "-0";
            }
            if(r[0] == '-') {
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else{
                f2.insert(f2.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }

        } else if (check == 2) {
            if(r == "0"){
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else if(r[0] == '-'){
                f1.insert(f1.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }
            else {
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
        }
        else if (check == 3){
            f1 = "0";
        }
    }
    else if (signNumber == '+' && number2.signNumber == '-') {
        if (check == 1) {
            if(r == "0"){
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else if(r[0] == '-'){
                f2.insert(f2.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }
            else {
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
        } else if (check == 2) {
            if(r == "0") {
                r = "-0";
            }
            if (r[0] == '-'){
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else{
                f1.insert(f1.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }
        }
        else if(check == 3){
            f1 = "0";
        }
    }
    else  {
        BigReal num1(f1), num2(f2), num;
        num = num1 + num2;
        f1 = num.getNumber();
        if(f1.length() > f2.length()){
            f1.erase(0,1);
            addcarry(r, Carry);
        }
    }
    FinalResult.number = r + "." + f1;
    return FinalResult;

}

helper helper :: operator-(const helper& number2) {
    int check,count =0;
    string Carry = "1", r, f1 = fraction, f2 = number2.fraction;
    helper FinalResult;
    BigReal r1 = whole - number2.whole;
    r = r1.getNumber();
    matchzeros(f1, f2);

    for (int i = 0; i < f1.length(); ++i) {
        if ((int) f1[i] > (int) f2[i]) {
            check = 1;
            break;
        } else if ((int) f1[i] < (int) f2[i]) {
            check = 2;
            break;
        }
        else{
            count++;
        }
    }
    if(f1.length() == count){
        check = 3;
    }
    if (signNumber == '-' && number2.signNumber == '+') {
        BigReal num1(f1), num2(f2), num;
        num = num1 + num2;
        f1 = num.getNumber();
        if(f1.length() > f2.length()){
            f1.erase(0,1);
            addcarry(r, Carry);
        }
    }
    else if (signNumber == '+' && number2.signNumber == '-') {
        BigReal num1(f1), num2(f2), num;
        num = num1 + num2;
        f1 = num.getNumber();
        if(f1.length() > f2.length()){
            f1.erase(0,1);
            addcarry(r, Carry);
        }
    }
    else  {
        if (check == 1) {
            if(r == "0"){
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else if(r[0] == '-'){
                f2.insert(f2.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }
            else {
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
        } else if (check == 2) {
            if(r == "0") {
                r = "-0";
            }
            if (r[0] == '-'){
                BigReal num1(f1), num2(f2), num;
                num = num2 - num1;
                f1 = num.getNumber();
                while (count != 0){
                    f1.insert(f1.begin(),'0');
                    count--;
                }
            }
            else{
                f1.insert(f1.begin(), '1');
                BigReal num1(f1), num2(f2), num;
                num = num1 - num2;
                f1 = num.getNumber();
                subcarry(r, Carry);
            }
        }
        else if(check == 3){
            f1 = "0";
        }
    }
    FinalResult.number = r + "." + f1;
    return FinalResult;
}

bool helper :: operator < (helper& anotherReal)
{
    if(signNumber=='+' && anotherReal.signNumber=='-')
    {
        return false;

    }
    if (signNumber=='-' && anotherReal.signNumber=='+')
    {
        return true;
    }
    string leftf=fraction;
    string rightf=anotherReal.fraction;
    matchzeros(leftf,rightf);

    if(whole==anotherReal.whole)
    {
        if(signNumber=='-')  //-3.555 < -3.65
        {
            return(leftf>rightf);
        }
        else
        {
            return(leftf<rightf);
        }
    }
    else
    {
        return(whole<anotherReal.whole);

    }
}

bool helper :: operator > (helper& anotherReal)
{
    if(signNumber=='+' && anotherReal.signNumber=='-')
    {
        return true;

    }
    if (signNumber=='-' && anotherReal.signNumber=='+')
    {
        return false;
    }
    string leftf=fraction;
    string rightf=anotherReal.fraction;
    matchzeros(leftf,rightf);

    if(whole==anotherReal.whole)
    {
        if(signNumber=='-')
        {
            return(leftf<rightf);
        }
        else
        {
            return(leftf>rightf);
        }
    }
    else
    {
        return(whole>anotherReal.whole);

    }
}

bool helper :: operator == (helper &anotherReal)
{
    if (signNumber == anotherReal.signNumber && number == anotherReal.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}

int helper :: size()
{
    return whole.size()+fraction.size();
}

int helper :: sign()
{
    if (signNumber == '+')
    {
        return true;
    }
    else
    {
        return false ;
    }
}

ostream &operator << (ostream &out, const helper& num)
{

    if(num.signNumber == '+')
    {
        out << num.number ;
    }
    else
    {
        if(num.number == "0")
        {
            out << num.number ;
        }
        else
        {
            out << num.signNumber << num.number ;
        }
    }
    return out;
}
istream& operator >> (istream& out, helper& num)
{
    string str1;
    out >> str1;
    num.setNumber(str1);
    return out;
}

/////////////////////////////////////////////////////////////////////

int main()
{
    while (true) {
        char option;
        helper c1, c2;
        cout << "---------------------------------------------------------" << endl;
        cout << "< Choose Operation >" << endl
             << "1- Addition Operation" << endl
             << "2- Subtraction Operation" << endl
             << "3- Assignment Operation" << endl
             << "4- Is Equal Operation" << endl
             << "5- Is Greater  Operation" << endl
             << "6- IS Smaller Operation" << endl
             << "7- >> Operation" << endl
             << "8- << Operation" << endl
             << "9- Exit" << endl;
        cin >> option;
        if (option != '1' && option != '2' && option != '3' && option != '4' && option != '5'
        && option != '6' && option != '7' && option != '8' && option != '9' ){
            cout << "Invalid" << endl;
            continue;
        }


        if (option == '1') {
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;
            helper c3 = c1 + c2;
            cout << "The Result of addition = " << c3 << endl;
        } else if (option == '2') {
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;
            helper c3 = c1 - c2;
            cout << "The Result of subtraction = " << c3 << endl;
        }else if (option == '3'){
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;

            c1 = c2 ;
            cout << "Now the second number is equal the value of the first one; look!! : " << c2 << endl;
        }else if (option == '4'){
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;
            if (c1 == c2) {
                cout << "Numbers are equal" << endl;
                cout << "----------------------------------------------------------" << endl;
            }else{
                cout << "Numbers are not equal" << endl;
                cout << "----------------------------------------------------------" << endl;
            }
        }else if (option == '5'){
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;
            if (c1 > c2) {
                cout << "The first number is greater than second one" << endl;
                cout << "----------------------------------------------------------" << endl;
            }
            else {
                cout << "The first number is not greater than second one" << endl;
                cout << "----------------------------------------------------------" << endl;

            }
        }else if (option == '6'){
            cout << "---------------------------------------------------------" << endl;
            cout << "Enter The First Number : " << endl;
            cin >> c1;
            cout << "Enter The Second Number : " << endl;
            cin >> c2;
            cout << "----------------------------------------------------------" << endl;
            if (c1 < c2) {
                cout << "The second number is not smaller than first one" << endl;
                cout << "----------------------------------------------------------" << endl;
            }else{
                cout << "The second number is smaller than first one" << endl;
                cout << "----------------------------------------------------------" << endl;
            }
        }else if (option == '7'){

            cout << "Enter The Number to test >> operator : " << endl;
            cin >> c1;
        }else if (option == '8'){
            cout << "Enter The Number to test << operator : " << endl;
            cin >> c1;
            cout << "The number you entered is : " << endl;
            cout << c1;
        }else if (option == '9') {
            cout << "   Program Exits   " <<endl << "   goodbye     "<<endl ;
            break;
        }

        cout << endl ;
        cout << " Another Operation ? Type (y/n) : " << endl;
        char option2;
        cin >> option2;
        if(option2 == 'y')
            continue;
        if(option2 == 'n')
            cout << "------- << thanks for your time :) >> -------" << endl;
        break;
    }


    return 0;
}

