/*
 *	Tape.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "Tape.h"
#include <iostream>

Tape::Tape(std::string name, unsigned char flags)
	: m_inputBuffer(BUFFER_SIZE)
	, m_outputBuffer(BUFFER_SIZE)
	, m_name(name)
	, m_file(m_name, flags)
	, m_lastPutValue(-1)
{
}


Tape::Tape(std::string name, Tape* copied)
: m_inputBuffer(BUFFER_SIZE)
, m_outputBuffer(BUFFER_SIZE)
, m_name(name)
, m_file(m_name, NEW_TAPE)
, m_lastPutValue(-1)
{
	std::ifstream  source(copied->getName(), std::ios::binary);
	std::ofstream  dest(m_name, std::ios::binary);
	dest << source.rdbuf();
}


Tape::~Tape() {
	m_file.writeBuffer(&m_inputBuffer);
}

double Tape::getNextRecordValue() {
	/* Flush input buffer */
	flushInputBuffer();

	double value = m_outputBuffer.getNextRecordValue();

	/* Next record is in buffer */
	if(value != END_OF_BUFFER){
		return value;

	/* End of buffer, filling next records from file */
	}else{
		m_outputBuffer.clearBuffer();
		m_file.fillBuffer(&m_outputBuffer);

		value = m_outputBuffer.getNextRecordValue();

		/* No value after filling buffer means EOF */
		if(value == END_OF_BUFFER){
			return END_OF_TAPE;
		}else{
			return value;
		}
	}
}

Record* Tape::popNextRecord() {
	Record* record;
	bool result;

	/* Flush input buffer */
	flushInputBuffer();

	/* Check in buffer */
	result = m_outputBuffer.popRecord(record);

	/* Record is in buffer */
	if(result == true){
		return record;

	/* Buffer is empty, filling next records from file */
	}else{
		m_outputBuffer.clearBuffer();
		m_file.fillBuffer(&m_outputBuffer);

		/* Check in buffer */
		result = m_outputBuffer.popRecord(record);

		/* No value after filling buffer means EOF */
		if(result == false){
			return 0;
		}else{
			return record;
		}
	}
}

bool Tape::putRecord(Record* recordToWrite) {
	bool result;
	m_lastPutValue = recordToWrite->getVolume();

	result = m_inputBuffer.putRecord(recordToWrite);

	/* Buffer is full */
	if(result == false){
		/* Write buffer to file */
		m_file.writeBuffer(&m_inputBuffer);

		m_inputBuffer.clearBuffer();

		result = m_inputBuffer.putRecord(recordToWrite);

		if(result == false){
			std::cerr << "Unknown error in putRecord()" << std::endl;
			return false;
		}

		return true;

	/* Buffer is not full - writing to it */
	}else{
		return true;
	}
}

void Tape::print() {
	double lastValue = -1;

	std::cout << "( " << m_name << " ):  ";

	/* Print file */
	m_file.print(&lastValue);

	/* Print input buffer */
	m_inputBuffer.print(&lastValue);

	std::cout << std::endl << std::endl;
}

void Tape::rewind() {
	/* Reset buffers and state*/
	m_outputBuffer.clearBuffer();
	m_inputBuffer.clearBuffer();
	m_lastPutValue = -1;

	/* Truncate file */
	m_file.clearFile();
}

void Tape::flushInputBuffer() {
	if(m_inputBuffer.getRecordCount()){
		m_file.writeBuffer(&m_inputBuffer);
		m_inputBuffer.clearBuffer();
	}
}
