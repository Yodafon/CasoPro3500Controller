#pragma once
#include <BLEDevice.h>
#include <string>
#include <HardwareSerial.h>
class Bluetooth {

private:
	BLECharacteristic* destinationTemperatureCharacteristic;
	BLECharacteristic* realtimeTemperatureCharacteristic;
	BLEService* pService;
	float& destinationTemperature;
public:
	Bluetooth(float &destinationTemperature);
	void advertisingCurrentTemperarture(float currentTemperature);

};

class MyServerCallbacks : public BLECharacteristicCallbacks {
public:
	float& temperature;

	MyServerCallbacks(float& temperature):temperature(temperature) {

	}

	void onWrite(BLECharacteristic* pCharacteristic) {
		std::string rxValue = pCharacteristic->getValue();
		if ((rxValue.length() > 0) && (rxValue.find('&') == std::string::npos)) {
			this->temperature = atof(rxValue.c_str());
			pCharacteristic->setValue(this->temperature);
			pCharacteristic->notify();
			delay(200);
			Serial.print("Set new value: "); Serial.println(temperature);
		}
	}
};