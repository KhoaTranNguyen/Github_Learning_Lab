#pragma once
#include <iostream>

using namespace std;

class Product {
    private:
        float price;
        float weight;
        float discount;
    public:
        Product(): price(0), weight(0), discount(0) {}
        Product(const float& price, const float& weight, const float& discount):
            price(price), weight(weight), discount(discount) {}
        Product(const Product& other) {
            price = other.price;
            weight = other.weight;
            discount = other.discount;
        }

        Product operator+(const Product& other) const {
            return Product(price + other.price, weight + other.weight, discount + other.discount);
        }

        Product& operator=(const Product& other) {
            if (this != & other) {
                price = other.price;
                weight = other.weight;
                discount = other.discount;
            }
            return *this;
        }

        bool operator==(const Product& other) const {
            //if (price == other.price && weight == other.weight && discount == other.discount) {}
            return !(price != other.price || weight != other.weight || discount != other.discount);
        }

        void describe() {
            cout << "Price: " << price << " Weight: " << weight << " Discount: " << discount << endl;
        }
};