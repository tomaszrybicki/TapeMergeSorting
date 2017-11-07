//============================================================================
// Name        : main.cpp
// Author      : Tomasz Rybicki
// Version     : 1.0
// Description : Entry point of the application. The application
// 				 demonstrates 2+2 natural merge sorting of tapes
//============================================================================

#include <iostream>
#include "RecordFile.h"
#include "Tape.h"
#include "Record.h"
#include "Buffer.h"
#include "Worker.h"

using namespace std;

/* TODO:
 * -binary files
 * -pagefile counter
 * -generate files
 * -byte page size
 * -wEOF vs end of series detection?
 */

int main() {
	std::cerr << "Application started" << endl;

	Worker w;
	//w.generateRandomFile("unsorted", 10);
	w.sort2plus2("unsorted");

	//delete tape;
	cerr << "Closing application" << endl;
	return 0;
}
