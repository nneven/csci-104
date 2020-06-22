#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../../hash.h"

TEST(Hash, LengthOne)
{
	std::string password = "u"; 
	int hash = 16957; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthTwo)
{
	std::string password = "us"; 
	int hash = 16010; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthThree)
{
	std::string password = "usc"; 
	int hash = 7149; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthFour)
{
	std::string password = "troj"; 
	int hash = 20895; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthFive) 
{
	std::string password = "troja"; 
	int hash = 4495; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthSix)
{
	std::string password = "trojan"; 
	int hash = 19066; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthSeven)
{
	std::string password = "trojans"; 
	int hash = 25278; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthEightA)
{
	std::string password = "goodluck"; 
	int hash = 53642; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthEightB)
{
	std::string password = "&havefun"; 
	int hash = 53307; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}

TEST(Hash, LengthEightC)
{
	std::string password = "inCS201!"; 
	int hash = 51915; 
	EXPECT_EQ(calculateHash(password), hash) << "Expected for hash value to be " << hash << " but it was actually " << calculateHash(password); 
}