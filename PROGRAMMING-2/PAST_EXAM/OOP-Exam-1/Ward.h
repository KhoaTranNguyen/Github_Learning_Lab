#pragma once
#include <iostream>
#include <algorithm>

#define null "null"

using namespace std;

class Person {
    protected:
        string name;
        int year_of_birth;
    public:
        Person(): name(null), year_of_birth(0) {}
        Person(const string& name, const int& year_of_birth):
            name(name), year_of_birth(year_of_birth) {}
        
        virtual void describe() = 0;

        friend class Ward;
};

class Student: public Person {
    private:
        string grade;
    public:
        Student(const string& name, const int& year_of_birth, const string& grade):
            Person(name, year_of_birth), grade(grade) {}
        
        void describe() override {
            cout << "Name: " << name << " - " << "yearOfBirth: " << year_of_birth << " - " << "Grade: " << grade << endl;
        }
};

class Teacher: public Person {
    private:
        string subject;
    public:
        Teacher(const string& name, const int& year_of_birth, const string& subject):
            Person(name, year_of_birth), subject(subject) {}
        
        void describe() override {
            cout << "Name: " << name << " - " << "yearOfBirth: " << year_of_birth << " - " << "Subject: " << subject << endl;
        }
};

class Doctor: public Person {
    private:
        string specialist;
    public:
        Doctor(const string& name, const int& year_of_birth, const string& specialist):
            Person(name, year_of_birth), specialist(specialist) {}
        
        void describe() override {
            cout << "Name: " << name << " - " << "yearOfBirth: " << year_of_birth << " - " << "Specialist: " << specialist << endl;
        }
};

class Ward {
    private:
        string name;
        unsigned person_num;
        Person** person_list;
    public:
        Ward(): name(null), person_num(0), person_list(nullptr) {}
        Ward(const string& name, const unsigned& num = 0): name(name) {
            person_num = (num > 0) ? num : 0;
            person_list = (person_num > 0) ? new Person*[person_num] : nullptr;
        }

        void describe() const {
            if (name != null) cout << "Ward Name: " << name << endl;
            if (person_list != nullptr && person_num > 0) {
                for (int i = 0; i < person_num; i++) {
                    person_list[i]->describe();
                }
            }
        }

        void addPerson(Person* person) {
            if (person != nullptr) {
                if (person_list == nullptr || person_num == 0) {
                    person_list = new Person*[person_num + 1];
                }
                person_list[person_num++] = person;
            }
        }

        int countDoctor() const {
            if (person_list != nullptr && person_num > 0) {
                int doctor_num = 0;
                for (int i = 0; i < person_num; i++) {
                    if (dynamic_cast<Doctor*>(person_list[i]) != nullptr) {
                        doctor_num += 1;
                    }
                }
                return doctor_num;
            }
            return 0;
        }

        void sortAge() {
            if (person_list != nullptr && person_num > 0) {
                sort(person_list, person_list + person_num, [](Person* a, Person* b){
                    return a->year_of_birth > b->year_of_birth;
                });
            }
        }

        int aveTeacherYearOfBirth() const {
            if (person_list != nullptr && person_num > 0) {
                int teacher_year = 0;
                int teacher_num = 0;
                for (int i = 0; i < person_num; i++) {
                    if (dynamic_cast<Teacher*>(person_list[i]) != nullptr) {
                        teacher_year += person_list[i]->year_of_birth;
                        teacher_num += 1;
                    }
                }
                return teacher_year / teacher_num;
            }
            return 0;
        }
};