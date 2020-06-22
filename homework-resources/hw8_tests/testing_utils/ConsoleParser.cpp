#include "ConsoleParser.h"

#include <misc_utils.h>

kwsys::RegularExpression ConsoleParser::menuEqualsSep("===+");

kwsys::RegularExpression ConsoleParser::login("user logged in");
kwsys::RegularExpression ConsoleParser::enterCommandLine("enter command:");
kwsys::RegularExpression ConsoleParser::noRecs("no recommendations available");
kwsys::RegularExpression ConsoleParser::invalidRequest("invalid request");
kwsys::RegularExpression ConsoleParser::invalidUser("invalid user");
kwsys::RegularExpression ConsoleParser::invalidLogin("invalid login credentials");
kwsys::RegularExpression ConsoleParser::noCurrentUser("no current user");

kwsys::RegularExpression ConsoleParser::reviewDate("[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]");

ConsoleParser::ConsoleProduct::ConsoleProduct(const std::string& name, const std::string& info, int stock, double price, double _rating)
		: mName(name)
		, mInfo(info)
		, mStock(stock)
		, mPrice(price)
		, rating(_rating)
{
}

bool ConsoleParser::ConsoleProduct::operator<(const ConsoleParser::ConsoleProduct& rhs) const
{
	if (mStock == rhs.mStock)
	{
		if (mName == rhs.mName)
		{
			if (mInfo == rhs.mInfo)
			{
				if(Approximately(mPrice, rhs.mPrice))
				{
					return rating < rhs.rating && !Approximately(rating, rhs.rating);
				}

				return mPrice < rhs.mPrice && !Approximately(mPrice, rhs.mPrice);
			}
			else
			{
				return mInfo < rhs.mInfo;
			}
		}
		else
		{
			return mName < rhs.mName;
		}
	}
	else
	{
		return mStock < rhs.mStock;
	}
}

bool ConsoleParser::ConsoleProduct::operator==(const ConsoleParser::ConsoleProduct& rhs) const
{
	return mName == rhs.mName
	       && mInfo == rhs.mInfo
	       && mStock == rhs.mStock
	       && Approximately(mPrice, rhs.mPrice)
	       && Approximately(rating, rhs.rating);
}

ConsoleParser::ConsoleReview::ConsoleReview(uint8_t _rating, const std::string &_username, const std::string &_date, const std::string &_text):
		rating(_rating),
		username(_username),
		date(_date),
		text(_text)
{

}

bool ConsoleParser::ConsoleReview::operator<(const ConsoleParser::ConsoleReview &rhs) const
{
	if(rating == rhs.rating)
	{
		if(username == rhs.username)
		{
			if(date == rhs.date)
			{
				return text < rhs.text;
			}
			else
			{
				return date < rhs.date;
			}
		}
		else
		{
			return username < rhs.username;
		}
	}
	else
	{
		return rating < rhs.rating;
	}

}

bool ConsoleParser::ConsoleReview::operator==(const ConsoleParser::ConsoleReview &rhs) const
{
	return rating == rhs.rating
	       && username == rhs.username
	       && date == rhs.date
	       && text == rhs.text;
}


ConsoleParser::ConsoleRecommendation::ConsoleRecommendation(double _score, std::string const & _productName):
score(_score),
productName(_productName)
{

}

bool ConsoleParser::ConsoleRecommendation::operator<(const ConsoleParser::ConsoleRecommendation &rhs) const
{
	if(Approximately(score, rhs.score))
	{
		return productName < rhs.productName;
	}

	// sort by increasing score
	return score > rhs.score;
}

bool ConsoleParser::ConsoleRecommendation::operator==(const ConsoleParser::ConsoleRecommendation &rhs) const
{
	return Approximately(score, rhs.score) && productName == rhs.productName;
}


void ConsoleParser::HitList::AddProduct(ConsoleParser::ConsoleProduct&& p)
{
	emplace_back(p);
}

bool ConsoleParser::HitList::operator==(const HitList& rhs) const
{
	return OrderedComparison<ConsoleParser::ConsoleProduct>(*this, rhs);
}

void ConsoleParser::CartList::AddProduct(ConsoleParser::ConsoleProduct&& p)
{
	emplace_back(p);
}

bool ConsoleParser::CartList::operator==(const CartList& rhs) const
{
	return OrderedComparison<ConsoleParser::ConsoleProduct>(*this, rhs);
}

void ConsoleParser::ReviewList::AddReview(ConsoleParser::ConsoleReview &&p)
{
	emplace_back(p);
}

bool ConsoleParser::ReviewList::operator==(const ReviewList& rhs) const
{
	return OrderedComparison<ConsoleParser::ConsoleReview>(*this, rhs);
}

