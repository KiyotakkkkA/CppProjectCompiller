#include "../includes/JsonHandler.hpp"
#include <iostream>
#include <algorithm>

JsonHandler::JsonHandler(const std::string& filename) : ServiceObject("JSON_HANDLER") {
    this->filename = filename;
    createJsonFile();
}

void JsonHandler::createJsonFile() {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream outputFile(filename);
        std::string data = "{";
        data += createField("SRC_PATH", "src");
        data += createField("EXE_NAME", "main");
        data += createField("MAIN_NAME", "main");
        data += createField("RUN_AFTER_BUILD", "true");
        data += "\n}";
        outputFile << data;
        outputFile.close();
        return;
    }
    file.close();
}

std::string JsonHandler::createField(const char* fieldname, const char* value) {
    return "\n\t\"" + std::string(fieldname) + "\": " + "\"" + std::string(value) + "\",";
}

std::unordered_map<std::string, std::string> JsonHandler::readJson() {
    std::ifstream file(filename);
    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return parseJson(jsonData);
}

std::unordered_map<std::string, std::string> JsonHandler::parseJson(const std::string& jsonData) {
    std::unordered_map<std::string, std::string> result;
    std::string trimmedData = jsonData;
    trim(trimmedData);

    if (trimmedData[0] != '{' || trimmedData[trimmedData.size() - 1] != '}') {
        std::cerr << "Incorrect JSON format" << std::endl;
        return result;
    }

    trimmedData = trimmedData.substr(1, trimmedData.size() - 2);
    std::string key, value;
    bool insideString = false;
    bool parsingKey = true;

    for (size_t i = 0; i < trimmedData.size(); ++i) {
        char current = trimmedData[i];

        if (current == '"') {
            insideString = !insideString;
            if (!insideString) {
                if (parsingKey) {
                    parsingKey = false;
                } else {
                    result[key] = value;
                    key.clear();
                    value.clear();
                    parsingKey = true;
                }
            }
            continue;
        }

        if (!insideString && (current == ':' || current == ',')) {
            continue;
        }

        if (insideString) {
            if (parsingKey) {
                key += current;
            } else {
                value += current;
            }
        }
    }

    return result;
}

void JsonHandler::trim(std::string &str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), str.end());
}