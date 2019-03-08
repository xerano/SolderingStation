
#include "Serial.h"

Serial::Serial() {
}

void Serial::init(){
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

#if defined(USE_X2)
	UCSRA |= _BV(U2X);
#else
	UCSRA &= ~_BV(U2X);
#endif

	UCSRB |= _BV(TXEN) | _BV(RXEN); // transmit and receive
#if	defined (__AVR_ATmega8__)
	UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0); // 8 data bits, 1 stop bit
#else
	UCSRC = _BV(UCSZ1) | _BV(UCSZ0); // 8 data bits, 1 stop bit
#endif
}

void Serial::transmitByte(unsigned char data){
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = data;
}

unsigned char Serial::receiveByte() {
	loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
}

void Serial::print(const char *string){
	uint8_t i = 0;
	while(string[i]){
		transmitByte(string[i++]);
	}
}

void Serial::println(const char *string){
	this->print(string);
	transmitByte('\n');
}
