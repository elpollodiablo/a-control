#include <Arduino.h>
#include <Wire.h>
#include <SerialCommand.h>
#include <DHT.h>
#include "a-device.h"
#include "a-dht.h"
#include "a-emg.h"
#include "a-onoff.h"

AControlDevice devices[20];
int device_count = 0;
int dht_a[]= {30, 32};
int dht_b[]= {22, 24};
int motora[] = {4, 5};
int motorb[] = {6, 7};
int emg[] = {0, 9};
char *command_device_c;
SerialCommand sercmd; 
void set() {
  command_device_c = sercmd.next();
  if (command_device_c != NULL) {
    devices[atoi(command_device_c)].set(&sercmd);
  } 
  else {
    Serial.println("set needs an integer argument to identify a device");
  }
}

void ping() {
  Serial.println("pong");
  
}
void setup() {
  noInterrupts();
  Serial.begin(115200);
  devices[0].configure(ACD_DHT22, dht_a, "dht22a");
  device_count++;
  devices[1].configure(ACD_DMPWM, motora, "motor_a");
  device_count++;
  devices[2].configure(ACD_DMPWM, motorb, "motor_b");
  device_count++;
  devices[3].configure(ACD_DHT22, dht_b, "dht22b");
  device_count++;
  devices[4].configure(ACD_EMG, emg, "emg");
  device_count++;
  sercmd.addCommand("set", set);
  sercmd.addCommand("ping", ping);
  
  
//  devices[2].configure(ACD_DMPWM, motorb, "motor_b");
//  device_count++;
  AControlDevice *acd;
  // put your setup code here, to run once:
  for (unsigned int i = 0; i < device_count; i++){
    acd = &devices[i];
    acd->setup();
  }
  //devices[1].set(0, 40);
  //devices[2].set(0, 40);
  interrupts();
}

void loop() {
  sercmd.readSerial();
  for (unsigned int i = 0; i < device_count; i++){
    if (devices[i].has_sensor) {
      devices[i].sensor_read_loop();
    }
  }
  for (unsigned int i = 0; i < device_count; i++){
    if (devices[i].has_actuator) {
      devices[i].actuator_write_loop();
    }
  }
}
