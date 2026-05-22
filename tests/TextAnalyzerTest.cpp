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

    // Test 14: Session lifecycle - set, get, clear, get (REFACTOR-03-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_saved_value_when_key_exists" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back("좋은 경험");

            // Set
            Session::setCurrentFeedbacks(feedbacks, "default");

            // Get and verify
            auto retrieved = Session::currentFeedbacks("default");
            if (retrieved.size() == 1 && retrieved[0].getText() == "좋은 경험") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Retrieved value doesn't match saved value" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 15: Session lifecycle - return empty when key doesn't exist (REFACTOR-03-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_empty_value_when_key_does_not_exist" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Don't set anything, just get
            auto retrieved = Session::currentFeedbacks("nonexistent_session");
            if (retrieved.size() == 0) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected empty result for nonexistent key" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 16: Session lifecycle - clear removes all values (REFACTOR-03-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_remove_all_values_when_session_is_cleared" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Setup: set multiple state values
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back("테스트");
            Session::setCurrentFeedbacks(feedbacks, "default");

            std::map<std::string, int> sentiment = {{"긍정", 5}};
            std::map<std::string, int> keyword = {{"좋음", 3}};
            Session::setAnalysisResults(sentiment, keyword, "default");
            Session::setFilterState("긍정", "피드백", "default");

            // Clear all
            Session::clear("default");

            // Verify all are cleared
            auto currentFB = Session::currentFeedbacks("default");
            auto filteredFB = Session::filteredFeedbacks("default");
            auto filterState = Session::getFilterState("default");
            auto analysisRes = Session::getAnalysisResults("default");

            bool allCleared = (currentFB.size() == 0 &&
                               filteredFB.size() == 0 &&
                               filterState.sentiment == "" &&
                               filterState.keyword == "" &&
                               analysisRes.sentimentCounts.size() == 0 &&
                               analysisRes.keywordCounts.size() == 0);

            if (allCleared) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Not all values were cleared" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 17: Session isolation - different sessions don't share values (REFACTOR-03-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_not_share_values_when_sessionids_are_different" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks1;
            feedbacks1.emplace_back("세션 1");
            Session::setCurrentFeedbacks(feedbacks1, "session1");

            std::vector<Feedback> feedbacks2;
            feedbacks2.emplace_back("세션 2");
            Session::setCurrentFeedbacks(feedbacks2, "session2");

            // Verify isolation
            auto session1 = Session::currentFeedbacks("session1");
            auto session2 = Session::currentFeedbacks("session2");

            if (session1.size() == 1 && session1[0].getText() == "세션 1" &&
                session2.size() == 1 && session2[0].getText() == "세션 2") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Sessions shared values" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 18: Session lifecycle - selective clear maintains isolation (REFACTOR-03-05)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_clear_only_filter_state_when_clearFilterState_called" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Setup: set both feedbacks and filter state
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back("유지되어야 함");
            Session::setCurrentFeedbacks(feedbacks, "default");
            Session::setFilterState("긍정", "품질", "default");

            // Clear only filter state
            Session::clearFilterState("default");

            // Verify feedbacks still exist but filter state cleared
            auto currentFB = Session::currentFeedbacks("default");
            auto filterState = Session::getFilterState("default");

            if (currentFB.size() == 1 && currentFB[0].getText() == "유지되어야 함" &&
                filterState.sentiment == "" && filterState.keyword == "") {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Selective clear didn't work correctly" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 19: Weighted sentiment scoring - positive keywords outnumber negative (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_positive_when_positive_keywords_outnumber_negative_keywords" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // 3 positive keywords (좋아요, 만족, 감사) vs 1 negative keyword (별로)
            std::string text = u8"좋아요 만족 감사 별로";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 3 - 1 = 2, which is >= 1 (positive threshold)
            if (result == Constants::kSentimentPositive) {
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

    // Test 20: Weighted sentiment scoring - negative keywords outnumber positive (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_negative_when_negative_keywords_outnumber_positive_keywords" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // 1 positive keyword (좋아요) vs 3 negative keywords (별로, 실망, 불만)
            std::string text = u8"좋아요 별로 실망 불만";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 1 - 3 = -2, which is <= -1 (negative threshold)
            if (result == Constants::kSentimentNegative) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '부정' but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 21: Weighted sentiment scoring - equal keyword counts (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_neutral_when_positive_and_negative_keyword_counts_are_equal" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // 2 positive keywords (좋아요, 만족) vs 2 negative keywords (별로, 실망)
            std::string text = u8"좋아요 만족 별로 실망";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 2 - 2 = 0, which is between -1 and 1 (neutral range)
            if (result == Constants::kSentimentNeutral) {
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

    // Test 22: Weighted sentiment scoring - multiple occurrences of same keyword (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_count_multiple_occurrences_of_same_keyword" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // "좋아요" appears 3 times, "별로" appears 1 time
            std::string text = u8"좋아요 좋아요 좋아요 별로";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 3 - 1 = 2, which is >= 1 (positive threshold)
            if (result == Constants::kSentimentPositive) {
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

    // Test 23: Weighted sentiment scoring - high positive count dominates (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_positive_when_positive_keywords_significantly_outnumber_negative" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // 5 positive keywords vs 1 negative keyword
            std::string text = u8"좋아요 만족 감사 친절 추천 별로";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 5 - 1 = 4, which is >= 1 (positive threshold)
            if (result == Constants::kSentimentPositive) {
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

    // Test 24: Weighted sentiment scoring - high negative count dominates (FEATURE-01-01)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_negative_when_negative_keywords_significantly_outnumber_positive" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // 1 positive keyword vs 5 negative keywords
            std::string text = u8"좋아요 별로 실망 불만 불편 최악";
            std::string result = fixture.analyzer.detectSentiment(text);
            // Score: 1 - 5 = -4, which is <= -1 (negative threshold)
            if (result == Constants::kSentimentNegative) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '부정' but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 25: Count positive keywords directly (FEATURE-01-02)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_count_all_positive_keywords_in_text" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 만족 감사 좋아요";  // 4 positive keyword occurrences
            int count = fixture.analyzer.getPositiveKeywordCount(text);
            if (count == 4) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected 4 but got " << count << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 26: Count negative keywords directly (FEATURE-01-02)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_count_all_negative_keywords_in_text" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"별로 실망 불만 별로";  // 4 negative keyword occurrences
            int count = fixture.analyzer.getNegativeKeywordCount(text);
            if (count == 4) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected 4 but got " << count << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 27: Mixed text with both positive and negative keywords (FEATURE-01-02)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_count_positive_and_negative_keywords_separately" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 만족 별로 실망 좋아요";  // 3 positive, 2 negative
            int positiveCount = fixture.analyzer.getPositiveKeywordCount(text);
            int negativeCount = fixture.analyzer.getNegativeKeywordCount(text);
            if (positiveCount == 3 && negativeCount == 2) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected positive=3, negative=2 but got positive=" << positiveCount << ", negative=" << negativeCount << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 28: Empty text returns zero counts (FEATURE-01-02)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_zero_when_counting_keywords_in_empty_text" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = "";
            int positiveCount = fixture.analyzer.getPositiveKeywordCount(text);
            int negativeCount = fixture.analyzer.getNegativeKeywordCount(text);
            if (positiveCount == 0 && negativeCount == 0) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected 0, 0 but got " << positiveCount << ", " << negativeCount << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 29: Calculate relative sentiment score - positive (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_calculate_positive_sentiment_score" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 만족 감사 별로";  // 3 positive - 1 negative = 2
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == 2) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=2 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 30: Calculate relative sentiment score - negative (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_calculate_negative_sentiment_score" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 별로 실망 불만";  // 1 positive - 3 negative = -2
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == -2) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=-2 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 31: Calculate relative sentiment score - neutral (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_calculate_neutral_sentiment_score" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 만족 별로 실망";  // 2 positive - 2 negative = 0
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == 0) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=0 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 32: Calculate relative sentiment score - empty text (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_return_zero_score_for_empty_text" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = "";
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == 0) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=0 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 33: Calculate relative sentiment score - only positive keywords (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_calculate_score_with_only_positive_keywords" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"좋아요 만족 감사";  // 3 positive - 0 negative = 3
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == 3) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=3 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 34: Calculate relative sentiment score - only negative keywords (FEATURE-01-03)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_calculate_score_with_only_negative_keywords" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string text = u8"별로 실망 불만";  // 0 positive - 3 negative = -3
            int score = fixture.analyzer.getSentimentScore(text);
            if (score == -3) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected score=-3 but got " << score << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 35: Classify sentiment with positive threshold boundary (FEATURE-01-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_classify_as_positive_at_threshold" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Score exactly at positive threshold (1)
            std::string text = u8"좋아요 별로";  // 1 positive - 1 negative = 0, but let's use score >= 1
            // Actually, let's use 2 positive - 1 negative = 1 to hit the threshold
            std::string text1 = u8"좋아요 만족 별로";  // 2 positive - 1 negative = 1
            std::string result = fixture.analyzer.detectSentiment(text1);
            if (result == Constants::kSentimentPositive) {
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

    // Test 36: Classify sentiment with negative threshold boundary (FEATURE-01-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_classify_as_negative_at_threshold" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            // Score exactly at negative threshold (-1)
            std::string text = u8"좋아요 별로 실망";  // 1 positive - 2 negative = -1
            std::string result = fixture.analyzer.detectSentiment(text);
            if (result == Constants::kSentimentNegative) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected '부정' but got '" << result << "'" << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 37: Sentiment analysis with weighted classification (FEATURE-01-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_analyze_sentiments_using_weighted_classification" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"좋아요 만족 감사");           // score=3 -> 긍정
            feedbacks.emplace_back(u8"별로 실망");                 // score=-2 -> 부정
            feedbacks.emplace_back(u8"좋아요 별로");              // score=0 -> 중립
            feedbacks.emplace_back(u8"좋아요 만족 별로 실망");     // score=0 -> 중립

            auto result = fixture.analyzer.analyzeSentiment(feedbacks);
            // Expected: 긍정=1, 부정=1, 중립=2
            if (result["긍정"] == 1 && result["부정"] == 1 && result["중립"] == 2) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected 긍정=1, 부정=1, 중립=2 but got 긍정=" << result["긍정"]
                          << ", 부정=" << result["부정"] << ", 중립=" << result["중립"] << std::endl;
                failed++;
            }
            fixture.TearDown();
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 38: Weighted sentiment classification with extreme scores (FEATURE-01-04)
    {
        std::cout << "[TEST] TextAnalyzerTest::should_correctly_classify_extreme_sentiment_scores" << std::endl;
        TextAnalyzerFixture fixture;
        fixture.SetUp();
        try {
            std::string positiveExtreme = u8"좋아요 만족 감사 친절 추천";  // 5 positive - 0 negative = 5
            std::string negativeExtreme = u8"별로 실망 불만 불편 최악";    // 0 positive - 5 negative = -5

            std::string positiveResult = fixture.analyzer.detectSentiment(positiveExtreme);
            std::string negativeResult = fixture.analyzer.detectSentiment(negativeExtreme);

            if (positiveResult == Constants::kSentimentPositive &&
                negativeResult == Constants::kSentimentNegative) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Extreme scores not classified correctly" << std::endl;
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
