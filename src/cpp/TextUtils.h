#pragma once

#include <algorithm>
#include <string>
#include <vector>

/**
 * @brief 텍스트 처리 유틸리티 함수들을 제공합니다.
 */
namespace TextUtils {
/**
 * @brief 대상 텍스트가 주어진 키워드 중 하나 이상을 포함하는지 확인합니다.
 * @param targetText 검색 대상 텍스트
 * @param keywords 검색할 키워드 목록
 * @return 키워드 중 하나라도 포함되면 true, 아니면 false
 */
inline bool containsAny(const std::string& targetText, const std::vector<std::string>& keywords) {
    if (targetText.empty() || keywords.empty()) {
        return false;
    }

    return std::any_of(keywords.begin(), keywords.end(), [&targetText](const std::string& keyword) {
        return !keyword.empty() && targetText.find(keyword) != std::string::npos;
    });
}

/**
 * @brief 대상 텍스트에서 주어진 키워드들이 출현하는 총 횟수를 계산합니다.
 * @param targetText 검색 대상 텍스트
 * @param keywords 검색할 키워드 목록
 * @return 모든 키워드의 총 출현 횟수
 */
inline int countKeywordOccurrences(const std::string& targetText, const std::vector<std::string>& keywords) {
    if (targetText.empty() || keywords.empty()) {
        return 0;
    }

    int count = 0;
    for (const auto& keyword : keywords) {
        if (keyword.empty()) {
            continue;
        }

        std::string::size_type position = targetText.find(keyword);
        while (position != std::string::npos) {
            ++count;
            position = targetText.find(keyword, position + keyword.size());
        }
    }

    return count;
}
}
