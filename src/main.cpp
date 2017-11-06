//============================================================================
// Name        : main.cpp
// Author      : Tomasz Rybicki
// Version     : 1.0
// Description : Entry point of the application. The application
// 				 demonstrates 2+2 natural merging sorting of tapes
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
 * -add clearing file?
 */

int main() {
	std::cerr << "Application started" << endl;
//
//	Tape* tape = new Tape("test", NEW_TAPE);
////
//	Record* created;
//	Record* read;
//
//
//	for(int i =10 ; i>0; i--){
//		created = new Record(1,i);
//		tape->putRecord(created);
//	}
//
//	cerr << "Putted now poping" << std::endl;
//
//	for(int i =1 ; i<10; i++){
//		read = tape.popNextRecord();
//
//		if(read){
//			cout << read->getRadius() << endl;
//		}else{
//			cout <<"End of file";
//		}
//	}

	Worker w;
	w.sort2plus2("test");

//delete tape;
	cerr << "Closing application" << endl;
	return 0;
}
