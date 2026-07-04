#include "../include/crow-backend/InMemoryDeviceRepository.hpp"

InMemoryDeviceRepository::InMemoryDeviceRepository() {}

void InMemoryDeviceRepository::addDevice(Device* d) {
    this->devices.push_back(d);
}

Device* InMemoryDeviceRepository::getDevice(int id) {
    for (Device* d: this->devices)
    {
        if(d->id==id) {
            return d;
        }
    }
    return nullptr;
    
}

std::vector<Device*> InMemoryDeviceRepository::getAllDevices() {
    return this->devices;
}

bool InMemoryDeviceRepository::updateDevice(int id, Device* d) {
    for (size_t i = 0; i < this->devices.size(); i++) {
        if(this->devices[i]->id==id) {
            delete this->devices[i];

            this->devices[i] = d;

            return true;
        }
    }
    return false;
}

bool InMemoryDeviceRepository::deleteDevice(int id) {
    for (size_t i = 0; i < this->devices.size(); i++)
    {
        if(this->devices[i]->id==id) {
            delete this->devices[i];
            this->devices.erase(this->devices.begin() + i);
            return true;
        }
    }
    return false;
}