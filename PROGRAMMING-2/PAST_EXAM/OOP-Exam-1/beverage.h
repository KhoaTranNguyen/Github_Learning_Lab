#include <iostream>

using namespace std;

class Beverage {
    private:
        float price;
        float topping_price;
        float condiment_price;
    public:
        Beverage(): price(0), topping_price(0), condiment_price(0) {}
        Beverage(float price, float topping_price, float condiment_price):
            price(price), topping_price(topping_price), condiment_price(condiment_price) {}
        Beverage(const Beverage& other) {
            price = other.price;
            topping_price = other.topping_price;
            condiment_price = other.condiment_price;
        }

        Beverage operator+(const Beverage& other) const {
            return Beverage(price + other.price, topping_price + other.topping_price, condiment_price + other.condiment_price);
        }

        bool operator==(const Beverage& other) const {
            return (price == other.price && topping_price == other.topping_price && condiment_price == other.condiment_price);
        }

        void describe() {
            cout << "price: " << price << " topping price: " << topping_price << " condiment price: " << condiment_price << endl;
        }
};