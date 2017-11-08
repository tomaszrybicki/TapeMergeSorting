/*
 *	Tape.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef TAPE_H_
#define TAPE_H_

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
 *
 * When passing USE_EXISTING_FILE as flag tape will
 * load the contents of file with 'name'
 * otherwise it will create empty tape
 */


class Tape {
public:
	Tape(std::string name, unsigned char flags);

	/* Creates a tape with contents of other tape */
	Tape(std::string name, Tape* copied);

	virtual ~Tape();

	/* Return the sorting value of next pointed record
	 *  without removing it. Returns END_OF_TAPE on empty tape */
	double getNextRecordValue();

	/* Return next record and remove it from the tape
	 * returns 0 on empty tape*/
	Record* popNextRecord();

	/* Write record to tape */
	bool putRecord(Record* recordToWrite);

	/* Print record with series delimiting */
	void print();

	/* Rewinds tape so that it can existing tape can be reused */
	void rewind();


	double getLastPutValue() const {
		return m_lastPutValue;
	}

	const std::string& getName() const {
		return m_name;
	}

private:
	void flushInputBuffer();

private:
	Buffer m_inputBuffer;
	Buffer m_outputBuffer;
	std::string m_name;
	RecordFile m_file;
	double m_lastPutValue;
};

#endif /* TAPE_H_ */
