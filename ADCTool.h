#ifndef ADCTOOL_H_
#define ADCTOOL_H_

#include <inttypes.h>

class ADCTool {
public:
	static void init();
	static uint16_t read(uint8_t channel);
	static uint16_t readAvg(uint8_t channel, uint8_t samples);
};

#endif /* ADC_H_ */
