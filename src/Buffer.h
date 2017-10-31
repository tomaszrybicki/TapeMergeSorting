/*
 *	Buffer.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <list>
#include "Record.h"

/*
 * Buffer is a wrapper class for a list which serves as
 * buffer in memory.
 *
 * When buffer is full it is its owner responsibility
 * to write it's contents to file and clear the buffer.
 *
 * Buffer is responsible for releasing the resources!
 */
class Buffer {
public:
	/* Creates an empty buffer with bufferSize */
	Buffer(int bufferSize);

	/* Calls clearBuffer()! */
	virtual ~Buffer();

	/* Returns true if there is a record to fetch,
	 *  false otherwise*/
	bool getRecord(Record* recordToGet);

	/* Returns true if there is space for a record
	 * returns false otherwise */
	bool putRecord(Record* recordToBePut);

	/* Deletes stored pointers locations,
	 * and empties the list. Returns true when successful
	 * false when buffer is already cleared */
	bool clearBuffer();

private:
	std::list<Record*> m_records;
	unsigned int m_buffer_size;
	std::list<Record*>::iterator m_iterator;
};

#endif /* BUFFER_H_ */
