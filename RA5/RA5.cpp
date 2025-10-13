#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

class Word {
private:
    int numVowels;
    string lexeme;

public:
    Word() {
        numVowels = -1;
    }
    Word(string lexeme) {
        this->lexeme = lexeme;
        for(char c : lexeme) {
            if(isVowel(c)) {
                numVowels++;
            }
        }
    }

    // Getters
    int getNumVowels() const { return numVowels; }
    string getLexeme() const { return lexeme; }

    // Setters
    void setNumVowels(int numVowels) { this->numVowels = numVowels; }
    void setLexeme(string lexeme) { this->lexeme = lexeme; }
};

enum NextWordStatus {
    GOT_WORD,
    GOT_ERROR,
    GOT_EOF
};

NextWordStatus getNextWord(istream& inStream, Word& nextWord) {
    char c = 0;
    string lexeme = "";
    // Skip whitespace
    while(isspace(c = inStream.get())) {}
    // Check for EOF
    if(inStream.eof()) {
        return GOT_EOF;
    }

    // Scan chars until space, or eof
    int numVowels = 0;
    while(!isspace(c) && !inStream.eof()) {
        lexeme += c;
        if (isVowel(c)) numVowels++;
        c = inStream.get();
    }

    // Return by reference nextWord
    nextWord.setLexeme(lexeme);
    nextWord.setNumVowels(numVowels);

    return GOT_WORD;
}

int main(int argc, char** argv) {
    string filename; 
    bool vow1Flag = false;

    // CLI Args
    if(argc < 2) {
        cout << "Error: Usage - ra5 <filename> [-all | -vow1 | -vow2 | -vow3]" << endl;
        return -1;
    }
    
    string arg;
    filename = argv[1];
    for(int i = 2; i < argc; i++) {
        arg = argv[i];
        if(arg == "-vow1") {
            vow1Flag = true;
        }

        // Do the rest...
    }

    // Open fstream
    ifstream inStream(filename, ios::in);
    if(inStream.fail()) {
        cout << "Error: Cannot open file \"" << filename << "\"" << endl;
        return -1;
    }

    /**
     *  Initialize Maps
     */
    // wordMap: maps integer keys to a map (from strings to ints) as a value)
    map<int, map<string, int>> wordMap;

    // Read words; collect stats
    Word nextWord;
    while(getNextWord(inStream, nextWord) != GOT_EOF) {
        wordMap[nextWord.getNumVowels()][nextWord.getLexeme()]++;
    }

    // Print vowel counts
    for(auto it1 : wordMap) {
        int numVowels = it1.first;
        map<string, int> words = it1.second;

        cout << "Words with " << numVowels << " vowels:" << endl;
        for(auto it2 : words) {
            string lexeme = it2.first;
            int count = it2.second;

            cout << "  " << lexeme << ": " << count << endl;
        }
    }

    inStream.close();

    return 0;
}