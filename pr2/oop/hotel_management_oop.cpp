#include <iostream>
#include <string>

using namespace std;

class Person {
    private:
        string name;
        int age;
        string id;
    public:
        Person(const string& name, const int age, const string& id)
            : name(name), age(age), id(id) {}
        
        // Getters
        string nameGetter() const { return name; }
        int ageGetter() const { return age; }
        string idGetter() const { return id; }

        // Setters
        void nameSetter(const string& name) { this->name = name;}
        void ageSetter(const int age) { this->age = age;}
        void idSetter(const string& id) { this->id = id;}
};

class Employee: public Person {
    protected:
        string department;
};