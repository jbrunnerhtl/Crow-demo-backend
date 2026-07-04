#ifndef I_Device_Repository_hpp
#define I_Device_Repository_hpp

#include "string"
#include "Device.hpp"
#include "vector"

class IDeviceRepository {
    public:

        virtual void addDevice(Device* d)= 0;
        virtual Device* getDevice(int id)= 0;
        virtual std::vector<Device*> getAllDevices() = 0;
        virtual bool updateDevice(int id, Device* d) = 0;
        virtual bool deleteDevice(int id) = 0;
};

#endif