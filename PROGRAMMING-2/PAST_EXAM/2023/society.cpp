#include <iostream>
#include "Society.h"

using namespace std;

int main() {
    Participant participant("Alice", 1995, "Art");
    participant.describe();

    Mentor mentor1("Bob", 1980, "Math");
    mentor1.describe();

    Mentor mentor2("Carol", 1970, "Science");
    mentor2.describe();

    Coordinator coordinator1("David", 1985, "Events");
    Coordinator coordinator2("Thomas", 1980, "Logistics");

    Society society("society1");
    society.addMember(&participant);
    society.addMember(&mentor1);
    society.addMember(&mentor2);
    society.addMember(&coordinator1);
    society.addMember(&coordinator2);

    society.describe();

    int numberOfCoordinators = society.countCoordinator();
    cout << "numberOfCoordinators: " << numberOfCoordinators << endl;

    society.sortBirthYear();
    society.describe();

    double aveMentorYearOfBirth = society.aveMentorYearOfBirth();
    cout << "Average year of birth(Mentors): " << aveMentorYearOfBirth << endl;
}