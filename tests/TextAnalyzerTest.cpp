#include <iostream>
#include <vector>

#include "Constants.h"
#include "Feedback.h"
#include "Session.h"
#include "TextAnalyzer.h"

// TextAnalyzerTest Fixture implementation
// This will be migrated to Google Test once GTest is installed
// Format follows the testing convention: should_[result]_when_[condition]

class TextAnalyzerFixture {
public:
    TextAnalyzer analyzer;

    void SetUp() {
        // Initialize Constants for each test (sentiment/keyword dictionaries)
        Constants::init();

        // Reset session state to ensure test isolation
        Session::clear("default");
    }

    void TearDown() {
        // Cleanup after each test
        // Clear session to prevent state leakage to next test
        Session::clear("default");
    }
};

int main() {
    int passed = 0;
    int failed = 0;

    // Test 1: Fixture should compile and instantiate
    {
        std::cout << "[TEST] TextAnalyzerTest::should_compile_fixture_when_created" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            fixture.TearDown();
            std::cout << "[PASS]" << std::endl;
            passed++;
        } catch (...) {
            std::cout << "[FAIL]" << std::endl;
            failed++;
        }
    }

    // Test 2: Analyzer should return zero sentiment counts for empty input
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_zero_counts_for_all_sentiments_when_input_is_empty" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            auto result = fixture.analyzer.analyzeSentiment(feedbacks);
            // Empty input should return map with all sentiment keys initialized to 0
            if (result.size() == 3 &&
                result["긍정"] == 0 && result["부정"] == 0 && result["중립"] == 0) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected map with 3 keys all set to 0" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 3: Empty string should be detected as neutral without exception
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_neutral_when_input_is_empty_string" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string emptyText = "";
            std::string result = fixture.analyzer.detectSentiment(emptyText);
            // Empty string should return neutral (no positive/negative keywords)
            if (result == "중립") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '중립' but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 4: Empty feedback vector should return empty keyword counts
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_zero_keyword_counts_when_input_is_empty" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            auto result = fixture.analyzer.analyzeKeywords(feedbacks);
            // Check if all category counts are 0
            bool allZero = true;
            for (const auto& [category, count] : result) {
                if (count != 0) {
                    allZero = false;
                    break;
                }
            }
            if (allZero && !result.empty()) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected all keyword counts to be 0 with empty input" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Summary
    std::cout << "\n========================================" << std::endl;
    std::cout << "Total: " << (passed + failed) << " tests" << std::endl;
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;

    return (failed == 0) ? 0 : 1;
}
