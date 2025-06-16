#include "Ward.h"

int main() {
    Student student("studentA", 2010, "7");
    student.describe();

    Teacher teacher1("teacherA", 1969, "Math");
    teacher1.describe();

    Doctor doctor1("doctorA", 1945, "Endocrinologists");
    doctor1.describe();

    Teacher teacher2("teacherB", 1995, "History");
    Doctor doctor2("doctor2", 1975, "Cardiologists");

    Ward ward("Ward1");
    ward.addPerson(&student);
    ward.addPerson(&teacher1);
    ward.addPerson(&teacher2);
    ward.addPerson(&doctor1);
    ward.addPerson(&doctor2);
    ward.describe();

    int numberOfDoctors = ward.countDoctor();
    cout << "number of doctors: " << numberOfDoctors << endl;

    ward.sortAge();
    ward.describe();

    int aveTeacherYearOfBirth = ward.aveTeacherYearOfBirth();
    cout << "average year of birth (teachers): " << aveTeacherYearOfBirth << endl;
    
    return 0;
}