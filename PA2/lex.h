/*
 * lex.h
 * Lexical Analyzer for the Basic Perl-Like (BPL) Language
 * CS280
 * Fall 2025
*/

#ifndef LEX_H_
#define LEX_H_

#include <string>
#include <iostream>
#include <map>
using namespace std;


//Definition of all the possible token types
enum Token {
	// keywords
	PRINTLN, IF, ELSE, 
	// identifiers
	IDENT, 
	// an integer, real, and string constant
	ICONST, FCONST, SCONST, 
	// the numeric operators, assignment, numeric and string comparison operators
	PLUS, MINUS, MULT, DIV, REM, EXPONENT, NEQ, SEQ, NLT, NGTE,
	SLTE, SGT, CAT, SREPEAT, AND, OR, NOT, ASSOP, CADDA, CSUBA, CCATA,
	//Delimiters
	COMMA, SEMICOL, LPAREN, RPAREN, LBRACES, RBRACES, 
	// any error returns this token
	ERR,
	// when completed (EOF), return this token
	DONE,
};


//Class definition of LexItem
class LexItem {
	Token	token;
	string	lexeme;
	int	lnum;

public:
	LexItem() {
		token = ERR;
		lnum = -1;
	}
	LexItem(Token token, string lexeme, int line) {
		this->token = token;
		this->lexeme = lexeme;
		this->lnum = line;
	}

	bool operator==(const Token token) const { return this->token == token; }
	bool operator!=(const Token token) const { return this->token != token; }

	Token	GetToken() const { return token; }
	string	GetLexeme() const { return lexeme; }
	int	GetLinenum() const { return lnum; }
};



extern ostream& operator<<(ostream& out, const LexItem& tok);
extern LexItem id_or_kw(const string& lexeme, int linenum);
extern LexItem getNextToken(istream& in, int& linenum);


#endif /* LEX_H_ */
