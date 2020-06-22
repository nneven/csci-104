//
// CS104 HW1 majors parse
//

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
#include "../../setops.h"


//Runs the user's executable given the input and commands, as well as a location to direct the output
std::string checkMajors(std::string const & testName, 
	                    std::string const & inputContents, 
	                    std::string const & commandContents, 
	                    bool useValgrind = true)
{
	// Prepares to write input/output files
	std::string executablePath = MAJORS_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/majors_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/" + testName + ".in";
	std::string commandFilePath = testFolder +"/" + testName + ".cmd"; 
	std::string outputFilePath = testFolder +"/" + testName + ".out";
	std::string stdoutFilePath = testFolder +"/" + "stdout.txt";
	
	// write input to file
	//std::ofstream inputWriter(inputFilePath);
	//while(inputWriter << inputContents) {}
	//inputWriter << inputContents << std::endl;

	//write commands to file 
	//std::ofstream commandWriter(commandFilePath); 
	//while(commandWriter << commandContents) {}
	//ommandWriter << commandContents << std::endl; 

	// run the program
	UserCodeRunner runner(testFolder, 
						  executablePath, 
						  {inputFilePath, commandFilePath, outputFilePath}, 
						  stdoutFilePath, 
						  useValgrind);
	testing::AssertionResult result = runner.execute();
	return outputFilePath;
};

//Compares expected output to actual output
testing::AssertionResult checkOutput(std::string outputFilePath, std::string expectedOutputFilePath) 
{
	std::ifstream outputFile(outputFilePath);
	std::ifstream expectedOutput(expectedOutputFilePath); 
	if(!outputFile)
	{
		return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
	}

	std::set<std::string> expectedOutputSet; 
	std::set<std::string> actualOutputSet; 
	//std::stringstream ss; 
	//ss << expectedOutput; 

	std::ofstream debug("debug.txt"); 

	std::string line; 

	debug << "start reading in from expected output" << std::endl; 
	while (getline(expectedOutput, line)) 
	{
		debug << "reading in from expected output : " << line << std::endl; 
		expectedOutputSet.insert(line); 
	}

	while (getline(outputFile, line))
	{
		actualOutputSet.insert(line); 
	}

	debug << "Size of expected: " << expectedOutputSet.size() << std::endl; 
	debug << "Size of actual: " << actualOutputSet.size() << std::endl; 

	debug << "contents of expected" << std::endl; 
	std::set<std::string>::iterator it;
	for (it = expectedOutputSet.begin(); it != expectedOutputSet.end(); ++it) debug << *it << std::endl; 

	debug << "contents of actual" << std::endl; 
	for (it = actualOutputSet.begin(); it != actualOutputSet.end(); ++it) debug << *it << std::endl; 


	if (0 == actualOutputSet.size()) return testing::AssertionFailure() << "Expected output does not match what was returned";  
	if (0 == expectedOutputSet.size()) return testing::AssertionFailure() << "Expected output does not match what was returned";  

	//if actual is smaller than expected, then fail
	if (expectedOutputSet.size() > actualOutputSet.size()) return testing::AssertionFailure() << "Expected output does not match what was returned";
	


	//Check each line for extra spaces, etc. 
	std::set<std::string>::iterator itExp = expectedOutputSet.begin(); 
	std::set<std::string>::iterator itAct = actualOutputSet.begin(); 

	for(; itExp != expectedOutputSet.end() && itAct != actualOutputSet.end(); ++itExp, ++itAct) 
	{
		//if actual output smaller than expected output, then failed
		if(itAct->size() < itExp->size()) return testing::AssertionFailure() << "Expected output does not match what was returned"; 

		//if actual output does not have the important parts of expected output
		if (itAct->substr(0, itExp->size()) != *itExp) return testing::AssertionFailure() << "Expected output does not match what was returned"; 
	}

	return testing::AssertionSuccess(); 
}

///////////////////////////////////////////////////////////
//SimpleInput.Normal INPUT, COMMANDS, AND EXPECTED OUTPUT//
///////////////////////////////////////////////////////////

