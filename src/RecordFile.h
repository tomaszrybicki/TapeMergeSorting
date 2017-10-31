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
	RecordFile();
	virtual ~RecordFile();

	bool writeBuffer(Buffer* buffer);
	bool fillBuffer(Buffer* buffer);

private:
	std::string m_filename;
	int m_cursor;
	std::fstream m_file;
};

#endif /* RECORDFILE_H_ */
