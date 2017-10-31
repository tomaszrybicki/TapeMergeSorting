/*
 *	Tape.h
 *
 *  Created on: Oct 30, 2017
 *  Author:		Tomasz Rybicki
 */

#ifndef TAPE_H_
#define TAPE_H_

#define KiB 1024
#define BUFFER_SIZE 4*KiB

/*
 * Tape represents a block device slow enough to need
 * buffering as well as sorting algorithms that
 * use mostly sequential access as random access
 * introduces too big latency.
 *
 * It is implemented as a regular file with
 * database records. Reads and writes are buffered
 * to maximize performance
 */
class Tape {
public:
	Tape();
	virtual ~Tape();

private:

};

#endif /* TAPE_H_ */
