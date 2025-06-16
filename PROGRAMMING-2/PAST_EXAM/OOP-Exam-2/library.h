#pragma once
#include <iostream>
using namespace std;

class Media {
    protected:
        float price;
    public:
        Media(): price(0.0) {}
        Media(const float& price): price(price) {}
        virtual void describe() const {}
};

class Book: public Media {
    protected:
        string name;
    public:
        Book(): name(""), Media() {}
        Book(const string& name, const float& price):
            name(name), Media(price) {}
        void describe() const override {
            cout << "name: " << name << " ;price: " << price << endl;
        }
};

class CD: public Media {
    protected:
        unsigned id;
    public:
        CD(): id(0), Media() {}
        CD(const unsigned& id, const float& price):
            id(id), Media(price) {}
        void describe() const override {
            cout << "ID: " << id << " ;price: " << price << endl;
        }
};

class Library {
    private:
        string name;
        unsigned media_num;
        Media** media_list;
    public:
        Library(): name(""), media_num(0), media_list(nullptr) {}
        Library(const string& name, const unsigned& num = 0): name(name) {
            media_num = (num > 0) ? num : 0;
            media_list = (media_num > 0) ? new Media*[media_num] : nullptr;
        }

        void addMedia(Media* media) {
            if (media == nullptr) return;

            // Allocate new array of size media_num + 1
            Media** new_list = new Media*[media_num + 1];

            // Copy existing pointers
            for (unsigned i = 0; i < media_num; i++) {
                new_list[i] = media_list[i];
            }

            // Add new media
            new_list[media_num] = media;

            // Free old list
            delete[] media_list;

            // Update pointer and counter
            media_list = new_list;
            media_num++;
        }

        void describe() const {
            if (name != "") cout << "Lib Name: " << name << endl;
            if (media_list != nullptr && media_num > 0) {
                for (unsigned i = 0; i < media_num; i++) {
                    media_list[i]->describe();
                }
            }
        }

        ~Library() {
            delete[] media_list;
        }
};