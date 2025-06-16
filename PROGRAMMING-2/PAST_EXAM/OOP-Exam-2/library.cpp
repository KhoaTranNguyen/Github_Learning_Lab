#include "library.h"

int main() {
    Book book1("C++", 20.0);
    book1.describe();

    CD cd1(12345, 5.52);
    cd1.describe();

    cout << "\nLibrary Content" << endl;
    Book book2("C#", 21.0);
    Library library("Lib1");
    library.addMedia(&book1);
    library.addMedia(new Book("C++", 20.0));
    library.addMedia(&cd1);
    library.describe();

    return 0;
}