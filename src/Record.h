/*
 *	Record.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef RECORD_H_
#define RECORD_H_

#include <math.h>

/*
 * Class describing a record in database file
 * which represents a cone
 */
class Record {
public:
	Record(double h, double r);
	virtual ~Record();
	double getVolume();

private:
	double m_radius;
	double m_height;
};

#endif /* RECORD_H_ */
