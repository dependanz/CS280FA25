#include <math.h>
#include <string>
#include <iostream>

using namespace std;

string remainder2str(int remainder) {
    if (remainder < 0) throw "Invalid remainder";
    if (remainder < 10) return to_string(remainder);
    return string(1, 'A' + (remainder - 10));
}

string DecToBaseN(int num, int base) {
    // [Implement this with recursion]
}