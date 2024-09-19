#ifndef COMPILLER_HPP
#define COMPILLER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include "Logger.hpp"
#include "JsonHandler.hpp"
#include "Config.hpp"

class Compiller {
public:
    Compiller();
    ~Compiller();

    void compile();

private:
    bool createDirectory(const std::string& path);
    void executeCommand(const std::string& command, std::unordered_map<std::string, std::string>& files);
    void logAndDisplaySuccess(const std::string& mainName);
    void logAndDisplayError(const std::string& command);
    void runExecutable(const std::string& exeName);

    std::unique_ptr<Logger> logger;
    std::unique_ptr<JsonHandler> jsonHandler;
    std::unique_ptr<Config> config;
};

#endif 