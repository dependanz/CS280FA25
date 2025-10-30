/**
 *	[NOTE] Some of this is copied directly from GivenParserPart.cpp
 */

/* Given Part for Building a Parser
 * for the Basic Perl-Like Language (BPL)
 * GivenParserPart.cpp
 * Programming Assignment 2
 * Fall 2025
*/

#include "parser.h"

map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << error_count << ". Line " << line << ": " << msg << endl;
}


// [START] Demo, this code does not work on its own.

// <AddExpr> ::= <MultExpr> { ( + | - | . ) <MultExpr> }
bool AddExpr(istream& in, int& line)
{
	bool status = false;

	// MultExpr first
	status = MultExpr(in, line);
	if(!status) {
		ParseError(line, "Invalid AddExpr");
		return false;
	}

	// Check if next token is on of ( + | - | . )
	LexItem token = Parser::GetNextToken(in, line);
	switch (token.GetToken())
	{
		case PLUS:
		case MINUS:
		case CAT:
			/**
			 * 	[NOTE] You can call AddExpr again instead of having a loop because
			 *  <AddExpr> ::= <MultExpr> { ( + | - | . ) <MultExpr> }
			 * 			  = <MultExpr> | <MultExpr> (+ | - | .) <AddExpr>
			 */ 
			status = AddExpr(in, line);
			if(!status) {
				ParseError(line, "Invalid AddExpr");
				return false;
			}
			break;
		case ERR:
			ParseError(line, "Lexical Error");
			return false;
		default:
			// If not one of (+ | - | .), push back the token
			Parser::PushBackToken(token);
	}

	return status;
}

// [END] Demo, this code does not work on its own.