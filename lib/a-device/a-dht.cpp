#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>

#include "a-device.h"
#include "a-dht.h"


#define DHT_INTERVAL 5000
ADHTDevice::ADHTDevice (){
}

void ADHTDevice::configure(AControlDevice *device){
  this->device = device;
  this->device->has_actuator = true;
  this->device->has_sensor = true;
  this->device->send_serial_results = true;
}

void ADHTDevice::enable() {
  Serial.print("DHTxx Sensor enabled on pin");
  Serial.println(this->device->pins[1], DEC);
  digitalWrite(this->device->pins[1], HIGH);
}

void ADHTDevice::disable() {
  if (this->device->my_type == ACD_DHT11) {
    Serial.print("DHT11 Sensor disabled on pin");
    Serial.println(this->device->pins[1], DEC);
    digitalWrite(this->device->pins[1], LOW);
  }
}

bool ADHTDevice::is_enabled() {
  return (digitalRead(this->device->pins[1]) == HIGH);
}

void ADHTDevice::setup(){
  pinMode(this->device->pins[0], OUTPUT);
  pinMode(this->device->pins[1], OUTPUT);
  enable();
  if (this->device->my_type == ACD_DHT11) {
    this->dht.setup(this->device->pins[0], DHT::DHT11);
  } else {
    this->dht.setup(this->device->pins[0], DHT::DHT22);
  }
  disable();
}

void ADHTDevice::sensor_read_loop(){
  this->last_delay = millis() - this->last_millis;
  if (
    (
      (this->device->my_type == ACD_DHT11
      && this->last_delay > (DHT_INTERVAL + this->dht.getMinimumSamplingPeriod() * 2))
      || (this->device->my_type == ACD_DHT22
      && this->last_delay > DHT_INTERVAL)
    )
    &&
    this->is_enabled()
  ){
    this->device->sensor_result(0, (int)(this->dht.getHumidity() * 100));
    this->device->sensor_result(1, (int)(this->dht.getTemperature() * 100));
    Serial.print("sensor ");
    Serial.print(this->dht.getModel());
    Serial.print(": ");
    Serial.print(this->device->name);
    Serial.print(" status: ");
    Serial.println(this->dht.getStatusString());
    disable();
    this->last_millis = millis();
  } else if (
    this->last_delay > DHT_INTERVAL
    &&
    !this->is_enabled()
  ) {
    enable();
  }
}