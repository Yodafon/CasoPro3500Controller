#include "Bluetooth.h"

BLEUUID REALTIME_TEMPERATURE_CHARACTERISTIC_UUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLEUUID SET_TEMPERATURE_CHARACTERISTIC_UUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLEUUID CONTROLLER_SERVICE_UUID("dce32293-581b-4ce1-b9b0-29634f77e412");

using namespace std;

Bluetooth::Bluetooth() {
	Serial.println("Starting BLE work!");

	BLEDevice::init("Caso Pro 3500 controller");
	BLEServer* pServer = BLEDevice::createServer();
	pService = pServer->createService(CONTROLLER_SERVICE_UUID);
	setTemperatureCharacteristic = pService->createCharacteristic(
		SET_TEMPERATURE_CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_WRITE
	);

	realtimeTemperatureCharacteristic = pService->createCharacteristic(
		REALTIME_TEMPERATURE_CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ);


	BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(CONTROLLER_SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);
	pService->start();
	BLEDevice::startAdvertising();
}

float Bluetooth::getValue()
{
	string value = setTemperatureCharacteristic->getValue();
	delay(500);
	return atof(value.c_str());
}

bool Bluetooth::hasNewValue()
{
	if (getValue() != currentSetTemperature)
	{
		setNewTemperature(getValue());
		return true;
	}
	else { return false; }
}

void Bluetooth::setNewTemperature(float newTemperature)
{
	this->currentSetTemperature = newTemperature;
}

void Bluetooth::advertisingCurrentTemperarture(float currentTemperature)
{
	realtimeTemperatureCharacteristic->setValue(currentTemperature);
	delay(500);
	Serial.println("Characteristic defined! Now you can read it in your phone!");
}