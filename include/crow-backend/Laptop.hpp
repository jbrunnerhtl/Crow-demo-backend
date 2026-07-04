#pragma once
#ifndef Laptop_hpp
#define Laptop_hpp

#include "string"
#include "Device.hpp"

class Laptop: public Device {
    public:
        int batteryLifeHours;
    public:
        Laptop(int id, std::string brand, std::string model, int batteryLifeHours);
        std::string getSpecs() const override;
};


#endif