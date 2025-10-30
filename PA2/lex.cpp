/*
 * lex.cpp
 *
 * CS280 - Fall 2025
 * Lexical Analyzer for the Basic Perl-Like (BPL) Language
 */

#include <cctype>
#include <map>

using std::map;
using namespace std;

#include "lex.h"
//Keywords mapping
LexItem id_or_kw(const string& lexeme , int linenum)
{
	map<string,Token> kwmap = {
		{ "println", PRINTLN },
		{ "if", IF },
		{ "else", ELSE },
	};
	Token tt = IDENT;
	string keyword = lexeme;
	for(int i = 0; i < keyword.length(); i++)
	{
		keyword[i] = tolower(keyword[i]);
	}
	//cout << "inside id_or_kw " << lexeme << endl;
	auto kIt = kwmap.find(keyword);
	if( kIt != kwmap.end() )
	{
		tt = kIt->second;
	}
	
	return LexItem(tt, lexeme, linenum);
}

map<Token,string> tokenPrint = {
		{PRINTLN, "PRINTLN"},
		{ IF, "IF" },
		{ ELSE, "ELSE" },	
		{ IDENT, "IDENT" },
		
		{ ICONST, "ICONST" },
		{ FCONST, "FCONST" },
		{ SCONST, "SCONST" },
			
		{ PLUS, "PLUS" },
		{ MINUS, "MINUS" },
		{ MULT, "MULT" },
		{ DIV, "DIV" },
		{ REM, "REM" },
		
		{ EXPONENT, "EXPONENT" },
		{ ASSOP, "ASSOP" },
		{ NEQ, "NEQ" },
		{ NLT, "NLT" },
		{ NGTE, "NGTE" },
		
		{ CAT, "CAT" },
		{ SREPEAT, "SREPEAT" },
		{ SEQ, "SEQ" },
		{ SLTE, "SLTE" },
		{ SGT, "SGT" },
		{ AND, "AND" },
		{ OR, "OR" },
		{ NOT, "NOT" },
		{ CADDA, "CADDA" },
		{ CSUBA, "CSUBA" },
		{ CCATA, "CCATA" },
				            
		{ COMMA, "COMMA" },
		{ SEMICOL, "SEMICOL" },
		{ LPAREN, "LPAREN" },
		{ RPAREN, "RPAREN" },
		{ LBRACES, "LBRACES" },
		{ RBRACES, "RBRACES" },
		
				
		{ ERR, "ERR" },

		{ DONE, "DONE" },
};

ostream& operator<<(ostream& out, const LexItem& tok) {
	
	Token tt = tok.GetToken() ;
	out << tokenPrint[ tt ] << ": ";
	if( tt == IDENT ) 
		out << "(" << tok.GetLexeme() << ")";
	else if (tt == ICONST || tt == FCONST ) {
		out << "[" << tok.GetLexeme() << "]";
	}
	else if (tt == SCONST)
	{
		out << "<" << tok.GetLexeme() << ">";
	}
	else if (tt == ERR)
	{
		int line = tok.GetLinenum() + 1;
		out << "Error-Unrecognized Lexeme {" << tok.GetLexeme() << "} in line " << line;
	}
	else
	{
		out << "\"" << tok.GetLexeme() << "\"";
	}
	return out;
}

