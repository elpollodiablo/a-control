#include <Arduino.h>
#include <SerialCommand.h>
#include "a-device.h"

/**
 * @file a-control.cpp
 * @author Philip Poten
 * @version 0.1
 */

AControlDevice::AControlDevice() {
  this->active = false;
  this->has_sensor = false;
  this->has_actuator = false;
  this->send_serial_results = false;
  this->sensor_last_millis = 0;
  this->actuator_last_millis = 0;
  this->sensor_interval_millis = 0;
  this->actuator_interval_millis = 0;
};

void AControlDevice::configure(int my_type, int pins[], char name[]) {
  memcpy(this->name, name, 20);
  memcpy(this->pins, pins, 20);
  this->my_type = my_type;
  this->counter++;
  switch(this->my_type) {
      case ACD_DMPWM:
        this->acd_dmpwm.configure(this);
        break;
      case ACD_DHT11:
        this->acd_dht.configure(this);
        break;
      case ACD_DHT22:
        this->acd_dht.configure(this);
        break;
      case ACD_EMG:
        this->acd_emg.configure(this);
        break;
      case ACD_ONOFF:
        this->acd_onoff.configure(this);
        break;
  }
};

void AControlDevice::set(SerialCommand *sercmd) {
  switch(this->my_type) {
      case ACD_DMPWM:
        this->acd_dmpwm.set(sercmd);
        break;
  }
};

void AControlDevice::sensor_result(int slot, int value) {
  if (this->send_serial_results) {
    Serial.print(F("result/"));
    Serial.print(this->name);
    Serial.print("/");
    Serial.print(slot);
    Serial.print(":");
    Serial.print(value, DEC);
    Serial.print("\r\n");
  }
}
void AControlDevice::sensor_result(int slot, float value) {
  if (this->send_serial_results) {
    Serial.print(F("result/"));
    Serial.print(this->name);
    Serial.print("/");
    Serial.print(slot);
    Serial.print(":");
    Serial.print(value);
    Serial.print("\r\n");
  }
}
void AControlDevice::sensor_result(int slot, bool value) {
  if (this->send_serial_results) {
    Serial.print(F("result/"));
    Serial.print(this->name);
    Serial.print("/");
    Serial.print(slot);
    Serial.print(":");
    Serial.print(value);
    Serial.print("\r\n");
  }
}
void AControlDevice::error(int slot, int value, char *error_string) {
  if (this->send_serial_results) {
    Serial.print(F("error/"));
    Serial.print(this->name);
    Serial.print("/");
    Serial.print(slot);
    Serial.print(":");
    Serial.print(value, DEC);
    Serial.print("/");
    Serial.print(error_string);
    Serial.print("\r\n");
  }
}

void AControlDevice::setup(void) {
  switch(this->my_type) {
      case ACD_DMPWM:
        this->acd_dmpwm.setup();
        break;
      case ACD_DHT11:
      case ACD_DHT22:
        this->acd_dht.setup();
        break;
      case ACD_EMG:
        this->acd_emg.setup();
        break;
      case ACD_ONOFF:
        this->acd_onoff.setup();
        break;
  }
};

void AControlDevice::actuator_write_loop(void) {
  switch(this->my_type) {
      case ACD_DMPWM:
        this->acd_dmpwm.actuator_write_loop();
        break;
      case ACD_ONOFF:
        this->acd_onoff.actuator_write_loop();
        break;
  }
};

void AControlDevice::sensor_read_loop(void) {
  switch(this->my_type) {
      case ACD_DMPWM:
        this->acd_dmpwm.sensor_read_loop();
        break;
      case ACD_DHT11:
      case ACD_DHT22:
        this->acd_dht.sensor_read_loop();
        break;
      case ACD_EMG:
        this->acd_emg.sensor_read_loop();
        break;
      case ACD_ONOFF:
        this->acd_onoff.sensor_read_loop();
        break;
  }
};
