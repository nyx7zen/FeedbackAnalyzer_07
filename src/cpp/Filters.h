#pragma once

#include <string>
#include <vector>

#include "Feedback.h"

class Filters {
public:
    /**
     * @brief 감성과 카테고리 조건을 이용해 피드백을 필터링합니다.
     * @param dataList 원본 피드백 목록
     * @param sentimentFilter 감성 필터 값
     * @param keywordFilter 카테고리 필터 값
     * @return 필터링된 피드백 목록
     */
    std::vector<Feedback> applyFilter(
        const std::vector<Feedback>& dataList,
        const std::string& sentimentFilter,
        const std::string& keywordFilter) const;
};
