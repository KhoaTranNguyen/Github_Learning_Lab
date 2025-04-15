#include <iostream>
#include <string>
using namespace std;

class Mother {
private:
    string name;
public:
    Mother() : name("Unknown") {}
    Mother(const string& motherName) : name(motherName) {}

    void hello() const {
        cout << "I'm mom. My name is " << name << "\n";
    }

    string getName() const { 
        if (name == "")
            return "Unknown"; 
        else
            return name;
    }
};

class Daughter : public Mother {
public:
    Daughter() : Mother() {}
    Daughter(const string& daughterName)
    : Mother(daughterName) {}

    void hello() const {
        cout << "I'm daughter. My name is " << getName() << "\n";
    }
};

int main() {
    Mother m("Alice");
    m.hello();
    Daughter d("Sophia");
    d.hello(); // Output: I'm daughter of Unknown. My name is Sophia

    return 0;
}
