#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include "Utility.h"
#include <set>
#include <iostream>
#include <gtest/gtest.h>

class DatabaseParser
{
public:
	class DatabaseProduct
	{
	public:
		DatabaseProduct(const std::string& type, 
			const std::string& name, 
			const std::string& info1, 
			const std::string& info2, 
			double price, 
			int stock);
		bool operator<(const DatabaseProduct& rhs) const;
		bool operator==(const DatabaseProduct& rhs) const;

	public:
		std::string mType;
		std::string mName;
		std::string mInfo1;
		std::string mInfo2;
		double mPrice;
		int mStock;
	};

	class DatabaseUser
	{
	public:
		DatabaseUser(const std::string& name, double credit, int type);
		bool operator<(const DatabaseUser& rhs) const;
		bool operator==(const DatabaseUser& rhs) const;

	public:
		std::string mName;
		double mCredit;
		int mType;
	};

	class DatabaseReview
	{
	public:
		DatabaseReview(const std::string& _productName, uint8_t _rating, const std::string & _username, const std::string & _date, const std::string & _text);
		bool operator<(const DatabaseReview& rhs) const;
		bool operator==(const DatabaseReview& rhs) const;

	public:
		std::string productName;
		uint8_t rating;
		std::string username;
		std::string date; // in YYYY-MM-DD format
		std::string text;

	};


public:
	testing::AssertionResult CompareProduct(const DatabaseParser &actual) const;
	testing::AssertionResult CompareUser(const DatabaseParser &actual) const;
	testing::AssertionResult CompareReviews(const DatabaseParser &actual) const;
	testing::AssertionResult ParseProduct(std::istream &stream);
	testing::AssertionResult ParseUser(std::istream &stream);
	testing::AssertionResult ParseReviews(std::istream &stream);

private:
	std::set<DatabaseProduct> mProduct;
	std::set<DatabaseUser> mUsers;
	std::set<DatabaseReview> mReviews;

};

std::ostream & operator<<(std::ostream & stream, const DatabaseParser::DatabaseProduct databaseProduct);

std::ostream & operator<<(std::ostream & stream, const DatabaseParser::DatabaseUser databaseUser);

std::ostream & operator<<(std::ostream & stream, const DatabaseParser::DatabaseReview databaseReview);

#endif
