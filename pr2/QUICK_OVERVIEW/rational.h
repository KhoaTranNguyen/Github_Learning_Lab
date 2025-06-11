#pragma once
#include <iostream>
using namespace std;

class Rational {
    private:
        long long int numerator;
        long long int denominator;
        long long int gcd(long long int a, long long int b) {
            return (b == 0) ? a : gcd(b, a % b);
        }

    public:
        Rational(): numerator(1), denominator(1) {};
        Rational(long long int num, long long int denom) {
            if (denom == 0) {
                cout << "denominator must be not equal to 0.\n";
                numerator = 1;
                denominator = 0;
            }
            else {
                long long int common_div = gcd(abs(num), abs(denom));
                if (common_div == 1) {
                    numerator = num;
                    denominator = denom;
                }
                else {
                    numerator = num / common_div;
                    denominator = denom / common_div;
                }
            }
        }
        Rational (long long int whole): numerator(whole), denominator(1) {}
        
        long long int get_numerator() {return numerator;}
        long long int get_denumerator() {return denominator;}
        void print_fraction() {cout << numerator << "/" << denominator;}
};