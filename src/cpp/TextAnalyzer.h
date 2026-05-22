#pragma once

#include <map>
#include <string>
#include <vector>

#include "Feedback.h"

class TextAnalyzer {
public:
    /**
     * @brief 피드백 목록을 감성별로 분류합니다.
     * @param feedbacks 분석할 피드백 목록
     * @return 감성 라벨별 개수
     */
    std::map<std::string, int> analyzeSentiment(const std::vector<Feedback>& feedbacks) const;

    /**
     * @brief 피드백 목록을 카테고리 키워드 기준으로 집계합니다.
     * @param feedbacks 분석할 피드백 목록
     * @return 카테고리별 개수
     */
    std::map<std::string, int> analyzeKeywords(const std::vector<Feedback>& feedbacks) const;

    /**
     * @brief 단일 피드백의 감성을 판별합니다.
     * @param text 분석할 텍스트
     * @return 긍정, 중립, 부정 중 하나의 감성 라벨
     */
    std::string detectSentiment(const std::string& text) const;

    /**
     * @brief 텍스트에서 긍정 키워드의 누적 출현 횟수를 계산합니다.
     * @param text 분석할 텍스트
     * @return 긍정 키워드 총 출현 횟수
     */
    int getPositiveKeywordCount(const std::string& text) const;

    /**
     * @brief 텍스트에서 부정 키워드의 누적 출현 횟수를 계산합니다.
     * @param text 분석할 텍스트
     * @return 부정 키워드 총 출현 횟수
     */
    int getNegativeKeywordCount(const std::string& text) const;
};
