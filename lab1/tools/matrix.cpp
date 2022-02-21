#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "../include/matrix.h"

using namespace std;

/*
template<typename T>
class Matrix;

template<typename T>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
*/

template <typename T>
Matrix<T>::Matrix(size_t n_row, size_t m_column): n(n_row), m(m_column)
{
    a = (T**)malloc(n*sizeof(T*));

    for(size_t i = 0; i < n; ++i)
        a[i] = (T*)malloc(m*sizeof(T));

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            a[i][j] = 0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& clonner) : n(clonner.n), m(clonner.m)
{
    a = (T**)malloc(n*sizeof(T*));

    for(size_t i = 0; i < n; ++i)
        a[i] = (T*)malloc(m*sizeof(T));

    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < m; ++j)
            a[i][j] = clonner.a[i][j];
}

template<typename T>
Matrix<T>::~Matrix()
{
    for(size_t i = 0; i < n; ++i)
        free(a[i]);
    free(a);
}

template<typename T>
T Matrix<T>::get(size_t i, size_t j)
{
    if(/*i < 0 || */i >= n)
        throw printOutOfBound("i", i);
    if(/*j < 0 || */j >= m)
        throw printOutOfBound("j", j);
    return a[i][j];
}

template<typename T>
void Matrix<T>::set(T value, size_t i, size_t j)
{
    if(/*i < 0 || */i >= n)
        throw printOutOfBound("i", i);
    if(/*j < 0 || */j >= m)
        throw printOutOfBound("j", j);
    a[i][j] = value;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& one, const Matrix& two)
{
    if(one.m != two.n)
        throw "Matrix is not multiplable (one.m_column = " + to_string(one.m) + ", two.n_row = " + to_string(two.n) + "). ";

    /*n1xm1 * n2xm2 -> n1xm2*/
    Matrix<T> res(one.n, two.m);

    for(size_t res_i = 0; res_i < res.n; ++res_i)
        for(size_t res_j = 0; res_j < res.m; ++res_j)
        {
            T buff = 0;
            for(size_t other_i = 0; other_i < one.m; ++other_i)
                buff += one.a[res_i][other_i] * two.a[other_i][res_j];
            res.a[res_i][res_j] = buff;
        }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& other) const
{
    return Matrix<T>::multiply(*this, other);
}

template<typename T>
Matrix<T> Matrix<T>::add(const Matrix& one, const Matrix& two)
{
    if(!(one.n == two.n && one.m == two.m))
        throw "Matrix is not addeble. Its size different. ";

    /*n1xm1 * n2xm2 -> n1xm2*/
    Matrix<T> res(one.n, two.m);

    for(size_t i = 0; i < res.n; ++i)
        for(size_t j = 0; j < res.m; ++j)
            res.a[i][j] = one.a[i][j] + two.a[i][j];
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::add(const Matrix& other) const
{
    return Matrix<T>::add(*this, other);
}

template<typename T>
string Matrix<T>::toString()
{
    ostringstream res;
    for(size_t i = 0; i < n; ++i)
    {
        if(i == 0)
            res << "";
        for(size_t j = 0; j < m; ++j)
        {
            res << setw(5) << a[i][j];
            if(i == n-1)
            {
                if(j != m-1)
                    res << ", ";
            }
            else
                res << ", ";
        }
        if(i == n-1)
            res << "";
        else
            res << "\n";
    }
    return res.str();
}

template<typename T>
string Matrix<T>::str()
{
    return toString();
}

/*template<class T>
ostream& operator<< (ostream &out, const Matrix<T> &ma)
{
    out << ma.toString();
    return out;
}*/

template<typename T>
string Matrix<T>::printOutOfBound(string ij, size_t ij_val)
{
    return "Out of bounds: n_row = " + to_string(n) + ", m_column = " + to_string(m) + ", and " + ij + " = " + to_string(ij_val) + ". ";
}

// https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function

template class Matrix<double>;
template class Matrix<int>;