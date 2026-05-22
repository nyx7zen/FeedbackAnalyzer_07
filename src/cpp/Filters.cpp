#include "Filters.h"

#include "Constants.h"
#include "TextAnalyzer.h"
#include "TextUtils.h"

namespace {
bool matchesCategory(const std::string& text, const std::string& category) {
    const auto categoryIt = Constants::CATEGORY_KEYWORDS.find(category);
    if (categoryIt == Constants::CATEGORY_KEYWORDS.end()) {
        return false;
    }

    for (const auto& [groupName, keywords] : categoryIt->second) {
        if (groupName == "main") {
            continue;
        }
        if (TextUtils::containsAny(text, keywords)) {
            return true;
        }
    }

    const auto mainIt = categoryIt->second.find("main");
    return mainIt != categoryIt->second.end() && TextUtils::containsAny(text, mainIt->second);
}

bool matchesSentimentFilter(const std::string& sentiment, const std::string& sentimentFilter) {
    return sentimentFilter == Constants::kFilterAll || sentiment == sentimentFilter;
}

bool matchesKeywordFilter(const std::string& text, const std::string& keywordFilter) {
    return keywordFilter == Constants::kFilterAll || matchesCategory(text, keywordFilter);
}
}

std::vector<Feedback> Filters::applyFilter(
    const std::vector<Feedback>& dataList,
    const std::string& sentimentFilter,
    const std::string& keywordFilter) const {
    TextAnalyzer analyzer;
    std::vector<Feedback> filtered;

    for (const auto& feedback : dataList) {
        const std::string sentiment = analyzer.detectSentiment(feedback.getText());
        const bool matchesSentiment = matchesSentimentFilter(sentiment, sentimentFilter);
        const bool matchesKeyword = matchesKeywordFilter(feedback.getText(), keywordFilter);

        if (matchesSentiment && matchesKeyword) {
            filtered.push_back(feedback);
        }
    }

    return filtered;
}
