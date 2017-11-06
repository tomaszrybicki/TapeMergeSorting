/*
 * Worker.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: Tomasz Rybicki
 */

#include "Worker.h"
#include "Tape.h"

Worker::Worker() {
	// TODO Auto-generated constructor stub

}

Worker::~Worker() {
	// TODO Auto-generated destructor stub
}

void Worker::sort2plus2(std::string tapeName) {
	/* Open original unsorted tape */
	Tape* original = new Tape(tapeName, USE_EXISTING_FILE);

	/* Create 2+2 tapes */
	Tape* tape1 = new Tape("tape1", NEW_TAPE);
	Tape* tape2 = new Tape("tape2", NEW_TAPE);
	Tape* tape3 = new Tape("tape3", NEW_TAPE);
	Tape* tape4 = new Tape("tape4", NEW_TAPE);

	Record* record;

	Tape* currentTape = tape1;
	Tape* otherTape = tape2;

	/* First distribution */
	while( (record = original->popNextRecord()) ){

		if(record->getVolume() >= currentTape->getLastPutValue()){
			currentTape->putRecord(record);

		/* Start writing to other tape if end of series */
		}else{
			std::swap(currentTape, otherTape);
			currentTape->putRecord(record);
		}
	}

	//REWIND TAPE
	//DELETES!

}
