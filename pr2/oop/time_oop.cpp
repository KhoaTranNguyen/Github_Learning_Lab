#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours;
    int minutes;
    int seconds;
public:
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    Time operator+(const Time& other) const {
        int new_hour = hours + other.hours;
        int new_min = minutes + other.minutes;
        int new_sec = seconds + other.seconds;

        return Time(
            ((new_hour + ((new_min + new_sec / 60) / 60)) % 24),
            ((new_min + new_sec / 60) % 60),
            (new_sec % 60)
        );
    }

    bool operator>(const Time& other) const {
        return (hours*3600 + minutes*60 + seconds) > (other.hours*3600 + other.minutes*60 + other.seconds);
    }

    Time operator=(const Time& other) {
        if (this != &other) {  // phòng trường hợp tự gán
            hours = other.hours;
            minutes = other.minutes;
            seconds = other.seconds;
        }
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Time& t) {
        os << t.hours << ":"
            << std::setw(2) << std::setfill('0') << t.minutes << ":"
            << std::setw(2) << std::setfill('0') << t.seconds;
        return os;
    }
};

int main() {
    Time t1(10, 45, 30);
    Time t2(5, 20, 50);

    // Test operator+
    Time t3 = t1 + t2;
    cout << "t1 + t2 = " << t3 << endl;  // Kỳ vọng: 16:06:20

    // Test operator>
    cout << "t1 > t2 ? " << (t1 > t2 ? "Yes" : "No") << endl; // Yes
    cout << "t2 > t1 ? " << (t2 > t1 ? "Yes" : "No") << endl; // No

    // Test operator=
    Time t4;
    t4 = t1;
    cout << "t4 after assignment = " << t4 << endl; // 10:45:30

    // Test operator+ với tràn giờ (vượt 24h)
    Time t5(23, 59, 59);
    Time t6(0, 0, 2);
    Time t7 = t5 + t6;
    cout << "t5 + t6 = " << t7 << endl;  // Kỳ vọng: 0:0:1

    Time khietdank;

    return 0;
}