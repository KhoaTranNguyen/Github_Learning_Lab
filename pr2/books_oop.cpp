#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    string author;
    string title;
    string format;
    double price;
    int year;
    string publisher;

public:
    // Default constructor
    Book() : author("Unknown"), title("Unknown"), format("Unknown"), price(0.0), year(0), publisher("Unknown") {}

    // Parameterized constructor
    Book(const string& author, const string& title, const string& format, 
         double price, int year, const string& publisher)
        : author(author), title(title), format(format), price(price), year(year), publisher(publisher) {}

    // Getters
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getFormat() const { return format; }
    double getPrice() const { return price; }
    int getYear() const { return year; }
    string getPublisher() const { return publisher; }

    // Setters
    void setAuthor(const string& author) { this->author = author; }
    void setTitle(const string& title) { this->title = title; }
    void setFormat(const string& format) { this->format = format; }
    void setPrice(double price) { this->price = price; }
    void setYear(int year) { this->year = year; }
    void setPublisher(const string& publisher) { this->publisher = publisher; }
};

void printBookDetails(const Book& book) {
    cout << "Book Details:" << endl;
    cout << "Author: " << book.getAuthor() << endl;
    cout << "Title: " << book.getTitle() << endl;
    cout << "Format: " << book.getFormat() << endl;
    cout << "Price: $" << book.getPrice() << endl;
    cout << "Year: " << book.getYear() << endl;
    cout << "Publisher: " << book.getPublisher() << endl;
    cout << endl;
}

int main() {
    // Create a Book object using the setters
    Book book1;

    book1.setAuthor("George Orwell");
    book1.setTitle("1984");
    book1.setFormat("Paperback");
    book1.setPrice(12.99);
    book1.setYear(1949);
    book1.setPublisher("Secker & Warburg");

    // Create another Book object using the parameterized constructor
    Book book2("J.K. Rowling", "Harry Potter and the Philosopher's Stone", "Hardcover", 19.99, 1997, "Bloomsbury");

    // Display book1 & book2 details
    printBookDetails(book1);
    printBookDetails(book2);
    
    return 0;
}