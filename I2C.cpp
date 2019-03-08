#include "I2C.h"

I2C::I2C() {
}

void I2C::init() {
	TWSR = 0x00;
	TWBR = 72;  // 16000000 / (16 + 2 * 72 * 1) 100kHz
	TWCR |= _BV(TWEN);
}

void I2C::waitForComplete(){
	while  (!(TWCR & (1<<TWINT)));
}

uint8_t I2C::start(){
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);
	I2C::waitForComplete();
	if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
	  return 1;

	return 0;
}

void I2C::stop() {
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}

uint8_t I2C::readAcknowledge(){
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	I2C::waitForComplete();
	return TWDR;
}

uint8_t I2C::readNoAcknowledge(){
	TWCR = _BV(TWINT) | _BV(TWEN);
	I2C::waitForComplete();
	return TWDR;
}

void I2C::send(uint8_t data){
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	I2C::waitForComplete();
}