const std::string normalInput = 
"Mark W. Redekopp,CECS\n"
"Alan Turing,CSCI\n" 
"Joe Genius,PHCS\n" 
"CS Minorville,BUAD\n" 
"Ada Lovelace,CSGM\n"; 

const std::string normalCommands = 
"CSCI\n"
"CECS\n" 
"CSGM\n"
"BUAD\n";

const std::string normalExpectedOutput = 
"CSCI\n"
"Alan Turing\n" 
"\n"
"CECS\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(SimpleInput, Normal) 
{
	std::string testName = "Normal"; 
	std::string outputFilePath = checkMajors(testName, normalInput, normalCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << normalExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out"));
}

////////////////////////////////////////////////////////////////
//SimpleInput.SingleSpace INPUT, COMMANDS, AND EXPECTED OUTPUT//
////////////////////////////////////////////////////////////////

const std::string singleSpaceInput = 
"Mark W. Redekopp ,EE\n"
"Alan Turing, CSCI\n" 
" Joe Genius,PHCS\n" 
"CS Minorville ,BUAD\n" 
"Ada Lovelace, CSGM\n"; 

const std::string singleSpaceCommands = 
"PHCS\n"
"EE\n" 
"CSCI\n"
"CSGM\n";

const std::string singleSpaceExpectedOutput = 
"PHCS\n"
"Joe Genius\n" 
"\n" 
"EE\n"
"Mark W. Redekopp\n" 
"\n" 
"CSCI\n" 
"Alan Turing\n" 
"\n" 
"CSGM\n" 
"Ada Lovelace\n";

TEST(SimpleInput, SingleSpace) 
{
	std::string testName = "SingleSpace"; 
	std::string outputFilePath = checkMajors(testName, singleSpaceInput, singleSpaceCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << singleSpaceExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

//////////////////////////////////////////////////////////////
//SimpleInput.SingleTab INPUT, COMMANDS, AND EXPECTED OUTPUT//
//////////////////////////////////////////////////////////////

const std::string singleTabInput = 
"Mark W. Redekopp,\tCECS\n"
"\tAlan Turing,CSCI\n" 
"Joe Genius,\tPHCS\n" 
"CS Minorville\t,BUAD\n" 
"Ada Lovelace,CSGM\t\n"; 

const std::string singleTabCommands = 
"CSCI\n"
"CECS\n" 
"CSGM\n"
"BUAD\n";

const std::string singleTabExpectedOutput = 
"CSCI\n"
"Alan Turing\n" 
"\n"
"CECS\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(SimpleInput, SingleTab) 
{
	std::string testName = "SingleTab"; 
	std::string outputFilePath = checkMajors(testName, singleTabInput, singleTabCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << singleTabExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

////////////////////////////////////////////////////////////////////
//SimpleInput.CaseInsensitive INPUT, COMMANDS, AND EXPECTED OUTPUT//
////////////////////////////////////////////////////////////////////

const std::string caseInsensitiveInput = 
"Mark W. Redekopp,CeCs\n"
"Alan Turing,CscI\n" 
"Joe Genius,PHcS\n" 
"CS Minorville,buad\n" 
"Ada Lovelace,cSGM\n"; 

const std::string caseInsensitiveCommands = 
"Csci\n"
"CECs\n" 
"cSGM\n"
"BuAd\n";

const std::string caseInsensitiveExpectedOutput = 
"Csci\n"
"Alan Turing\n" 
"\n"
"CECs\n"
"Mark W. Redekopp\n" 
"\n" 
"cSGM\n"
"Ada Lovelace\n"
"\n"
"BuAd\n"
"CS Minorville\n"; 

TEST(SimpleInput, CaseInsensitive) 
{
	std::string testName = "CaseInsensitive"; 
	std::string outputFilePath = checkMajors(testName, caseInsensitiveInput, caseInsensitiveCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << caseInsensitiveExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

/////////////////////////////////////////////////////////////////////////
//SimpleInput.MultiMajorSingleLine INPUT, COMMANDS, AND EXPECTED OUTPUT//
/////////////////////////////////////////////////////////////////////////

const std::string multiMajorSingleLineInput = 
"Mark W. Redekopp,CECS EE\n"
"Alan Turing,CSCI BISC\n" 
"Joe Genius,PHCS CSCI\n" 
"CS Minorville,CSCI BUAD\n" 
"Ada Lovelace,CSGM\n"; 

const std::string multiMajorSingleLineCommands = 
"CSCI\n"
"EE\n" 
"CSGM\n"
"BUAD\n";

const std::string multiMajorSingleLineExpectedOutput = 
"CSCI\n"
"Alan Turing\n"
"CS Minorville\n"
"Joe Genius\n"
"\n"
"EE\n"
"Mark W. Redekopp\n"
"\n"
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(SimpleInput, MultiMajorSingleLine) 
{
	std::string testName = "MultiMajorSingleLine"; 
	std::string outputFilePath = checkMajors(testName, multiMajorSingleLineInput, multiMajorSingleLineCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiMajorSingleLineExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}


////////////////////////////////////////////////////////////////////////
//SimpleInput.MultiMajorMultiLine INPUT, COMMANDS, AND EXPECTED OUTPUT//
////////////////////////////////////////////////////////////////////////

const std::string multiMajorMultiLineInput = 
"Mark W. Redekopp,CECS\n"
"Mark W. Redekopp,EE\n"
"Alan Turing,CSCI\n"
"Alan Turing,BISC\n" 
"Joe Genius,PHCS\n"
"Joe Genius,CSCI\n" 
"CS Minorville,CSCI\n"
"CS Minorville,BUAD\n" 
"Ada Lovelace,CSGM\n"; 

const std::string multiMajorMultiLineCommands = 
"CSCI\n"
"EE\n" 
"CSGM\n"
"BUAD\n";

const std::string multiMajorMultiLineExpectedOutput = 
"CSCI\n"
"Alan Turing\n"
"CS Minorville\n"
"Joe Genius\n"
"\n"
"EE\n"
"Mark W. Redekopp\n"
"\n"
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(SimpleInput, MultiMajorMultiLine) 
{
	std::string testName = "MultiMajorMultiLine"; 
	std::string outputFilePath = checkMajors(testName, multiMajorMultiLineInput, multiMajorMultiLineCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiMajorMultiLineExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

///////////////////////////////////////////////////////////////////////
//SimpleInput.NoStudentsInMajors INPUT, COMMANDS, AND EXPECTED OUTPUT//
///////////////////////////////////////////////////////////////////////

const std::string noStudentsInMajorsInput = 
"Mark W. Redekopp,CECS\n"
"Alan Turing,CSCI\n" 
"Joe Genius,PHCS\n" 
"CS Minorville,BUAD\n" 
"Ada Lovelace,CSGM\n"; 

const std::string noStudentsInMajorsCommands = 
"BISC\n"
"MATH\n";

const std::string noStudentsInMajorsExpectedOutput = 
"BISC\n"
"\n" 
"MATH\n"
"\n";  

TEST(SimpleInput, NoStudentsInMajors) 
{
	std::string testName = "NoStudentsInMajors"; 
	std::string outputFilePath = checkMajors(testName, noStudentsInMajorsInput, noStudentsInMajorsCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << noStudentsInMajorsExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

/////////////////////////////////////////////////////////////////
//ModerateInput.MultiSpace INPUT, COMMANDS, AND EXPECTED OUTPUT//
/////////////////////////////////////////////////////////////////

const std::string multiSpaceInput = 
" Mark W. Redekopp , CECS \n"
"  Alan Turing, CSCI\n" 
"Joe Genius  ,PHCS\n" 
"    CS Minorville    ,BUAD\n" 
"Ada Lovelace,   CSGM    \n"; 

const std::string multiSpaceCommands = 
"CSCI\n"
"CECS\n" 
"CSGM\n"
"BUAD\n";

const std::string multiSpaceExpectedOutput = 
"CSCI\n"
"Alan Turing\n" 
"\n"
"CECS\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(ModerateInput, MultiSpace) 
{
	std::string testName = "MultiSpace"; 
	std::string outputFilePath = checkMajors(testName, multiSpaceInput, multiSpaceCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiSpaceExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

///////////////////////////////////////////////////////////////
//ModerateInput.MultiTab INPUT, COMMANDS, AND EXPECTED OUTPUT//
///////////////////////////////////////////////////////////////

const std::string multiTabInput = 
"\tMark W. Redekopp\t,\tCECS\t\n"
"\t\t\tAlan Turing,CSCI\n" 
"Joe Genius\t,\t\tPHCS\n" 
"CS Minorville,BUAD\t\t\t\n" 
"\t\tAda Lovelace\t\t,\t\tCSGM\n"; 

const std::string multiTabCommands = 
"CSCI\n"
"CECS\n" 
"CSGM\n"
"BUAD\n";

const std::string multiTabExpectedOutput = 
"CSCI\n"
"Alan Turing\n" 
"\n"
"CECS\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGM\n"
"Ada Lovelace\n"
"\n"
"BUAD\n"
"CS Minorville\n"; 

TEST(ModerateInput, MultiTab) 
{
	std::string testName = "MultiTab"; 
	std::string outputFilePath = checkMajors(testName, multiTabInput, multiTabCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiTabExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

////////////////////////////////////////////////////////////////////////////////
//ModerateInput.MultiSpaceCaseInsensitive INPUT, COMMANDS, AND EXPECTED OUTPUT//
////////////////////////////////////////////////////////////////////////////////

const std::string multiSpaceCaseInsensitiveInput = 
" Mark W. Redekopp , CecS \n"
"  Alan Turing, cSCI\n" 
"Joe Genius  ,phcs\n" 
"    CS Minorville    ,BUAD\n" 
"Ada Lovelace,   csGM    \n"; 

const std::string multiSpaceCaseInsensitiveCommands = 
"csCI\n"
"cecs\n" 
"CSGm\n"
"bUAd\n";

const std::string multiSpaceCaseInsensitiveExpectedOutput = 
"csCI\n"
"Alan Turing\n" 
"\n"
"cecs\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGm\n"
"Ada Lovelace\n"
"\n"
"bUAd\n"
"CS Minorville\n";  

TEST(ModerateInput, MultiSpaceCaseInsensitive) 
{
	std::string testName = "MultiSpaceCaseInsensitive"; 
	std::string outputFilePath = checkMajors(testName, multiSpaceCaseInsensitiveInput, multiSpaceCaseInsensitiveCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiSpaceCaseInsensitiveExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

//////////////////////////////////////////////////////////////////////////////
//ModerateInput.MultiTabCaseInsensitive INPUT, COMMANDS, AND EXPECTED OUTPUT//
//////////////////////////////////////////////////////////////////////////////

const std::string multiTabCaseInsensitiveInput = 
"\tMark W. Redekopp\t,\tCecS\t\n"
"\t\tAlan Turing,\tcSCI\n" 
"Joe Genius\t\t,phcs\n" 
"\t\tCS Minorville\t\t\t,BUAD\n" 
"Ada Lovelace,\tcsGM\t\t\t\n"; 

const std::string multiTabCaseInsensitiveCommands = 
"csCI\n"
"cecs\n" 
"CSGm\n"
"bUAd\n";

const std::string multiTabCaseInsensitiveExpectedOutput = 
"csCI\n"
"Alan Turing\n" 
"\n"
"cecs\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGm\n"
"Ada Lovelace\n"
"\n"
"bUAd\n"
"CS Minorville\n";  

TEST(ModerateInput, MultiTabCaseInsensitive) 
{
	std::string testName = "MultiTabCaseInsensitive"; 
	std::string outputFilePath = checkMajors(testName, multiTabCaseInsensitiveInput, multiTabCaseInsensitiveCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiTabCaseInsensitiveExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

//////////////////////////////////////////////////////////////////////////////////
//ComplexInput.MultiSpaceTabCaseInsensitive INPUT, COMMANDS, AND EXPECTED OUTPUT//
//////////////////////////////////////////////////////////////////////////////////

const std::string multiSpaceTabCaseInsensitiveInput = 
"  Mark W. Redekopp\t\t,\t\t CECS\n"
"\t Alan Turing\t ,\t CSCI\n" 
"Joe Genius ,\t\tPHCS  \n" 
"  \t\t  \t\tCS Minorville,BUAD\n" 
" \t \tAda Lovelace \t,CSGM\n"; 

const std::string multiSpaceTabCaseInsensitiveCommands = 
"CSCi\n"
"CECs\n" 
"CSGm\n"
"BUAd\n";

const std::string multiSpaceTabCaseInsensitiveExpectedOutput = 
"CSCi\n"
"Alan Turing\n" 
"\n"
"CECs\n"
"Mark W. Redekopp\n" 
"\n" 
"CSGm\n"
"Ada Lovelace\n"
"\n"
"BUAd\n"
"CS Minorville\n"; 

TEST(ComplexInput, MultiSpaceTabCaseInsensitive) 
{
	std::string testName = "MultiSpaceTabCaseInsensitive"; 
	std::string outputFilePath = checkMajors(testName, multiSpaceTabCaseInsensitiveInput, multiSpaceTabCaseInsensitiveCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << multiSpaceTabCaseInsensitiveExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//ComplexInput.MultiSpaceTabCaseInsensitiveMultiMajorSingleLine INPUT, COMMANDS, AND EXPECTED OUTPUT//
//////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string mSTCIMMSLInput = 
"  Mark W. Redekopp\t\t,\t\t CECS \t EE\n"
"\t Alan Turing\t ,\t CSCI  BUAD\n" 
"Joe Genius ,\t\tPHCS  \n" 
"  \t\t  \t\tCS Minorville,BUAD BISC\n" 
" \t \tAda Lovelace \t,CSGM\n"; 

const std::string mSTCIMMSLCommands = 
"eE\n"
"cECs\n" 
"bISC\n"
"bUAd\n";

const std::string mSTCIMMSLExpectedOutput = 
"eE\n"
"Mark W. Redekopp\n" 
"\n"
"cECs\n"
"Mark W. Redekopp\n" 
"\n" 
"bISC\n"
"CS Minorville\n"
"\n"
"bUAd\n"
"Alan Turing\n"
"CS Minorville\n"; 

TEST(ComplexInput, MultiSpaceTabCaseInsensitiveMultiMajorSingleLine) 
{
	std::string testName = "MultiSpaceTabCaseInsensitiveMultiMajorSingleLine"; 
	std::string outputFilePath = checkMajors(testName, mSTCIMMSLInput, mSTCIMMSLCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << mSTCIMMSLExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//ComplexInput.MultiSpaceTabCaseInsensitiveMultiMajorMultiLine INPUT, COMMANDS, AND EXPECTED OUTPUT//
/////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string mSTCIMMMLInput = 
"  Mark W. Redekopp\t\t,\t\t CECS\n"
" \tMark W. Redekopp,  EE\n"
"\t Alan Turing\t ,\t CSCI\n"
"Alan Turing\t , BUAD\n" 
"Joe Genius ,\t\tPHCS  \n" 
"  \t\t  \t\tCS Minorville,BUAD\n"
"\t CS Minorville,  BISC\n" 
" \t \tAda Lovelace \t,CSGM\n"; 

const std::string mSTCIMMMLCommands = 
"ee\n"
"ceCs\n" 
"biSC\n"
"buAd\n";

const std::string mSTCIMMMLExpectedOutput = 
"ee\n"
"Mark W. Redekopp\n" 
"\n"
"ceCs\n"
"Mark W. Redekopp\n" 
"\n" 
"biSC\n"
"CS Minorville\n"
"\n"
"buAd\n"
"Alan Turing\n"
"CS Minorville\n"; 

TEST(ComplexInput, MultiSpaceTabCaseInsensitiveMultiMajorMultiLine) 
{
	std::string testName = "MultiSpaceTabCaseInsensitiveMultiMajorMultiLine"; 
	std::string outputFilePath = checkMajors(testName, mSTCIMMMLInput, mSTCIMMMLCommands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << mSTCIMMMLExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

///////////////////////////////////////////////////////////////////
//ComplexInput.AnythingGoes1 INPUT, COMMANDS, AND EXPECTED OUTPUT//
///////////////////////////////////////////////////////////////////

const std::string anythingGoes1Input = 
"  Mark W. Redekopp\t\t,\t\t CECS\t\tEE\n"
"\t Alan Turing\t ,\t CSCI\n"
"Alan Turing\t , BUAD\n" 
"Joe Genius ,\t\tPHCS  \n" 
"  \t\t  \t\tCS Minorville,BUAD\n"
"\t CS Minorville,  BISC\n" 
" \t \tAda Lovelace \t,CSGM\n"; 

const std::string anythingGoes1Commands = 
"ee\n"
"ceCs\n" 
"biSC\n"
"math\n";

const std::string anythingGoes1ExpectedOutput = 
"ee\n"
"Mark W. Redekopp\n" 
"\n"
"ceCs\n"
"Mark W. Redekopp\n" 
"\n" 
"biSC\n"
"CS Minorville\n"
"\n"
"math\n"
"\n"; 

TEST(ComplexInput, AnythingGoes1) 
{
	std::string testName = "AnythingGoes1"; 
	std::string outputFilePath = checkMajors(testName, anythingGoes1Input, anythingGoes1Commands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << anythingGoes1ExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

///////////////////////////////////////////////////////////////////
//ComplexInput.AnythingGoes2 INPUT, COMMANDS, AND EXPECTED OUTPUT//
///////////////////////////////////////////////////////////////////

const std::string anythingGoes2Input = 
"  Mark W. Redekopp\t\t,\t\t ceCS\t\tEE\t CSCI BISC\n"
"\t Alan Turing\t ,\t CSCi\n"
"Alan Turing\t , BuAD\n" 
"Joe Genius ,\t\tPHCS  \n" 
"  \t\t  \t\tCS Minorville,BUAD\n"
"\t CS Minorville,  BISC\n" 
" \t \tAda Lovelace \t,CSGM\n"; 

const std::string anythingGoes2Commands = 
"ee\n"
"ceCs\n" 
"biSC\n"
"math\n"
"CSCI";

const std::string anythingGoes2ExpectedOutput = 
"ee\n"
"Mark W. Redekopp\n" 
"\n"
"ceCs\n"
"Mark W. Redekopp\n" 
"\n" 
"biSC\n"
"CS Minorville\n"
"Mark W. Redekopp\n"
"\n"
"math\n"
"\n"
"CSCI\n"
"Alan Turing\n"
"Mark W. Redekopp\n";

TEST(ComplexInput, AnythingGoes2) 
{
	std::string testName = "AnythingGoes2"; 
	std::string outputFilePath = checkMajors(testName, anythingGoes2Input, anythingGoes2Commands); 
	std::ofstream expectedOutput("testFiles/" + testName + "/" + "Expected.out"); 
	expectedOutput << anythingGoes2ExpectedOutput; 
	expectedOutput.close(); 
	outputFilePath = "testFiles/" + testName + "/" + testName + ".out"; 
	EXPECT_TRUE(checkOutput(outputFilePath, "testFiles/" + testName + "/" + "Expected.out")); 
}

// TEST(NormalTest, NormalInputTest) 
// {
// 	std::string outputFilePath = checkMajors("NormalInput", normalInput, normalInputCommands);
// 	std::ofstream expectedOutput("ExpectedOutputNormal.out"); 
// 	expectedOutput << normalInputExpectedOutput; 
// 	expectedOutput.close(); 
// 	outputFilePath = "testFiles/NormalInput/NormalInput.out"; 
// 	EXPECT_TRUE(checkOutput(outputFilePath, "ExpectedOutputNormal.out")); 
//}



























