#include <Arduino.h>
#include <Wire.h>
#include <SerialCommand.h>
#include "a-device.h"

char *onoff_value_c;
int onoff_value;
AOnOffDevice::AOnOffDevice (){
}

void AOnOffDevice::setup() {
  pinMode(this->device->pins[0], OUTPUT);
}

void AOnOffDevice::set(SerialCommand *sercmd) {
  onoff_value_c = sercmd->next();
  if (onoff_value_c != NULL) {
    onoff_value = atoi(onoff_value_c);
    if (onoff_value == 0) {
      this->on = false;
    } else {
      this->on = true;      
    }
    this->dirty = true;
  }
}

void AOnOffDevice::configure(AControlDevice *device) {
  this->device = device;
  this->device->has_actuator = true;
  this->device->has_sensor = true;
  this->last_on_millis = 0;
  this->on_hysteresis_millis = 0;
  this->last_off_millis = 0;
  this->off_hysteresis_millis = 0;
  this->on = false;
}

void AOnOffDevice::actuator_write_loop() {
  if (this->dirty == true && this->on && millis() > this->last_on_millis + this->on_hysteresis_millis) {
    digitalWrite(this->device->pins[0], HIGH);
    this->last_on_millis = millis();
    this->dirty = false;
  } else if (this->dirty == true && !this->on && millis() > this->last_off_millis + this->off_hysteresis_millis) {
    digitalWrite(this->device->pins[0], LOW);
    this->last_off_millis = millis();
    this->dirty = false;
  }
}

void AOnOffDevice::sensor_read_loop() {
  this->device->sensor_result(0, digitalRead(this->device->pins[0]));
}