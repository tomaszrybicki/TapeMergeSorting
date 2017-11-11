/*
 *	Buffer.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "Buffer.h"
#include "Defines.h"

Buffer::Buffer(int bufferSize)
	: m_buffer_size(bufferSize)
{
	m_iterator = m_records.begin();
}

Buffer::~Buffer() {
	clearBuffer();
}

bool Buffer::popRecord(Record* &recordToGet) {
	/* Iterated entire list - return false */
	if(m_iterator == m_records.end() || m_records.size() == 0 || *m_iterator == 0){
		recordToGet = 0;
		return false;
	}

	recordToGet = *m_iterator;

	/* Remove element and advance iterator */
	m_iterator = m_records.erase(m_iterator);

	return true;
}

bool Buffer::putRecord(Record* recordToBePut) {
	/* Buffer is full - return false */
	if(m_records.size() == (m_buffer_size / RECORD_SIZE)){
		return false;
	}

	m_records.push_back(recordToBePut);

	/* Make iterator point to first element */
	if(m_records.size() == 1){
		m_iterator = m_records.begin();
	}

	return true;
}

double Buffer::getNextRecordValue() {
	if(m_iterator == m_records.end() || m_records.size() == 0){
		return END_OF_BUFFER;
	}

	Record* record = *m_iterator;

	return record->getVolume();

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

void Buffer::print(double* previousValue) {
	Record* record;
	double value;

	for(auto i = m_records.begin(); i != m_records.end(); ++i){
		record = *i;
		value = record->getVolume();

		/* Series delimiter */
		if(value < *previousValue){
			std::cout << "|  ";
		}

		std::cout << value << "  ";
		*previousValue = value;
	}
}

int Buffer::getRecordCount() {
	return m_records.size();
}
