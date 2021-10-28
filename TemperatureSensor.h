#pragma once
#include <OneWire.h>
#include <DallasTemperature.h>

class TemperatureSensor {

private:

	// GPIO where the DS18B20 is connected to
	const int oneWireBus = 22;

	// Setup a oneWire instance to communicate with any OneWire devices
	OneWire* oneWire;

	// Pass our oneWire reference to Dallas Temperature sensor 
	DallasTemperature* sensor;

public:
	TemperatureSensor();
	float getCurrentTemperature();


};