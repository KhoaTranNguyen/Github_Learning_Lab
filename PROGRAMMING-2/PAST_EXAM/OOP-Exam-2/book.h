#include <iostream>

using namespace std;

class Date {
    private:
        int pub_date;
        int pub_month;
        int pub_year;
    public:
        Date (const int& pub_date, const int& pub_month, const int& pub_year):
            pub_date(pub_date), pub_month(pub_month), pub_year(pub_year) {}

        void describe() {
            cout << "Day: " << pub_date << " - month: " << pub_month << " - year: " << pub_year << endl;
        }
};

class Book {
    private:
        string name;
        string author;
        Date* date;
    public:
        Book (const string& name, const string& author, Date* input_date): name(name), author(author) {
            date = input_date;
        }
        Book(const string& name, const string& author, const int& pub_date, const int& pub_month, const int& pub_year):
            name(name), author(author) {
                date = new Date(pub_date, pub_month, pub_year);
            }

        void describe() {
            cout << "Book name: " << name << " - Author name: " << author << endl;
            date->describe();
        }
};