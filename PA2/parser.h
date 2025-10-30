/* Implementation of Recursive-Descent Parser
 * for the Basic Perl-Like Language (BPL)
 * parse.h
 * Programming Assignment 2
 * Fall 2025
*/

#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>

using namespace std;

#include "lex.h"



extern bool Prog(istream& in, int& line);
extern bool StmtList(istream& in, int& line);
extern bool Stmt(istream& in, int& line);
extern bool PrintLnStmt(istream& in, int& line);
extern bool IfStmt(istream& in, int& line);
extern bool AssignStmt(istream& in, int& line);
extern bool Var(istream& in, int& line);
extern bool ExprList(istream& in, int& line);
extern bool Expr(istream& in, int& line);
extern bool AssigOp(istream& in, int& line);
extern bool OrExpr(istream& in, int& line);
extern bool AndExpr(istream& in, int& line);
extern bool RelExpr(istream& in, int& line);
extern bool AddExpr(istream& in, int& line);
extern bool MultExpr(istream& in, int& line);
extern bool UnaryExpr(istream& in, int& line);
extern bool ExponExpr(istream& in, int& line, int sign);
extern bool PrimaryExpr(istream& in, int& line, int sign);
extern int ErrCount();

#endif /* PARSE_H_ */
