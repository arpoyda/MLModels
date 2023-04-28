#include "LinVector.h"

LinVector::LinVector(int size_) {
	size = size_;
	vector = new float[size_];
	for (size_t i = 0; i < size_; i++)
		vector[i] = 0;
}

LinVector::LinVector(int size_, float* arr) {
	size = size_;
	vector = new float[size_];
	for (size_t i = 0; i < size_; i++)
		vector[i] = arr[i];
}

LinVector::LinVector(const LinVector& other) : LinVector{other.size, other.vector} {}

LinVector::LinVector(LinVector&& other) : size{ other.size }, vector{ other.vector } {
	other.vector = nullptr;
}

LinVector::~LinVector() {
	delete [] vector;
}

int LinVector::getSize() const {
	return size;
}

float LinVector::dot(const LinVector& other) const {
	if (size == other.size)
		fatal_error("Different size of vectors in [dot]");
	float result = 0;
	for (int i = 0; i < size; i++)
		result += vector[i] * other.vector[i];
	return result;
}

float LinVector::dot(const LinVector& vec1, const LinVector& vec2) {
	if (vec1.size == vec2.size)
		fatal_error("Different size of vectors in [static dot]");
	float result = 0;
	for (int i = 0; i < vec1.size; i++)
		result += vec1[i] * vec2[i];
	return result;
}

float LinVector::mean() const {
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += vector[i];
	float mean = sum / size;
	return mean;
}

float LinVector::std() const {
	float sum_sq = 0;
	float mean = this->mean();
	for (int i = 0; i < size; i++)
		sum_sq += (vector[i] - mean) * (vector[i] - mean);
	float mean_sq_div = sum_sq / size;
	float std = std::sqrt(mean_sq_div);
	return std;
}




