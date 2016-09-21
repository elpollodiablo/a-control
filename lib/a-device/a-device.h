#pragma once

/**
 * @file a-control.h
 * @author Philip Poten
 */

#include <Arduino.h>
#include "a-types.h"
#include "a-dmpwm.h"
#include "a-dht.h"
#include "a-emg.h"
#include "a-onoff.h"

#define ACD_DMPWM 0
#define ACD_DHT11 1
#define ACD_EMG   2
#define ACD_ONOFF 3
#define ACD_DHT22 4

class AControlDevice {
  int counter;
  ADirectionalMotorPWMDevice acd_dmpwm;
  ADHTDevice acd_dht;
  AOlimexEMGDevice acd_emg;
  AOnOffDevice acd_onoff;
	public:
    int my_type;
    bool active;
    bool has_sensor;
    bool has_actuator;
    bool send_serial_results;
    char name[20];
    int pins[10];
    int sensor_last_millis;
    int actuator_last_millis;
    int sensor_interval_millis;
    int actuator_interval_millis;
    AControlDevice();
    void configure(int, int[], char[]);
    void setup(void);
    void actuator_write_loop(void);
    void sensor_read_loop(void);
    void sensor_result(int, int);
    void sensor_result(int, float);
    void sensor_result(int, bool);
    void error(int, int, char*);
    void set(SerialCommand *sercmd);
};