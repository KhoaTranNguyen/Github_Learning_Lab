#pragma once
#include <iostream>
using namespace std;

#define null "null"

class Books {
    private:
        string author;
        string title;
        string format;
        double price;
        int year_publication;
        string publisher;
    public:
        Books():
            author(null), title(null), format(null), price(0.0), year_publication(0), publisher(null) {};
        Books(string auth, string tit, string form, double price, int year, string pub):
            author(auth), title(tit), format(form), price(price), year_publication(year), publisher(pub){};

        // Setter
        void set_auth(const string& auth) {author = auth;}
        void set_title(const string& tit) {title = tit;}
        void set_format(const string& form) {format = form;}
        void set_price(const double& price) {this->price = price;}
        void set_auth(const int& year) {year_publication = year;}
        void set_auth(const string& pub) {publisher = pub;}

        // Getter
        string get_author() const { return author; }
        string get_title() const { return title; }
        string get_format() const { return format; }
        double get_price() const { return price; }
        int get_year() const { return year_publication; }
        string get_publisher() const { return publisher; }
};