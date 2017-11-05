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
#include "Tape.h"

using namespace std;

int main() {
	std::cerr << "Application started" << endl;

	RecordFile file("test");
	Tape tape("test");

	Record* a = new Record(1,1);
	Record* b = new Record(2,1);
	Record* c = new Record(3,1);
	Record* d = new Record(4,1);
	Record* e = new Record(5,1);


	tape.putRecord(a);
	tape.putRecord(b);
	tape.putRecord(c);
	tape.putRecord(d);
	tape.putRecord(e);

	/* TODO: consider one buffer, flush? */

	cerr << "Putted now poping" << std::endl;

	tape.popNextRecord();
	tape.popNextRecord();
	tape.popNextRecord();
	tape.popNextRecord();
	tape.popNextRecord();

	tape.popNextRecord();

	cerr << "Closing application" << endl;
	return 0;
}
