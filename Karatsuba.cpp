#include <iostream>
#include <cmath>

using namespace std;

int karatsuba(int x, int y);
int num(int x);

int main() { //Test Code


    cout << "7*6 = " << karatsuba(7, 6) << endl; // 42
    cout << "15*15 = " << karatsuba(15, 15) << endl; // 225
    cout << "6*13 = " << karatsuba(6, 13) << endl; // 78
    cout << "51*49 = " << karatsuba(51, 49) << endl; // 2499
    cout << "111*111 = " << karatsuba(111, 111) << endl; // 12321
    cout << "5678*1234 = " << karatsuba(5678, 1234) << endl; // 7006652
    cout << "12345678*1 = " << karatsuba(12345678, 1) << endl; // 12345678
    cout << "12345678*0 = " << karatsuba(12345678, 0) << endl; // 0
    return 0;
}

int karatsuba(int x, int y) //Karatsuba implementation
{
    int n = 0;
    int numx;
    int numy;
if (x == 0 || y == 0) //Initial if statement for 0
    {
        return 0;
    }
    numx = num(x); //Finding number of digits for x and y
    numy = num(y);


    if (numx < numy) //Finding the lowest number of digits between x and y
    {
        n = numx;
    }
    else
    {
        n = numy;
    }

    if (n == 1) //Initial if statement for single digits
    {
        return x*y;
    }
    else
    {

    int a,b,c,d;
    int splitNum;
    int mod;

    splitNum = ceil(n/2);

    mod = ceil(pow(10,splitNum)); //finding the modulus as a buffer variable

    a = floor(x/(pow(10,splitNum))); //Finding first half of number
    b = x % mod; //Finding the rest of the number
    c = floor(y/(pow(10,splitNum)));
    d = y % mod;

    int ac = karatsuba(a,c);
    int bd = karatsuba(b,d);
    int mid = karatsuba(a+b,c+d) - ac - bd;


        return ac*pow(10,(2*splitNum))+(mid*pow(10,splitNum))+bd;
    }


}

int num(int x) //Function to find the number of digits in a number
{


    int newX = floor(log(x)/log(10) + 1);

    return newX;
}