testing::AssertionResult ConsoleParser::CompareHit(const ConsoleParser &actual) const
{
	if(mHit.size() != actual.mHit.size())
	{
		return testing::AssertionFailure() << "Mismatch between numbers of search queries in actual and real outputs.";
	}

	for(size_t searchIndex = 0; searchIndex < mHit.size(); ++searchIndex)
	{
		if(mHit[searchIndex] != actual.mHit[searchIndex])
		{
			return testing::AssertionFailure() << "Mismatch between search result hits on query " << (searchIndex + 1) << " of " << mHit.size() << ": Expected:\n" << vectorToString(mHit[searchIndex]) << ",\n actual:\n" << vectorToString(actual.mHit[searchIndex]);
		}
	}

	return testing::AssertionSuccess();
}

testing::AssertionResult ConsoleParser::CompareCart(const ConsoleParser &actual) const
{

	if(mCart.size() != actual.mCart.size())
	{
		return testing::AssertionFailure() << "Mismatch between numbers of cart queries in actual and real outputs.";
	}

	for(size_t searchIndex = 0; searchIndex < mCart.size(); ++searchIndex)
	{
		if(mCart[searchIndex] != actual.mCart[searchIndex])
		{
			return testing::AssertionFailure() << "Mismatch between cart items on query " << (searchIndex + 1) << " of " << mCart.size() << ": Expected:\n" << vectorToString(mCart[searchIndex]) << ",\n actual:\n" << vectorToString(actual.mCart[searchIndex]);
		}
	}

	return testing::AssertionSuccess();
}

testing::AssertionResult ConsoleParser::CompareReviews(const ConsoleParser &actual) const
{

	if(mReviews.size() != actual.mReviews.size())
	{
		return testing::AssertionFailure() << "Mismatch between numbers of review-returning queries in actual and real outputs.";
	}

	for(size_t searchIndex = 0; searchIndex < mReviews.size(); ++searchIndex)
	{
		if(mReviews[searchIndex] != actual.mReviews[searchIndex])
		{
			return testing::AssertionFailure() << "Mismatch between review data on review query " << (searchIndex + 1) << " of " << mReviews.size() << ": Expected:\n" << vectorToString(mReviews[searchIndex]) << ",\n actual:\n" << vectorToString(actual.mReviews[searchIndex]);
		}
	}

	return testing::AssertionSuccess();
}

testing::AssertionResult ConsoleParser::CompareRecs(const ConsoleParser &actual, bool checkOrder) const
{
	if(mRecs.size() != actual.mRecs.size())
	{
		return testing::AssertionFailure() << "Mismatch between numbers of recommendation commands in actual and real outputs.";
	}

	for(size_t searchIndex = 0; searchIndex < mRecs.size(); ++searchIndex)
	{
		// if we're checking order, then just use the vectors as-is, since they should be in the right order
		if(checkOrder)
		{
			if(mRecs[searchIndex] != actual.mRecs[searchIndex])
			{
				return testing::AssertionFailure() << "Mismatch on order-checked recommendation query " << (searchIndex + 1) << " of " << mRecs.size() << ": Expected:\n" << vectorToString(mRecs[searchIndex]) << ",\n actual:\n" << vectorToString(actual.mRecs[searchIndex]);
			}
		}
		else
		{
			// otherwise, compare by sets so we can sort the recs and remove duplicates
			std::set<ConsoleRecommendation> expectedRecs(mRecs[searchIndex].begin(), mRecs[searchIndex].end());
			std::set<ConsoleRecommendation> actualRecs(actual.mRecs[searchIndex].begin(), actual.mRecs[searchIndex].end());

			if(expectedRecs != actualRecs)
			{
				return testing::AssertionFailure() << "Mismatch on recommendation query " << (searchIndex + 1) << " of " << mRecs.size() << ": Expected:\n" << setToString(expectedRecs) << ",\n actual:\n" << setToString(actualRecs);
			}

		}

	}

	return testing::AssertionSuccess();;
}

testing::AssertionResult ConsoleParser::ParseMenu(std::istream &stream)
{
	bool seenFirstEqualsSep;

	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			if(menuEqualsSep.find(content))
			{
				if(!seenFirstEqualsSep)
				{
					seenFirstEqualsSep = true;
				}
				else
				{
					// second "================" divider found, done parsing menu
					return testing::AssertionSuccess();
				}

			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for end of menu";
		}
	}
}

testing::AssertionResult ConsoleParser::ParseInput(std::istream &stream)
{
	return ParseConsoleCommand(stream, "input");
}

testing::AssertionResult ConsoleParser::ParseLogin(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(login.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for user logged in message";
		}
	}

}

testing::AssertionResult ConsoleParser::ParseNoRecs(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(noRecs.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for no recommendations available message";
		}
	}
}


testing::AssertionResult ConsoleParser::ParseInvalidRequest(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(invalidRequest.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for invalid request message";
		}
	}
}

testing::AssertionResult ConsoleParser::ParseInvalidUser(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(invalidUser.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for invalid user message";
		}
	}

}

testing::AssertionResult ConsoleParser::ParseInvalidLogin(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(invalidLogin.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for invalid login credentials message";
		}
	}

}


testing::AssertionResult ConsoleParser::ParseNoUser(std::istream &stream)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(noCurrentUser.find(content))
			{
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered while searching for no current user message";
		}
	}}


