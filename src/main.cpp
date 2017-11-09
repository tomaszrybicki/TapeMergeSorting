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

int fileReads = 0;
int fileWrites = 0;

int main() {

	Worker w;
	w.interface();

	return 0;
}
