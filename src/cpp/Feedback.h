#pragma once

#include <string>
#include <utility>

/**
 * @brief 사용자 피드백 데이터를 나타내는 클래스입니다.
 */
class Feedback {
    std::string text;

public:
    /**
     * @brief 주어진 텍스트로 Feedback 객체를 생성합니다.
     * @param t 피드백 텍스트
     */
    explicit Feedback(std::string t) : text(std::move(t)) {}

    /**
     * @brief 피드백 텍스트를 반환합니다.
     * @return 피드백 텍스트 참조
     */
    const std::string& getText() const { return text; }
};
