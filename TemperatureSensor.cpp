#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() {
    this->oneWire = new OneWire(oneWireBus);
    this->sensor = new DallasTemperature(this->oneWire);
    sensor->begin();
}

float TemperatureSensor::getCurrentTemperature()
{
    sensor->requestTemperatures();
    float temperatureC = sensor->getTempC(0);
    return temperatureC;
}
