/*
 * Main.cpp
 *
 *  Created on: Jan 16, 2013
 *      Author: allen
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

string reserved_word[]=
{
		"begin",
		"end",
		"if",
		"then",
		"for",
		"while",
		"print",
		"int",
		"float"
};
string Math_operator[]=
{
		".",
		"+",
		"-",
		"*",
		"/",
		"="
};
string Comparison_operator[]=
{
		">",
		"<",
		">=",
		"<"
};
string Shift_operator[]=
{
		">>",
		"<<"
};
string Grouping_operator[]=
{
		"{",
		"}",
		"[",
		"]"
};

//using c++-11 the auto feature
//auto find(from beginning of list, to end of list, the token you're seacrhing through)
bool check_reserved_word(string ttoken)
{
    auto i = find(begin(reserved_word), end(reserved_word), ttoken); 
    if(i != end(reserved_word))
        return true;
    return false;
}

bool check_Math_operator(string ttoken)
{
    auto i = find(begin(Math_operator), end(Math_operator), ttoken); 
    if(i != end(Math_operator))
        return true;
    return false;
}
bool check_Comparison_operator(string ttoken)
{
    auto i = find(begin(Comparison_operator), end(Comparison_operator), ttoken); 
    if(i != end(Comparison_operator))
        return true;
    return false;
}
bool check_Shift_operator(string ttoken)
{
    auto i = find(begin(Shift_operator), end(Shift_operator), ttoken); 
    if(i != end(Shift_operator))
        return true;
    return false;
}
bool check_Grouping_operator(string ttoken)
{
    auto i = find(begin(Grouping_operator), end(Grouping_operator), ttoken); 
    if(i != end(Grouping_operator))
        return true;
    return false;
}

bool check_Literal(string ttoken)	//check digit
{
	for(int i = 0; i < ttoken.length(); i++)
	{
		if(isdigit(ttoken[i])==0)
		{
			return false;
		}
	}
	return true;
}
bool check_Decimal(string ttoken)	//check decimal/float
{
	for(int i = 0; i < ttoken.length(); i++)
	{
		if(isdigit(ttoken[i])==0)
		{
			if(ttoken[i]=='.')//if the digit is a '.' the next characters after '.' have to be a digit otherwise it's an error
			{
				for(int j = i+1; j<ttoken.length(); j++)
				{
					if(isdigit(ttoken[j])==0)	//loops through the token until a character reached is not a digit
						return false;		
				}
				return true;				//if looped through the whole token and a nondigit is reached
			}						//this means that the characters after the . is digits
			return false;		
		}
	}
	return false;
}
bool check_Identifier_EC0(string ttoken)		//finding invalid characters in token
{//learning how to use iota.
	//making vectors of allowed characters
	vector<char> allowed_characters = {'+', '.', '-', '*', '/', '=', '>', '<', '{', '}', '[', ']' };
	vector<char> capitals(26);
	vector<char> lowercase(26);
	vector<char> numbers(10);
	//fill characters in vectors
	iota(begin(capitals), end(capitals), 'A');
	iota(begin(lowercase), end(lowercase), 'a');
	iota(begin(numbers), end(numbers), '0');
	//adding the newly created vectors to the total allowed characters
	allowed_characters.insert(end(allowed_characters), begin(capitals), end(capitals));
	allowed_characters.insert(end(allowed_characters), begin(lowercase), end(lowercase));
	allowed_characters.insert(end(allowed_characters), begin(numbers), end(numbers));

/*
	// C++-98 way of making a predicate.
	// C++-11 added llambda, which made this obselete.
	class EC0_Predicate {
		bool operator(char checkMe){
			auto val = std::find(begin(allowed_characters), end(allowed_characters), checkMe);
			if(val == end(allowed_characters))
			{	
				return true;
			}
			return false;
		}
	};
	return std::any_of(begin(ttoken), end(ttoken), EC0_Predicate);
*/
	//Use Sweet C++-11 Style
	return std::any_of(begin(ttoken), end(ttoken),		//return true if predicate returns true otherwise false
	[allowed_characters, ttoken](char checkMe)		//lambda function another c++-11 feature 
	{
		auto val = std::find(begin(allowed_characters), end(allowed_characters), checkMe);
		if(val == end(allowed_characters))		//if reaches the end, this means that error code 0 
		{						
			return true;				
		}
		return false;					
	});							
}
bool check_Identifier_EC1(string ttoken)			//finding invalid tokens in the grammar
{								//the characters can be valid but doesn't satisfy the grammar
	//initializing the allowed characters
	vector<char> allowed_characters = {'+', '.', '-', '*', '/', '=', '>', '<', '{', '}', '[', ']' };
	vector<char> numbers(10);
	iota(begin(numbers), end(numbers), '0');
	allowed_characters.insert(end(allowed_characters), begin(numbers), end(numbers));
	
	return std::any_of(begin(ttoken), end(ttoken),		//return true if predicate returns true otherwise false
        [allowed_characters, ttoken](char checkMe) 		//more lambda function. c++-11 feature
	{
		auto val = std::find(begin(allowed_characters), end(allowed_characters), checkMe);
		if(val == end(allowed_characters))
		{	
			return false;
		}
		return true;
	});
}

string get_token()
{	//reading in the token. disregards whitespace
	//if whitespace is read. exit program. this is usually the end of file
	string token;
	cin >> token;
	if(token == "")
		exit(0);

	return token;
}

int main() {
	string token = get_token();
	while(token != "")//making sure that the return is not a space
	{
		if(check_reserved_word(token)==true)
		{
			printf("%s %s",token.data(), "\t\t is a reserved word! \n");
		}
		else if(check_Math_operator(token)==true)
		{
			printf("%s %s",token.data(), "\t\t is a math operator! \n");
		}
		else if(check_Comparison_operator(token)==true)
		{
			printf("%s %s", token.data(), "\t\t is a comparison operator! \n");
		}
		else if(check_Shift_operator(token)==true)
		{
			printf("%s %s", token.data(), "\t\t is a shift operator! \n");
		}
		else if(check_Grouping_operator(token)==true)
		{
			printf("%s %s", token.data(), "\t\t is a grouping operator! \n");
		}
		else if(check_Literal(token)==true)
		{
			printf("%s %s", token.data(), "\t\t is an integer! \n");
		}
		else if(check_Decimal(token)==true)
		{
			printf("%s %s", token.data(), "\t\t is a float! \n");
		}
		else if(check_Identifier_EC0(token)==true)
		{
			printf("%s %s", token.data(), "\t\t ERROR CODE 0: Lexical error: invalid character found in token! \n");
		}
		else if(check_Identifier_EC1(token)==true)
		{
			printf("%s %s", token.data(), "\t\t ERROR CODE 1: Lexical error: token not valid in language! \n");			
		}
		else
			printf("%s %s", token.data(), "\t\t is a identifier\n");
		token = get_token();
	}
}
