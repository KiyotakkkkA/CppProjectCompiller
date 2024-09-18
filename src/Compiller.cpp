#include "../includes/Compiller.hpp"
#include <filesystem>
#include <cstdlib>

Compiller::~Compiller() {
    delete logger;
    delete config;
    delete jsonHandler;
}

Compiller::Compiller() {
    logger = new Logger("compiller/logs.txt");
    logger->logServiceInit(logger->getName());

    if (!std::filesystem::exists("build")) {
        std::filesystem::create_directory("build");
        logger->logCreate("Created build directory");
    }

    if (!std::filesystem::exists("compiller")) {
        std::filesystem::create_directory("compiller");
        logger->logCreate("Created compiller directory");
    }

    jsonHandler = new JsonHandler("compiller/data.json");
    logger->logServiceInit(jsonHandler->getName());
    config = new Config(jsonHandler);
    logger->logServiceInit(config->getName());
    logger->logInfo("All services initialized successfully");

    compile();
}

void Compiller::compile() {
    std::unordered_map<std::string, std::string> files = config->getConfig();
    std::string command = "g++ ";
    
    if (files["SRC_PATH"] == "") {
        command = command + files["MAIN_NAME"] + ".cpp" + " -o build/" + files["EXE_NAME"];
    } else {
        if (std::filesystem::exists(files["SRC_PATH"]) && std::filesystem::is_directory(files["SRC_PATH"])) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(files["SRC_PATH"])) {
                if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
                    command += entry.path().string() + " ";
                }
            }
            command += files["MAIN_NAME"] + ".cpp" + " -o build/" + files["EXE_NAME"];
        }
    }
    command += " 2> compiller/crash_reports.txt";
    int result = std::system(command.c_str());

    if (result == 0) {
        std::cout << "Compilation successful\nSee Logs.txt in compiller/ directory for more info" << std::endl;
        std::cout << "Exe file is in build/ directory" << std::endl;
        logger->logInfo("Compilation successful");
        logger->logInfo("Command used: " + command);
    } else {
        std::cout << "Compilation failed\nSee crash_reports.txt in compiller/ directory for more info" << std::endl;
        logger->logError("Compilation failed");
        logger->logInfo("Command used: " + command);
    }
    std::system("pause");
}