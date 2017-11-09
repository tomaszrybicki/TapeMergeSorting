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

	/* Create 2+2 tapes */
	Tape* tape1 = new Tape("File1", original);
	Tape* tape2 = new Tape("File2", NEW_TAPE);
	Tape* tape3 = new Tape("File3", NEW_TAPE);
	Tape* tape4 = new Tape("File4", NEW_TAPE);

	tape1->print();

	/* Original was copied to tape1 and can be released */
	delete original;

	/* We start off using tape1(original) and tape2 (empty)
	 *  as tapes which are read */
	Record* recordToMove;
	Tape* inTape1 = tape1;
	Tape* inTape2 = tape2;
	Tape* currentOutTape = tape3;
	Tape* otherOutTape = tape4;
	Tape* tapeToRead;


	/* While we have two non-empty input tapes that need merging == unsorted */
	int phase = 0;
	do{
		phase++;

		/* While there is at least one record in any of input tapes */
		while(inTape1->getNextRecordValue() != END_OF_TAPE
				|| inTape2->getNextRecordValue() != END_OF_TAPE){
			distribute(inTape1, inTape2, tapeToRead, currentOutTape, otherOutTape, recordToMove);
		}

		std::cout << std::endl << "After phase: " << phase << std::endl;
		printStatus(inTape1, inTape2, currentOutTape, otherOutTape);

		/* Swap outTapes with inTapes for another phase*/
		inTape1->rewind();
		inTape2->rewind();
		std::swap(inTape1, currentOutTape);
		std::swap(inTape2, otherOutTape);

	}while(inTape1->getNextRecordValue() != END_OF_TAPE
			&& inTape2->getNextRecordValue() != END_OF_TAPE);



	/* We have sorted the tape */
	std::cout << std::endl << "After sorting" << std::endl;
	printStatus(inTape1, inTape2, currentOutTape, otherOutTape);

	delete tape1;
	delete tape2;
	delete tape3;
	delete tape4;
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

void Worker::distribute(Tape* inTape1, Tape* inTape2, Tape* tapeToRead, Tape* currentOutTape,
		Tape* otherOutTape, Record* recordToMove) {

	/* Choose a tape to read which has smallest value */
	double value1 = inTape1->getNextRecordValue();
	double value2 = inTape2->getNextRecordValue();

	if ((value1 <= value2 && value1 != END_OF_TAPE) || value2 == END_OF_TAPE){
		tapeToRead = inTape1;
	}else{
		tapeToRead = inTape2;
	}

	/* Get the record */
	recordToMove = tapeToRead->popNextRecord();

	value1 = currentOutTape->getLastPutValue();
	value2 = otherOutTape->getLastPutValue();

	/* Write the record to current outTape if it continues series */
	if (recordToMove->getVolume() >= value1){
		currentOutTape->putRecord(recordToMove);
	}else{
		std::swap(currentOutTape, otherOutTape);
		currentOutTape->putRecord(recordToMove);
	}
}

void Worker::printStatus(Tape* in1, Tape* in2, Tape* out1, Tape* out2) {
	std::cout << "Input Tape 1:\t";
	in1->print();
	std::cout << "Input Tape 2:\t";
	in2->print();
	std::cout << "Output Tape 1:\t";
	out1->print();
	std::cout << "Output Tape 2:\t";
	out2->print();
}

double Worker::random(double min, double max){
	/* Generate [0:1] */
	double fraction = (double)rand() / RAND_MAX;

	/* Set min and max */
	return (min + fraction * (max - min));
}
