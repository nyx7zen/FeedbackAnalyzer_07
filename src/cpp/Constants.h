#pragma once

#include <map>
#include <string>
#include <vector>

/**
 * @brief 감성 분석 및 카테고리 분석에 사용되는 상수 및 키워드 저장소입니다.
 */
class Constants {
public:
    /** @brief 긍정 감성 라벨 */
    inline static const std::string kSentimentPositive = u8"긍정";
    /** @brief 중립 감성 라벨 */
    inline static const std::string kSentimentNeutral = u8"중립";
    /** @brief 부정 감성 라벨 */
    inline static const std::string kSentimentNegative = u8"부정";
    /** @brief 전체 필터 라벨 */
    inline static const std::string kFilterAll = u8"전체";
    /** @brief 긍정 감성 판정 임계값 */
    inline static constexpr int kPositiveThreshold = 1;
    /** @brief 부정 감성 판정 임계값 */
    inline static constexpr int kNegativeThreshold = -1;

    /** @brief 감성 키워드 사전 (감성 라벨 -> 키워드 목록) */
    static std::map<std::string, std::vector<std::string>> SENTIMENT_KEYWORDS;
    /** @brief 카테고리 키워드 사전 (카테고리 -> 감성별 키워드 목록) */
    static std::map<std::string, std::map<std::string, std::vector<std::string>>> CATEGORY_KEYWORDS;

    /**
     * @brief 감성 및 카테고리 키워드 사전을 초기화합니다.
     */
    static void init();
};
