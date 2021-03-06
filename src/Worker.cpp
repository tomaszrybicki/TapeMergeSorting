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
	m_printInfo = false;
}

Worker::~Worker() {
}

void Worker::sort2plus2(string tapeName) {
	/* Open original unsorted tape */
	Tape* original = new Tape(tapeName, USE_EXISTING_FILE);

	cout << "Before sorting:" << endl;
	original->print();

	/* Create 2+2 tapes */
	Tape* tape1 = new Tape("File1.bin", original);
	Tape* tape2 = new Tape("File2.bin", NEW_TAPE);
	Tape* tape3 = new Tape("File3.bin", NEW_TAPE);

	/* Original was copied to tape1 and can be released */
	delete original;

	Record* recordToMove = NULL;
	Tape* inTape = tape1;
	Tape* outTape1 = tape2;
	Tape* outTape2 = tape3;
	Tape* tapeToRead = NULL;

	bool isSorted=true;


	/* While during merge we had more than one series */
	int phase = 0;
	do{
		phase++;
		isSorted = true;

		/* While there is at least one record in the input tape */
		while(inTape->getNextRecordValue() != END_OF_TAPE){
			distribute(inTape, outTape1, outTape2, recordToMove);
		}

		inTape->rewind();

		/* While there is at least one record to merge */
		while(outTape1->getNextRecordValue() != END_OF_TAPE
				|| outTape2->getNextRecordValue() != END_OF_TAPE){

			/* If there was more than one series, tape is not sorted */
			if(!merge(outTape1, outTape2, tapeToRead, inTape, recordToMove)){
				isSorted = false;
			}

		}

		if(m_printInfo){
				cout << endl << "After phase: " << phase << endl;
				printStatus(inTape, outTape1, outTape2);
		}

		outTape1->rewind();
		outTape2->rewind();

	}while(!isSorted);
	/* We have sorted the tape */

	cout << "After sorting: " << endl;
	inTape->print();
	cout << "File reads: " << fileReads << " file writes: " << fileWrites << " phases: " << phase << endl;

	delete tape1;
	delete tape2;
	delete tape3;
}

void Worker::generateRandomFile(string name, unsigned int recordCount) {
	Tape* tape = new Tape(name, NEW_TAPE);
	Record* record;
	double height, radius;

	for (unsigned int i = 0;  i < recordCount; i++) {
		height = Worker::random(MIN_HEIGHT, MAX_HEIGHT);
		radius = Worker::random(MIN_RADIUS, MAX_RADIUS);

		record = new Record(height, radius);
		if(!tape->putRecord(record)){
			delete record;
			break;
		}
	}

	delete tape;
}

bool Worker::merge(Tape* inTape1, Tape* inTape2, Tape* tapeToRead, Tape* &currentOutTape, Record* recordToMove) {

	/* Choose a tape to read which has smallest value */
	double value1 = inTape1->getNextRecordValue();
	double value2 = inTape2->getNextRecordValue();
	double lastValue = currentOutTape->getLastPutValue();
	bool isSeriesKept = true;

	/* Don't use empty tape */
	if(value1 == END_OF_TAPE){
		tapeToRead = inTape2;
	}else if (value2 == END_OF_TAPE){
		tapeToRead = inTape1;

	/* Both values from input tapes are continuing series */
	}else if(value1 >= lastValue && value2 >= lastValue){

		/* Choose tape with smaller value */
		if(value1 < value2){
			tapeToRead = inTape1;
		}else{
			tapeToRead = inTape2;
		}

	/* None of the input values continues series */
	}else if(value1 < lastValue && value2 < lastValue){

		/* Choose tape with smaller value */
		if(value1 < value2){
			tapeToRead = inTape1;
		}else{
			tapeToRead = inTape2;
		}

	/* Only one input value continues series */
	}else{
		if(value1 >= lastValue){
			tapeToRead = inTape1;
		}else{
			tapeToRead = inTape2;
		}
	}

	/* Get the record */
	recordToMove = tapeToRead->popNextRecord();

	if(recordToMove->getVolume() < currentOutTape->getLastPutValue()){
		isSeriesKept = false;
	}

	currentOutTape->putRecord(recordToMove);

	return isSeriesKept;
}

void Worker::distribute(Tape* inTape, Tape* &otherOutTape, Tape* &currentOutTape,
		 Record* recordToMove) {

	double value;

	/* Get the record */
	recordToMove = inTape->popNextRecord();

	value = currentOutTape->getLastPutValue();

	/* Write the record to current outTape if it continues series */
	if (recordToMove->getVolume() >= value){
		currentOutTape->putRecord(recordToMove);
	}else{
		swap(currentOutTape, otherOutTape);
		currentOutTape->putRecord(recordToMove);
	}
}

void Worker::interface() {
	char input = 0;

	while (input != '6'){
		do
		{
			cin.sync();
			cin.clear();
			printMenu();
			cin >> input;
		}
		while( !cin.fail() && input!='1' && input!='2' && input!='3' && input!='4' && input!='5' && input!='6' );

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
			sort2plus2(DEFAULT_NAME);
			break;

		case '5':
			interfaceTextFile();
			break;

		case '6':
			return;

		}
	}
}

void Worker::printMenu() {
	cout << endl << "Press the key with chosen option: " << endl;
	cout << "1) Generate file with random records" << endl;
	cout << "2) Generate file with keyboard input" << endl;
	cout << "3) Toggle printing sorting info (currently: " << m_printInfo << ")" << endl;
	cout << "4) Sort the file" << endl;
	cout << "5) Load a text test file" << endl;
	cout << "6) Exit" << endl;
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

	generateRandomFile(DEFAULT_NAME, input);

	cout << "Generated random file " << DEFAULT_NAME << endl << endl;
}

void Worker::interfaceKeyboardInput() {
	std::string input;
	double radius, height;
	Record* newRecord;
	Tape* newTape = new Tape(DEFAULT_NAME, NEW_TAPE);

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

void Worker::interfaceTextFile() {
	std::string input;

	cin.sync();
	cin.clear();
	cout << "Enter the name of the test file" << endl;
	cout << "> ";
	cin >> input;

	Tape::textToBinary(input);

	cout << "Loaded test file: " << input << endl << endl;
}


void Worker::printStatus(Tape* in1, Tape* out1, Tape* out2) {
	cout << "Input Tape 1:\t";
	in1->print();
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
