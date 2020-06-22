#include "setops.h"
using namespace std;

// Computes the intersection of s1 and s2
std::set<std::string> operator&(const std::set<std::string>& s1, const std::set<std::string>& s2)
{
	set<string> result;
	for (set<string>::iterator itr = s1.begin(); itr != s1.end(); ++itr) {
		if (s2.find(*itr) != s2.end()) result.insert(*itr);
	}
	return result;
}

// Computes the union of s1 and s2
std::set<std::string> operator|(const std::set<std::string>& s1, const std::set<std::string>& s2)
{
	set<string> result;
	for (set<string>::iterator itr = s1.begin(); itr != s1.end(); ++itr) {
		result.insert(*itr);
	}
	for (set<string>::iterator itr = s2.begin(); itr != s2.end(); ++itr) {
		result.insert(*itr);
	}
	return result;
}

// Computes the difference of s1 - s2
std::set<std::string> operator-(const std::set<std::string>& s1, const std::set<std::string>& s2)
{
	set<string> result;
	for (set<string>::iterator itr = s1.begin(); itr != s1.end(); ++itr) {
		if (s2.find(*itr) == s2.end()) result.insert(*itr);
	}
	return result;
}