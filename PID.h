#ifndef PID_H_
#define PID_H_

class PID {
public:
	PID(float kp, float ki, float kd){
		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
	}

	/**
	 *
	 */
	int calculate(int setpoint, int current);
private:
	float kp = 0;
	float ki = 0;
	float kd = 0;
};


#endif /* PID_H_ */
