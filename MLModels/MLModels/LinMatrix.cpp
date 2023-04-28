#include "LinMatrix.h"

LinMatrix::LinMatrix(int n_row_, int n_col_) {
	n_row = n_row_;
	n_col = n_col_;
	shape = { n_row, n_col };
	matrix = new float* [n_row];
	for (int i = 0; i < n_row; i++) {
		matrix[i] = new float[n_col];
		for (int j = 0; j < n_col; j++)
			matrix[i][j] = 0;
	}
}

LinMatrix::LinMatrix(int n_row_, int n_col_, const float* arr) {
	n_row = n_row_;
	n_col = n_col_;
	shape = { n_row, n_col };
	matrix = new float* [n_row];
	for (int i = 0; i < n_row; i++) {
		matrix[i] = new float[n_col];
		for (int j = 0; j < n_col; j++)
			matrix[i][j] = arr[i * n_col + j];
	}
}

LinMatrix::LinMatrix(int n_row_, int n_col_, float* const * arr) { // for the future: some problems with 'const' 
	n_row = n_row_;
	n_col = n_col_;
	shape = { n_row, n_col };
	matrix = new float* [n_row];
	for (int i = 0; i < n_row; i++) {
		matrix[i] = new float[n_col];
		for (int j = 0; j < n_col; j++)
			matrix[i][j] = arr[i][j];
	}
}

LinMatrix::LinMatrix(const LinMatrix& other) : LinMatrix{other.n_row, other.n_col, other.matrix} {} // ERROR IF const float** arr in constrructor above

LinMatrix::LinMatrix(LinMatrix&& other) : n_row{ other.n_row }, n_col{ other.n_col }, shape{ other.shape }, matrix { other.matrix } {
	other.matrix = nullptr;
}

LinMatrix::~LinMatrix() {
	delete[] matrix;
}

LinMatrix LinMatrix::getRow(int idx_row) const {
	if (idx_row > n_row)
		fatal_error("Row idx > n_row! in [getRow]");
	LinMatrix res { 1, n_col };
	for (int j = 0; j < n_col; j++)
		res.matrix[0][j] = matrix[idx_row][j];
	return res;
}

LinMatrix LinMatrix::getCol(int idx_col) const {
	if (idx_col > n_col)
		fatal_error("Col idx > n_col! in [getCol]");
	LinMatrix res{ n_row, 1 };
	for (int i = 0; i < n_row; i++)
		res.matrix[i][0] = matrix[i][idx_col];
	return res;
}

LinMatrix LinMatrix::setRow(int idx_row, const LinMatrix& mat) const {
	if (idx_row > n_row)
		fatal_error("Row idx > n_row! in [setRow]");
	if (n_col != mat.n_col)
		fatal_error("Different n_col in [setRow]");
	if (mat.n_row != 1)
		fatal_error("Not a row (n_row > 1) in [setRow]");
	LinMatrix res = *this;
	for (int j = 0; j < n_col; j++)
		res.matrix[idx_row][j] = mat[idx_row][j];
	return res;
}

LinMatrix LinMatrix::setCol(int idx_col, const LinMatrix& mat) const {
	if (idx_col > n_col)
		fatal_error("Row idx > n_col! in [setCol]");
	if (n_row != mat.n_row)
		fatal_error("Different n_row in [setCol]");
	if (mat.n_col != 1)
		fatal_error("Not a col (n_col > 1) in [setCol]");
	LinMatrix res = *this;
	for (int i = 0; i < n_row; i++)
		res.matrix[i][idx_col] = mat[i][idx_col];
	return res;
}

LinMatrix LinMatrix::matmul(const LinMatrix& other) const {
	return matmul(*this, other);
}

LinMatrix LinMatrix::matmul(const LinMatrix& mat1, const LinMatrix& mat2) {
	if (mat1.n_col != mat2.n_row)
		fatal_error("Incorrect shape of matrices in [matmul]");
	LinMatrix res{ mat1.n_row, mat2.n_col };
	for (int i = 0; i < mat1.n_row; i++)
		for (int j = 0; j < mat2.n_col; j++)
			for (int k = 0; k < mat1.n_col; k++)
				res.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
	return res;
}

LinMatrix LinMatrix::hadamard(const LinMatrix& other) const {
	return hadamard(*this, other);
}

LinMatrix LinMatrix::hadamard(const LinMatrix& mat1, const LinMatrix& mat2) {
	if (mat1.shape != mat2.shape)
		fatal_error("Different shape of matrices in hadamard");
	LinMatrix res{ mat1.n_row, mat1.n_col };
	for (int i = 0; i < mat1.n_row; i++)
		for (int j = 0; j < mat1.n_col; j++)
			res.matrix[i][j] = mat1.matrix[i][j] * mat1.matrix[i][j];
	return res;
}

LinMatrix LinMatrix::flatten(int axis) const { // flatting along axis (this axis will have BIG shape)
	return flatten(axis, *this);
}

