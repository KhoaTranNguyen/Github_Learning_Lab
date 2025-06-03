#include <iostream>
using namespace std;

// Create a simple class with an overloaded operator++. Try calling this
// operator in both pre- and postfix form and see what kind of compiler
// warning you get

class Counter {
private:
    int count_;
public:
    Counter(int count = 0) : count_(count) {}

    // Overload the prefix ++ operator
    Counter& operator++() {
        ++count_;
        return *this;
    }

    // Overload the postfix ++ operator
    Counter operator++(int) {
        Counter temp = *this; // Create a copy of the current object
        ++count_;             // Increment the count
        return temp;         // Return the copy (not incremented)
    }

    void display() const {
        cout << "Count: " << count_ << " || ";
    }

    void displayRes() const {
        cout << "Assigned: " << count_ << endl;
    }
};

int main() {
    //Loading
    cout << "Loading: ";
    Counter counter;
    counter.display();
    Counter result;
    result.displayRes();

    // Test prefix increment
    cout << "Prefix: ";
    result = ++counter;
    counter.display();
    result.displayRes();

    // Test postfix increment
    cout << "Postfix: ";
    result = counter++;
    counter.display();
    result.displayRes();

    return 0;
}