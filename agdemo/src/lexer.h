#ifndef agdemo_lexer_h
#define agdemo_lexer_h

#include <string>

enum Token {
    INT, REAL, PLUS, SEMICOLON, ERR, DONE
};

enum LexerState {
    START, ININT, INREAL, INERR
};

class LexItem {
private:
    Token token;
    int linenum;
    std::string lexeme;

public:
    LexItem() : token(ERR), linenum(0), lexeme("") {}
    LexItem(Token t, int line, const std::string &lex) : token(t), linenum(line), lexeme(lex) {}

    Token getToken() const { return token; }
    int getLinenum() const { return linenum; }
    std::string getLexeme() const { return lexeme; }
    
    friend std::ostream& operator<<(std::ostream &os, const LexItem &item) {
        os << "<" << item.lexeme << ">(" << item.token << ", " << item.linenum << ")";
        return os;
    }
};

#endif