
#include "crow.h"
#include "../include/crow-backend/InMemoryDeviceRepository.hpp"
#include "../include/crow-backend/Laptop.hpp"
#include "../include/crow-backend/Server.hpp"

void create_getRoutes(crow::SimpleApp& app, InMemoryDeviceRepository& repo) {
    CROW_ROUTE(app, "/devices")
    .methods(crow::HTTPMethod::GET)
    ([&repo]{
        auto list = repo.getAllDevices();
        
        crow::json::wvalue::list json_list;

        for(Device* d: list) {
            crow::json::wvalue json_value;
            json_value["Description"]=d->getSpecs();

            json_list.push_back(std::move(json_value));
        }

        crow::json::wvalue response;
        response["devices"]=std::move(json_list);

        return crow::response(crow::status::OK, response);
    });

    CROW_ROUTE(app, "/devices/<int>")
    .methods(crow::HTTPMethod::GET)
    ([&repo](int id) {
            Device* d = repo.getDevice(id);
            if(!d) {
                crow::json::wvalue json_error;
                json_error["description"]="Nothing found";
                return crow::response(crow::status::NO_CONTENT);
            }
            crow::json::wvalue json;
            json["description"]=d->getSpecs();
            return crow::response(crow::OK, json);
        
    });
}

Device* check_body(crow::json::rvalue& body) {
    if(!body) {
        throw std::runtime_error("Invalid json body.");
    }
    std::string type_device = body["type"].s();
        if(type_device.empty()) {
            throw std::runtime_error("No field type.");
        }

        int id = body["id"].i();
        std::string brand = body["brand"].s();
        std::string model = body["model"].s();
        
        if(!id || brand.empty() || model.empty()) {
            throw std::runtime_error("No field id or brand or model given.");
        }
        if(type_device == "Laptop") {
            int batteryLife = body["batteryLifeHours"].i();
            if(!batteryLife || batteryLife < 0) {
                throw std::runtime_error("Battery life hours can't be less then 0");
            }
            Laptop* laptop = new Laptop(id, brand, model, batteryLife);
            return laptop;
        }else if(type_device == "Server") {
            int ramGB = body["ramGB"].i();
            int cores = body["cores"].i();

            if(!ramGB || ramGB <0 || !cores || cores < 0) {
                throw std::runtime_error("ramGB is mandatory and can't be less then 0 and cores are also mandatory and also can't be less then 0.");
            }
            Server* server = new Server(id, brand, model, ramGB, cores);
            return server;
        }else {
            throw std::runtime_error("Not valid type");
        }
}

void create_postRoutes(crow::SimpleApp& app, InMemoryDeviceRepository& repo) {
    CROW_ROUTE(app, "/devices")
    .methods(crow::HTTPMethod::POST)
    ([&repo](const crow::request& req ){
        auto body = crow::json::load(req.body);
        
        try
        {
            Device* device = check_body(body);
            bool valid =repo.addDevice(device);
            if(!valid) {
                throw std::runtime_error("Can't be added. Check if id is unique.");
            }
            return crow::response(crow::status::CREATED);
        }
        catch(const std::exception& e)
        {
            return crow::response(crow::status::BAD_REQUEST, e.what());
        }
        
    });
}

void create_putRoutes(crow::SimpleApp& app, InMemoryDeviceRepository& repo) {
    CROW_ROUTE(app, "/devices/<int>")
    .methods(crow::HTTPMethod::PUT)
    ([&repo](const crow::request& req, int id ){
        auto body = crow::json::load(req.body);

        try
        {
            Device* device = check_body(body);
            bool valid =repo.updateDevice(id, device);
            if(!valid) {
                throw std::runtime_error("Can't be update. Check if id is unique");
            }
            return crow::response(crow::status::OK, "Updated");
        }
        catch(const std::exception& e)
        {
            return crow::response(crow::status::BAD_REQUEST, e.what());   
        }
        
    });
}


int main() {
    crow::SimpleApp app;
    
    InMemoryDeviceRepository* repo = new InMemoryDeviceRepository();
    
    create_getRoutes(app, *repo);

    create_postRoutes(app, *repo);

    create_putRoutes(app, *repo);

    app.bindaddr("127.0.0.1").port(3000).multithreaded().run();
    return 0;
}