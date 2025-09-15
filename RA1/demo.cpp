// Danzel Serrano
// ds867
// CS 280-011

#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    // argc // # of arguments given 
    // argv[...] // a string array of the arguments
    
    // g++ demo.cpp -o demo2.exe
    // argv[0] = "g++"
    // argv[1] = "demo.cpp"
    // argv[2] = "-o"
    // argv[3] = "demo2.exe"

    // if(argc < 2) {
    //     cout << "Usage: g++ <source_code>";
    //     return -1; // bad execution
    // }

    cout << "What's your name? >>";
    
    string name;
    cin >> name;

    cout << "Hello, " << name << "!" << endl;

    return 0;
}