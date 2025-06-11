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
        string GetName() const { return name; }
        int GetAge() const { return age; }

        // Setter
        void SetName(const string& name) {this->name = name;}
        void SetAge(const int year) {this->age = year;}

        // Public method
        virtual void Hello() const {cout<<"Person: Hello! I'm "<<name<<".\n";}
};
    
class Student : public Person {
    public:
        Student(const string& StudentName, const int StudentAge)
        : Person(StudentName, StudentAge) {}

        // Public method
        void GoToClasses() {cout<<"Student: I'm going to class.\n";}
        void ShowAge() {cout<<"Student: My age is: "<<GetAge()<<" years old.\n";}
        void Hello() const override {
            cout << "Student: Hello! I'm "<<GetName()<<".\n";
        }
};

class Teacher : public Person {
    private:
        string subject;
    public:
        Teacher() : subject("Unknown") {}
        Teacher(const string& TeacherName, const int TeacherAge, const string& Teachersubject)
        : Person(TeacherName, TeacherAge), subject(Teachersubject) {}

        // Getter
        string GetSubject() const { return subject; }

        // Setter
        void SetSubject(const string& subject) {this->subject = subject;}

        // Public method
        void Hello() const override {
            cout << "Teacher: Hi! I'm Proffessor "<<GetName()<<".\n";
        }
        void Explain() {cout<<"Teacher: Explanation on "<< subject << " begins now.\n";}
};

int main() {
    Person p("Person", 10);
    p.Hello();

    Student s("Nick", 21);
    s.Hello();

    Teacher t("Terry", 30, "CS");
    t.Hello();
    t.Explain();
    return 0;
}
