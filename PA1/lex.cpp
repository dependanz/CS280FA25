#include <iostream>
#include "lex.h"

using namespace std;

ostream& operator<<(ostream& out, const LexItem& tok) {
    return (out << tok.GetLexeme() << " : " << tok.GetToken() << " : " << tok.GetLinenum());
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    // not correct code, keywords are case-insensitive
    if (lexeme == "println") {
        return LexItem(PRINTLN, lexeme, linenum);
    }
    return LexItem(IDENT, lexeme, linenum);
}

LexItem delimiter(char& c, int linenum) {
    switch(c) {
        case ',':
            return LexItem(COMMA, ",", linenum);
        case ';':
            return LexItem(SEMICOL, ";", linenum);
        case '(':
            return LexItem(LPAREN, "(", linenum);
        case ')':
            return LexItem(RPAREN, ")", linenum);
        case '{':
            return LexItem(LBRACES, "{", linenum);
        case '}':
            return LexItem(RBRACES, "}", linenum);
        default:
            return LexItem();
    }
}

enum TokState {
    START,
    IN_IDENT,
    IN_ERR
};

LexItem getNextToken(istream& in, int& linenum) {
    char c = 0;
    string lexeme = "";
    LexItem returnToken;
    TokState lexstate = TokState::START;

    // Skip whitespace
    while(isspace(c = in.get())) {}

    // Skip comment lines
    if (c == '#') {
        while((c = in.get()) != '\n') {}
        linenum += 1;
        return getNextToken(in, linenum);
    }

    // Check if delimiter char or EOF.
    returnToken = delimiter(c, linenum);
    if(returnToken.GetToken() != ERR) {
        return returnToken;
    } else if(c == EOF) {
        return LexItem(DONE, "", linenum);
    } else {
        // Else put back into in stream
        in.putback(c);
    }

    while(in.get(c)) {
        // Check if whitespace or delimiter, put back if it is.
        if(isspace(c) || delimiter(c, linenum).GetToken() != ERR) {
            in.putback(c);
            break;
        }
       
        // Add current char to lexeme
        lexeme += c;

        // Tokenize based on derivation rules of terminal symbols.
        switch(lexstate) {
            case TokState::START:
                // Check if first char is letter or '_'
                if(isalpha(c) || c == '_') {
                    lexstate = TokState::IN_IDENT;
                } else {
                    /*
                        Whole bunch of other checks for the rest of
                        the terminals, but for now, this demo is for
                        identifiers. Assume everything else is ERR.
                    */
                    lexstate = TokState::IN_ERR;
                }
                break;
            case TokState::IN_IDENT:
                // Check if not valid identifier
                if(!isalnum(c) && c != '_') {
                    // Check if whitespace or delimiter, put back if it is.
                    if(isspace(c) || delimiter(c, linenum).GetToken() != ERR) {
                        in.putback(c);
                    } else {
                        lexstate = TokState::IN_ERR;
                    }
                }
                break;
            case TokState::IN_ERR:
                // Read the rest of the chars until whitespace or EOF
                c = in.get();
                while(!isspace(c) && c != EOF) {
                    lexeme += c;
                    c = in.get();
                }
                in.putback(c);
                break;
        }
    }

    // Check if identifier, and call id_or_kw
    if(lexstate == TokState::IN_IDENT) {
        return id_or_kw(lexeme, linenum);
    }

    // Default error token.
    return LexItem(ERR, lexeme, linenum);
}