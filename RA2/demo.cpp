#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char      **      argv) {
    ifstream inStream;

    inStream.open("dog_breeds.txt");

    // string str;
    // inStream >> str;

    char c;
    int largestDogLength = 0;
    while(!inStream.eof()) {
        string line;
        c = inStream.get();

        // Another loop for processing the entire line
        while(c != '\n' && !inStream.eof()) {
            line += c;
            c = inStream.get();
        }
        cout << line << " : " << line.length() << endl;

        // Keep track of longest line
        if(line.length() > largestDogLength)
            largestDogLength = line.length();
    }

    // Print out your stats
    cout << "Largest Dog Length: " << largestDogLength << endl;
    
    return 0;
}