#include "Control.h"
#include "TemperatureSensor.h"
#include "Bluetooth.h"


Control* control;
TemperatureSensor* sensor;
Bluetooth* bluetooth;

float destinationTemperature = 0.0f;
float currentTemperature = 0.0f;

void setup() {
	Serial.begin(115200);
	control = new Control;
	sensor = new TemperatureSensor;
	bluetooth = new Bluetooth(destinationTemperature);
}

void loop() {

	currentTemperature = sensor->getCurrentTemperature();
	Serial.print("Current temperature: "); Serial.println(currentTemperature);
	bluetooth->advertisingCurrentTemperarture(currentTemperature);
	if (currentTemperature < destinationTemperature) {
		control->powerUp();
		Serial.println("Power Up");
	}
	if (currentTemperature > destinationTemperature) {
		control->powerDown();
		Serial.println("Power Down");
	}
}
