#include "../include/crow-backend/InMemoryDeviceRepository.hpp"

InMemoryDeviceRepository::InMemoryDeviceRepository() {}

bool InMemoryDeviceRepository::addDevice(Device* d) {
    for(Device* d1: this->devices) {
        if(d1->id==d->id) {
            return false;
        }
    }
    this->devices.push_back(d);
    return true;

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
            for(Device* d1: this->devices) {
                if(d1->id==d->id && d1->id!=id) {
                    delete d;
                    return false;
                }
            }
            delete this->devices[i];

            this->devices[i] = d;

            return true;
        }
    }
    delete d;
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