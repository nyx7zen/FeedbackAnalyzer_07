#include "TextAnalyzer.h"

#include "Constants.h"
#include "TextUtils.h"

namespace {
int getPositiveKeywordCountHelper(const std::string& text) {
    return TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentPositive]);
}

int getNegativeKeywordCountHelper(const std::string& text) {
    return TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentNegative]);
}

int calculateSentimentScore(const std::string& text) {
    const int positiveCount = getPositiveKeywordCountHelper(text);
    const int negativeCount = getNegativeKeywordCountHelper(text);
    return positiveCount - negativeCount;
}

bool doesFeedbackMatchCategory(const std::string& text, const std::string& category) {
    const auto categoryIt = Constants::CATEGORY_KEYWORDS.find(category);
    if (categoryIt == Constants::CATEGORY_KEYWORDS.end()) {
        return false;
    }

    const auto mainIt = categoryIt->second.find("main");
    return mainIt != categoryIt->second.end() && TextUtils::containsAny(text, mainIt->second);
}

std::map<std::string, int> initializeCategoryResults() {
    std::map<std::string, int> results;
    for (const auto& [category, _] : Constants::CATEGORY_KEYWORDS) {
        results[category] = 0;
    }
    return results;
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
    auto results = initializeCategoryResults();

    for (const auto& feedback : feedbacks) {
        for (const auto& [category, _] : Constants::CATEGORY_KEYWORDS) {
            if (doesFeedbackMatchCategory(feedback.getText(), category)) {
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

int TextAnalyzer::getPositiveKeywordCount(const std::string& text) const {
    return getPositiveKeywordCountHelper(text);
}

int TextAnalyzer::getNegativeKeywordCount(const std::string& text) const {
    return getNegativeKeywordCountHelper(text);
}
