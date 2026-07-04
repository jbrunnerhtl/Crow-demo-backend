#include "../include/crow-backend/Server.hpp"
#include "string"

Server::Server(int id, std::string brand, std::string model, int ramGB, int cores) 
    : Device(id, brand, model), ramGB(ramGB), cores(cores) 
{
    
};

std::string Server::getSpecs() const{
        return "Id:" + std::to_string(this->id) + 
        ";Brand:" + this->brand + ";Model:"
        +this->model+";RamGB:" + std::to_string(this->ramGB) + ";Cores:" + std::to_string(this->cores);
};