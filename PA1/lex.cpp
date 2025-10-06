#include <iostream>
#include "lex.h"

using namespace std;

ostream& operator<<(ostream& out, const LexItem& tok) {
    return (out << tok.GetLexeme() << " : " << tok.GetToken() << " : " << tok.GetLinenum());
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    return LexItem();
}

LexItem getNextToken(istream& in, int& linenum) {
    char c = 0;
    string lexeme;
    // Skip whitespace
    while(isspace(c = in.get())) {}

    // If comment, skip rest of line
    if(c == '#') {
        while((c = in.get()) != '\n') {}
        return getNextToken(in, linenum);
    }

    // [start] Read token
    
    // [end]
}