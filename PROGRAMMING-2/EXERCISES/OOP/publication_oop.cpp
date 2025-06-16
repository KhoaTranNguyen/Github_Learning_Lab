#include <iostream>
#include <string>

using namespace std;

class Publication {
    protected:
        string publisher;
        string date;

    public:
        // Default constructor
        // is a constructor that takes no arguments (or has all arguments with default values).
        // It is used to initialize an object with default values.
        // If no constructor is explicitly defined, the compiler provides a default constructor automatically.
        Publication(): publisher("Unknown"), date("01-01-1200") {}

        // Parameterized constructor
        // takes one or more arguments to initialize an object with specific values.
        // It allows you to customize the initialization of an object.
        Publication(const string& pub = "Unknown", const string& dt = "Unknown")
            : publisher(pub), date(dt) {}
        // allows you to specify values for publisher and date.
        // If no value is provided for dt, it defaults to an empty string ("").
};

class Book: public Publication {
    protected:
        string ISBN;
        string author;
};

class Magazine: public Publication {
    protected:
        string circulation;
        string issuesOfYear;
};