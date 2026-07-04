#pragma once
#ifndef Device_hpp
#define Device_hpp

#include "string"

class Device
{
    public:
    int id;
    std::string brand;
    std::string model;

    public:
    Device(int id, std::string brand, std::string model);
    virtual std::string getSpecs() const = 0;

    virtual ~Device() = default;
};


#endif