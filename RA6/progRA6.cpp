#include <iostream>
#include <string>
#include <fstream>
#include "DecToBaseN.cpp"  // [C/C++ Note] This include of straight *.cpp is considered bad practice, but still valid to do.
using namespace std;
string DecToBaseN(int num, int base);

int main(int argc, char *argv[])
{
	int dec, base ;
	
	ifstream  file ;

	if (argc == 1)
	{
		cerr << "NO SPECIFIED INPUT FILE." << endl;
		return 0;
	}
	else
	{
		file.open(argv[1]);
		if( file.is_open() == false ) {
			cerr << "CANNOT OPEN THE FILE " << argv[1] << endl;
			return 0;
		}

	}
	
	file >> dec >> base;
	
	string str = DecToBaseN(dec, base);
	
	cout << "result of converting the decimal number " << dec << " to base " << base << ": " << "\"" 
		<< str << "\"" << endl;
}
