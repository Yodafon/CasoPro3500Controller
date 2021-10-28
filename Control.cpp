#include "Control.h"

Control::Control()
{
	wattDownButtonRelay = new Relay(26);
	wattUpButtonRelay = new Relay(27);
}

void Control::powerUp()
{
	wattUpButtonRelay->switchOn();
	delay(100);
	wattUpButtonRelay->switchOff();
}

void Control::powerDown()
{
	wattDownButtonRelay->switchOn();
	delay(100);
	wattDownButtonRelay->switchOff();
}
