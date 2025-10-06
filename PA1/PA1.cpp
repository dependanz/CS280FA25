#include <iostream>
#include <fstream>
#include <vector>
#include "lex.h"

using namespace std;

int main(int argc, char** argv) {
    char* filename; 
    bool verbose = false;
    bool numFlag = false;
    bool strFlag = false;
    bool idFlag  = false;

    // CLI Args
    if(argc == 1) {
        cout << "usage - PA1Demo <filename> [-v | -num | -str | -ids]" << endl;
        return -1;
    }
    
    // [start] Process filename and flags
    filename = argv[1];
    // ...
    // [end]

    // [start] Open input file stream
    ifstream fileStream(filename);
    // [end] 

    // [start] Call getNextToken until returns Token::DONE or Token::ERR
    vector<LexItem> identList;
    vector<LexItem> numList;
    vector<LexItem> strList;
    int linenum = 0;
    LexItem currentToken = getNextToken(fileStream, linenum);
    while(currentToken != DONE) {
        cout << currentToken << endl;
        switch(currentToken.GetToken()) {
            case IDENT:
                identList.push_back(currentToken);
                break;
            case ICONST:
            case FCONST:
                numList.push_back(currentToken);
                break;
            case SCONST:
                strList.push_back(currentToken);
                break;
        }
        currentToken = getNextToken(fileStream, linenum);
    }
    // [end]

    // [start] Print required info according to provided flags
    cout << "Demo, printing out all idents:" << endl;
    for(int i = 0; i < identList.size(); i++) {
        cout << i << ") \"" << identList[i] << "\"" << endl;
    }

    // [end]

    fileStream.close();

    return 0;
}