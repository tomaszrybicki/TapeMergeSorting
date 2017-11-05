/*
 *	RecordFile.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "RecordFile.h"
#include <iostream>

RecordFile::RecordFile(std::string filename)
	: m_filename(filename)
{
	/* Clear file */
	std::ofstream file(m_filename, std::ofstream::out | std::ofstream::trunc);
	file.close();
}

RecordFile::~RecordFile() {

}

bool RecordFile::writeBuffer(Buffer* buffer) {
	std::ofstream file(m_filename, std::ios::out|std::ios::app);

	/* File cannot be opened */
	if (!file.good()){
		std::cerr << "File cannot be opened: " << m_filename << std::endl;
		return false;
	}

	Record* record;

	/* Write each record data to file from buffer */
	while (buffer->popRecord(record)){
		file << record->getHeight();
		file << std::endl;
		file << record->getRadius();
		file << std::endl;
	}

	file.close();

	return true;
}

bool RecordFile::fillBuffer(Buffer* buffer) {
	double height, radius;
	Record* newRecord;

	std::ifstream file(m_filename, std::ios::in);

	/* File cannot be opened */
	if (!file.good()){
		std::cerr << "File cannot be opened: " << m_filename << std::endl;
		return false;
	}

	/* Create and add records until buffer is full or file has ended */
	for(unsigned int i = 0; i < buffer->getBufferSize(); i++){
		/* TODO: set/get streampos */

		/* We got the data */
		if(file >> height && file >> radius){
			newRecord = new Record(height, radius);
			buffer->putRecord(newRecord);

		/* EOF */
		}else{
			break;
		}
	}

	/* Save file read position */
	m_cursor = file.tellg();

	/* Close file */
	file.close();

	return true;

}
