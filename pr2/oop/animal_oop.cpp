#include <iostream>
#include <string>
using namespace std;

class Animal {
private:
    string name;
    int age;
public:
    Animal() : name("Unknown"), age(0) {}
    Animal(const string& AnimalName, const int AnimalAge) : name(AnimalName), age(AnimalAge) {}

    // Setter
    void setValue (const string& AnimalName, const int AnimalAge) {
        name = AnimalName;
        age = AnimalAge;
    }

    // Getter
    string peekName() const {return name;}
    int peekAge() const {return age;}
};

class Zebra : public Animal {
    public:
        Zebra() : Animal() {}
        
        Zebra(const string& ZebraName, const int ZebraAge)
        : Animal(ZebraName, ZebraAge) {}

        void hello() const {
            cout << "I'm Zebra. My name is " << peekName()
                << ". I'm " << peekAge() << " years old. "
                << "I have black and white stripes!\n";;
        }
};

class Dolphin : public Animal {
    public:
        Dolphin() : Animal() {}
    
        Dolphin(const string& dolphinName, const int dolphinAge)
            : Animal(dolphinName, dolphinAge) {}
    
        void hello() const {
            cout << "I'm Dolphin. My name is " << peekName()
                 << ". I'm " << peekAge() << " years old. I love swimming and jumping!\n";
        }
    };
    

int main() {
    Zebra z("Alice", 3);
    z.hello();

    Dolphin d("Khang", 5);
    d.hello();
    return 0;
}
