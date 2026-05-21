#pragma once

#include <string>

class Logger {
public:
    static void logInfo(const std::string& message);
    static void logWarning(const std::string& message);
    static void logError(const std::string& message);
    static void logDebug(const std::string& message);

    static void setDebugMode(bool mode);
    static bool isDebugMode();

private:
    static bool debugMode_;

    static std::string getTimestamp();
    static void write(const std::string& level, const std::string& message, bool useErrorStream);
};
