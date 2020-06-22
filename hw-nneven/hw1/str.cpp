#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"

using namespace std;

// Add your implementations here.

Str::Str()
{
	length = 0;
	data_ = nullptr;
}

Str::Str(const char* s)
{
	if (!s) Str();
	else {
		length = strlen(s);
		data_ = new char[length];
		strcpy(data_, s);
	}
}

Str::Str(const Str& s)
{
	// Str(s.data_);
	length = s.length;
	data_ = new char[length];
	strcpy(data_, s.data_);
}

Str::~Str()
{
	delete[] data_;
}

Str& Str::operator=(const Str& s)
{
	return (*this = s.data_);
}

Str& Str::operator=(const char* s)
{
	if (!s) Str();
	else {
		delete[] data_;
		length = strlen(s);
		data_ = new char[length];
		strcpy(data_, s);
	}
	return *this;
}

Str& Str::operator+=(const Str& s)
{
	return (*this += s.data_);
}

Str& Str::operator+=(const char* s)
{
	Str result;
	result.length = length + strlen(s) - 1;
	result.data_ = new char[result.length];
	strcpy(result.data_, this->data_);
	strcat(result.data_, s);
	*this = result;
	return *this;
}

size_t Str::size() const
{
	return length;
}

char& Str::operator[](unsigned int i)
{
	if ((int)i >= length) throw out_of_range("Index is out of range");
	return data_[i];
}

char const & Str::operator[](unsigned int i) const
{
	if ((int)i >= length) throw out_of_range("Index is out of range");
	return data_[i];
}

Str Str::operator+(const Str& s) const
{
	//Str result;
	//return result + s.data_;
	Str result;
	result.length = this->length + s.length;
	result.data_ = new char[result.length];
	strcpy(result.data_, this->data_);
	strcat(result.data_, s.data_);
	
	return result;
}

Str Str::operator+(const char* rhs) const
{
	if (!rhs) return *this;
	Str result;
	result.length = this->length + strlen(rhs);
	result.data_ = new char[result.length];
	strcpy(result.data_, this->data_);
	strcat(result.data_, rhs);
	
	return result;
}

bool Str::operator==(const Str& s) const
{
	if (this->length != s.length) return false;
	for (int i = 0; i < length; i++)
		if (data_[i] != s.data_[i]) return false;

	return true;
}

bool Str::operator!=(const Str& s) const
{
	return !(*this == s);
}

bool Str::operator>(const Str& s) const
{
	if (strcmp(data_, s.data_) > 0) return true;
	return false;
}

bool Str::operator<(const Str & s) const
{
	if (strcmp(data_, s.data_) < 0) return true;
	return false;
}

std::ostream& operator<<(std::ostream& ostr, const Str& s)
{
	for (int i = 0; i < s.length; i++)
		ostr << s.data_[i];

	return ostr;
}

std::istream& operator>>(std::istream& istr, Str& s)
{
	std::string stemp;
	istr >> stemp;
	s = stemp.c_str();
	return istr;
}