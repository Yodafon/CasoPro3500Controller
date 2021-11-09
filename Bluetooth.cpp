#include "Bluetooth.h"

BLEUUID REALTIME_TEMPERATURE_CHARACTERISTIC_UUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");
BLEUUID DESTINATION_TEMPERATURE_CHARACTERISTIC_UUID("3625d6cc-3226-4497-9d42-a6df047f4300");
BLEUUID CONTROLLER_SERVICE_UUID("dce32293-581b-4ce1-b9b0-29634f77e412");
BLEUUID CLIENT_CHARACTERISTICS_CONFIGURATION_UUID("00002902-0000-1000-8000-00805f9b34fb");

using namespace std;

Bluetooth::Bluetooth(float &destinationTemperature):destinationTemperature(destinationTemperature) {
	Serial.println("Starting BLE work!");

	BLEDevice::init("Caso Pro 3500 controller");
	BLEServer* pServer = BLEDevice::createServer();
	pService = pServer->createService(CONTROLLER_SERVICE_UUID);
	destinationTemperatureCharacteristic = pService->createCharacteristic(
		DESTINATION_TEMPERATURE_CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_WRITE |
		BLECharacteristic::PROPERTY_READ |
		BLECharacteristic::PROPERTY_BROADCAST |
		BLECharacteristic::PROPERTY_NOTIFY 
	);

	realtimeTemperatureCharacteristic = pService->createCharacteristic(
		REALTIME_TEMPERATURE_CHARACTERISTIC_UUID,
		BLECharacteristic::PROPERTY_READ | 
		BLECharacteristic::PROPERTY_BROADCAST |
		BLECharacteristic::PROPERTY_NOTIFY 
	);

	realtimeTemperatureCharacteristic->addDescriptor(new BLEDescriptor(CLIENT_CHARACTERISTICS_CONFIGURATION_UUID));
	destinationTemperatureCharacteristic->addDescriptor(new BLEDescriptor(CLIENT_CHARACTERISTICS_CONFIGURATION_UUID));
	destinationTemperatureCharacteristic->setCallbacks(new MyServerCallbacks(this->destinationTemperature));

	BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(CONTROLLER_SERVICE_UUID);
	pAdvertising->setScanResponse(true);
	pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
	pAdvertising->setMinPreferred(0x12);
	pService->start();
	BLEDevice::startAdvertising();
}

void Bluetooth::advertisingCurrentTemperarture(float currentTemperature)
{
	realtimeTemperatureCharacteristic->setValue(currentTemperature);
	realtimeTemperatureCharacteristic->notify();
	delay(50);
}