#include "Array.h"
#include <iostream>

Array::Array() {
	data = nullptr;
	size = 0;
}

// Array::~Array() {
// 	std::cout << "Delete called on memory address: " << data << std::endl;
// 	delete[] data;
// }

// Array::Array(const Array& other) {
// 	this->data = new int[other.size];
// 	this->size = other.size;
// 	for (int i = 0; i < other.size; ++i)
// 		this->data[i] = other.data[i];
// }

// Array& Array::operator=(const Array& other) {
// 	delete[] this->data;
// 	this->data = new int[other.size];
// 	this->size = other.size;
// 	for (int i = 0; i < other.size; ++i)
// 		this->data[i] = other.data[i];
// 	return (*this);
// }


Array Array::operator+(const Array& other) const {
	Array result;
	result.data = new int[this->size + other.size];
	result.size = this->size + other.size;
	for (int i = 0; i < this->size; ++i)
		result.data[i] = this->data[i];
	for (int i = 0; i < other.size; ++i)
		result.data[i + this->size] = other.data[i];
	return result;
}

int Array::getValAt(int index) const {
	return data[index];
}

int Array::getSize() const {
	return size;
}

void Array::push(int _val) {
	if (data == nullptr) {
		data = new int[1];
		data[0] = _val;
		size = 1;
		return;
	}
	int* newdata = new int[size + 1];
	for (int i = 0; i < size; ++i) 
		newdata[i] = data[i];
	newdata[size] = _val;
	delete[] data;
	data = newdata;
	++size;
}