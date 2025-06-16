#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() = 0; // Pure virtual function (abstract)
};

class Dog : public Animal {
    // No override of makeSound()
};

int main() {
    // Dog d;              // ❌ Compilation error: Dog is abstract
    // Animal a;           // ❌ Compilation error: Animal is abstract
    Animal* a;             // ✅ Allowed: pointer to abstract class
    a->makeSound();
    return 0;
}