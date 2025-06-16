#pragma once
#include <iostream>
using namespace std;

class Course {
    private:
        int courseCode;
        string courseName;
    public:
        Course(const int& code, const string& name): courseCode(code), courseName(name) {}
        void describe() {
            cout << "Course code: " << courseCode << " - ";
            cout << "Course name: " << courseName << endl;
        }
};

class Student {
    private:
        string name;
        int studentID;
        Course* course;
    public:
        Student(const string& name, const int& studentID, const int& courseCode, const string courseName):
            name(name), studentID(studentID) {
                course = new Course(courseCode, courseName);
            }
        
        void describe() {
            cout << "Student name: " << name << " - ";
            cout << "Student ID: " << studentID << endl;
            course->describe();
        }

        ~Student() {delete course;}
};