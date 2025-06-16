#include <iostream>
#include "LinkedList.h"

int main() {
    LinkedList<int> moi(3);
    moi.print();
    moi.append(3);
    moi.print();
    moi.prepend(3);
    moi.print();
    moi.insert(2, 3);
    moi.print();
    moi.find(5);
    moi.get(3);
    moi.replace(0, 6);
    moi.print();
    moi.isEmpty();
    moi.remove(5);
    moi.print();
    moi.clear();
    moi.isEmpty();
}