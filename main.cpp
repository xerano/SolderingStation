#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "PID.h"
#include "I2C.h"
#include "Serial.h"
#include "LCD.h"
#include "ADCTool.h"

PID pid(10, 1, 1);
Serial serial;
I2C i2c;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long map(long value, long in_min, long in_max, long out_min, long out_max);
long calculateTemp(long value);

void blink(uint8_t times) {
	for(uint8_t i = 0; i < times; i++){
		PORTB ^= _BV(DDB1);
		_delay_ms(50);
	}
}

int main(int argc, char **argv) {

	DDRB |= _BV(DDB1);

	blink(2);

	serial.init();

	serial.println("Ready");

	blink(2);

	serial.println("Init LCD...");

	lcd.init();

	serial.println("LCD initialized");

	lcd.clear();

	blink(2);

	lcd.backlight();
	lcd.setCursor(1, 0);
	lcd.printstr("DIY Soldering");
	lcd.setCursor(4, 1);
	lcd.printstr("Station");

	char buffer[16];

	_delay_ms(1000);

	lcd.clear();

	ADCTool::init();

	while (1) {
		uint16_t poti = ADCTool::readAvg(DDC0, 3);
		uint16_t sensor = ADCTool::readAvg(DDC2, 3);

		serial.print("POTI: ");
		serial.print(itoa(poti, buffer, 10));
		serial.print("Sensor: ");
		serial.println(itoa(sensor, buffer, 10));

		long setpoint = map(poti, 0, 1023, 90, 450);
		long temp = calculateTemp(sensor);
		sprintf(buffer, "%03ld/%03ld", temp, setpoint);

		pid.calculate(setpoint, temp);

		lcd.setCursor(1, 0);
		lcd.printstr(buffer);
		_delay_ms(300);
	}

}

long map(long value, long in_min, long in_max, long out_min, long out_max){
	return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long calculateTemp(long input){
	// 300 * 0.000041 = 0.0123
	return (5.0 / 1023) * input / 0.0123;
}
