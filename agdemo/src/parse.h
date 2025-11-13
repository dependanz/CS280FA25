#ifndef agdemo_parse_h
#define agdemo_parse_h

#include "value.h"

extern bool exprlist(std::istream &input, int &linenum);
extern bool expr(std::istream &input, int &linenum, CalcValue &value);
extern bool num(std::istream &input, int &linenum, CalcValue &value);

#endif