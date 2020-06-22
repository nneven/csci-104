#ifndef CONSOLE_PARSER_H
#define CONSOLE_PARSER_H

#include "Utility.h"
#include <set>
#include <vector>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>

#include <kwsys/RegularExpression.hxx>

enum ConsoleParserCommand
{
	Menu,
	Input,
	Login,
	Hit,
	Cart,
	ViewReviews,
	Recs,
	NoRecs,
	InvalidRequest,
	InvalidUser,
	InvalidLogin,
	NoUser
};

class ConsoleParser
{
public:
	class ConsoleProduct
	{
	public:
		ConsoleProduct(const std::string& name, const std::string& info, int stock, double price, double _rating);
		bool operator<(const ConsoleProduct& rhs) const;
		bool operator==(const ConsoleProduct& rhs) const;

		std::string mName;
		std::string mInfo;
		int mStock;
		double mPrice;
		double rating;
	};

	class ConsoleReview
	{
	public:
		ConsoleReview(uint8_t _rating, const std::string & _username, const std::string & _date, const std::string & _text);
		bool operator<(const ConsoleReview& rhs) const;
		bool operator==(const ConsoleReview& rhs) const;

	public:
		uint8_t rating;
		std::string username;
		std::string date; // in YYYY-MM-DD format
		std::string text;

	};

	class ConsoleRecommendation
	{
	public:
		ConsoleRecommendation(double _score, std::string const & _productName);

		bool operator<(const ConsoleRecommendation& rhs) const;
		bool operator==(const ConsoleRecommendation& rhs) const;

	public:
		double score;
		std::string productName;
	};

	class HitList : public std::vector<ConsoleProduct>
	{
	public:
		void AddProduct(ConsoleProduct&& p);
		bool operator==(const HitList& rhs) const;
	};

	class CartList : public std::vector<ConsoleProduct>
	{
	public:
		void AddProduct(ConsoleProduct&& p);
		bool operator==(const CartList& rhs) const;
	};

	class ReviewList : public std::vector<ConsoleReview>
	{
	public:
		void AddReview(ConsoleReview &&p);
		bool operator==(const ReviewList& rhs) const;
	};

	typedef std::vector<ConsoleRecommendation> RecList;

	testing::AssertionResult CompareHit(const ConsoleParser &actual) const;
	testing::AssertionResult CompareCart(const ConsoleParser &actual) const;
	testing::AssertionResult CompareReviews(const ConsoleParser &actual) const;
	testing::AssertionResult CompareRecs(const ConsoleParser &actual, bool checkOrder) const;

	testing::AssertionResult ParseMenu(std::istream &stream);
	testing::AssertionResult ParseInput(std::istream &stream);
	testing::AssertionResult ParseLogin(std::istream &stream);
	testing::AssertionResult ParseHit(std::istream &stream);
	testing::AssertionResult ParseCart(std::istream &stream);
	testing::AssertionResult ParseReviews(std::istream & stream);
	testing::AssertionResult ParseNoRecs(std::istream &stream);
	testing::AssertionResult ParseInvalidRequest(std::istream &stream);
	testing::AssertionResult ParseInvalidUser(std::istream &stream);
	testing::AssertionResult ParseInvalidLogin(std::istream &stream);
	testing::AssertionResult ParseNoUser(std::istream &stream);

	// regex to match the equals sign line that denotes the menu
	static kwsys::RegularExpression menuEqualsSep;

	// regex to match the command line prompt given by the program
	static kwsys::RegularExpression enterCommandLine;

	// regex to match the successful login message
	static kwsys::RegularExpression login;

	// regexes to match the error messages
	static kwsys::RegularExpression noRecs;
	static kwsys::RegularExpression invalidRequest;
	static kwsys::RegularExpression invalidUser;
	static kwsys::RegularExpression invalidLogin;
	static kwsys::RegularExpression noCurrentUser;

	// regexes to match a valid review date
	static kwsys::RegularExpression reviewDate;


public:
	/**
	 * Parse a sequence of commands feom an input file.
	 * @param stream
	 * @param sequence
	 * @return
	 */
	testing::AssertionResult parseSequence(std::istream& stream, std::vector<ConsoleParserCommand> sequence);

private:
	testing::AssertionResult ParseConsoleCommand(std::istream &stream, std::string const &sectionName);

	template<typename T>
	testing::AssertionResult ParseConsoleProduct(std::istream &stream, std::vector<T> &container);

	testing::AssertionResult ParseRecommendations(std::istream &stream);

private:
	std::vector<std::string> mCommand;
	std::vector<HitList> mHit;
	std::vector<CartList> mCart;
	std::vector<ReviewList> mReviews;
	std::vector<RecList> mRecs;

};

template<typename T>
testing::AssertionResult ConsoleParser::ParseConsoleProduct(std::istream &stream, std::vector<T> &container)
{
	std::streampos pos = stream.tellg();
	T hits;

	std::string content;
	int running = 1;
	int counter;
	while (stream >> content >> counter)
	{

		if(counter != running)
		{
			return testing::AssertionFailure() << "Product numbering is not continuous!  Prev number was " << (running - 1) << ", this listing was " << counter;
		}

		getline(stream, content); // remove newline

		std::string name, info;
		double price;
		int stock;
		double rating;

		getline(stream, name);
		getline(stream, info);
		stream >> price >> stock;

		// throw away the rest of the line
		getline(stream, content);

		// throw away "Rating:"
		stream >> content;

		stream >> rating;

		if (stream.fail())
		{
			return testing::AssertionFailure() << "Product description is formatted incorrectly!";
		}
		else
		{
			// product parsed successfully
			RemoveWhiteSpace(trim(name));
			RemoveWhiteSpace(trim(info));

			if(name.empty() || info.empty() || stock < 0)
			{
				return testing::AssertionFailure() << "Parts of the search result were empty or formatted incorrectly!";
			}

			hits.AddProduct(ConsoleProduct(name, info, stock, price, rating));
		}

		++running;
		pos = stream.tellg(); // set position to after current search
	}
	container.emplace_back(hits);
	stream.clear();
	stream.seekg(pos); // restore position to before failed "Hit #"

	return testing::AssertionSuccess();
}

std::ostream & operator<<(std::ostream & stream, const ConsoleParser::ConsoleProduct product);

std::ostream & operator<<(std::ostream & stream, const ConsoleParser::ConsoleReview databaseReview);

std::ostream & operator<<(std::ostream & stream, const ConsoleParser::ConsoleRecommendation recommendation);

#endif
