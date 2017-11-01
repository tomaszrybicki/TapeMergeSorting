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
}

RecordFile::~RecordFile() {

}

bool RecordFile::writeBuffer(Buffer* buffer) {
}

bool RecordFile::fillBuffer(Buffer* buffer) {
	double height, radius;
	Record* newRecord;

	std::ofstream file(m_filename, std::ios::out|std::ios::app);

	/* File cannot be opened */
	if (!file.good()){
		std::cout << "File cannot be opened: " << m_filename << std::endl;
		return false;
	}

	/* Create and add records until buffer is full or file has ended */
	for(int i = 0; i < buffer->getBufferSize(); i++){
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
