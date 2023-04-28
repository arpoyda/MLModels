#pragma once
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <format>
#include "fatalerror.h"

// invers matrix (code example is right!, algorithm is broken...!): https://www.researchgate.net/publication/220337322_An_Efficient_and_Simple_Algorithm_for_Matrix_Inversion/link/58d77e9daca2727e5ef29dc8/download

class LinMatrix {
	float** matrix;
	int n_row;
	int n_col;
	struct Shape
	{
		int n_row;
		int n_col;
	public:
		int operator[](int idx) const {
			if (idx == 0)
				return n_row;
			else if (idx == 1)
				return n_col;
			else
				fatal_error("Shape hase only 2 values for 2 dims!"); // TODO: Add smth
		}
		bool operator==(const Shape& other) const {
			return ((n_row == other.n_row) && (n_col == other.n_col));
		}
	};
	Shape shape;
	//float det = 0; // Implement!

public:
	LinMatrix(int n_row_, int n_col_);
	LinMatrix(int n_row_, int n_col_, const float* arr);
	LinMatrix(int n_row_, int n_col_, float* const * arr);
	LinMatrix(int n_row_, int n_col_, float val);
	LinMatrix(const LinMatrix& other);
	LinMatrix(LinMatrix&& other);
	~LinMatrix();

	Shape getShape() const { // CHANGE to return reference!!
		return shape;
	}

	//float getDet() const { // Implement!
	//	return det;
	//}

	LinMatrix getRow(int idx_row) const;
	LinMatrix getCol(int idx_col) const;

	LinMatrix setRow(int idx_row, const LinMatrix& mat) const;
	LinMatrix setCol(int idx_row, const LinMatrix& mat) const;
	
	LinMatrix matmul(const LinMatrix& other) const;
	static LinMatrix matmul(const LinMatrix& mat1, const LinMatrix& mat2);

	LinMatrix hadamard(const LinMatrix& other) const;
	static LinMatrix hadamard(const LinMatrix& mat1, const LinMatrix& mat2);

	LinMatrix flatten(int axis) const;
	static LinMatrix flatten(int axis, const LinMatrix& mat);

	LinMatrix T() const;
	static LinMatrix T(const LinMatrix& mat);

	LinMatrix inverse() const;
	static LinMatrix inverse(const LinMatrix& mat);

	LinMatrix daig() const;
	static LinMatrix diag(const LinMatrix& mat);

	LinMatrix eigValues() const;
	static LinMatrix eigValues(const LinMatrix& mat);

	LinMatrix eigVectorsLeft() const;
	static LinMatrix eigVectorsLeft(const LinMatrix& mat);

	void print() const; // Will be modified later!
	
	/*float& operator()(const int idx_row, const int idx_col) {
		if (idx_row > n_row)
			fatal_error("Row idx > n_row!");
		if (idx_col > n_col)
			fatal_error("Col idx > n_col!");
		return matrix[idx_row][idx_col];
	}

	const float& operator()(const int idx_row, const int idx_col) const {
		if (idx_row > n_row)
			fatal_error("Row idx > n_row!");
		if (idx_col > n_col)
			fatal_error("Col idx > n_col!");
		return matrix[idx_row][idx_col];
	}*/

	float* operator[](const int idx) { // PROBLEM with checking limits!
		return matrix[idx];
	}

	const float* operator[](const int idx) const {
		return matrix[idx];
	}

	LinMatrix operator+(const LinMatrix& other) const;

	LinMatrix operator+(const int val) const;

	LinMatrix& operator+=(const LinMatrix& other);

	LinMatrix& operator+=(const float val);

	LinMatrix operator-(const LinMatrix& other) const;

	LinMatrix operator-(const int val) const;

	LinMatrix& operator-=(const LinMatrix& other);

	LinMatrix& operator-=(const float val);

	LinMatrix operator*(const float val) const;

	LinMatrix& operator*=(const float val);

	LinMatrix operator/(const float val) const;

	LinMatrix& operator/=(const float val);

	LinMatrix& operator=(const LinMatrix& other);
};