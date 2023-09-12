//============================================================================
//
//% Student Name 1: Emmett Sewell
//% Student 1 #: 301565227
//% Student 1 esa97@sfu.ca
//
//% Student Name 2: Allen Shapiro
//% Student 2 #: 123456782
//% Student 2 userid (email): stu2 (stu2@sfu.ca)
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers: _everybody helped us/me with the assignment (list names or put 'None')__
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in tokenClasses.cpp  too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P2_<userid1>_<userid2>" (eg. P2_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit files to courses.cs.sfu.ca
//
// Name        : TestPart2.cpp
// Description : Course Project Part 2 (Token Classifier)
// Original portions Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE Course Project Part 2
#include <vector>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include <boost/algorithm/string/join.hpp>

#include "tokenClassifier.hpp"
//#include "tokenClasses.hpp"

using namespace boost::algorithm;
using namespace ensc251;
using namespace std;

#ifndef ENSC251_CHECK_EQUAL
#define ENSC251_CHECKER(A, B) BOOST_CHECK(A == B)
#else
#define ENSC251_CHECKER(A, B) BOOST_CHECK_EQUAL(A, B)
#endif

struct tokenStruct{
	std::string tokenValue;
	int lineIndex;
	int posIndex;
	std::string tokenType;
};

void check(std::string input, vector<tokenStruct> tokens)
{
	istringstream code(input);
	std::vector<std::shared_ptr<ensc251::Token> > tokenObjects{tokenClassifier(code)};

	for(unsigned int i{0}; i<min(tokens.size(),tokenObjects.size()); i++)
	{
		std::string type{ensc251::demangle(typeid(*tokenObjects.at(i)).name())};
		if(type==tokens.at(i).tokenType) {
			if(type=="ensc251::int_const<int>")
			{
				ensc251::numeric_const<int> *intToken{dynamic_cast<ensc251::int_const<int> *>(tokenObjects.at(i).get())};
				BOOST_CHECK_EQUAL(intToken->getValue(), atoi(tokens.at(i).tokenValue.c_str()));
				BOOST_CHECK_EQUAL(intToken->getLineIndex(), tokens.at(i).lineIndex);
				BOOST_CHECK_EQUAL(intToken->getPosIndex(), tokens.at(i).posIndex);
			}
			else if(type=="ensc251::numeric_const<float>")
			{
				ensc251::numeric_const<float> *floatToken{dynamic_cast<ensc251::numeric_const<float> *>(tokenObjects.at(i).get())};
				BOOST_CHECK_EQUAL(floatToken->getValue(), (float)atof(tokens.at(i).tokenValue.c_str()) );
				BOOST_CHECK_EQUAL(floatToken->getLineIndex(), tokens.at(i).lineIndex);
				BOOST_CHECK_EQUAL(floatToken->getPosIndex(), tokens.at(i).posIndex);
			}
			else if(type=="ensc251::int_const<char>")
			{
				ensc251::numeric_const<char> *charToken{dynamic_cast<ensc251::int_const<char> *>(tokenObjects.at(i).get())};
				BOOST_CHECK_EQUAL(charToken->getValue(),  tokens.at(i).tokenValue.at(1));
				BOOST_CHECK_EQUAL(charToken->getLineIndex(), tokens.at(i).lineIndex);
				BOOST_CHECK_EQUAL(charToken->getPosIndex(), tokens.at(i).posIndex);

			}
			else
			{
				ensc251::StringBasedToken *strToken{dynamic_cast<ensc251::StringBasedToken *>(tokenObjects.at(i).get())};
				BOOST_CHECK_EQUAL(strToken->getStringValue(), tokens.at(i).tokenValue);
				BOOST_CHECK_EQUAL(strToken->getLineIndex(), tokens.at(i).lineIndex);
				BOOST_CHECK_EQUAL(strToken->getPosIndex(), tokens.at(i).posIndex);
			}
		}
		else {
			BOOST_CHECK_EQUAL(type, tokens.at(i).tokenType);
		}
	}
	if(tokenObjects.size()!=tokens.size())
		BOOST_ERROR("Wrong number of tokens.");
}

