/*
 *	Tape.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef TAPE_H_
#define TAPE_H_

#define KiB 1024
#define BUFFER_SIZE 4 //* KiB

#define END_OF_TAPE -1

#include "Record.h"
#include "RecordFile.h"
#include "Buffer.h"

/*
 * Tape represents a block device slow enough to need
 * buffering as well as sorting algorithms that
 * use mostly sequential access as random access
 * introduces too big latency.
 *
 * It is implemented as a regular file with
 * database records. Reads and writes are buffered
 * to maximize performance
 */
class Tape {
public:
	Tape(std::string name);
	virtual ~Tape();

	/* Return the sorting value of next pointed record
	 *  without removing it. Returns END_OF_TAPE on empty tape */
	double getNextRecordValue();

	/* Return next record and remove it from the tape
	 * returns 0 on empty tape*/
	Record* popNextRecord();

	/* Write record to tape */
	bool putRecord(Record* recordToWrite);

private:
	Buffer m_inputBuffer;
	Buffer m_outputBuffer;
	std::string m_name;
	RecordFile m_file;
};

#endif /* TAPE_H_ */
