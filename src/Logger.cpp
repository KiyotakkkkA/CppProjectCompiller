#include "../includes/Logger.hpp"
#include "../includes/ServiceObject.hpp"

Logger::Logger(const std::string& filename) : ServiceObject("LOGGER") {
        logFile.open(filename, std::ios::app);
}

Logger::~Logger() {
        logFile.close();
}

void Logger::logInfo(const std::string& message) {
        logFile << "LOGGER -> [INFO]: " << getCurrentDateTime() << " -> " << message << std::endl;
}

void Logger::logError(const std::string& message) {
        logFile << "LOGGER -> [ERROR]: " << getCurrentDateTime() << " -> " << message << std::endl;
}

void Logger::logServiceInit(const std::string& serviceName) {
        logFile << "LOGGER -> [InitService]: " << getCurrentDateTime() << " -> " << serviceName << " initialized" << std::endl;
}

void Logger::logWarning(const std::string& message) {
        logFile << "LOGGER -> [WARNING]: " << getCurrentDateTime() << " -> " << message << std::endl;
}

void Logger::logCreate(const std::string& message) {
        logFile << "LOGGER -> [CREATE]: " << getCurrentDateTime() << " -> " << message << std::endl;
}

std::string Logger::getCurrentDateTime() {
        time_t now = time(0);
        struct tm* timeInfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
        return buffer;
}