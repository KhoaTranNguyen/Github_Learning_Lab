#pragma once
#include <iostream>
using namespace std;

class Manufacturer {
    private:
        int id;
        string location;
    public:
        Manufacturer(const int& id, const string& location):
            id(id), location(location) {}
        void describe() {
            cout << "ID: " << id << " - " << "Location: " << location << endl;
        }
};

class Device {
    private:
        string name;
        double price;
        Manufacturer *manufacturer;
    public:
        Device(const string& name, const double& price, const int& id, const string& location):
            name(name), price(price) {
                manufacturer = new Manufacturer(id, location);
            }
        void describe() {
            cout << "Name: " << name << " - " << "Price: " << price << endl;
            manufacturer->describe();
        }
        ~Device() {delete manufacturer;}
};