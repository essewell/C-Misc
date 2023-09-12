//============================================================================
//
//% Student Name 1: Allen Shapiro
//% Student 1 #: 301567861
//% Student 1 userid (email): asa486@sfu.ca
//
//% Student Name 2: Emmett Sewwel
//% Student 2 #: 301565227
//% Student 2 userid (email): esa97@sfu.ca
//
//% Below, edit to list any people who helped you with the code in this file,
//%      or put ï¿½noneï¿½ if nobody helped (the two of) you.
//
// Helpers: SALEM ALAISARI HELPED ME
//
// Also, list any resources beyond the course textbook and the course pages on Piazza
// that you used in making your submission.
//
// Resources:  ___________
//
//%% Instructions:
//% * Put your name(s), student number(s), userid(s) in the above section.
//% * Enter the above information in Test.cpp if you are submitting that file too.
//% * Edit the "Helpers" line and "Resources" line.
//% * Your group name should be "P1_<userid1>_<userid2>" (eg. P1_stu1_stu2)
//% * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
//% * Submit one or two files to courses.cs.sfu.ca
//
// Name        : Part1Tokenizer.cpp
// Description : Tokenizer
// Original Version Copyright (c) 2023 Simon Fraser University
//============================================================================

#include "Part1Tokenizer.hpp"

using namespace std;

// Accepts a stream and returns a vector of tokens with any remaining preprocessing lines stripped out
// Input: a stream
// Output: a vector of tokens
vector<string> tokenizeCodeStrip(istream& code) {

	vector<string> tokens;
	string stringline;
	string token;
	bool stringswitch=false;
	bool numswitch=false;
	int lineindex=-1;
	while(getline(code,stringline)){
		lineindex++;
		if (stringline[0]=='#'){
			continue;
		}
		for(int i=0;i<stringline.size();i++){
			char prevprevprevcurrent=stringline[i-3];
			char prevprevcurrent=stringline[i-2];
			char prevcurrent=stringline[i-1];
			char current=stringline[i];
			char nextcurrent=stringline[i+1];
			char nextnextcurrent=stringline[i+2];
			char nextnextnextcurrent=stringline[i+3];

			if(stringswitch){
				token+=current;
				if(current=='"' && prevcurrent=='\\'){
					continue;
				}
				if(current=='"'){
					stringswitch=false;
					if(token!=""){
					tokens.push_back(token);
					token="";
					}
					continue;
				}
			}
			else if(prevcurrent=='2'&&current=='e'&&nextcurrent=='-'){
							token+=current;
							tokens.push_back(token);
							token="";
						}
			else if(prevcurrent=='e'&&current=='-'&&nextcurrent=='e'){
										token+=current;
										tokens.push_back(token);
										token="";
									}

			else if (current==' '){
				if(token!=""){
				tokens.push_back(token);
				token="";
				}
			}
			else if(current=='\''){
				if(nextnextcurrent!='\''&&nextnextnextcurrent!='\''){
					if (prevprevcurrent!='\''&&prevprevprevcurrent!='\''){
						token="";
						tokens.push_back(token);
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

			else if(prevcurrent!=' '&& current =='.'&& nextcurrent=='.'){
				token+=current;
				tokens.push_back(token);
				token="";
			}
			else if(prevcurrent=' '&& current =='.'&& nextcurrent=='.'){
				tokens.push_back(token);
				token="";
			}
			else if(current=='2'&&nextcurrent=='e'){
				token+=current;
				tokens.push_back(token);
				token=""; /* lineIndex*/
			}
			else if(prevcurrent=='2'&&current=='e'&&nextcurrent=='-'){
				token+=current;
				tokens.push_back(token);
				token="";
			}

			else if (current=='|'){
				tokens.push_back(token);
								token="";
			}
			else if (current =='+' && nextcurrent=='+'){
				if(token!=""){
					tokens.push_back(token);
					token="";
				}
				tokens.push_back("++");
				i++;
			}
			else if(current=='='||current=='+'||current==';' || current=='*'){
				if(token!=""){
					tokens.push_back(token);
					token="";
					}
				token+=current;
				tokens.push_back(token);
				token="";
			}
			else{
				token += current;
			}
		}
		if(stringswitch){
			token="";
			tokens.push_back(token);
			stringswitch=false;
		}
		if(token!=""){
			tokens.push_back(token);
			token="";
			}
	}

	return tokens;
}
