#include <fstream>
#include <string>
#include <iostream>
#include "lexer.h"
#include "parse.h"

namespace Parser {
    LexItem pushBackToken;
    bool pushedBack = false;

    LexItem NextToken(std::istream &input, int &linenum) {
        if(pushedBack) {
            pushedBack = false;
            return pushBackToken;
        }

        // Skip Whitespace
        char ch;
        while (input.get(ch)) {
            if (ch == '\n') {
                linenum++;
            }
            if (!isspace(ch)) {
                input.putback(ch);
                break;
            }
        }

        // EOF check
        if (input.eof()) {
            return LexItem(DONE, linenum, "");
        }

        std::string lexeme;
        
        // Single char check
        ch = input.get();
        lexeme += ch;
        if(isspace(input.peek()) || input.eof()) {
            if (ch == ';') {
                return LexItem(SEMICOLON, linenum, lexeme);
            } else if (ch == '+') {
                return LexItem(PLUS, linenum, lexeme);
            } else {
                return LexItem(ERR, linenum, lexeme);
            }
        }

        // DFA
        LexerState state = START;
        while(true) {
            switch(state) {
                case START:
                    if(ch == '+' || ch == '-') {
                        ch = input.get();
                        lexeme += ch;   // Since next char is guaranteed nonspace
                    }
                    if(ch == '.') {
                        state = INREAL;
                    } else if (isdigit(ch)) {
                        state = ININT;
                    }
                    if(state == START) {
                        state = INERR;
                    }
                    break;
                case ININT:
                    ch = input.get();
                    if(isspace(ch) || ch == ';' || ch == '+' || ch == EOF) {
                        input.putback(ch);
                        return LexItem(INT, linenum, lexeme);
                    }
                    if(ch == '.') {
                        state = INREAL;
                    } else if (!isdigit(ch)) {
                        state = INERR;
                    }
                    lexeme += ch;

                    break;
                case INREAL:
                    ch = input.get();
                    if(isspace(ch) || ch == ';' || ch == '+' || ch == EOF) {
                        input.putback(ch);
                        return LexItem(REAL, linenum, lexeme);
                    }
                    if(ch == 'e' || ch == 'E') {
                        state = INERR;
                    }
                    if(!isdigit(ch)) {
                        state = INERR;
                    }
                    lexeme += ch;
                    break;
                case INERR:
                default:
                    // Read the rest of the lexeme
                    while(!isspace(input.peek()) && !input.eof()) {
                        ch = input.get();
                        lexeme += ch;
                    }
                    return LexItem(ERR, linenum, lexeme);
            }
        }
        return LexItem(ERR, linenum, lexeme);
    }

    void PushBack(LexItem token) {
        if(pushedBack) {
            throw std::runtime_error("Cannot push back more than one token");
        }
        pushBackToken = token;
        pushedBack = true;
    }
};

// exprlist: expr ; [exprlist]
bool exprlist(std::istream &input, int &linenum) {
    CalcValue value;
    bool result = expr(input, linenum, value);
    if(!result) return false;

    // "Predicate validation" at exprlist (static semantic error message within expr)
    if(value.getType() == VALUE_ERROR) return false;

    // An example of a "dynamic semantic" : to print evaluated expression to console
    std::cout << value << std::endl;

    LexItem token = Parser::NextToken(input, linenum);
    if(token.getToken() != SEMICOLON) {
        std::cout << "Error: missing semicolon at line " << linenum + 1 << std::endl;
        return false;
    }

    token = Parser::NextToken(input, linenum);
    if(token.getToken() != DONE) {
        Parser::PushBack(token);
        result = exprlist(input, linenum);
        if(!result) return false;
    }

    return true;
}

// expr: num + num | num
bool expr(std::istream &input, int &linenum, CalcValue &value) {
    CalcValue value2;
    bool result = num(input, linenum, value);
    if(!result) return false;
    if(value.getType() == VALUE_ERROR) return false;

    LexItem token = Parser::NextToken(input, linenum);
    if(token.getToken() == PLUS) {
        bool result = num(input, linenum, value2);
        if(!result) return false;

        // Synthesized attribute (using overloaded '+' operator)
        value = value + value2;
        if(value.getType() == VALUE_ERROR) return false;
    } else {
        Parser::PushBack(token);
    }
    return true;
}

// num: INT | REAL
bool num(std::istream &input, int &linenum, CalcValue &value) {
    LexItem token = Parser::NextToken(input, linenum);
    switch(token.getToken()) {
        case INT:
            // stol "string to long"
            value = CalcValue(std::stol(token.getLexeme()));
            break;
        case REAL:
            // stod "string to double"
            value = CalcValue(std::stod(token.getLexeme()));
            break;
        default:
            value = CalcValue();
            return false;
    }
    return true;
}