#pragma once
#include "Relay.h"
class Control {

public:
	Control();
	void powerUp();
	void powerDown();
private:
	Relay* wattUpButtonRelay;
	Relay* wattDownButtonRelay;
};