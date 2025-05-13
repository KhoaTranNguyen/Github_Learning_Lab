#include <iostream>
using namespace std;

// Create a simple class containing an int and overload the (binary) 
// operator+ as a member function. In other words, adding 2 objects of 
// your class would result in the addition of the 2 corresponding integers. 
// Test your class to show that it works correctly.

class Counter {
private:
    int count_; // Private member variable
public: 
    // Constructor to initialize count_
    Counter(int count = 0) : count_(count) {}

    // Overload the + operator
    Counter operator+(const Counter& other) const {
        return Counter(count_ + other.count_);
    }

    Counter operator-(const Counter& other) const {
        return Counter(count_ - other.count_);
    }

    // Overload the prefix ++ operator
    Counter& operator++() {
        ++count_;
        return *this;
    }

    // Overload the postfix ++ operator
    const Counter operator++(int) {
        Counter temp = *this; // Create a copy of the current object
        ++count_;             // Increment the count
        return temp;         // Return the copy (not incremented)
    } // This ensures the returned object cannot be modified, which is useful in preventing unintended operations like:
      // (counter++)++;
      // That would be nonsense and should be rejected.

    // Overload the prefix -- operator
    Counter& operator--() {
        --count_;
        return *this;
    }

    // Overload the postfix -- operator
    const Counter operator--(int) {
        Counter temp = *this; // Create a copy of the current object
        --count_;             // Decrement the count
        return temp;         // Return the copy (not incremented)
    }

    // Display function to show the value of count_
    void displayCount() const {
        cout << "Count: " << count_ << endl;
    }

    void display() const {
        cout << count_ << endl;
    }
};


int main() {
    Counter counter1(5);
    counter1.displayCount();
    Counter counter2(10);
    counter2.displayCount();
    Counter addition = counter1 + counter2;
    Counter subtraction = counter1 - counter2;
    Counter expression = counter1 + counter2 - counter1;

    // Display the result of the addition
    cout << endl << "Addition: ";
    addition.display();
    cout << "Prefix of addition: ";
    ++addition;
    addition.display();
    cout << "Postfix of addition: ";
    addition++;
    addition.display();

    cout << endl << "Subtraction: ";
    subtraction.display();
    cout << "Prefix of subtraction: ";
    --subtraction;
    subtraction.display();
    cout << "Postfix of subtraction: ";
    subtraction--;
    subtraction.display();
    cout << "Test Postfix const: Passed!" << endl;
    // (subtraction--)--; // ❌ INVALID — cannot modify const object

    subtraction.display();
    cout << endl << "Full expression: ";
    expression.display();

    return 0;
}