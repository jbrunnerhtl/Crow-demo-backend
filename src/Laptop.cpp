#include "../include/crow-backend/Laptop.hpp"

#include "string"

Laptop::Laptop(int id, std::string brand, std::string model, int batteryLifeHours)
    : Device(id, brand, model), batteryLifeHours(batteryLifeHours)
{

};


std::string Laptop::getSpecs() const {
    return "Id:" + std::to_string(this->id) + ";Brand:" + this->brand + ";Model:" + this->model
        + ";BatteryLifeHours:" + std::to_string(this->batteryLifeHours);
}