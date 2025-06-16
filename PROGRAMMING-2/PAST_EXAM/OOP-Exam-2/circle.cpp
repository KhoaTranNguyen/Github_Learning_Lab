#include "data.h"

int main() {
    Circle circle1(5);
    Circle circle2(7);
    Data<Circle> circleData(circle1, circle2);

    Circle sumCircle = circleData.sum();
    sumCircle.describe();
}