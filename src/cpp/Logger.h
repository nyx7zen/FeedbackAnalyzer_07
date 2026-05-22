#pragma once

#include <string>

/**
 * @brief 로깅 레벨을 정의합니다.
 */
enum class LogLevel {
    /** @brief 정보 메시지 */
    Info,
    /** @brief 경고 메시지 */
    Warning,
    /** @brief 에러 메시지 */
    Error
};

/**
 * @brief 로깅 기능을 제공합니다.
 *
 * 레벨별 로깅, 디버그 모드 제어, 로그 레벨 필터링 기능을 지원합니다.
 */
class Logger {
public:
    /**
     * @brief 정보 메시지를 로깅합니다.
     * @param message 로깅할 메시지
     */
    static void logInfo(const std::string& message);

    /**
     * @brief 경고 메시지를 로깅합니다.
     * @param message 로깅할 메시지
     */
    static void logWarning(const std::string& message);

    /**
     * @brief 에러 메시지를 로깅합니다.
     * @param message 로깅할 메시지
     */
    static void logError(const std::string& message);

    /**
     * @brief 디버그 메시지를 로깅합니다.
     * @param message 로깅할 메시지
     */
    static void logDebug(const std::string& message);

    /**
     * @brief 디버그 모드를 설정합니다.
     * @param mode true면 디버그 모드 활성화, false면 비활성화
     */
    static void setDebugMode(bool mode);

    /**
     * @brief 현재 디버그 모드 상태를 반환합니다.
     * @return 디버그 모드 활성화 여부
     */
    static bool isDebugMode();

    /**
     * @brief 로그 레벨을 설정합니다.
     * @param level 설정할 로그 레벨
     */
    static void setLogLevel(LogLevel level);

    /**
     * @brief 현재 로그 레벨을 반환합니다.
     * @return 현재 로그 레벨
     */
    static LogLevel getLogLevel();

private:
    static bool debugMode_;
    static LogLevel currentLogLevel_;

    static std::string getTimestamp();
    static void write(const std::string& level, const std::string& message, bool useErrorStream);
};
