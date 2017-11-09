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
 * -generate by keyboard
 * -byte page size *
 */

int main() {

	Worker w;
	w.generateRandomFile("Unsorted", 5);
	w.sort2plus2("Unsorted");

	return 0;
}
