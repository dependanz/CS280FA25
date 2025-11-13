/**
 * See agdemo.lang for the simple grammar that this
 * program accepts
 */

#include <fstream>
#include <iostream>

#include "lexer.h"
#include "parse.h"

using namespace std;

int main(int argc, char **argv)
{
    // [Parse Args]
    if (argc != 2) {
        cout << "Usage: calc <input-file>" << endl;
        return -1;
    }

    // [Open file]
    ifstream inputFile(argv[1]);
    if (inputFile.fail()) {
        cout << "Error: could not open file " << argv[1] << endl;
        return -1;
    }

    // [Parser] Call exprlist(...)
    int linenum = 0;
    bool result = exprlist(inputFile, linenum);

    // [Result]
    if (result) {
        cout << "Parsing completed successfully, total lines: " << linenum + 1 << endl;
    } else {
        cout << "Parsing failed, line: " << linenum + 1 << "." << endl;
    }

    // [optional clean up]
    inputFile.close();

    return 0;
}