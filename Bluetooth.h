#pragma once
#include <BLEDevice.h>
#include <string>
#include <HardwareSerial.h>
class Bluetooth {

private:
	float currentSetTemperature;
	BLECharacteristic* setTemperatureCharacteristic;
	BLECharacteristic* realtimeTemperatureCharacteristic;
	BLEService* pService;
	void setNewTemperature(float newTemperature);
public:
	Bluetooth();
	float getValue();
	bool hasNewValue();

	void advertisingCurrentTemperarture(float currentTemperature);

};