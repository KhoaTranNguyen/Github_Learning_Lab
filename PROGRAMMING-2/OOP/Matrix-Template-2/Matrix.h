#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>
#include <cmath>

template<typename T>
class Matrix {
private:
    int mNumEdges;
    T** mData;
    std::string mName;

    void allocate(int edges) {
        mData = new T*[edges];
        for (int i = 0; i < edges; ++i) {
            mData[i] = new T[edges]{};
            for (int j = 0; j < edges; ++j) mData[i][j] = 0; //Generate Zero Matrix
        }
    }

    void deallocate() {
        if (mData) {
            for (int i = 0; i < mNumEdges; ++i)
                delete[] mData[i];
            delete[] mData;
            mData = nullptr;
        }
    }


public:
    // Constructor with size and optional name
    Matrix(int edge = 0, const std::string& name = "")
        : mNumEdges(edge), mName(name), mData(nullptr) {
        if (mNumEdges > 0) {
            allocate(mNumEdges);
        }
        if (!mName.empty())
            std::cout << "Constructed Matrix " << mName << " (" << mNumEdges << "x" << mNumEdges << ")\n";
    }

    // Constructor from initializer_list, unnamed
    Matrix(std::initializer_list<std::initializer_list<T>> initList)
        : mNumEdges(initList.size()), mName("<unnamed>"), mData(nullptr) {
        if (initList.size() == initList.begin()->size()) {
            allocate(mNumEdges);

            int row = 0;
            for (const auto& rowList : initList) {
                if (rowList.size() != static_cast<size_t>(mNumEdges)) {
                    throw std::invalid_argument("All rows must have the same number of columns.");
                }
                std::copy(rowList.begin(), rowList.end(), mData[row]);
                ++row;
            }

            std::cout << "Constructed unnamed Matrix (" << mNumEdges << "x" << mNumEdges << ")\n";
        }
        else {
            std::cout << "Mismatch! Only accept size n*n.\n";
        }
    }

    // Constructor from initializer_list with name
    Matrix(const std::string& name, std::initializer_list<std::initializer_list<T>> initList)
        : mNumEdges(initList.size()), mName(name), mData(nullptr) {
        if (initList.size() == initList.begin()->size()) {
            allocate(mNumEdges);

            int row = 0;
            for (const auto& rowList : initList) {
                if (rowList.size() != static_cast<size_t>(mNumEdges)) {
                    throw std::invalid_argument("All rows must have the same number of columns.");
                }
                std::copy(rowList.begin(), rowList.end(), mData[row]);
                ++row;
            }

            std::cout << "Constructed unnamed Matrix (" << mNumEdges << "x" << mNumEdges << ")\n";
        }
        else {
            std::cout << "Mismatch! Only accept size n*n.\n";
        }
    }

    // Copy constructor (deep copy)
    Matrix(const Matrix<T>& other) : mNumEdges(other.mNumEdges), mData(nullptr) {
        if (mNumEdges > 0 && mNumEdges > 0) {
            allocate(mNumEdges);
            for (int i = 0; i < mNumEdges; ++i)
                for (int j = 0; j < mNumEdges; ++j)
                    mData[i][j] = other.mData[i][j];
        }
    }

    // Move constructor
    Matrix(Matrix<T>&& other) noexcept 
        : mNumEdges(other.mNumEdges), mData(other.mData) {
        other.mData = nullptr;
        other.mNumEdges = 0;
    }

    // Destructor
    ~Matrix() {
        deallocate();
    }

    // Assignment operators can be added similarly...

    // Access elements
    T& operator()(int row, int col) {
        if (row < 0 || row >= mNumEdges || col < 0 || col >= mNumEdges)
            throw std::out_of_range("Index out of range");
        return mData[row][col];
    }

    T operator()(int row, int col) const {
        if (row < 0 || row >= mNumEdges || col < 0 || col >= mNumEdges)
            throw std::out_of_range("Index out of range");
        return mData[row][col];
    }

    int sizes() const { return mNumEdges; }

    // Frobenius norm
    T frobenius() {
        T fb = 0;
        for (int row = 0; row < mNumEdges; row++) {
            for (int col = 0; col < mNumEdges; col++) {
                fb += mData[row][col]*mData[row][col];
            }
        }
        return sqrt(fb);
    }

    // Row sum nom
    T row_sum_norm() {
        T rsn = 0;
        for (int row = 0; row < mNumEdges; row++) {
            T temp = 0;
            for (int col = 0; col < mNumEdges; col++) {
                temp += abs(mData[row][col]);
            }
            if (temp > rsn) rsn = temp;
        }
        return rsn;
    }

    // Total norm
    T total_norm() {
        T total = 0;
        for (int row = 0; row < mNumEdges; row++) {
            for (int col = 0; col < mNumEdges; col++) {
                if (abs(mData[row][col]) > total) total = abs(mData[row][col]);
            }
        }
        return mNumEdges*total;
    }

    // Print matrix for debugging
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
        for (int i = 0; i < mat.mNumEdges; ++i) {
            for (int j = 0; j < mat.mNumEdges; ++j) {
                os << mat(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }
};

#endif // MATRIX_H
