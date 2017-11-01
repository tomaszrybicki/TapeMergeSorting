/*
 *	Buffer.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "Buffer.h"

Buffer::Buffer(int bufferSize)
	: m_buffer_size(bufferSize)
{
}

Buffer::~Buffer() {
	clearBuffer();
	m_iterator = m_records.end();
}

bool Buffer::getRecord(Record* recordToGet) {
	/* Iterated entire list - return false */
	if(m_iterator == m_records.end()){
		recordToGet = 0;
		return false;
	}

	/* If we haven't initialized the iterator -
	 * initialize it with the beginning of the list */
	if(m_iterator == m_records.end()){ /*TODO: fix initialization */
		m_iterator = m_records.begin();
	}

	recordToGet = *m_iterator;

	/* Advance iterator */
	m_iterator++;

	return true;
}

bool Buffer::putRecord(Record* recordToBePut) {
	/* Buffer is full - return false */
	if(m_records.size() == m_buffer_size){
		return false;
	}

	m_records.push_back(recordToBePut);

	return true;
}

bool Buffer::clearBuffer(){
	/* Return false on empty buffer */
	if(m_records.size() == 0){
		return false;
	}

	/* Release the resources */
	for(auto i = m_records.begin(); i != m_records.end(); ++i){
		Record* record = *i;
		delete record;
	}

	/* Clear the list */
	m_records.clear();

	/* Reset the iterator */
	m_iterator = m_records.end();

	return true;
}

