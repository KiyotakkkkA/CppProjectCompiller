#ifndef JSON_HANDLER_HPP
#define JSON_HANDLER_HPP

#include <unordered_map>
#include <string>
#include <fstream>
#include "ServiceObject.hpp"

class JsonHandler : public ServiceObject{
public:
    JsonHandler(const std::string& filename);
    void createJsonFile();
    std::unordered_map<std::string, std::string> readJson();

private:
    std::string filename;
    std::unordered_map<std::string, std::string> parseJson(const std::string& jsonData);
    void trim(std::string& str);
    std::string createField(const char* fieldname, const char* value);
};

#endif