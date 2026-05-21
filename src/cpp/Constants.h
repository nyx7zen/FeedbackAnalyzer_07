#pragma once

#include <map>
#include <string>
#include <vector>

class Constants {
public:
    inline static const std::string kSentimentPositive = u8"긍정";
    inline static const std::string kSentimentNeutral = u8"중립";
    inline static const std::string kSentimentNegative = u8"부정";
    inline static const std::string kFilterAll = u8"전체";
    inline static constexpr int kPositiveThreshold = 1;
    inline static constexpr int kNegativeThreshold = -1;

    static std::map<std::string, std::vector<std::string>> SENTIMENT_KEYWORDS;
    static std::map<std::string, std::map<std::string, std::vector<std::string>>> CATEGORY_KEYWORDS;

    static void init();
};