BOOST_AUTO_TEST_CASE( test1 ){
	std::string input{"int a = 2 ;"};
	vector<tokenStruct> tokens{{"int", 0, 0, "ensc251::type_spec"},
							   {"a", 0, 4, "ensc251::int_id"},
							   {"=", 0, 6, "ensc251::gen_assignment_operator"},
							   {"2", 0, 8, "ensc251::int_const<int>"},
							   {";", 0, 10, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test2 ){
	std::string input{"char c = 'c' ;"};
	vector<tokenStruct> tokens   {{"char", 0, 0, "ensc251::type_spec"},
								  {"c", 0, 5, "ensc251::int_id"},
								  {"=", 0, 7, "ensc251::gen_assignment_operator"},
								  {"'c'", 0, 9, "ensc251::int_const<char>"},
								  {";", 0, 13, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test3 ){
	std::string input{"float _fnumber; _fnumber += 10.5 % 5;"};
	vector<tokenStruct> tokens   {{"float", 0, 0, "ensc251::type_spec"},
								  {"_fnumber", 0, 6, "ensc251::numeric_id"},
								  {";", 0, 14, "ensc251::punctuator"},
								  {"_fnumber", 0, 16, "ensc251::numeric_id"},
								  {"+=", 0, 25, "ensc251::gen_assignment_operator"},
								  {"10.5", 0, 28, "ensc251::numeric_const<float>"},
								  {"%" , 0, 33, "ensc251::mod_operator"},
								  {"5", 0, 35, "ensc251::int_const<int>"},
								  {";", 0, 36, "ensc251::punctuator"}};
	check(input, tokens);
}
BOOST_AUTO_TEST_CASE( test4 ){
	std::string input{"char Int = errno ? 10 : 20 ;"};
	vector<tokenStruct> tokens   {{"char", 0, 0, "ensc251::type_spec"},
								  {"Int", 0, 5, "ensc251::int_id"},
								  {"=", 0, 9, "ensc251::gen_assignment_operator"},
								  {"errno", 0, 11, "ensc251::int_id"},
								  {"?", 0, 17, "ensc251::conditional_operator"},
								  {"10", 0, 19, "ensc251::int_const<int>"},
								  {":", 0, 22, "ensc251::punctuator"},
								  {"20", 0, 24, "ensc251::int_const<int>"},
								  {";", 0, 27, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test5 ){
	std::string input{"errno <<= '2' >> 5 ;"};
	vector<tokenStruct> tokens   {{"errno", 0, 0, "ensc251::int_id"},
								  {"<<=", 0, 6, "ensc251::int_assignment_operator"},
								  {"'2'", 0, 10, "ensc251::int_const<char>"},
								  {">>", 0, 14, "ensc251::shift_operator"},
								  {"5", 0, 17, "ensc251::int_const<int>"},
								  {";", 0, 19, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test6 ){
	std::string input{"float _f; \n_f= 39E-2 - ( _f ++ ) ;"};
	vector<tokenStruct> tokens   {{"float", 0, 0, "ensc251::type_spec"},
								  {"_f", 0, 6, "ensc251::numeric_id"},
								  {";", 0, 8, "ensc251::punctuator"},
								  {"_f", 1, 0, "ensc251::numeric_id"},
								  {"=", 1, 2, "ensc251::gen_assignment_operator"},
								  {"39E-2", 1, 4, "ensc251::numeric_const<float>"},
								  {"-", 1, 10, "ensc251::additive_operator"} ,
								  {"(", 1, 12, "ensc251::punctuator"} ,
								  {"_f", 1, 14, "ensc251::numeric_id"},
								  {"++", 1, 17, "ensc251::postfix_operator"},
								  {")", 1, 20, "ensc251::punctuator"},
								  {";", 1, 22, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test7 ){
	std::string input{"char* _str = \"Hello World\" ;"};
	vector<tokenStruct> tokens   {{"char", 0, 0, "ensc251::type_spec"},
								  {"*", 0, 4, "ensc251::punctuator"},
								  {"_str", 0, 6, "ensc251::pointer_id"},
								  {"=", 0, 11, "ensc251::gen_assignment_operator"},
								  {"\"Hello World\"", 0, 13, "ensc251::string"},
								  {";", 0, 27, "ensc251::punctuator"}};
	check(input, tokens);
}

BOOST_AUTO_TEST_CASE( test8 ){
	std::string input{"char* err &= \"test ;"};
	vector<tokenStruct> tokens   {{"char", 0, 0, "ensc251::type_spec"},
								  {"*", 0, 4, "ensc251::punctuator"},
								  {"err", 0, 6, "ensc251::pointer_id"},
								  {"&", 0, 10, "ensc251::incorrect"},
								  {"=", 0, 11, "ensc251::gen_assignment_operator"},
								  {"\"test ;", 0, 13, "ensc251::incorrect"}};
	check(input, tokens);
}
