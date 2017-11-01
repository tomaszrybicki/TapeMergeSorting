/*
 *	RecordFile.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef RECORDFILE_H_
#define RECORDFILE_H_

#include <string>
#include <fstream>
#include <Buffer.h>

/*
 * This class represents a file to which records are saved.
 */
class RecordFile {
public:
	RecordFile(std::string filename);
	virtual ~RecordFile();

	/* This function writes buffer contents to file */
	bool writeBuffer(Buffer* buffer);

	/* This function writes file contents to buffer */
	bool fillBuffer(Buffer* buffer);

private:
	std::string m_filename;
	std::streampos m_cursor;
};

#endif /* RECORDFILE_H_ */
