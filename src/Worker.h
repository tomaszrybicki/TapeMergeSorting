/*
 * Worker.h
 *
 *  Created on: Nov 6, 2017
 *      Author: Tomasz Rybicki
 */

#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

#include <string>

/* Class which offers general methods for performing sorting */
class Worker {
public:
	Worker();
	virtual ~Worker();

	/* Sorting using natural merging with 2+2 tape scheme */
	void sort2plus2(std::string tapeName);

	/* Creates file with random records */
	void generateRandomFile(std::string name, unsigned int recordCount);

private:
	double random(double min, double max);
};

#endif /* SRC_WORKER_H_ */
