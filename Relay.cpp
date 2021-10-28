#include "Relay.h"

Relay::Relay(int pin): relayDataPin(pin)
{
	pinMode(pin, OUTPUT);
	this->switchOff();
}

void Relay::switchOn()
{
	digitalWrite(relayDataPin, LOW);
	Serial.println("Pin is Flowing : " + relayDataPin);
}

void Relay::switchOff()
{
	digitalWrite(relayDataPin, HIGH);
	Serial.println("Pin is not Flowing : "+relayDataPin);
}
