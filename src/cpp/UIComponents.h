#pragma once

#include <string>
#include <vector>

/**
 * @brief UI 컴포넌트 관련 기능을 제공합니다.
 */
class UIComponents {
public:
    /**
     * @brief 사용 가능한 카테고리 목록을 반환합니다.
     * @return 카테고리 이름들의 벡터 참조
     */
    static const std::vector<std::string>& getCategories();
};
