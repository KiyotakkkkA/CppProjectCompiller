#include "../includes/Compiller.hpp"
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>

const std::string COLOR_RESET = "\033[0m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_RED = "\033[31m";
const std::string COLOR_YELLOW = "\033[33m";

Compiller::Compiller() 
    : logger(std::make_unique<Logger>("compiller/logs.txt")),
      jsonHandler(std::make_unique<JsonHandler>("compiller/data.json")),
      config(std::make_unique<Config>(jsonHandler.get())) {

    logger->logServiceInit(logger->getName());

    if (!createDirectory("build")) logger->logError("Failed to create build directory");
    if (!createDirectory("compiller")) logger->logError("Failed to create compiller directory");

    logger->logServiceInit(jsonHandler->getName());
    logger->logServiceInit(config->getName());
    logger->logInfo("All services initialized successfully");

    compile();
}

Compiller::~Compiller() = default;

bool Compiller::createDirectory(const std::string& path) {
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
        logger->logCreate("Created " + path + " directory");
        return true;
    }
    return false;
}

void Compiller::compile() {
    std::unordered_map<std::string, std::string> files = config->getConfig();
    std::ostringstream command;

    command << "g++ ";

    if (files["SRC_PATH"].empty()) {
        command << files["MAIN_NAME"] << ".cpp -o build/" << files["EXE_NAME"];
    } else if (std::filesystem::exists(files["SRC_PATH"]) && std::filesystem::is_directory(files["SRC_PATH"])) {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(files["SRC_PATH"])) {
            if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
                command << entry.path().string() << " ";
            }
        }
        command << files["MAIN_NAME"] << ".cpp -o build/" << files["EXE_NAME"];
    }
    command << " 2> compiller/crash_reports.txt";

    executeCommand(command.str(), files);
}

void Compiller::executeCommand(const std::string& command, std::unordered_map<std::string, std::string>& files) {
    int result = std::system(command.c_str());

    std::cout << std::string(50, '-') << std::endl;
    if (result == 0) {
        logger->logInfo("Command used: " + command);
        logAndDisplaySuccess(files["MAIN_NAME"]);
    } else {
        logAndDisplayError(command);
        return;
    }

    if (files["RUN_AFTER_BUILD"] == "true") {
        runExecutable(files["EXE_NAME"]);
    } else {
        std::system("pause");
    }
}

void Compiller::logAndDisplaySuccess(const std::string& mainName) {
    std::cout << COLOR_GREEN << "[SUCCESS] Compilation successful!" << COLOR_RESET << std::endl;
    std::cout << "See logs in compiller/logs.txt for more info" << std::endl;
    std::cout << "Executable file is located in the build/" << mainName;
    logger->logInfo("Compilation successful");
}

void Compiller::logAndDisplayError(const std::string& command) {
    std::cout << COLOR_RED << "[ERROR] Compilation failed!" << COLOR_RESET << std::endl;
    std::cout << "See crash reports in compiller/crash_reports.txt for more info" << std::endl;
    logger->logError("Compilation failed");
    logger->logInfo("Command used: " + command);
    std::cout << std::string(50, '-') << "\n";
    std::system("pause");
}

void Compiller::runExecutable(const std::string& exeName) {
    std::string runCommand = "build\\" + exeName;
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << COLOR_YELLOW << "[INFO] Executable file is running..." << COLOR_RESET << std::endl;
    std::cout << std::string(50, '-') << "\n";
    std::system(runCommand.c_str());
    logger->logInfo("Command used: " + runCommand);
    std::system("pause");

}