#include "book.h"

int main() {
    Book book("C++", "Peter", 27, 6, 2022);
    book.describe();

    Date publicationDate(27, 6, 2022);
    Book book1("C++", "Peter", &publicationDate);
    book1.describe();
}