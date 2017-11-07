/*
 * Worker.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: Tomasz Rybicki
 */

#include "Worker.h"
#include "Tape.h"
#include <time.h>

Worker::Worker() {
	srand(time(NULL));
}

Worker::~Worker() {
}

void Worker::sort2plus2(std::string tapeName) {
	/* Open original unsorted tape */
	Tape* original = new Tape(tapeName, USE_EXISTING_FILE);
	original->print();

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
		std::cout<<record->getVolume()<<std::endl;
		if(record->getVolume() >= currentTape->getLastPutValue()){
			currentTape->putRecord(record);

		/* Start writing to other tape if end of series */
		}else{
			std::swap(currentTape, otherTape);
			currentTape->putRecord(record);
		}
	}

	tape1->print();
	tape2->print();

	tape1->rewind();
	tape2->rewind();

	double value3;
	double value4;

	/* While we have records to distribute */
	while(tape3->getNextRecordValue() != END_OF_TAPE
			&& tape4->getNextRecordValue() != END_OF_TAPE){

		/* Distribute */
		value1 =

	}


	delete tape1;
	delete tape2;

	//REWIND TAPE
	//DELETES!

}

void Worker::generateRandomFile(std::string name, unsigned int recordCount) {
	Tape* tape = new Tape(name, NEW_TAPE);
	Record* record;
	double height, radius;

	for (unsigned int i = 0;  i < recordCount; i++) {
		height = Worker::random(MIN_HEIGHT, MAX_HEIGHT);
		radius = Worker::random(MIN_RADIUS, MAX_RADIUS);

		record = new Record(height, radius);
		tape->putRecord(record);
	}

	delete tape;
}

double Worker::random(double min, double max){
	/* Generate [0:1] */
	double fraction = (double)rand() / RAND_MAX;

	/* Set min and max */
	return (min + fraction * (max - min));
}
