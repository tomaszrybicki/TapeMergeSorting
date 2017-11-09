/*
 * Worker.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: Tomasz Rybicki
 */

#include "Worker.h"
#include "Tape.h"
#include <time.h>

using namespace std;

Worker::Worker() {
	srand(time(NULL));
	m_printInfo = true;
}

Worker::~Worker() {
}

void Worker::sort2plus2(string tapeName) {
	/* Open original unsorted tape */
	Tape* original = new Tape(tapeName, USE_EXISTING_FILE);

	cout << "Before sorting" << endl;
	original->print();

	/* Create 2+2 tapes */
	Tape* tape1 = new Tape("File1.bin", original);
	Tape* tape2 = new Tape("File2.bin", NEW_TAPE);
	Tape* tape3 = new Tape("File3.bin", NEW_TAPE);
	Tape* tape4 = new Tape("File4.bin", NEW_TAPE);

	/* Original was copied to tape1 and can be released */
	delete original;

	/* We start off using tape1(original) and tape2 (empty)
	 *  as tapes which are read */

	Record* recordToMove = NULL;
	Tape* inTape1 = tape1;
	Tape* inTape2 = tape2;
	Tape* currentOutTape = tape3;
	Tape* otherOutTape = tape4;
	Tape* tapeToRead = NULL;


	/* While we have two non-empty input tapes that need merging == unsorted */
	int phase = 0;
	do{
		phase++;

		/* While there is at least one record in any of input tapes */
		while(inTape1->getNextRecordValue() != END_OF_TAPE
				|| inTape2->getNextRecordValue() != END_OF_TAPE){

			distribute(inTape1, inTape2, tapeToRead, currentOutTape, otherOutTape, recordToMove);

		}

		if(m_printInfo){
			cout << endl << "After phase: " << phase << endl;
			printStatus(inTape1, inTape2, currentOutTape, otherOutTape);
		}

		/* Swap outTapes with inTapes for another phase*/
		inTape1->rewind();
		inTape2->rewind();
		swap(inTape1, currentOutTape);
		swap(inTape2, otherOutTape);

	}while(inTape1->getNextRecordValue() != END_OF_TAPE
			&& inTape2->getNextRecordValue() != END_OF_TAPE);

	cout << "After sorting: " << endl;
	if(inTape1->getNextRecordValue() != END_OF_TAPE){
		inTape1->print();
	}else{
		inTape2->print();
	}
	cout << "File reads: " << fileReads << " file writes: " << fileWrites << endl;



	/* We have sorted the tape */
	delete tape1;
	delete tape2;
	delete tape3;
	delete tape4;
}

void Worker::generateRandomFile(string name, unsigned int recordCount) {
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
		swap(currentOutTape, otherOutTape);
		currentOutTape->putRecord(recordToMove);
	}
}

void Worker::interface() {
	char input = 0;

	while (input != '5'){
		do
		{
			cin.sync();
			cin.clear();
			printMenu();
			cin >> input;
		}
		while( !cin.fail() && input!='1' && input!='2' && input!='3' && input!='4' && input!='5' );

		switch(input){
		case '1':
			interfaceGenerateFile();
			break;

		case '2':
			interfaceKeyboardInput();
			break;

		case '3':
			m_printInfo = !m_printInfo;
			break;

		case '4':
			fileReads = 0;
			fileWrites = 0;
			sort2plus2("Unsorted.bin");
			break;

		case '5':
			return;

		}
	}
}

void Worker::printMenu() {
	cout << "Press the key with chosen option: " << endl;
	cout << "1) Generate file with random records" << endl;
	cout << "2) Generate file with keyboard input" << endl;
	cout << "3) Toggle printing sorting info (currently: " << m_printInfo << ")" << endl;
	cout << "4) Sort the file" << endl;
	cout << "5) Exit" << endl;
	cout << "> ";
}

void Worker::interfaceGenerateFile() {
	int input = 0;

	do
	{
		cin.sync();
		cin.clear();
		cout << "Enter the number of records to generate. Their radius and height will be a random number in (0.0 ; 10.0)" << endl;
		cout << "> ";
		cin >> input;
	}
	while( !cin.fail() && input <= 0 );

	generateRandomFile("Unsorted.bin", input);

	cout << "Generated random file Unsorted.bin" << endl << endl;
}

void Worker::interfaceKeyboardInput() {
	std::string input;
	double radius, height;
	Record* newRecord;
	Tape* newTape = new Tape("Unsorted.bin", NEW_TAPE);

	do
	{
		cin.sync();
		cin.clear();
		cout << endl << "Enter record radius ('Q' to quit): ";
		cin >> input;
		if(input == "Q"){
			break;
		}

		radius = atof(input.c_str());

		cout << "Enter record height ('Q' to quit): ";
		if(input == "Q"){
			break;
		}

		cin >> input;
		height = atof(input.c_str());

		/* Add record */
		cout << "Added record R: " << radius <<" H: " << height <<endl;
		newRecord = new Record(height, radius);
		newTape->putRecord(newRecord);

	}
	while( !cin.fail() );

	newTape->print();
	delete newTape;

}

void Worker::printStatus(Tape* in1, Tape* in2, Tape* out1, Tape* out2) {
	cout << "Input Tape 1:\t";
	in1->print();
	cout << "Input Tape 2:\t";
	in2->print();
	cout << "Output Tape 1:\t";
	out1->print();
	cout << "Output Tape 2:\t";
	out2->print();
	cout << "File reads: " << fileReads << " file writes: " << fileWrites << endl;

}

double Worker::random(double min, double max){
	/* Generate [0:1] */
	double fraction = (double)rand() / RAND_MAX;

	/* Set min and max */
	return (min + fraction * (max - min));
}
