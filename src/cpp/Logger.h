#pragma once

#include <string>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    static void logInfo(const std::string& message);
    static void logWarning(const std::string& message);
    static void logError(const std::string& message);
    static void logDebug(const std::string& message);

    static void setDebugMode(bool mode);
    static bool isDebugMode();

    static void setLogLevel(LogLevel level);
    static LogLevel getLogLevel();

private:
    static bool debugMode_;
    static LogLevel currentLogLevel_;

    static std::string getTimestamp();
    static void write(const std::string& level, const std::string& message, bool useErrorStream);
};
