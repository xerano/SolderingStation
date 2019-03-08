
#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <util/twi.h>

class I2C {
public:
	I2C();
	static void init();
	static void waitForComplete();
	static uint8_t start();
	static void stop();
	static void send(uint8_t data);
	static uint8_t readAcknowledge();
	static uint8_t readNoAcknowledge();
};

#endif /* I2C_H_ */
