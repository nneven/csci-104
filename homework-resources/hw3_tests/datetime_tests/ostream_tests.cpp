#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>
#include <regex>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>

#define private public
#define protected public


#include "../../util.h"
#include "../../datetime.h"

#undef private
#undef protected

// Print DateTime constructed using the default constructor
TEST(OStream, Default)
{
	std::stringstream ss; 
	DateTime d; 

	ss << d; 

	std::string result = ss.str(); 

	std::string year = result.substr(0,4); 
	std::string month = result.substr(5,2); 

	// EXPECT_EQ(year, "2019"); 
	// EXPECT_EQ(month, "06"); 
	EXPECT_TRUE((year == "2019") && (month == "06")) << "DateTime was not set to the system time from the default constructor"; 
}

// Print DateTime constructed using the overloaded constructor
TEST(OStream, Normal) 
{
	std::stringstream ss; 
	DateTime d(12, 12, 12, 1912, 12, 12); 

	ss << d; 

	std::string result = ss.str(); 

	std::string year = result.substr(0,4); 
	std::string month = result.substr(5, 2); 

	EXPECT_TRUE((year == "1912") && (month == "12")) << "DateTime was not set properly based on the overloaded constructor";
}