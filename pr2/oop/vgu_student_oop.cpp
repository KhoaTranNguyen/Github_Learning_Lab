#include <iostream>
#include <string>
using namespace std;

class Person {
    private:
        string name;
        int age;
    public:
        Person() : name("Unknown"), age(0) {}
        Person(const string& PersonName, const int PersonAge) : name(PersonName), age(PersonAge) {}

        // Getter
        string getName() const { return name; }
        int getAge() const { return age; }

        // Setter
        void setName(const string& name) {this->name = name;}
        void setAge(const int year) {this->age = year;}
};
    
class Student : public Person {
    private:
        string major;
        int duration;
        long id;
    public:
        Student() : major("Unknown"), duration(0), id(0) {}
        Student(const string& StudentName, const int StudentAge, const string& StudentMajor, const long id, const int StudentDuration)
        : Person(StudentName, StudentAge), major(StudentMajor), duration(StudentDuration), id(id) {}

        // Getter
        string getMajor() const { return major; }
        int getDuration() const { return duration; }
        long getID() const { return id; }

        // Setter
        void setMajor(const string& major) {this->major = major;}
        void setDuration(const int duration) {this->duration = duration;}
        void setID(const long id) {this->id = id;}

        //Public method
        void display() {
            cout << "|| VGU Student Information:" << endl;
            cout << "Name: " << getName() << endl;
            cout << "Age: " << getAge() << endl;
            cout << "Major: " << getMajor() << endl;
            cout << "ID: " << getID() << endl;
            cout << "Duration: " << getDuration() << " years" << endl;
        }

        // Destructor
        ~Student() {
            cout << "Destructor called for Student: " << getName() << endl << "----" << endl;
        }
};

int main() {
    Student s("Alice", 20, "Computer Science", 10423060, 4);

    s.display();

    return 0;
}