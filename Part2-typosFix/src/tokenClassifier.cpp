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
// Name        : tokenClassifier.cpp
// Description : Course Project Part 2 (Token Classifier)
// Original portions Copyright (c) 2023 School of Engineering Science, Simon Fraser University
//============================================================================

#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include "tokenClasses.hpp"
#include<cstring>
using namespace std;
using namespace ensc251;

// Construct token objects categorized into appropriate types
// Input: a stream with code from the subset of C++
// Output: a vector containing shared pointers to Token objects properly categorized
vector<shared_ptr<Token> > tokenClassifier(istream& code){
		vector<shared_ptr<Token> > tokens;
		std::string stringline;
		std::string token;
		bool stringswitch=false;
		bool numswitch=false;
		bool int_idswitch=false;
		bool numidswitch=false;
		bool floatswitch=false;
		bool slashswitch=false;
		bool pointerid = false;
		std::string savednumid = " ";

		int lineindex=-1;
		while(getline(code,stringline)){
			lineindex++;
			if (stringline[0]=='#'){
				continue;
			}
			int i;
			for(i = 0;i<stringline.size();i++){
				char prevprevprevcurrent=stringline[i-3];
				char prevprevcurrent=stringline[i-2];
				char prevcurrent=stringline[i-1];
				char current=stringline[i];
				char nextcurrent=stringline[i+1];
				char nextnextcurrent=stringline[i+2];
				char nextnextnextcurrent=stringline[i+3];
				if (token=="int"){
					tokens.push_back(make_shared<type_spec >(type_spec(token, lineindex, i-token.length()/*posIndex*/)));
					token="";
					int_idswitch=true;
				}
				if (token=="char"){
					tokens.push_back(make_shared<type_spec >(type_spec(token, lineindex, i-token.length()/*posIndex*/)));
					token="";
					int_idswitch=true;
				}
				if (token=="float"){
					tokens.push_back(make_shared<type_spec >(type_spec(token, lineindex, i-token.length()/*posIndex*/)));
					token="";
					numidswitch=true;
				}
				if (nextcurrent == ' ' && (current == 'r' && token == "er")){
					token += current;
					tokens.push_back(make_shared<numeric_id>(numeric_id(token, lineindex, i-token.length()+1/*posIndex*/)));
					token = "";
					continue;
				}
				if (token == savednumid){
					tokens.push_back(make_shared<numeric_id>(numeric_id(token, lineindex, i-token.length()/*posIndex*/)));
					token = "";
				}
				if (int_idswitch==true && (current == ' ' && prevcurrent != ' ')){
					if (token!=""){
						tokens.push_back(make_shared<int_id>(int_id(token, lineindex, i-token.length()/*posIndex*/)));
						token="";
						int_idswitch=false;
					}
				}
				if (pointerid){
					int a = 0;
					while (current != ' '){
						token += current;
						a++;
					}
					if (token != ""){
						tokens.push_back(make_shared<pointer_id>(pointer_id(token, lineindex, i-token.length()+a/*posIndex*/)));
						token = "";
					}
					continue;
				}
				if (current == '\\' && nextcurrent == '"'){
					if (stringswitch){
						token+=current;
						token+=nextcurrent;
						i++;
						tokens.push_back(make_shared<ensc251::string>(ensc251::string(token, lineindex, i-token.length()/*posIndex*/)));
						token = "";
						stringswitch = false;
						continue;
					}
					slashswitch == true;
					token+=current;
					token+=nextcurrent;
					i++;
					stringswitch = true;
					continue;
				}
				if (current=='+'){
					if (nextcurrent=='='){
						token+=current;
						token+=nextcurrent;
						tokens.push_back(make_shared<gen_assignment_operator>(gen_assignment_operator(token, lineindex, i-token.length()+2/*posIndex*/)));
						token="";
						i++;
						continue;
					}
					if (nextcurrent=='+'){
						token+=current;
						token+=nextcurrent;
						tokens.push_back(make_shared<postfix_operator>(postfix_operator(token, lineindex, i-token.length()+2/*posIndex*/)));
						token="";
						i++;
						continue;
					}
				}
				if (current == '-' && nextcurrent == ' ' && prevcurrent == ' '){
					token+=current;
					tokens.push_back(make_shared<additive_operator>(additive_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}
				if (current=='='){
					token+=current;
					tokens.push_back(make_shared<gen_assignment_operator>(gen_assignment_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}
				if (current == '&'){
					token+=current;
					tokens.push_back(make_shared<incorrect>(incorrect(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}
				if (current == '*'){
					token+=current;
					tokens.push_back(make_shared<punctuator>(punctuator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					pointerid = true;
					continue;
				}
				if (current == '(' || current == ')'){
					token+=current;
					tokens.push_back(make_shared<punctuator>(punctuator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}
				if (current == '<'){
					if (nextcurrent == '<' && nextnextcurrent == '='){
						token+=current;
						token+=nextcurrent;
						token+=nextnextcurrent;
						tokens.push_back(make_shared<int_assignment_operator>(int_assignment_operator(token, lineindex, i-token.length()+3/*posIndex*/)));
						token = "";
						i+=2;
						continue;
					}
					else if (nextcurrent == '<' && nextnextcurrent == ' '){
						token+=current;
						token+=nextcurrent;
						tokens.push_back(make_shared<shift_operator>(shift_operator(token, lineindex, i-token.length()+2/*posIndex*/)));
						token="";
						i++;
						continue;
					}
					else if (nextcurrent == ' '){
						token += current;
						tokens.push_back(make_shared<conditional_operator>(conditional_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
						token="";
						continue;
					}
				}
				if (current == '>'){
					if (nextcurrent == '>' && nextnextcurrent == '='){
						token+=current;
						token+=nextcurrent;
						token+=nextnextcurrent;
						tokens.push_back(make_shared<int_assignment_operator>(int_assignment_operator(token, lineindex, i-token.length()+3/*posIndex*/)));
						token = "";
						i+=2;
						continue;
					}
					else if (nextcurrent == '>' && nextnextcurrent == ' '){
						token+=current;
						token+=nextcurrent;
						tokens.push_back(make_shared<shift_operator>(shift_operator(token, lineindex, i-token.length()+2/*posIndex*/)));
						token="";
						i++;
						continue;
					}
					else if (nextcurrent == ' '){
						token += current;
						tokens.push_back(make_shared<conditional_operator>(conditional_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
						token="";
						continue;
					}
				}
				if (current == '%'){
					token+=current;
					tokens.push_back(make_shared<mod_operator>(mod_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					numswitch = true;
					continue;
				}
				if (current == '?'){
					token += current;
					tokens.push_back(make_shared<conditional_operator>(conditional_operator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}

				if (numidswitch&&token!=""){
					if (current==';' || current == ' '){
						savednumid = token;
						numidswitch = false;
						tokens.push_back(make_shared<numeric_id>(numeric_id(token, lineindex, i-token.length()/*posIndex*/)));
						token = "";
					}
					else{
						token+=current;
						continue;
					}
				}
				if (token=="errno"){
					tokens.push_back(make_shared<int_id >(int_id(token, lineindex, i-token.length()/*posIndex*/)));
					token="";
					continue;
				}
				if (current=='\'' && nextnextcurrent=='\''){
					token += current;
					token += nextcurrent;
					token += nextnextcurrent;
					tokens.push_back(make_shared<int_const<char>>(int_const<char>(token[1], lineindex, i/*posIndex*/)));
					token = "";
					i+=2;
					continue;
				}

				if(numswitch){
					if (current=='.'){
						token+=current;
						floatswitch = true;
						continue;
					}
					if((current=='e'||current=='E') && isdigit(nextcurrent)){
						token+=current;
						token+=nextcurrent;
						i++;
						tokens.push_back(make_shared<numeric_const<std::string>>(numeric_const<std::string>(token, lineindex, i-token.length()+1/*posIndex*/)));
					}
					if((current=='e'||current=='E') && nextcurrent=='-' && isdigit(nextnextcurrent)){
					    token+=current;
					    token+=nextcurrent;
					    token+=nextnextcurrent;
					    i+=2;
					    floatswitch = true;
					    continue;
					}
					if(!isdigit(current)&&floatswitch){
						numswitch=false;
						float ftoken = std::stof(token);
						tokens.push_back(make_shared<numeric_const<float>>(numeric_const<float>(ftoken, lineindex, i-token.length()/*posIndex*/)));
						token="";
						continue;
					}
					if(!isdigit(current)){
						numswitch=false;
						const int length=token.length();
						char* char_array = new char[length+1];
						strcpy(char_array,token.c_str());
						int itoken = std::atoi(char_array);
						tokens.push_back(make_shared<int_const<int>>(int_const<int>(itoken, lineindex, i-token.length()/*posIndex*/)));
						token="";
						continue;
					}
					if(current!=' '){
					token+=current;
					}
					continue;
				}
				if (current==';' || current==':'){
					token+=current;
					tokens.push_back(make_shared<punctuator>(punctuator(token, lineindex, i-token.length()+1/*posIndex*/)));
					token="";
					continue;
				}
				if(stringswitch){
					token+=current;
					if(current=='"' && prevcurrent=='\\'){
						continue;
					}
					if(current=='"' && (nextcurrent == ' ' || nextcurrent == ';')){
						stringswitch=false;
						if(token!=""){
							tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
						token="";
						}
						continue;
					}
				}


//				else if(prevcurrent=='2'&&current=='e'&&nextcurrent=='-'){
//								token+=current;
//								tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//								token="";
//							}
//				else if(prevcurrent=='e'&&current=='-'&&nextcurrent=='e'){
//											token+=current;
//											tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//											token="";
//										}

				else if (current==' '){
					if(token!=""){
						tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
						token="";
					}
				}
				else if(current=='\''){
					if(nextnextcurrent!='\''&&nextnextnextcurrent!='\''){
						if (prevprevcurrent!='\''&&prevprevprevcurrent!='\''){
							token="";
							tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
							i+=2;
							}
						else{
							token+=current;
							}
						}
					else{
						token+=current;
						}
					}
				else if (current == '"'){
					stringswitch=true;
					token+=current;
				}

//				else if(prevcurrent!=' '&& current =='.'&& nextcurrent=='.'){
//					token+=current;
//					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//					token="";
//				}
//				else if(prevcurrent=' '&& current =='.'&& nextcurrent=='.'){
//					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//					token="";
//				}
//				else if(current=='2'&&nextcurrent=='e'){
//					token+=current;
//					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//					token=""; /* lineIndex*/
//				}
//				else if(prevcurrent=='2'&&current=='e'&&nextcurrent=='-'){
//					token+=current;
//					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
//					token="";
//				}

				else if (current=='|'){
					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
									token="";
				}
				else if (current =='+' && nextcurrent=='+'){
					if(token!=""){
						tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
						token="";
					}
					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken("++", lineindex, i-token.length()/*posIndex*/)));
					i++;
				}
				else if(current=='='||current=='+'||current==';' || current=='*'){
					if(token!=""){
						tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
						token="";
						}
					token+=current;
					tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
					token="";
				}
				else if (isdigit(current)|| current=='.'){
					token+=current;
					numswitch=true;
				}
				else{
					token += current;
				}
			}
			if(stringswitch){
				token="";
				tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
				stringswitch=false;
			}
			if(token!=""){
				tokens.push_back(make_shared<StringBasedToken >(StringBasedToken(token, lineindex, i-token.length()/*posIndex*/)));
				token="";
			}
		}
        return tokens;
}

