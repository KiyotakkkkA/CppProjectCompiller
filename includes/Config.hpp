#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "ServiceObject.hpp"
#include "JsonHandler.hpp"
#include <unordered_map>

class Config : public ServiceObject {
    std::unordered_map<std::string, std::string> data;
    public:
    Config(JsonHandler* jsonHandler);
    ~Config();
    std::unordered_map<std::string, std::string> getConfig() const;
};

#endif
