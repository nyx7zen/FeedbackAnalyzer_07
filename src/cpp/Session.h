#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Feedback.h"

class Session {
public:
    struct FilterState {
        std::string sentiment = "";
        std::string keyword = "";
    };

    /**
     * @brief 세션 상태를 초기화합니다.
     * @param sessionId 초기화할 세션 ID
     */
    static void clear(const std::string& sessionId = "default");

    /**
     * @brief 현재 피드백 목록을 반환합니다.
     * @param sessionId 조회할 세션 ID
     * @return 현재 피드백 목록 참조
     */
    static std::vector<Feedback>& currentFeedbacks(const std::string& sessionId = "default");

    /**
     * @brief 현재 필터 결과 목록을 반환합니다.
     * @param sessionId 조회할 세션 ID
     * @return 필터링된 피드백 목록 참조
     */
    static std::vector<Feedback>& filteredFeedbacks(const std::string& sessionId = "default");

    /**
     * @brief 현재 피드백 목록을 교체합니다.
     * @param feedbacks 저장할 피드백 목록
     * @param sessionId 대상 세션 ID
     */
    static void setCurrentFeedbacks(
        const std::vector<Feedback>& feedbacks,
        const std::string& sessionId = "default");

    /**
     * @brief 필터링된 피드백 목록을 교체합니다.
     * @param feedbacks 저장할 피드백 목록
     * @param sessionId 대상 세션 ID
     */
    static void setFilteredFeedbacks(
        const std::vector<Feedback>& feedbacks,
        const std::string& sessionId = "default");

    /**
     * @brief 현재 선택된 필터 상태를 저장합니다.
     * @param sentiment 감성 필터
     * @param keyword 카테고리 필터
     * @param sessionId 대상 세션 ID
     */
    static void setFilterState(
        const std::string& sentiment,
        const std::string& keyword,
        const std::string& sessionId = "default");

    /**
     * @brief 현재 선택된 필터 상태를 조회합니다.
     * @param sessionId 조회할 세션 ID
     * @return 저장된 필터 상태
     */
    static FilterState getFilterState(const std::string& sessionId = "default");

private:
    struct SessionState {
        std::vector<Feedback> currentFeedbacks;
        std::vector<Feedback> filteredFeedbacks;
        FilterState filterState;
    };

    static std::unordered_map<std::string, SessionState> sessions_;

    static SessionState& state(const std::string& sessionId);
};