testing::AssertionResult ConsoleParser::ParseHit(std::istream &stream)
{
	return ParseConsoleProduct<HitList>(stream, mHit);
}

testing::AssertionResult ConsoleParser::ParseCart(std::istream &stream)
{
	return ParseConsoleProduct<CartList>(stream, mCart);
}


testing::AssertionResult ConsoleParser::ParseReviews(std::istream &stream)
{
	ReviewList reviews;

	while(true)
	{
		// check the first token of the line and see if it looks like a date
		// if not, then we have gone past the end of the reviews, and we're done here
		std::streampos origPos = stream.tellg();
		std::string date;
		stream >> date;

		if(!reviewDate.find(date))
		{
			stream.seekg(origPos);
			break;
		}

		// parse rest of review
		uint8_t rating;
		std::string username;
		std::string reviewText;

		stream >> rating >> username;
		std::getline(stream, reviewText);

		if (stream.fail())
		{
			return testing::AssertionFailure() << "A review is formatted incorrectly!";
		}
		else
		{
			// product parsed successfully
			RemoveWhiteSpace(trim(username));
			RemoveWhiteSpace(trim(reviewText));

			reviews.AddReview(ConsoleReview(rating, username, date, reviewText));
		}

	}

	// add in this list of reviews
	mReviews.push_back(reviews);

	return testing::AssertionSuccess();
}


testing::AssertionResult ConsoleParser::ParseConsoleCommand(std::istream &stream, std::string const &sectionName)
{
	std::string content;
	while(true)
	{
		if(getline(stream, content))
		{
			makeLowercase(content);
			if(enterCommandLine.find(content))
			{
				// found prompt for next command
				return testing::AssertionSuccess();
			}
		}
		else
		{
			return testing::AssertionFailure() << "End of file encountered in " << sectionName << " section of output";
		}
	}
}

testing::AssertionResult ConsoleParser::ParseRecommendations(std::istream &stream)
{
	std::streampos pos = stream.tellg();
	RecList hits;

	// get the username at the start
	std::string username;
	stream >> username;

	double score;
	while (stream >> score)
	{

		std::string productName;
		getline(stream, productName);

		if (stream.fail())
		{
			return testing::AssertionFailure() << "Parse error on recommendation list!";
		}
		else
		{
			RemoveWhiteSpace(trim(productName));

			hits.push_back(ConsoleRecommendation(score, productName));
		}

		pos = stream.tellg(); // set position to after current search
	}

	mRecs.emplace_back(hits);
	stream.clear();
	stream.seekg(pos); // restore position to before failed score read

	return testing::AssertionSuccess();
}

testing::AssertionResult ConsoleParser::parseSequence(std::istream& stream, std::vector<ConsoleParserCommand> sequence)
{
	for (unsigned int i = 0; i < sequence.size(); ++i)
	{
		switch(sequence[i])
		{
			case ConsoleParserCommand::Menu:
				SUB_ASSERT(ParseMenu(stream));
				break;
			case ConsoleParserCommand::Input:
				SUB_ASSERT(ParseInput(stream));
				break;
			case ConsoleParserCommand::Login:
				SUB_ASSERT(ParseLogin(stream));
				break;
			case ConsoleParserCommand::Hit:
				SUB_ASSERT(ParseHit(stream));
				break;
			case ConsoleParserCommand::Cart:
				SUB_ASSERT(ParseCart(stream));
				break;
			case ConsoleParserCommand::ViewReviews:
				SUB_ASSERT(ParseReviews(stream));
				break;
			case ConsoleParserCommand::Recs:
				SUB_ASSERT(ParseRecommendations(stream));
				break;
			case ConsoleParserCommand::NoRecs:
				SUB_ASSERT(ParseNoRecs(stream));
				break;
			case ConsoleParserCommand::InvalidRequest:
				SUB_ASSERT(ParseInvalidRequest(stream));
				break;
			case ConsoleParserCommand::InvalidUser:
				SUB_ASSERT(ParseInvalidUser(stream));
				break;
			case ConsoleParserCommand::InvalidLogin:
				SUB_ASSERT(ParseInvalidLogin(stream));
				break;

			case ConsoleParserCommand ::NoUser:
				SUB_ASSERT(ParseNoUser(stream));
				break;
		}
	}
	return testing::AssertionSuccess();
}

std::ostream &operator<<(std::ostream &stream, const ConsoleParser::ConsoleProduct product)
{
	stream << "{\nname: " << product.mName << ",\n info: " << product.mInfo << ",\n stock: " << product.mStock << ",\n price: " << product.mPrice << ",\n rating: " << product.rating << "\n}";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const ConsoleParser::ConsoleReview databaseReview)
{
	stream << "{\nrating: " << databaseReview.rating << ",\n username: " << databaseReview.username << ",\n date: " << databaseReview.date << ",\n review text: " << databaseReview.text << "\n}";
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const ConsoleParser::ConsoleRecommendation recommendation)
{
	stream << "{\nscore: " << recommendation.score << ",\n product: " << recommendation.productName << "\n}";
	return stream;
}
