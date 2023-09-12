//============================================================================
//
//% Student Name 1: Emmett Sewell
//% Student 1 #: 301565227
//% Student 1 userid (email): esa97@sfu.ca
//
//% Student Name 2: Allen Shapiro
//% Student 2 #: 301567861
//% Student 2 userid (email): asa486@sfu.ca
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put 'None' if nobody helped (the two of) you.
//
// Helpers:
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
// Name        : tokenClasses.hpp
// Description : Course Project Part 2 (Token Classifier)
// Original portions Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#ifndef TOKENCLASSES_HPP_
#define TOKENCLASSES_HPP_

#include <string>
#include <iostream>
//#include <typeinfo>

namespace ensc251 {

using namespace std;

char *demangle(const char *typeName);

class Token {	// The Base Token Class
private:
	int m_lineIndex;
	int m_posIndex;
public:

	int getLineIndex() const {
	   return m_lineIndex;
	}
	int getPosIndex() const {
	   return m_posIndex;
	}

	Token() { std::cout << "Warning:  Do not invoke this constructor" << std::endl; } // make sure this does not get invoked.

	Token(int lineIndex, int posIndex) : m_lineIndex(lineIndex), m_posIndex(posIndex) {}

	virtual const /*std::*/string& getStringValue() const = 0;

	 // we will fix this up when we learn more about virtual functions.
	friend std::ostream& operator <<(std::ostream& outs, const Token& token){
		token.print(outs);
		return outs;
	}

	void print(std::ostream& outs) const { outs << demangle(typeid(*this).name()) << " (line: " << m_lineIndex <<", pos: " << m_posIndex <<")" << ": "; }

	virtual ~Token() {} // You will learn about virtual soon, but for now, don't delete this line.
};

class StringBasedToken:public Token {
private:
	std::string m_stringValue;
public:
	// StringBasedToken() { std::cout << "Warning:  Do not invoke this constructor" << std::endl; }; // make sure this does not get invoked.
	StringBasedToken(const std::string &aStringValue, int lineIndex, int posIndex): Token(lineIndex, posIndex) , m_stringValue(aStringValue){}
	const std::string& getStringValue( ) const {
	   return m_stringValue;
	} // return the stringValue
	void print(std::ostream& outs) const { Token::print(outs); outs << ": " << m_stringValue; }
};

class punctuator:public StringBasedToken {

public:
	punctuator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class type_spec:public StringBasedToken {

public:
	type_spec(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

// do not instantiate this class.
class id:public StringBasedToken {
public:
	id(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class pointer_id:public id {
public:
	pointer_id(const std::string &aStringValue, int lineIndex, int posIndex): id(aStringValue, lineIndex, posIndex) {}
};

class numeric_id:public id {
public:
	numeric_id(const std::string &aStringValue, int lineIndex, int posIndex): id(aStringValue, lineIndex, posIndex) {}
};

class int_id:public numeric_id {
public:
	int_id(const std::string &aStringValue, int lineIndex, int posIndex): numeric_id(aStringValue, lineIndex, posIndex) {}
};

class gen_assignment_operator:public StringBasedToken{
public:
	gen_assignment_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class int_assignment_operator:public StringBasedToken{
public:
	int_assignment_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class conditional_operator:public StringBasedToken
{
public:
	conditional_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class shift_operator:public StringBasedToken{
public:
	shift_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class additive_operator:public StringBasedToken{
public:
	additive_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class div_operator:public StringBasedToken {
public:
	div_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class mod_operator:public StringBasedToken {
public:
	mod_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class comp_operator:public StringBasedToken{
public:
	comp_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class postfix_operator:public StringBasedToken{
public:
	postfix_operator(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class string:public StringBasedToken{
public:
	string(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class incorrect:public StringBasedToken{
public:
	incorrect(const std::string &aStringValue, int lineIndex, int posIndex): StringBasedToken(aStringValue, lineIndex, posIndex) {}
};

class constant:public Token
{
public:
	constant() { std::cout << "Warning:  Do not invoke this constructor" << std::endl; }; // make sure this does not get invoked.
	constant(int lineIndex, int posIndex): Token(lineIndex, posIndex) {};
};

template<typename T>
class numeric_const:public constant
{
	// e.g. 48.5
private:
	T m_value;
	std::string m_stringValue; // you will probably need something like this
public:
	numeric_const(const T& constValue, int lineIndex, int posIndex):constant(lineIndex, posIndex), m_value(constValue){  /* ... the implementation */ };
	//Fill in for additional constructors if desired
	const std::string& getStringValue() const {
		return m_stringValue;
	}
	const T& getValue() const {
		return m_value;
	}
	void print(std::ostream& outs) const {Token::print(outs); outs << ": " << m_value; }
};

template<typename T>
class int_const:public numeric_const<T>
{
	// e.g. 48 or '0' -- covers just int and char
public:
	int_const(const T& constValue, int lineIndex, int posIndex): numeric_const<T>(constValue, lineIndex, posIndex) {}
	//Fill in for additional constructors if desired
};

} // namespace ensc251
#endif /* TOKENCLASSES_HPP_ */
