#include <iostream>
#include <fstream>


using namespace std;


int main(int argc, char **argv) {
    char c;
    int num_cats = 0;


    // Check arg count
    if(argc != 2) {
        cout << "usage: demo <filename>" << endl;
        return -1;
    }


    // Read file
    ifstream inFile;
    inFile.open(argv[1], ios_base::in);


    // Check if open is successful
    if(inFile.fail()) {
        cout << "ERROR::FILE - Opening file unsuccessful" << endl;
        return -1;
    }


    // Count the cats
    c = 0;
    while(c != EOF) {
        // Skip whitespace
        c = inFile.get();
        if(isspace(c)) continue;


        // Check if first char is '\'
        if(c != '\\') continue;
        c = inFile.get();


        // Check if the next 3 is 'c' 'a' 't'
        if(c != 'c') continue;
        c = inFile.get();
        if(c != 'a') continue;
        c = inFile.get();
        if(c != 't') continue;


        // If next char is not whitespace, don't count and skip until whitespace
        c = inFile.get();
        if(!isspace(c) && c != EOF) {
            while(!isspace(c) && c != EOF) {
                c = inFile.get();
            }
        } else {
            num_cats += 1;
        }
    }


    inFile.close();


    cout << "There are " << num_cats << " \"\\cats\" in the dog house..." << endl;


    return 0;
}
