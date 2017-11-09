/*
 *	RecordFile.cpp
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#include "RecordFile.h"
#include <iostream>

RecordFile::RecordFile(std::string filename, volatile unsigned char flags)
	: m_filename(filename)
{
	/* If new tape - clear file */
	if(flags & NEW_TAPE){
		clearFile();
	}

	/*Set cursor to beginning of file */
	std::ifstream fileIn(m_filename, std::ios::in|std::ios::binary);
	m_cursor = fileIn.tellg();
}

RecordFile::~RecordFile() {

}

bool RecordFile::writeBuffer(Buffer* buffer) {
	std::ofstream file(m_filename, std::ios::out|std::ios::app|std::ios::binary);

	/* File cannot be opened */
	if (!file.good()){
		std::cerr << "File cannot be opened: " << m_filename << std::endl;
		return false;
	}

	fileWrites++;

	Record* record;
	double h,r;

	/* Write each record data to file from buffer in binary format*/
	while (buffer->popRecord(record)){
		h = record->getHeight();
		r = record->getRadius();
		file.write(reinterpret_cast<char*>(&h),sizeof(double));
		file.write(reinterpret_cast<char*>(&r),sizeof(double));
	}

	file.close();

	return true;
}

bool RecordFile::fillBuffer(Buffer* buffer, bool &wasEof) {
	double height, radius;
	Record* newRecord;
	/* Memory for reading a double */
	char* bytes = new char[2 * sizeof(double)];

	std::ifstream file(m_filename, std::ios::in|std::ios::binary);

	/* File cannot be opened */
	if (!file.good()){
		std::cerr << "File cannot be opened: " << m_filename << std::endl;
		return false;
	}

	fileReads++;

	/* Set cursor in file where we last finished*/
	file.seekg(m_cursor);

	/* Create and add records until buffer is full or file has ended */
	for(unsigned int i = 0; i < buffer->getBufferSize(); i+= 2*sizeof(double)){
		if(file.peek() == std::ifstream::traits_type::eof()){
			wasEof = true;
			break;
		}
		/* Read 2 doubles from file */
		file.read(reinterpret_cast<char*>(bytes), 2 * sizeof(double));

		if(file.eof()){
			wasEof = true;
			break;
		}

		/* Reinterpret bytes as doubles */
		double* values = (double*)bytes;

		height = values[0];
		radius = values[1];

		newRecord = new Record(height, radius);
		buffer->putRecord(newRecord);
	}

	/* Save file read position */
	m_cursor = file.tellg();

	/* Close file */
	file.close();

	return true;

}

void RecordFile::clearFile() {
	std::ofstream fileOut(m_filename, std::ofstream::out | std::ofstream::trunc|std::ios::binary);
	m_cursor = 0;
	fileOut.close();
}

void RecordFile::print(double* previousValue) {
	Record* newRecord;
	double height, radius, value;
	char* bytes = new char[2 * sizeof(double)];

	std::ifstream file(m_filename, std::ios::in|std::ios::binary);

	/* File cannot be opened */
	if (!file.good()){
		std::cerr << "File cannot be opened: " << m_filename << std::endl;
		return;
	}



	while(true){

		if(file.peek() == std::ifstream::traits_type::eof()){
			break;
		}
		/* Read 2 doubles from file */
		file.read(reinterpret_cast<char*>(bytes), 2 * sizeof(double));

		if(file.eof()){
			break;
		}

		/* Reinterpret bytes as doubles */
		double* values = (double*)bytes;

		height = values[0];
		radius = values[1];

		newRecord = new Record(height, radius);
		value = newRecord->getVolume();

		/* Print series delimiter */
		if(value < *previousValue){
			std::cout << "|  ";
		}

		std::cout << value << "  ";
		*previousValue = value;
		delete newRecord;
	}

	/* Close file */
	file.close();
}
