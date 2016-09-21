#include <Arduino.h>
#include <Wire.h>
#include <SerialCommand.h>
#include "a-device.h"

#define length_a 2
#define length_b 2
#define MAXPWM 140;
  //volatile int PATTERN_A[length_a] = {20, 40, 50, 70, 80, 100, 120, 160, 120, 100, 80, 70, 50, 40};
  //volatile int PATTERN_B[length_b] = {100, 120, 160, 120, 100, 80, 70, 50, 40, 20, 40, 50, 70, 80};
char *motor_value_c;
ADirectionalMotorPWMDevice::ADirectionalMotorPWMDevice (){
  this->pwm_value=0;
}

void ADirectionalMotorPWMDevice::set_output_mode() {
  pinMode(this->device->pins[0], OUTPUT);
  pinMode(this->device->pins[1], OUTPUT);
}

void ADirectionalMotorPWMDevice::setup() {
  this->set_output_mode();
}

void ADirectionalMotorPWMDevice::set(SerialCommand *sercmd) {
  motor_value_c = sercmd->next();
  if (motor_value_c != NULL) {
    this->pwm_value = atoi(motor_value_c);
    this->dirty = true;
  }
}

void ADirectionalMotorPWMDevice::configure(AControlDevice *device) {
  this->device = device;
  this->device->has_actuator = true;
  this->device->has_sensor = true;
}

void ADirectionalMotorPWMDevice::actuator_write_loop() {
  if (this->dirty == true) {
    this->set_pwm(this->pwm_value);
    this->dirty = false;
  }
}

void ADirectionalMotorPWMDevice::sensor_read_loop() {
  this->device->sensor_result(0, this->pwm_value);
}

void ADirectionalMotorPWMDevice::set_pwm(int value) {
  if (value > 0) {
    digitalWrite(this->device->pins[0], LOW);
    analogWrite(this->device->pins[1], value);
  } else if (value < 0) {
    digitalWrite(this->device->pins[1], LOW);
    analogWrite(this->device->pins[0], -value);   
  } else {
    digitalWrite(this->device->pins[0], LOW);
    digitalWrite(this->device->pins[1], LOW);
  }
}