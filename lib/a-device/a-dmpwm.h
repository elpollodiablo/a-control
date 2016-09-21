#include "../FlexiTimer2/FlexiTimer2.h"
#include <SerialCommand.h>
#ifndef _ACONTROL_ACTUATOR_H_
#define _ACONTROL_ACTUATOR_H_
class AControlDevice;
/**
 * @file BarLib.h
 * @author John Doe
 * @version 1.0
 */

#include <Arduino.h>
#include "a-device.h"
class ADirectionalMotorPWMDevice {
	public:
    AControlDevice *device;
		ADirectionalMotorPWMDevice();
    void configure(AControlDevice *);
    void actuator_write_loop(void);
    void sensor_read_loop(void);
    void setup();
    void loop();
    void set(SerialCommand *sercmd);
	private:
    int pattern[10];
    int pattern_wait[10];
    int pattern_counter;
    int pwm_value;
    bool dirty = false;
    void set_output_mode();
    void set_pwm(int value);
};

#endif
