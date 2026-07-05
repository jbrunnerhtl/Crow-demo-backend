#ifndef In_Memory_Device_Repository_hpp
#define In_Memory_Device_Repository_hpp

#include "IDeviceRepository.hpp"
#include "Device.hpp"


class InMemoryDeviceRepository : public IDeviceRepository {
    private:
        std::vector<Device*> devices;
    public:
        InMemoryDeviceRepository();
        bool addDevice(Device* d) override;
        Device* getDevice(int id) override;
        std::vector<Device*> getAllDevices() override;
        bool updateDevice(int id, Device* d) override;
        bool deleteDevice(int id) override;    
}; 

#endif