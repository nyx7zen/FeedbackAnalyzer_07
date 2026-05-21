#pragma once

#include <string>
#include <vector>

#include "Feedback.h"

class FileHandler {
public:
    /**
     * @brief 피드백 목록을 CSV 파일로 저장합니다.
     * @param data 저장할 피드백 목록
     * @param outputPath 출력 파일 경로
     */
    void saveResult(const std::vector<Feedback>& data, const std::string& outputPath) const;

    /**
     * @brief 기본 경로에 피드백 목록을 저장합니다.
     * @param data 저장할 피드백 목록
     */
    void save(const std::vector<Feedback>& data) const;

    /**
     * @brief 피드백 목록을 CSV 문자열로 직렬화합니다.
     * @param data 직렬화할 피드백 목록
     * @return UTF-8 BOM이 포함된 CSV 문자열
     */
    std::string buildCsvContent(const std::vector<Feedback>& data) const;

private:
    std::string escapeCsvField(const std::string& value) const;
};
