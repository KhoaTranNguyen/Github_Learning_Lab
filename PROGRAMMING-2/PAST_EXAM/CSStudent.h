#include <iostream>
using namespace std;

#define unknown "None"

class CSStudent {
    private:
        unsigned student_id;
        string student_name;
        string student_address;
        string student_scholarship;
    public:
        CSStudent():
            student_id(0), student_name(unknown), student_address(unknown), student_scholarship(unknown)   {}
        CSStudent(unsigned id, string name):
            student_id(id), student_name(name), student_address(unknown), student_scholarship(unknown)     {}
        CSStudent(unsigned id, string name, string address, string scholarship):
            student_id(id), student_name(name), student_address(address), student_scholarship(scholarship) {}
        
        // Setter
        void set_id(const unsigned& id)                      {student_id = id;}
        void set_name(const string& name)                    {student_name = name;}
        void set_address(const string& address)              {student_address = address;}
        void set_scholarship(const string& scholarship)      {student_scholarship = scholarship;}

        // Getter
        const unsigned id()                                  {return student_id;}
        const string name()                                  {return student_name;}
        const string address()                               {return student_address;}
        const string scholarship()                           {return student_scholarship;}

        // Type in
        void type_in() {
            cout << "Student information:"                    << endl;
            cout << " - Name: "; cin >> student_name;
            cout << " - ID: "  ; cin >> student_id;
            cout << " - Address: "; cin >> student_address;
            cout << " - Scholarship: "; cin >> student_scholarship;

            bool failed = student_name == unknown && student_id == 0 && student_address == unknown && student_scholarship == unknown;
            bool interrupted = student_name == unknown | student_id == 0 | student_address == unknown | student_scholarship == unknown;

            if (interrupted || cin.fail()) cout << "\n==========  I N T E R R U P T E D  ==========" << endl;
            else cout << "========== " << (failed ? "F A I L E D" : "S U C C E S S") << " ==========" << endl;
        }

        // Print
        void detail() {
            cout << "Student information:"                    << endl;
            cout << " - Name: " << student_name               << endl;
            cout << " - ID: "   << student_id                 << endl;
            cout << " - Address: " << student_address         << endl;
            cout << " - Scholarship: " << student_scholarship << endl;
            cout << "---------------------------------------" << endl;
        }
};