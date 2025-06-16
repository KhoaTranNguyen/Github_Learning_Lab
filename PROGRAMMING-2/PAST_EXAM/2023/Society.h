#pragma once
#include <iostream>
#include <algorithm>

using namespace std;

#define null "unknown"

class Member {
    public:
        string name;
        int year_of_birth;
        Member(): name(null), year_of_birth(0) {}
        Member(const string& name, const int& year_of_birth): name(name), year_of_birth(year_of_birth) {}
        
        virtual void describe() {}
};

class Participant: public Member {
    private:
        string field;
    public:
        Participant(): Member(), field(null) {}
        Participant(const string& name, const int& year_of_birth, const string& field):
            Member(name, year_of_birth), field(field) {}

        void describe() override {
            cout << "Participants - Name: " << name << " - yearOfBirth: " << year_of_birth << " - Field: " << field << endl;
        }
};

class Mentor: public Member {
    private:
        string subject;
    public:
        Mentor(): Member(), subject(null) {}
        Mentor(const string& name, const int& year_of_birth, const string& subject):
            Member(name, year_of_birth), subject(subject) {}
            
        void describe() override {
            cout << "Mentor - Name: " << name << " - yearOfBirth: " << year_of_birth << " - Subject: " << subject << endl;
        }
};

class Coordinator: public Member {
    private:
        string division;
    public:
        Coordinator(): Member(),division(null) {}
        Coordinator(const string& name, const int& year_of_birth, const string& division):
            Member(name, year_of_birth), division(division) {}
            
        void describe() override {
            cout << "Coordinator - Name: " << name << " - yearOfBirth: " << year_of_birth << " - Division: " << division << endl;
        }
};

class Society {
    private:
        string name;
        int num_members;
        Member** list_of_member;
    public:
        Society(): name(null), num_members(0), list_of_member(nullptr) {}
        Society(const string& name, int num = 0): name(name) {
            num_members = (num > 0) ? num : 0;
            list_of_member = (num > 0) ? new Member*[num] : nullptr;
        }

        void describe() const {
            cout << "Society Name: " << name << endl;

            if (list_of_member != nullptr && num_members != 0) {
                for (int i = 0; i < num_members; i++) {
                    list_of_member[i]->describe();
                }
            }
        }

        void addMember(Member* member) {
            if (member != nullptr) {
                if (num_members == 0) {
                    list_of_member = new Member*[num_members + 1];
                }
                list_of_member[num_members++] = member;
            }
        }

        int countCoordinator() const {
            if (list_of_member != nullptr && num_members != 0) {
                int num_coordinators = 0;
                for (int i = 0; i < num_members; i++) {
                    if (dynamic_cast<Coordinator*>(list_of_member[i]) != nullptr) {
                        num_coordinators += 1;
                    }
                }
                return num_coordinators;
            }
            return 0;
        }

        void sortBirthYear() {
            if (list_of_member != nullptr && num_members != 0) {
                sort(list_of_member, list_of_member + num_members, [](Member* a, Member* b) {
                    return a->year_of_birth < b->year_of_birth;
                });
            }
        }

        int aveMentorYearOfBirth() const {
            if (list_of_member != nullptr && num_members != 0) {
                int num_mentor = 0;
                int year_mentor = 0;
                for (int i = 0; i < num_members; i++) {
                    if (dynamic_cast<Mentor*>(list_of_member[i]) != nullptr) {
                        num_mentor += 1;
                        year_mentor += list_of_member[i]->year_of_birth;
                    }
                }
                return year_mentor / num_mentor;
            }
            return 0;
        }
};
