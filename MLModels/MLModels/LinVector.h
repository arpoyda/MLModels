#pragma once

#include <stdexcept>
#include <iterator>
#include <cmath>
#include <cassert>
#include "fatalerror.h"

class LinVector {
	float* vector;
	int size;

public:
	LinVector(int size_);
	LinVector(int size_, float* arr);
	LinVector(const LinVector& other);
	LinVector(LinVector&& other);
	~LinVector();
	int getSize() const;
	float dot(const LinVector& other) const;
	static float dot(const LinVector& vec1, const LinVector& vec2);
	float mean() const;
	float std() const;

	float& operator[](int idx) const {
		if (idx < 0)
			return vector[size + idx];
		return vector[idx];
	}

	LinVector operator+(const LinVector& other) const {
		if (size == other.size)
			fatal_error("Different size of vectors in _op_[+]");
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] + other.vector[i];
		return res;
	}

	LinVector operator+(const float val) const {
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] + val;
		return res;
	}

	LinVector operator-(const LinVector& other) const {
		if (size == other.size)
			fatal_error("Different size of vectors in _op_[-]");
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] - other.vector[i];
		return res;
	}

	LinVector operator-(const float val) const {
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] - val;
		return res;
	}

	LinVector& operator+=(const LinVector& other) {
		if (size == other.size)
			fatal_error("Different size of vectors in _op_[+=]");
		for (int i = 0; i < size; i++)
			vector[i] += other.vector[i];
		return *this;
	}

	LinVector& operator+=(const float val) {
		for (int i = 0; i < size; i++)
			vector[i] += val;
		return *this;
	}

	LinVector& operator-=(const LinVector& other) {
		if (size == other.size)
			fatal_error("Different size of vectors in _op_[-=]");
		for (int i = 0; i < size; i++)
			vector[i] -= other.vector[i];
		return *this;
	}

	LinVector& operator-=(const float val) {
		for (int i = 0; i < size; i++)
			vector[i] -= val;
		return *this;
	}

	LinVector operator*(const float val) const {
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] * val;
		return res;
	}

	LinVector& operator*=(const float val) {
		for (int i = 0; i < size; i++)
			vector[i] *= val;
		return *this;
	}

	LinVector operator/(const float val) const {
		LinVector res{ size };
		for (int i = 0; i < size; i++)
			res.vector[i] = vector[i] / val;
		return res;
	}

	LinVector& operator/=(const float val) {
		for (int i = 0; i < size; i++)
			vector[i] /= val;
		return *this;
	}



};