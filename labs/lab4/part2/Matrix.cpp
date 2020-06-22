#include "Matrix.h"
#include <iostream>

Matrix::Matrix() {
	rows = 0;
	cols = 0;
	data = nullptr;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> initializerList2D) {
	if (initializerList2D.size() == 0 || initializerList2D.begin()->size() == 0) {
		rows = 0;
		cols = 0;
		data = nullptr;
		return;
	}
	rows = initializerList2D.size();
	cols = initializerList2D.begin()->size();
	data = new int*[rows];
	for (int i = 0; i < rows; ++i) 
		data[i] = new int[cols];
	int i = 0, j = 0;
	for (const std::initializer_list<int>& row : initializerList2D) {
		for (int val : row) {
			data[i][j] = val;
			++j;
		}
		++i;
		j = 0;
	}

}

Matrix::Matrix(const Matrix& other) {
	// TODO
}

Matrix::~Matrix() {
	// TODO
}
	
Matrix& Matrix::operator=(const Matrix& other) {
	// TODO
}

Matrix Matrix::operator+(const Matrix& other) const {
	// TODO
}

Matrix Matrix::operator*(const Matrix& other) const {
	// TODO
}

bool Matrix::operator==(const Matrix& other) const {
	if (cols != other.cols || rows != other.rows)
		return false;
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			if (data[i][j] != other.data[i][j])
				return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	for (int i = 0; i < m.rows; ++i) {
		os << '[';
		for (int j = 0; j < m.cols; ++j) {
			os << m.data[i][j];
			if (j != m.cols - 1)
				os << '\t';
		}
		os << ']' << std::endl;
	}
	return os;
}