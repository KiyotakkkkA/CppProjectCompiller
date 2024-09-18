#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include "ServiceObject.hpp"

class Logger : public ServiceObject{
private:
    std::ofstream logFile;
    
public:
    Logger(const std::string& filename);

    ~Logger();

    void logInfo(const std::string& message);
    void logError(const std::string& message);
    void logCreate(const std::string& message);
    void logWarning(const std::string& message);
    void logServiceInit(const std::string& serviceName);

    std::string getCurrentDateTime();
};

#endif