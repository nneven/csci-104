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

// Test the default constructor
TEST(DateTimeConstructor, Default) 
{
	DateTime d; 

	EXPECT_EQ(d.year + d.month, 2025) << "Expected for the year and month to be 2019 and 6, respectively"; 
}

// Test the overloaded constructor
TEST(DateTimeConstructor, Alt) 
{
	DateTime d(12, 12, 12, 1912, 12, 12);
	int sum = d.year + d.month + d.day + d.hour + d.min + d.sec; 

	EXPECT_EQ(sum, 1972) << "Expected for all DateTime values to be equal to 12"; 
}