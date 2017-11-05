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
	m_iterator = m_records.begin();
}

Buffer::~Buffer() {
	clearBuffer();
}

bool Buffer::getRecord(Record* &recordToGet) {
	/* Iterated entire list - return false */
	if(m_iterator == m_records.end() || m_records.size() == 0){
		recordToGet = 0;
		return false;
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

	/* Make iterator point to first element */
	if(m_records.size() == 1){
		m_iterator = m_records.begin();
	}


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
	m_iterator = m_records.begin();

	return true;
}

