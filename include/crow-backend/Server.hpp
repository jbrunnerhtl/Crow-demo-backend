#ifndef Server_hpp
#define Server_hpp

#include "string"
#include "Device.hpp"

class Server: public Device {
    public:
        int ramGB;
        int cores;

    public:
        Server(int id, std::string brand, std::string model, int ramGB, int cores);
        std::string getSpecs() const override;    
};


#endif