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
 * - Fix large files
 */

int fileReads = 0;
int fileWrites = 0;

int main() {

	Worker w;
<<<<<<< HEAD
	w.interface();
=======
	w.generateRandomFile("Unsorted", 5);
	w.sort2plus2("Unsorted");
>>>>>>> 38206e77a39f12be1c8d4125a674935d36ff7148

	return 0;
}
