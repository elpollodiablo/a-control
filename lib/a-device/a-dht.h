#pragma once
#include <DHT.h>
#include "a-device.h"

class AControlDevice;

class ADHTDevice {
  AControlDevice *device;
	public:
    unsigned long last_delay;
    unsigned long last_millis;
    DHT dht;
		ADHTDevice();
    void configure(AControlDevice *);
    void sensor_read_loop(void);
    void setup();
    void enable();
    void disable();
    bool is_enabled();
};