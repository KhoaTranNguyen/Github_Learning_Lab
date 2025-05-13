#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;

class Shape {
public:
    Shape() {}
    vector<pair<int, int>> vertices;
    virtual int area() = 0;
};

class Square : public Shape {
public:
    Square() {}
    int area() override {
        if (vertices.size() != 2) return 0;
        int x1 = vertices[0].first, y1 = vertices[0].second;
        int x2 = vertices[1].first, y2 = vertices[1].second;
        return abs(x2 - x1) * abs(y2 - y1);
    }
};

class Rectangle : public Shape {
public:
    Rectangle() {}
    int area() override {
        if (vertices.size() != 2) return 0;
        int x1 = vertices[0].first, y1 = vertices[0].second;
        int x2 = vertices[1].first, y2 = vertices[1].second;
        return abs(x2 - x1) * abs(y2 - y1);
    }
};

class Parallelogram: public Shape {
    public:
        Parallelogram() {}
        int area() override {
            if (vertices.size() != 3) return 0.0; // Assuming parallelogram vertices are diagonal
            int x1 = vertices[0].first, y1 = vertices[0].second;
            int x2 = vertices[1].second, y2 = vertices[1].first;
            int y3 = vertices[1].first, y4 = vertices[1].second;
            return abs(x2 - x1) * abs(y2 - y1); // Calculate area (simplified)
        }
};

class Triangle : public Shape {
public:
    Triangle() {}
    int area() override {
        if (vertices.size() != 3) return 0;
        int x1 = vertices[0].first, y1 = vertices[0].second;
        int x2 = vertices[1].first, y2 = vertices[1].second;
        int x3 = vertices[2].first, y3 = vertices[2].second;
        int a = x1 * (y2 - y3);
        int b = x2 * (y3 - y1);
        int c = x3 * (y1 - y2);
        return abs(a + b + c) / 2;
    }
};

struct ShapeData {
    string line;
    int area;
    bool operator<(const ShapeData& other) const {
        return area < other.area;
    }
};

int main() {
    fstream file("input.txt", ios::in);
    if (!file) {
        cerr << "Failed to open file\n";
        return 1;
    }

    string line;
    vector<ShapeData> shapeDataList;
    string firstLine;
    int numline = 0;

    while (getline(file, line)) {
        if (numline == 0) {
            firstLine = line; // Store the number of shapes
        } else {
            Shape* obj = nullptr;
            switch (line[0]) {
                case 't': obj = new Triangle(); break;
                case 'r': obj = new Rectangle(); break;
                case 's': obj = new Square(); break;
                case 'p': obj = new Parallelogram(); break;
                default:
                    cout << "Unknown shape: " << line[0] << endl;
                    continue;
            }

            stringstream ss(line.substr(2));
            int x, y;
            while (ss >> x >> y) {
                obj->vertices.push_back({x, y});
            }

            int shape_area = obj->area();
            shapeDataList.push_back({line, shape_area});
            delete obj;
        }
        ++numline;
    }
    file.close();

    sort(shapeDataList.begin(), shapeDataList.end());

    // Rewrite the file
    ofstream out("input.txt");
    out << firstLine << "\n";
    for (const auto& shape : shapeDataList) {
        out << shape.line << " -> " << shape.area << "\n";
    }
    out.close();

    cout << "File sorted and updated by area.\n";
    return 0;
}
