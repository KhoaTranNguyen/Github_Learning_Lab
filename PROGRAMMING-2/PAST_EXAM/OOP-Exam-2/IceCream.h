#pragma once
#include <iostream>

using namespace std;

class IceCream {
    private:
        float ice_price, topping_price, flavor_price;
    public:
        IceCream(): ice_price(0.0), topping_price(0.0), flavor_price(0.0) {}
        IceCream(const float& ice_price, const float& topping_price, const float& flavor_price):
            ice_price(ice_price), topping_price(topping_price), flavor_price(flavor_price) {}
        IceCream(const IceCream& other) {
            ice_price = other.ice_price;
            topping_price = other.topping_price;
            flavor_price = other.flavor_price;
        }

        IceCream operator-(const IceCream& other) const {
            return IceCream(
                ice_price - other.ice_price,
                topping_price - other.topping_price,
                flavor_price - other.flavor_price
            );
        }

        bool operator<=(const IceCream& other) const {
            return (ice_price <= other.ice_price && topping_price <= other.topping_price && flavor_price <= other.flavor_price);
        }

        void describe() const {
            cout << "icc_price: " << ice_price << " topping_price: " << topping_price << " flavor_price: " << flavor_price << endl;
        }
};