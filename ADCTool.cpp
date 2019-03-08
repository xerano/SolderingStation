#include "ADCTool.h"
#include <avr/io.h>

void ADCTool::init() {
	// die Versorgungsspannung AVcc als Referenz wählen:
	ADMUX = (1 << REFS0);
	// oder interne Referenzspannung als Referenz für den ADC wählen:
	// ADMUX = (1<<REFS1) | (1<<REFS0);

	// Bit ADFR ("free running") in ADCSRA steht beim Einschalten
	// schon auf 0, also single conversion
	ADCSRA = (1 << ADPS1) | (1 << ADPS0);     // Frequenzvorteiler
	ADCSRA |= (1 << ADEN);                  // ADC aktivieren

	/* nach Aktivieren des ADC wird ein "Dummy-Readout" empfohlen, man liest
	 also einen Wert und verwirft diesen, um den ADC "warmlaufen zu lassen" */

	ADCSRA |= (1 << ADSC);                  // eine ADC-Wandlung
	while (ADCSRA & (1 << ADSC)) {     // auf Abschluss der Konvertierung warten
	}
	/* ADCW muss einmal gelesen werden, sonst wird Ergebnis der nächsten
	 Wandlung nicht übernommen. */
	(void) ADCW;
}

uint16_t ADCTool::read(uint8_t channel) {
	if (channel < 5) {
		// Kanal waehlen, ohne andere Bits zu beeinflußen
		ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
		ADCSRA |= (1 << ADSC);            // eine Wandlung "single conversion"
		while (ADCSRA & (1 << ADSC)) { // auf Abschluss der Konvertierung warten
		}
		return ADCW;                    // ADC auslesen und zurückgeben
	}

	return 0;
}

uint16_t ADCTool::readAvg(uint8_t channel, uint8_t samples) {
	uint32_t sum = 0;

	for (uint8_t i = 0; i < samples; ++i) {
		sum += read(channel);
	}

	return (uint16_t) (sum / samples);
}
