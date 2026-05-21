#include "TextAnalyzer.h"

#include "Constants.h"
#include "TextUtils.h"

namespace {
int calculateSentimentScore(const std::string& text) {
    const int positiveCount =
        TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentPositive]);
    const int negativeCount =
        TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentNegative]);
    return positiveCount - negativeCount;
}
}

std::map<std::string, int> TextAnalyzer::analyzeSentiment(const std::vector<Feedback>& feedbacks) const {
    std::map<std::string, int> results = {
        {Constants::kSentimentPositive, 0},
        {Constants::kSentimentNeutral, 0},
        {Constants::kSentimentNegative, 0},
    };

    for (const auto& feedback : feedbacks) {
        ++results[detectSentiment(feedback.getText())];
    }

    return results;
}

std::map<std::string, int> TextAnalyzer::analyzeKeywords(const std::vector<Feedback>& feedbacks) const {
    std::map<std::string, int> results;

    for (const auto& [category, _] : Constants::CATEGORY_KEYWORDS) {
        results[category] = 0;
    }

    for (const auto& feedback : feedbacks) {
        for (const auto& [category, keywordGroups] : Constants::CATEGORY_KEYWORDS) {
            const auto mainIt = keywordGroups.find("main");
            if (mainIt != keywordGroups.end() && TextUtils::containsAny(feedback.getText(), mainIt->second)) {
                ++results[category];
            }
        }
    }

    return results;
}

std::string TextAnalyzer::detectSentiment(const std::string& text) const {
    const int score = calculateSentimentScore(text);

    if (score >= Constants::kPositiveThreshold) {
        return Constants::kSentimentPositive;
    }
    if (score <= Constants::kNegativeThreshold) {
        return Constants::kSentimentNegative;
    }
    return Constants::kSentimentNeutral;
}
