#include "datetime.h"
using namespace std;

DateTime::DateTime()
{
	time_t raw_time;
	time(&raw_time);
	struct tm *now = localtime(&raw_time);
	this->hour = now->tm_hour;
	this->min = now->tm_min;
	this->sec = now->tm_sec;
	this->year = now->tm_year + 1900; // years since 1900
	this->month = now->tm_mon + 1; // months since January (0 - 11)
	this->day = now->tm_mday;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
	this->hour = hh;
	this->min = mm;
	this->sec = ss;
	this->year = year;
	this->month = month;
	this->day = day;
}

bool DateTime::operator<(const DateTime& other) const
{
	int result;
	if (year != other.year) result = year - other.year;
	else if (month != other.month) result = month - other.month;
	else if (day != other.day) result = day - other.day;
	else if (hour != other.hour) result = hour - other.hour;
	else if (min != other.min) result = min - other.min;
	else result = sec - other.sec;

	if (result < 0) return true;
	return false;
}

ostream& operator<<(ostream& os, const DateTime& other)
{

	os << setfill('0') << setw(4) << other.year << '-';
	os << setfill('0') << setw(2) << other.month << '-';
	os << setfill('0') << setw(2) << other.day << ' ';
	os << setfill('0') << setw(2) << other.hour << ':';
	os << setfill('0') << setw(2) << other.min << ':';
	os << setfill('0') << setw(2) << other.sec;
	return os;
}

istream& operator>>(istream& is, DateTime& dt)
{
	string result;
	getline(is, result);
	if (result.size() != 19) return is;
	dt.year = stoi(result.substr(11, 13));
	dt.month = stoi(result.substr(14, 16));
	dt.day = stoi(result.substr(17, 19));
	dt.hour = stoi(result.substr(0, 4));
	dt.min = stoi(result.substr(5, 7));
	dt.sec = stoi(result.substr(8, 10));
	return is;
}