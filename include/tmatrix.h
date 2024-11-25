// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero and less than max-vec size! (10^8)");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
            return *this;
        if (sz != v.sz)
        {
            T* tmp = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = tmp;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        std::swap(pMem, v.pMem);
        return *this;
    }
    size_t size() const noexcept { return sz; }
    // индексация
    T& operator[](size_t ind)
    {
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw "Out of range";
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw "Out of range";
        return pMem[ind];
    }
    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
            return false;
        for (int i = 0; i < sz; i++)
            if (operator[](i) != v[i])
                return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (operator==(v))
            return false;
        return true;
    }
    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] += val;
        return tmp;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] -= val;
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] *= val;
        return tmp;
    }
    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.size())
            throw "Incorrect size";
        TDynamicVector<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] += v[i];
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.size())
            throw "Incorrect size";
        TDynamicVector<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] -= v[i];
        return tmp;
    }
    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw "Incorrect size";
        T tmp = 0;
        for (int i = 0; i < sz; i++)
            tmp += pMem[i] * v[i];
        return tmp;
    }
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz == 0 || sz > MAX_MATRIX_SIZE)
            throw "Incorrect length!";
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    TDynamicMatrix(const TDynamicMatrix& m) : TDynamicVector<TDynamicVector<T>>(m.sz)
    {
        for (int i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(m.pMem[i]);
    }
    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    using TDynamicVector<TDynamicVector<T>>::operator=;
    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }
    int size()
    {
        return sz;
    }
    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] *= val;
        return tmp;
    }
    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz)
            throw "Incorrect size!";
        TDynamicVector<T> tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp[i] = pMem[i] * v;
        return tmp;
    }
    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "Incorrect size";
        TDynamicMatrix<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] = tmp[i] + m[i];
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "Incorrect size";
        TDynamicMatrix<T> tmp(*this);
        for (int i = 0; i < sz; i++)
            tmp[i] = tmp[i] - m[i];
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw "Incorrect size";
        TDynamicMatrix<T> tmp(sz);
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                for (int k = 0; k < sz; k++)
                    tmp[i][j] += pMem[i][k] * m[k][j];
        return tmp;
    }
    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << endl;
        return ostr;
    }
};

#endif