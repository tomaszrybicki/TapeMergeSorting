/*
 * Worker.h
 *
 *  Created on: Nov 6, 2017
 *      Author: Tomasz Rybicki
 */

#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

#include <string>
#include "Tape.h"

/* Class which offers general methods for performing sorting */
class Worker {
public:
	Worker();
	virtual ~Worker();

	/* Sorting using natural merging with 2+2 tape scheme */
	void sort2plus2(std::string tapeName);

	/* Creates file with random records */
	void generateRandomFile(std::string name, unsigned int recordCount);

	/* Enters user interface */
	void interface();

private:
	void interfaceGenerateFile();

	void interfaceKeyboardInput();

	void interfaceTextFile();

	void printMenu();

	double random(double min, double max);

	bool merge(Tape* inTape1, Tape* inTape2, Tape* tapeToRead, Tape* &currentOutTape,
			 Record* recordToMove);
	void distribute(Tape* inTape1, Tape* &otherOutTape, Tape* &currentOutTape,
			 Record* recordToMove);

	void printStatus(Tape* in1, Tape* out1, Tape* out2);

private:
	bool m_printInfo;

};

#endif /* SRC_WORKER_H_ */
