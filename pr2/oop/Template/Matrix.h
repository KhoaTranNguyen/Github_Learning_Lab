#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

template<typename T>
class Matrix {
private:
    int mNumRows;
    int mNumCols;
    T** mData;
    std::string mName;

    void allocate(int rows, int cols) {
        mData = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            mData[i] = new T[cols]{};
            for (int j = 0; j < cols; ++j) mData[i][j] = 0; //Generate Zero Matrix
        }
    }

    void deallocate() {
        if (mData) {
            for (int i = 0; i < mNumRows; ++i)
                delete[] mData[i];
            delete[] mData;
            mData = nullptr;
        }
    }


public:
    // Constructor with size and optional name
    Matrix(int row = 0, int col = 0, const std::string& name = "")
        : mNumRows(row), mNumCols(col), mName(name), mData(nullptr) {
        if (mNumRows > 0 && mNumCols > 0) {
            allocate(mNumRows, mNumCols);
        }
        if (!mName.empty())
            std::cout << "Constructed Matrix " << mName << " (" << mNumRows << "x" << mNumCols << ")\n";
    }

    // Constructor from initializer_list, unnamed
    Matrix(std::initializer_list<std::initializer_list<T>> initList)
        : mNumRows(initList.size()), mNumCols(initList.begin()->size()), mName("<unnamed>"), mData(nullptr) {
        allocate(mNumRows, mNumCols);

        int row = 0;
        for (const auto& rowList : initList) {
            if (rowList.size() != static_cast<size_t>(mNumCols)) {
                throw std::invalid_argument("All rows must have the same number of columns.");
            }
            std::copy(rowList.begin(), rowList.end(), mData[row]);
            ++row;
        }

        std::cout << "Constructed unnamed Matrix (" << mNumRows << "x" << mNumCols << ")\n";
    }

    // Constructor from initializer_list with name
    Matrix(const std::string& name, std::initializer_list<std::initializer_list<T>> initList)
        : mNumRows(initList.size()), mNumCols(initList.begin()->size()), mName(name), mData(nullptr) {
        allocate(mNumRows, mNumCols);

        int row = 0;
        for (const auto& rowList : initList) {
            if (rowList.size() != static_cast<size_t>(mNumCols)) {
                throw std::invalid_argument("All rows must have the same number of columns.");
            }
            std::copy(rowList.begin(), rowList.end(), mData[row]);
            ++row;
        }

        std::cout << "Constructed Matrix " << mName << " (" << mNumRows << "x" << mNumCols << ")\n";
    }

    // Copy constructor (deep copy)
    Matrix(const Matrix<T>& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols), mData(nullptr) {
        if (mNumRows > 0 && mNumCols > 0) {
            allocate(mNumRows, mNumCols);
            for (int i = 0; i < mNumRows; ++i)
                for (int j = 0; j < mNumCols; ++j)
                    mData[i][j] = other.mData[i][j];
        }
    }

    // Move constructor
    Matrix(Matrix<T>&& other) noexcept 
        : mNumRows(other.mNumRows), mNumCols(other.mNumCols), mData(other.mData) {
        other.mData = nullptr;
        other.mNumRows = 0;
        other.mNumCols = 0;
    }

    // Destructor
    ~Matrix() {
        deallocate();
    }

    // Assignment operators can be added similarly...

    // Access elements
    T& operator()(int row, int col) {
        if (row < 0 || row >= mNumRows || col < 0 || col >= mNumCols)
            throw std::out_of_range("Index out of range");
        return mData[row][col];
    }

    T operator()(int row, int col) const {
        if (row < 0 || row >= mNumRows || col < 0 || col >= mNumCols)
            throw std::out_of_range("Index out of range");
        return mData[row][col];
    }

    int rows() const { return mNumRows; }
    int cols() const { return mNumCols; }

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (mNumCols != other.mNumRows)
            throw std::runtime_error("\nError: Matrix dimension mismatch for multiplication.");

        Matrix<T> result(mNumRows, other.mNumCols);

        for (int i = 0; i < mNumRows; ++i) {
            for (int j = 0; j < other.mNumCols; ++j) {
                T sum = T{};
                for (int k = 0; k < mNumCols; ++k) {
                    sum += mData[i][k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    // Print matrix for debugging
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
        for (int i = 0; i < mat.mNumRows; ++i) {
            for (int j = 0; j < mat.mNumCols; ++j) {
                os << mat(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }
};

#endif // MATRIX_H