LexItem getNextToken(istream& in, int& linenum)
{
	enum TokState { START, INID, INSQSTR, INDQSTR, ININT, INFLOAT, INCOMMENT, INSCOMPARE } lexstate = START;
	string lexeme;
	char ch, nextch, nextchar;
	Token tt;
	bool dec = false;
	       
	while(in.get(ch)) {
    	
		switch( lexstate ) {
		case START:
			if( ch == '\n' )
			{
				linenum++;
			}	
                
			if( isspace(ch) )
				continue;

			lexeme = ch;

			if( isalpha(ch) || ch == '$') {
				lexeme = ch;
				lexstate = INID;
				
			}
				
			else if( ch == '\''  ) {
				lexstate = INSQSTR;
			}
			else if(ch == '\"') 
			{
				lexstate = INDQSTR;
			}
			else if( isdigit(ch) ) {
				lexstate = ININT;
			}
			else if( ch == '#' ) {
				lexstate = INCOMMENT;
			}
			else if( ch == '@' ) {
				lexstate = INSCOMPARE;
			}			
			else {
				tt = ERR;
				switch( ch ) {
				case '+':
					tt = PLUS;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = CADDA;
					}
                    break;  
					
				case '-':
					tt = MINUS;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = CSUBA;
					}
                    break; 
					
				case '*':
					tt = MULT;
					nextchar = in.peek();
					if(nextchar == '*'){
						in.get(ch);
						lexeme += ch;
						tt = EXPONENT;
						
					}
					break;

				case '/':
					tt = DIV;
					break;
				case '%':
					tt = REM;
					break;	
					
				case '=':
					tt = ASSOP;
					nextchar = in.peek();
					if(nextchar == '='){
						in.get(ch);
						lexeme += ch;
						tt = NEQ;
						
					}
					
					break;
				
				case '(':
					tt = LPAREN;
					break;			
				case ')':
					tt = RPAREN;
					break;
				case '{':
					tt = LBRACES;
					break;			
				case '}':
					tt = RBRACES;
					break;
				case ';':
					tt = SEMICOL;
					break;
					
				case ',':
					tt = COMMA;
					break;
					
				case '>':
					nextchar = in.peek();
					if(nextchar == '='){
						in.get(ch);
						lexeme += ch;
						tt = NGTE;
						
					}
					else
					{
						tt = ERR;
					}
					break;
				
				case '<':
					tt = NLT;
					break;
				case '!':
					tt = NOT;
					break;	
				
				case '&':
					nextchar = in.peek();
					if(nextchar == '&'){
						in.get(ch);
						lexeme += ch;
						tt = AND;	
					}
					else
					{
						tt = ERR;
					}
					break;
				
				case '|':
					nextchar = in.peek();
					if(nextchar == '|'){
						in.get(ch);
						lexeme += ch;
						tt = OR;	
					}
					else
					{
						tt = ERR;
					}
					break;
							
				case '.':
					tt = CAT;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = CCATA;
						
					}
					else if (nextchar == 'x') {
						in.get(ch);
						lexeme += ch;
						nextchar = in.peek();
						if(nextchar == '.')
						{
							in.get(ch);
							lexeme += ch;
							tt = SREPEAT;
							
						}
						else
						{
							tt = ERR;
							
						}
					}
					
					break;
				}
				return LexItem(tt, lexeme, linenum);
			}
			break;	//from START

		case INID:
			
			if( isalpha(ch) || isdigit(ch) || (ch == '_' ) || (ch == '$' )) {
							
				lexeme += ch;
			}
			else {
				in.putback(ch);
				return id_or_kw(lexeme, linenum);
			}
			break;//from INID
			
		case INSQSTR:
                          
			if( ch == '\n' ) {
				return LexItem(ERR, lexeme, linenum);
			}
			lexeme += ch;
			if( ch == '\'' ) {
				lexeme = lexeme.substr(1, lexeme.length()-2);
				return LexItem(SCONST, lexeme, linenum);
			}
			break;//from INSQSTR
		case INDQSTR:
                          
			if( ch == '\n' ) {
				return LexItem(ERR, lexeme, linenum);
			}
			lexeme += ch;
			if( ch == '\"' ) {
				lexeme = lexeme.substr(1, lexeme.length()-2);
				return LexItem(SCONST, lexeme, linenum);
			}
			break;//from INDQSTR
			
		case ININT:
			if( isdigit(ch) ) {
				lexeme += ch;
			}
			else if(ch == '.') {
				lexstate = INFLOAT;
				in.putback(ch);
			}
			else {
				in.putback(ch);
				return LexItem(ICONST, lexeme, linenum);
			}
			break;//from ININT
		
		case INFLOAT:
				
			if( ch ==  '.' && isdigit(in.peek()) && !dec) {
				lexeme += ch;
				in.get(ch);
				lexeme += ch; 
				dec = true;
			}
			else if(isdigit(ch) && dec)
			{
				lexeme += ch;
			}
			else if(( ch == 'E' || ch == 'e' ) && dec ){
				nextch = in.peek();
				if(nextch == '+' || nextch == '-' || isdigit(nextch))
				{
					lexeme += ch;
					in.get(ch);
					lexeme += ch;
					
				}
				else
				{
					in.putback(ch);//put back E character
					return LexItem(FCONST, lexeme, linenum);
				}
			}
			else if((ch == '.') && dec && isdigit(in.peek())){
				lexeme += ch;
				
				return LexItem(ERR, lexeme, linenum);
			}
			else {
				in.putback(ch);
				
				return LexItem(FCONST, lexeme, linenum);
			}
			
			break;//from INFLOAT
			
		case INCOMMENT:
			if(ch == '\n') {
				linenum++;
				
				lexstate = START;
			}
			break;//from INCOMMENT
			
		case INSCOMPARE:
			char currentch = tolower(ch);
			
			nextchar = in.peek();
			nextchar = tolower(nextchar);
			if(currentch == 'e' && nextchar == 'q')
			{
				lexeme += ch;
				in.get(ch);
				currentch = tolower(ch);
				lexeme += ch;
				return LexItem(SEQ, lexeme, linenum);
			}
			else if(currentch == 'g' && nextchar == 't')
			{
				lexeme += ch;
				in.get(ch);
				currentch = tolower(ch);
				lexeme += ch;
				return LexItem(SGT, lexeme, linenum);
			}
			else if(currentch == 'l' && nextchar == 'e')
			{
				lexeme += ch;
				in.get(ch);
				currentch = tolower(ch);
				lexeme += ch;
				return LexItem(SLTE, lexeme, linenum);
			}
			else
			{
				return LexItem(ERR, lexeme, linenum);
			}
			break;//from INSCOMPARE
		}
	
	}//end of while loop
	
	if( in.eof() )
		return LexItem(DONE, "", linenum);
		
	return LexItem(ERR, "some strange I/O error", linenum);
}