LinMatrix LinMatrix::flatten(int axis, const LinMatrix& mat) { // flatting along axis (this axis will have BIG shape)
	if (0 > axis > 1)
		fatal_error("Only 0 or 1 axis in [flatten]");

	if (axis == 0) {
		LinMatrix res{ mat.n_row * mat.n_col, 1 };
		for (int i = 0; i < mat.n_row; i++)
			for (int j = 0; j < mat.n_col; j++)
				res.matrix[i * mat.n_col + j][0] = mat.matrix[i][j];
		return res;
	}
	else if (axis == 1) {
		LinMatrix res{ 1, mat.n_row * mat.n_col };
		for (int i = 0; i < mat.n_row; i++)
			for (int j = 0; j < mat.n_col; j++)
				res.matrix[0][i * mat.n_col + j] = mat.matrix[i][j];
		return res;
	}
}

LinMatrix LinMatrix::T() const {
	return T(*this);
}

LinMatrix LinMatrix::T(const LinMatrix& mat) {
	LinMatrix res{ mat.n_col,mat.n_row };
	for (int i = 0; i < mat.n_row; i++)
		for (int j = 0; j < mat.n_col; j++)
			res.matrix[j][i] = mat.matrix[i][j];
	return res;
}


LinMatrix LinMatrix::inverse() const {
	return inverse(*this);
}


LinMatrix LinMatrix::inverse(const LinMatrix& mat) {
	if (mat.n_col != mat.n_row)
		fatal_error("Only square matrix can be inversed [inverse]");

	LinMatrix res = mat;
	int i, j, p;
	float pivot;
	//float d = 1;

	for (p = 0; p < mat.n_row; p++) {
		pivot = res.matrix[p][p];
		if (pivot == 0) {
			LinMatrix zero_mat = { mat.n_col,mat.n_row };
			return zero_mat;
		}
		//d *= pivot;
		
		for (i = 0; i < mat.n_row; i++)
			res.matrix[i][p] /= -pivot;
		for (i = 0; i < mat.n_row; i++)
			if (i != p)
				for (j = 0; j < mat.n_row; j++)
					if (j != p)
						res.matrix[i][j] += res.matrix[p][j] * res.matrix[i][p];
		for (j = 0; j < mat.n_row; j++)
			res.matrix[p][j] /= pivot;
		
		res.matrix[p][p] = 1 / pivot;
	}
	return res;
}

LinMatrix LinMatrix::daig() const {
	return diag(*this);
}

LinMatrix LinMatrix::diag(const LinMatrix& mat) {
	if (mat.n_row == mat.n_col) {
		LinMatrix res{ mat.n_row, 1 };
		for (int i = 0; i < mat.n_row; i++)
			res.matrix[i][0] = mat.matrix[i][i];
		return res;
	}
	if (mat.n_row == 1) {
		LinMatrix res{ mat.n_col, mat.n_col };
		for (int i = 0; i < mat.n_col; i++)
			res.matrix[i][i] = mat.matrix[0][i];
		return res;
	}
	if (mat.n_col == 1) {
		LinMatrix res{ mat.n_row, mat.n_row };
		for (int i = 0; i < mat.n_row; i++)
			res.matrix[i][i] = mat.matrix[i][0];
		return res;
	}
	fatal_error("Input is not vector or square matrix in [diag]");
}


void LinMatrix::print() const {
	if (n_row > 10 or n_col > 10) {
		std::cout << "Matrix is too big!" << "\n";
		return;
	}
	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < n_col; j++)
			std::cout << std::format("{:2.3f} ", matrix[i][j]);
		std::cout << "\n\n";
	}
	return;
}

LinMatrix LinMatrix::operator+(const LinMatrix& other) const {
	if (shape != other.shape)
		fatal_error("Different shape of matrices in _op_[+]");
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] + other[i][j];
	return res;
}

LinMatrix LinMatrix::operator+(const int val) const {
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] + val;
	return res;
}

LinMatrix& LinMatrix::operator+=(const LinMatrix& other) {
	if (shape != other.shape)
		fatal_error("Different shape of matrices in _op_[+=]");
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] += other.matrix[i][j];
	return *this;
}

LinMatrix& LinMatrix::operator+=(const float val) {
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] += val;
	return *this;
}

LinMatrix LinMatrix::operator-(const LinMatrix& other) const {
	if (shape != other.shape)
		fatal_error("Different shape of matrices in _op_[-]");
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
	return res;
}

LinMatrix LinMatrix::operator-(const int val) const {
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] - val;
	return res;
}

LinMatrix& LinMatrix::operator-=(const LinMatrix& other) {
	if (shape != other.shape)
		fatal_error("Different shape of matrices in _op_[-=]");
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] -= other.matrix[i][j];
	return *this;
}

LinMatrix& LinMatrix::operator-=(const float val) {
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] -= val;
	return *this;
}

LinMatrix LinMatrix::operator*(const float val) const {
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] * val;
	return res;
}

LinMatrix& LinMatrix::operator*=(const float val) {
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] *= val;
	return *this;
}

LinMatrix LinMatrix::operator/(const float val) const {
	LinMatrix res{ shape[0], shape[1] };
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			res.matrix[i][j] = matrix[i][j] / val;
	return res;
}

LinMatrix& LinMatrix::operator/=(const float val) {
	for (int i = 0; i < shape[0]; i++)
		for (int j = 0; j < shape[1]; j++)
			matrix[i][j] /= val;
	return *this;
}

LinMatrix& LinMatrix::operator=(const LinMatrix& other) {
	if (this == &other)
		return *this;
	LinMatrix res = *this;
	return res;
}