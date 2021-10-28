#pragma once
#include <esp32-hal-gpio.h>
#include <HardwareSerial.h>
class Relay {

private:
	const int relayDataPin;

public:
	Relay(int pin);
	void switchOn();
	void switchOff();


};