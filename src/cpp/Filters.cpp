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
}

std::vector<Feedback> Filters::applyFilter(
    const std::vector<Feedback>& dataList,
    const std::string& sentimentFilter,
    const std::string& keywordFilter) const {
    TextAnalyzer analyzer;
    std::vector<Feedback> filtered;

    for (const auto& feedback : dataList) {
        const bool matchesSentiment =
            sentimentFilter == Constants::kFilterAll ||
            analyzer.detectSentiment(feedback.getText()) == sentimentFilter;

        const bool matchesKeyword =
            keywordFilter == Constants::kFilterAll ||
            matchesCategory(feedback.getText(), keywordFilter);

        if (matchesSentiment && matchesKeyword) {
            filtered.push_back(feedback);
        }
    }

    return filtered;
}
