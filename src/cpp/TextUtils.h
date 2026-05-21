#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace TextUtils {
inline bool containsAny(const std::string& targetText, const std::vector<std::string>& keywords) {
    if (targetText.empty() || keywords.empty()) {
        return false;
    }

    return std::any_of(keywords.begin(), keywords.end(), [&targetText](const std::string& keyword) {
        return !keyword.empty() && targetText.find(keyword) != std::string::npos;
    });
}

inline int countKeywordOccurrences(const std::string& targetText, const std::vector<std::string>& keywords) {
    if (targetText.empty() || keywords.empty()) {
        return 0;
    }

    int count = 0;
    for (const auto& keyword : keywords) {
        if (keyword.empty()) {
            continue;
        }

        std::string::size_type position = targetText.find(keyword);
        while (position != std::string::npos) {
            ++count;
            position = targetText.find(keyword, position + keyword.size());
        }
    }

    return count;
}
}
