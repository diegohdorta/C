/* Copyright (c) 2019 NXP Semiconductors
 * Diego Dorta <diego.dorta@nxp.com>
 * SPDX-License-Identifier: GLP3
 */
#ifndef CALC_MATRIX_H
#define CALC_MATRIX_H

#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

template <class T>
class Matrix
{
    public:
        Matrix<T>();
        
        Matrix<T>(int height, int width);
        Matrix<T>(std::vector<std::vector<T> > const &array);
        
        Matrix<T> add(T const &value);
        Matrix<T> add(Matrix<T> const &m) const;
        
        Matrix<T> subtract(T const &value);
        Matrix<T> subtract(Matrix<T> const &m) const;
        
        Matrix<T> multiply(T const &value);
        Matrix<T> multiply(Matrix<T> const &m) const;        
        
        Matrix<T> dot(Matrix<T> const &m) const;
        Matrix<T> transpose() const;

        Matrix<T> applyFunction(T (*function)(T)) const;
        Matrix<T> subMatrix(int startH, int startW, int h, int w) const;


        int getHeight();
        int getWidth();

        void fill(T const &value);
        void put(int h, int w, T const &value);
        T get(int h, int w) const;


        void print(std::ostream &flux) const;

        bool operator==(Matrix<T> const &m);
        bool operator!=(Matrix<T> const &m);
        void operator+=(Matrix<T> const &m);
        void operator-=(Matrix<T> const &m);
        void operator*=(Matrix<T> const &m);
        void operator+=(T const &m);
        void operator-=(T const &m);
        void operator*=(T const &m);
        T& operator()(int y, int x);


    private:
        std::vector<std::vector<T> > array;
        int height;
        int width;
};

/* Include functions */
#include "calc-matrix.cpp"

#endif /* CALC_MATRIX_H defined */
