#include "Logger.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

bool Logger::debugMode_ = true;

std::string Logger::getTimestamp() {
    const auto now = std::time(nullptr);
    const auto currentTime = *std::localtime(&now);
    std::ostringstream output;
    output << std::put_time(&currentTime, "%Y-%m-%d %H:%M:%S");
    return output.str();
}

void Logger::write(const std::string& level, const std::string& message, const bool useErrorStream) {
    std::ostream& stream = useErrorStream ? std::cerr : std::cout;
    stream << "[" << getTimestamp() << "] " << level << ": " << message << std::endl;
}

void Logger::logInfo(const std::string& message) {
    write("INFO", message, false);
}

void Logger::logWarning(const std::string& message) {
    write("WARNING", message, false);
}

void Logger::logError(const std::string& message) {
    write("ERROR", message, true);
}

void Logger::logDebug(const std::string& message) {
    if (debugMode_) {
        write("DEBUG", message, false);
    }
}

void Logger::setDebugMode(const bool mode) {
    debugMode_ = mode;
}

bool Logger::isDebugMode() {
    return debugMode_;
}
