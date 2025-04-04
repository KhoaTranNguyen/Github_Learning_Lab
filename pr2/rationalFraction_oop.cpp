#include <iostream>

using namespace std;

class Rational {
private:
    int numerator;
    int denominator;
    double fraction;
    int gcd(int a, int b) {
        return (b == 0) ? a : gcd(b, a % b);
    }

public:
    //Default constructor: sets numerator and denominator to 0 and 1 respectively
    Rational() : numerator(1), denominator(1), fraction(1.0) {}

    //Fractional constructor: converts num and denom to fraction
    Rational(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            std::cerr << "Denominator cannot be zero. Setting to 1." << std::endl;
            denominator = 1;
        }
        int common = gcd(abs(num), abs(denom));
        numerator = num / common;
        denominator = denom / common;
        this->fraction = static_cast<double>(numerator) / denominator;
    }

    // Fraction constructor for whole numbers
    Rational(int whole) : numerator(whole), denominator(1), fraction(whole) {}

    //Returns the numerator and denominator
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    double getFraction() const { return fraction; }
};

int main(){
    Rational r1(12, 4);
    cout << r1.getNumerator() << "/" << r1.getDenominator() << " = " << r1.getFraction() << endl;
    Rational r2(5);
    cout << r2.getNumerator() << "/" << r2.getDenominator() << " = " << r2.getFraction() << endl;
    return 0;
}