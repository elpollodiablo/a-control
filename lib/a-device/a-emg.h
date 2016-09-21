#pragma once
#include <Arduino.h>
#include <SerialCommand.h>
#include "a-device.h"

class AControlDevice;

class AOlimexEMGDevice {
	public:
    AControlDevice *device;
    int interval;
    int timer_delay;
		AOlimexEMGDevice();
    void configure(AControlDevice *);
    void actuator_write_loop(void);
    void sensor_read_loop(void);
    void setup(void);
    void loop(void);
    void set(SerialCommand *sercmd);
	private:
    int counter;
    void toggle_calibration_signal(void);
};
