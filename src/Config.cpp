#include "../includes/Config.hpp"
#include "../includes/JsonHandler.hpp"
#include "../includes/ServiceObject.hpp"

Config::Config(JsonHandler* jsonHandler) : ServiceObject("CONFIG"){
    data = jsonHandler->readJson();
}

Config::~Config() {

}

std::unordered_map<std::string, std::string> Config::getConfig() const {
    return data;
}