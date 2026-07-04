
#include "crow.h"
#include "../include/crow-backend/InMemoryDeviceRepository.hpp"
#include "../include/crow-backend/Laptop.hpp"
#include "../include/crow-backend/Server.hpp"

int main() {
    crow::SimpleApp app;
    
    InMemoryDeviceRepository* repo = new InMemoryDeviceRepository();
    CROW_ROUTE(app, "/devices")
    .methods(crow::HTTPMethod::GET)
    ([&repo]{
        auto list = repo->getAllDevices();
        
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
            Device* d = repo->getDevice(id);
            if(!d) {
                crow::json::wvalue json_error;
                json_error["description"]="Nothing found";
                return crow::response(crow::status::NO_CONTENT);
            }
            crow::json::wvalue json;
            json["description"]=d->getSpecs();
            return crow::response(crow::OK, json);
        
    });

    CROW_ROUTE(app, "/devices")
    .methods(crow::HTTPMethod::POST)
    ([&repo](const crow::request& req ){
        auto body = crow::json::load(req.body);
        if(!body) {
            return crow::response(crow::status::BAD_REQUEST, "Invalid json body.");
        }

        std::string type_device = body["type"].s();
        if(type_device.empty()) {
            return crow::response(crow::status::BAD_REQUEST, "No json field type.");
        }

        int id = body["id"].i();
        std::string brand = body["brand"].s();
        std::string model = body["model"].s();
        
        if(!id || brand.empty() || model.empty()) {
            return crow::response(crow::status::BAD_REQUEST, "No field id or brand or model given.");
        }


        if(type_device == "Laptop") {
            int batteryLife = body["batteryLifeHours"].i();
            if(!batteryLife || batteryLife < 0) {
                return crow::response(crow::status::BAD_REQUEST, "Battery life hours can't be less then 0");
            }
            Laptop* laptop = new Laptop(id, brand, model, batteryLife);
            repo->addDevice(laptop);
            return crow::response(crow::status::CREATED);
        }else if(type_device == "Server") {
            int ramGB = body["ramGB"].i();
            int cores = body["cores"].i();

            if(!ramGB || ramGB <0 || !cores || cores < 0) {
                return crow::response(crow::status::BAD_REQUEST, "ramGB is mandatory and can't be less then 0 and cores are also mandatory and also can't be less then 0.");
            }
            Server* server = new Server(id, brand, model, ramGB, cores);
            repo->addDevice(server);
            return crow::response(crow::status::CREATED);
        }else {
            return crow::response(crow::status::BAD_REQUEST, "Not valid type");
        }
    });


    app.bindaddr("127.0.0.1").port(3000).multithreaded().run();
    return 0;
}