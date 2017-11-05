/*
 *	Tape.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "Tape.h"
#include <iostream>

Tape::Tape(std::string name)
	: m_inputBuffer(BUFFER_SIZE)
	, m_outputBuffer(BUFFER_SIZE)
	, m_name(name)
	, m_file(m_name)
{
}

Tape::~Tape() {
}

double Tape::getNextRecordValue() {
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
			std::cerr << "End of file in getNextRecordValue()" << std::endl;
			return END_OF_TAPE;
		}else{
			return value;
		}
	}
}

Record* Tape::popNextRecord() {
	Record* record;
	bool result;

	/* Check in buffer */
	result = m_outputBuffer.popRecord(record);

	/* Record is in buffer */
	if(result == true){
		m_outputBuffer.popRecord(record);
		return record;

	/* Buffer is empty, filling next records from file */
	}else{
		std::cerr << "Filling buffer from file" << std::endl;
		m_outputBuffer.clearBuffer();
		m_file.fillBuffer(&m_outputBuffer);

		/* Check in buffer */
		result = m_outputBuffer.popRecord(record);

		/* No value after filling buffer means EOF */
		if(result == false){
			std::cerr << "End of file in popNextRecord()" << std::endl;
			return 0;
		}else{
			return record;
		}
	}
}

bool Tape::putRecord(Record* recordToWrite) {
	bool result;

	result = m_inputBuffer.putRecord(recordToWrite);

	/* Buffer is full */
	if(result == false){
		/* Write buffer to file */
		std::cerr << "Writing buffer to file" << std::endl;
		m_file.writeBuffer(&m_inputBuffer);

		m_inputBuffer.clearBuffer();

		result = m_inputBuffer.putRecord(recordToWrite);

		if(result == false){
			std::cerr << "Unknown error in putRecord()" << std::endl;
			return false;
		}

		return true;

	/* Buffer in not full - writing to it */
	}else{
		return true;
	}
}
