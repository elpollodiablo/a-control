#include <Arduino.h>
#include <Wire.h>
#include <SerialCommand.h>
#include "a-device.h"
#include "a-emg.h"

AOlimexEMGDevice::AOlimexEMGDevice (){
  this->timer_delay = 10;
  this->counter = 0;
}

void AOlimexEMGDevice::toggle_calibration_signal(void){
  if(digitalRead(this->device->pins[1]) == HIGH) {
    digitalWrite(this->device->pins[1], LOW);
  } else{
    digitalWrite(this->device->pins[1], HIGH);
  }
}

void AOlimexEMGDevice::setup() {
  pinMode(this->device->pins[0], INPUT);
  pinMode(this->device->pins[1], OUTPUT);
}

void AOlimexEMGDevice::set(SerialCommand *sercmd) {
}

void AOlimexEMGDevice::configure(AControlDevice *device) {
  this->device = device;
  this->device->has_actuator = false;
  this->device->has_sensor = true;
  this->device->send_serial_results = false;
}

void AOlimexEMGDevice::actuator_write_loop() {
}

void AOlimexEMGDevice::sensor_read_loop() {
  this->device->sensor_result(0, analogRead(this->device->pins[0]));
  this->counter++;
  if(this->counter == 12){
    this->counter = 0;
    this->toggle_calibration_signal();
  }
}
