#include "Control.h"
#include "TemperatureSensor.h"
#include "Bluetooth.h"


Control* control;
TemperatureSensor* sensor;
Bluetooth* bluetooth;

float expectedTemperature = 0.0f;
float currentTemperature = 0.0f;

void setup() {
	Serial.begin(115200);
	control = new Control;
	sensor = new TemperatureSensor;
	bluetooth = new Bluetooth;
}

void loop() {

	currentTemperature = sensor->getCurrentTemperature();
	Serial.print("Current temperature: "); Serial.println(currentTemperature);
	bluetooth->advertisingCurrentTemperarture(currentTemperature);
	if (currentTemperature < expectedTemperature) {
		control->powerUp();
		Serial.println("Power Up");
	}
	if (currentTemperature > expectedTemperature) {
	control->powerDown();
		Serial.println("Power Down");
	}
	if (bluetooth->hasNewValue()) {
		expectedTemperature = bluetooth->getValue();
		Serial.print("Set new value: "); Serial.println(expectedTemperature);
	}
	delay(1000);
}
