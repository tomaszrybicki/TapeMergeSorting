//============================================================================
// Name        : main.cpp
// Author      : Tomasz Rybicki
// Version     : 1.0
// Description : Entry point of the application. The application
// 				 demonstrates 2+2 natural merging sorting of tapes
//============================================================================

#include <iostream>
#include "Record.h"
#include "RecordFile.h"
#include "Buffer.h"

using namespace std;

int main() {
	std::cerr << "Application started" << endl;

	Buffer buffer(3);
	RecordFile file("test");

	Record* a = new Record(1,1);
	Record* b = new Record(2,1);
	Record* c = new Record(3,1);
	Record* d = new Record(4,1);

	cout << buffer.putRecord(a) << endl;
	cout << buffer.putRecord(b) << endl;
	cout << buffer.putRecord(c) << endl;
	cout << buffer.putRecord(d) << endl;

	file.writeBuffer(&buffer);


	cerr << "Closing application" << endl;
	return 0;
}
