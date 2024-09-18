#ifndef COMPILLER_HPP
#define COMPILLER_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "Logger.hpp"
#include "Config.hpp"
#include "JsonHandler.hpp"

class Compiller {
    Logger* logger;
    JsonHandler* jsonHandler;
    Config* config;
    public:
    Compiller();
    ~Compiller();
    void compile();
};

#endif
