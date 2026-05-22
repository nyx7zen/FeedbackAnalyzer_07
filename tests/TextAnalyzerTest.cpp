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

    // Test 5: Special character input should not throw exception (RED-02-02)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_not_throw_when_input_has_special_characters" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string specialChars = "!@#$%^&*()_+-=[]{}|;:',.<>?/";
            std::string result = fixture.analyzer.detectSentiment(specialChars);
            // Special characters with no keywords should return neutral
            if (result == "중립") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected neutral for special chars, got " << result << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 6: Mixed sentiment input should return dominant sentiment (RED-02-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_positive_when_positive_count_exceeds_negative" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string mixedText = "좋아요 만족 감사 별로 실망";  // 3 positive, 2 negative -> positive
            std::string result = fixture.analyzer.detectSentiment(mixedText);
            if (result == "긍정") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '긍정' but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 7: Filter combination test (RED-02-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_handle_multiple_keywords_in_feedback" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back("배송이 빠르고 품질이 좋습니다");  // Contains multiple categories
            auto result = fixture.analyzer.analyzeKeywords(feedbacks);
            // Should count categories present in feedback
            if (!result.empty()) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected non-empty keyword analysis result" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 8: Neutral filter test - detect neutral sentiment correctly (RED-02-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_neutral_when_positive_and_negative_are_balanced" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string balancedText = "좋아요 별로";  // 1 positive, 1 negative -> balanced -> neutral
            std::string result = fixture.analyzer.detectSentiment(balancedText);
            if (result == "중립") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '중립' for balanced sentiment but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 9: Session isolation test (RED-02-06)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_maintain_session_isolation_between_tests" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Test 1: Add feedback to default session
            std::vector<Feedback> feedbacks1;
            feedbacks1.emplace_back("좋아요");
            fixture.analyzer.analyzeSentiment(feedbacks1);

            // Simulate new test instance
            fixture.TearDown();

            // Test 2: Create new fixture, check session is clean
            TextAnalyzerFixture fixture2;
            fixture2.SetUp();
            std::vector<Feedback> feedbacks2;
            auto result = fixture2.analyzer.analyzeSentiment(feedbacks2);

            // After isolation, empty vector should return all zeros
            bool isClean = (result["긍정"] == 0 && result["부정"] == 0 && result["중립"] == 0);
            if (isClean) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Session not properly isolated" << std::endl;
                failed++;
            }
            fixture2.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 10: Session storage map - store and retrieve analysis results (REFACTOR-03-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_store_and_retrieve_analysis_results_in_session" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Create test analysis results
            std::map<std::string, int> sentimentResults = {{"긍정", 2}, {"부정", 1}, {"중립", 1}};
            std::map<std::string, int> keywordResults = {{"만족", 2}, {"품질", 1}};

            // Store results in session
            Session::setAnalysisResults(sentimentResults, keywordResults, "default");

            // Retrieve and verify
            auto stored = Session::getAnalysisResults("default");
            bool sentimentMatch = (stored.sentimentCounts.size() == 3 &&
                                   stored.sentimentCounts["긍정"] == 2 &&
                                   stored.sentimentCounts["부정"] == 1 &&
                                   stored.sentimentCounts["중립"] == 1);
            bool keywordMatch = (stored.keywordCounts.size() == 2 &&
                                 stored.keywordCounts["만족"] == 2 &&
                                 stored.keywordCounts["품질"] == 1);

            if (sentimentMatch && keywordMatch) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Analysis results not stored/retrieved correctly" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 11: Session clear filter state (REFACTOR-03-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_clear_filter_state_when_clearFilterState_called" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Set filter state
            Session::setFilterState("긍정", "품질", "default");

            // Verify it was set
            auto before = Session::getFilterState("default");
            if (before.sentiment != "긍정" || before.keyword != "품질") {
                std::cout << "[FAIL] - Filter state not set correctly" << std::endl;
                failed++;
            } else {
                // Clear filter state
                Session::clearFilterState("default");

                // Verify it was cleared
                auto after = Session::getFilterState("default");
                if (after.sentiment == "" && after.keyword == "") {
                    std::cout << "[PASS]" << std::endl;
                    passed++;
                } else {
                    std::cout << "[FAIL] - Filter state not cleared" << std::endl;
                    failed++;
                }
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 12: Session clear analysis results (REFACTOR-03-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_clear_analysis_results_when_clearAnalysisResults_called" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Set analysis results
            std::map<std::string, int> sentimentResults = {{"긍정", 5}, {"부정", 3}};
            std::map<std::string, int> keywordResults = {{"만족", 4}};
            Session::setAnalysisResults(sentimentResults, keywordResults, "default");

            // Verify it was set
            auto before = Session::getAnalysisResults("default");
            if (before.sentimentCounts.size() == 0) {
                std::cout << "[FAIL] - Analysis results not set correctly" << std::endl;
                failed++;
            } else {
                // Clear analysis results
                Session::clearAnalysisResults("default");

                // Verify it was cleared
                auto after = Session::getAnalysisResults("default");
                if (after.sentimentCounts.size() == 0 && after.keywordCounts.size() == 0) {
                    std::cout << "[PASS]" << std::endl;
                    passed++;
                } else {
                    std::cout << "[FAIL] - Analysis results not cleared" << std::endl;
                    failed++;
                }
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 13: Session clear feedbacks (REFACTOR-03-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_clear_feedbacks_when_clearFeedbacks_called" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Set feedbacks
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back("좋아요");
            feedbacks.emplace_back("별로");
            Session::setCurrentFeedbacks(feedbacks, "default");

            // Verify it was set
            auto before = Session::currentFeedbacks("default");
            if (before.size() != 2) {
                std::cout << "[FAIL] - Feedbacks not set correctly" << std::endl;
                failed++;
            } else {
                // Clear feedbacks
                Session::clearFeedbacks("default");

                // Verify both current and filtered feedbacks were cleared
                auto afterCurrent = Session::currentFeedbacks("default");
                auto afterFiltered = Session::filteredFeedbacks("default");
                if (afterCurrent.size() == 0 && afterFiltered.size() == 0) {
                    std::cout << "[PASS]" << std::endl;
                    passed++;
                } else {
                    std::cout << "[FAIL] - Feedbacks not cleared" << std::endl;
                    failed++;
                }
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
