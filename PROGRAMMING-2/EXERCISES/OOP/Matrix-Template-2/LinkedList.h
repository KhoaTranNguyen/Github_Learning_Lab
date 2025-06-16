#pragma once

#include <iostream>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node() : data(T{}), next(nullptr) {}
    Node(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    void allocate(int size) {
        T temp;
        for (int i = 0; i < size; i++) {
            cout << "Enter " << i + 1 << "/" << size << " element: ";
            cin >> temp;

            Node<T>* newNode = new Node<T>(temp);
            if (i == 0) head = tail = newNode;
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    void deallocate() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(int s) : head(nullptr), tail(nullptr), size(0) {
        if (s > 0) {
            size = s;
            allocate(s);
        } else {
            cout << "Invalid size.\n";
        }
    }

    ~LinkedList() {
        clear();
    }

    void print() const {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node<T>* temp = head;
        while (temp) {
            cout << temp->data;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }

    void append(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        ++size;
        cout << "Appended " << val << " at the end.\n";
    }

    void prepend(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }

        ++size;
        cout << "Prepended " << val << " at the beginning.\n";
    }

    void insert(const int& idx, const T& val) {
        if (idx < 0 || idx > size) {
            cout << "Invalid index.\n";
            return;
        }

        if (idx == 0) {
            prepend(val);
        } else if (idx == size) {
            append(val);
        } else {
            Node<T>* current = head;
            for (int i = 0; i < idx - 1; ++i) {
                current = current->next;
            }

            Node<T>* newNode = new Node<T>(val);
            newNode->next = current->next;
            current->next = newNode;

            ++size;
            cout << "Inserted " << val << " at index " << idx << endl;
        }
    }

    void remove(const int& idx) {
        if (idx < 0 || idx >= size) {
            cout << "Invalid index.\n";
            return;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;

        for (int i = 0; i < idx; ++i) {
            prev = current;
            current = current->next;
        }

        T del_data = current->data;

        if (prev == nullptr) {
            head = current->next;
            if (current == tail) tail = nullptr;
        } else {
            prev->next = current->next;
            if (current == tail) tail = prev;
        }

        delete current;
        --size;

        cout << "Deleted " << del_data << " at index " << idx << "\n";
    }

    Node<T>* find(const T& val) {
        int idx = 0;
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == val) {
                cout << "Found " << val << " at index " << idx << endl;
                return temp;
            }
            temp = temp->next;
            ++idx;
        }
        cout << "Value " << val << " not found.\n";
        return nullptr;
    }

    Node<T>* get(const int& idx) {
        if (idx < 0 || idx >= size) {
            cout << "Invalid index.\n";
            return nullptr;
        }

        Node<T>* temp = head;
        for (int i = 0; i < idx; ++i) {
            temp = temp->next;
        }

        cout << "Got value " << temp->data << " at index " << idx << endl;
        return temp;
    }

    Node<T>* replace(const int& idx, const T& val) {
        if (idx < 0 || idx >= size) {
            cout << "Invalid index.\n";
            return nullptr;
        }

        Node<T>* temp = head;
        for (int i = 0; i < idx; ++i) {
            temp = temp->next;
        }

        cout << "Replaced " << temp->data << " with " << val << " at index " << idx << endl;
        temp->data = val;

        return temp;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        deallocate();
        head = tail = nullptr;
        size = 0;
        cout << "Cleared all elements.\n";
    }
};