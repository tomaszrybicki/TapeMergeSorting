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
		//std::cout<<record->getHeight() << " " << record->getRadius() << std::endl;
		if(record->getVolume() >= currentTape->getLastPutValue()){
			currentTape->putRecord(record);

		/* Start writing to other tape if end of series */
		}else{
			std::swap(currentTape, otherTape);
			currentTape->putRecord(record);
		}
	}

	//tape1->print();
	//tape2->print();

	tape1->rewind();
	tape2->rewind();

	double value1;
	double value2;

	Record* recordToMove;

	/* We start off using tape1 and tape2 as tapes which are read */
	Tape* inTape1 = tape1;
	Tape* inTape2 = tape2;
	Tape* currentOutTape = tape3;
	Tape* otherOutTape = tape4;

	Tape* tapeToWrite;
	Tape* tapeToRead;

	/* While we have records to distribute */
	while(inTape1->getNextRecordValue() != END_OF_TAPE
			&& inTape2->getNextRecordValue() != END_OF_TAPE){

		/* Choose a tape to read which has smallest value */
		value1 = inTape1->getNextRecordValue();
		value2 = inTape2->getNextRecordValue();

		if (value1 <= value2){
			tapeToRead = inTape1;
		}else{
			tapeToRead = inTape2;
		}

		/* Get the record */
		recordToMove = tapeToRead->popNextRecord();

		/* Write the record to current outTape if it continues series */

		/* value1 now shows value of first element in currentOutTape*/
		value1 = currentOutTape->getLastPutValue();
		value2 = otherOutTape->getLastPutValue();

		/* TODO: optimize code */
		if (recordToMove->getVolume() >= value1){
			currentOutTape->putRecord(recordToMove);
		}else{
			std::swap(currentOutTape, otherOutTape);
			currentOutTape->putRecord(recordToMove);
		}

		/* Swap outTapes with inTapes for another phase*/
		inTape1->rewind();
		inTape2->rewind();

		std::swap(inTape1, currentOutTape);
		std::swap(inTape2, otherOutTape);
	}

	/* We have sorted the tape */
	inTape1->print();
	inTape2->print();


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
