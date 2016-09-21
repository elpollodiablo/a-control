#pragma once
#include "../FlexiTimer2/FlexiTimer2.h"
#include <SerialCommand.h>
class AControlDevice;
/**
 * @file BarLib.h
 * @author John Doe
 * @version 1.0
 */

#include <Arduino.h>
#include "a-device.h"
class AOnOffDevice {
	public:
    AControlDevice *device;
		AOnOffDevice();
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
    bool on = false;
    int last_on_millis = 0;
    int on_hysteresis_millis = 0;
    int last_off_millis = 0;
    int off_hysteresis_millis = 0;
    bool dirty = false;
};