
#ifndef TOKENCLASSIFIER_HPP_
#define TOKENCLASSIFIER_HPP_

#include <vector>
#include <sstream>

#include "tokenClasses.hpp"

// Construct the token objects and categorize them into appropriate types
// Input: a stream with code from the subset of C++
// Output: a vector containing shared pointers to Token objects properly categorized
std::vector<std::shared_ptr<ensc251::Token> > tokenClassifier(std::istream& code);

#endif /* TOKENCLASSIFIER_HPP_ */
