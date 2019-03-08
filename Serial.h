/*
 * Serial.h
 *
 *  Created on: 07.03.2019
 *      Author: matthias
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#ifndef BAUD
#define BAUD 9600UL
#endif

#include <avr/io.h>
#include <util/setbaud.h>

class Serial {
public:
	Serial();
	void transmitByte(unsigned char data);
	void init();
	unsigned char receiveByte();
	void print(const char *string);
	void println(const char *string);
};

#endif /* SERIAL_H_ */
