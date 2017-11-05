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

	double getHeight() const {
		return m_height;
	}

	double getRadius() const {
		return m_radius;
	}

private:
	double m_height;
	double m_radius;
};

#endif /* RECORD_H_ */
