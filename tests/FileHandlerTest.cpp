#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>

#include "Feedback.h"
#include "FileHandler.h"

// FileHandlerTest Fixture implementation
// Format follows the testing convention: should_[result]_when_[condition]

class FileHandlerFixture {
public:
    FileHandler handler;
    const char* tempDir = "./test_csv_output";

    void SetUp() {
        // Simple directory creation (using mkdir)
        system("mkdir test_csv_output 2>nul");
    }

    void TearDown() {
        // Clean up temporary test files
        system("rmdir /s /q test_csv_output 2>nul");
    }

    std::string getTempFilePath(const std::string& filename) {
        return std::string(tempDir) + "/" + filename;
    }

    bool fileExists(const std::string& path) {
        std::ifstream file(path);
        return file.good();
    }

    std::string readFileContent(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + path);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    int countLines(const std::string& content) {
        int count = 0;
        for (char ch : content) {
            if (ch == '\n') {
                count++;
            }
        }
        return count;
    }
};

int main() {
    int passed = 0;
    int failed = 0;

    // Test 1: FileHandler should instantiate without error
    {
        std::cout << "[TEST] FileHandlerTest::should_instantiate_handler_without_error" << std::endl;
        try {
            FileHandlerFixture fixture;
            fixture.SetUp();
            FileHandler handler;
            fixture.TearDown();
            std::cout << "[PASS]" << std::endl;
            passed++;
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
    }

    // Test 2: CSV file should be created when feedback is saved
    {
        std::cout << "[TEST] FileHandlerTest::should_create_csv_file_when_feedback_is_saved" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"좋은 제품입니다");

            std::string outputPath = fixture.getTempFilePath("test_output.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            if (fixture.fileExists(outputPath)) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - CSV file was not created" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 3: CSV file should contain UTF-8 BOM
    {
        std::cout << "[TEST] FileHandlerTest::should_include_utf8_bom_in_csv_file" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"피드백 내용");

            std::string outputPath = fixture.getTempFilePath("test_bom.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string content = fixture.readFileContent(outputPath);
            // UTF-8 BOM: 0xEF 0xBB 0xBF
            bool hasBom = (content.size() >= 3 &&
                          (unsigned char)content[0] == 0xEF &&
                          (unsigned char)content[1] == 0xBB &&
                          (unsigned char)content[2] == 0xBF);

            if (hasBom) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - UTF-8 BOM not found in file" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 4: CSV should contain header row
    {
        std::cout << "[TEST] FileHandlerTest::should_write_header_row_in_csv_file" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"테스트");

            std::string outputPath = fixture.getTempFilePath("test_header.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string content = fixture.readFileContent(outputPath);
            // After BOM, should have "text" header
            bool hasHeader = (content.find("text") != std::string::npos);

            if (hasHeader) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - CSV header 'text' not found" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 5: CSV should contain feedback rows
    {
        std::cout << "[TEST] FileHandlerTest::should_write_feedback_rows_in_csv_file" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"첫번째 피드백");
            feedbacks.emplace_back(u8"두번째 피드백");
            feedbacks.emplace_back(u8"세번째 피드백");

            std::string outputPath = fixture.getTempFilePath("test_rows.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string content = fixture.readFileContent(outputPath);
            int lineCount = fixture.countLines(content);
            // Expected: BOM + header line + 3 feedback lines = 4 total lines
            // Note: countLines counts newlines, so 3 newlines = 4 lines total

            if (lineCount >= 3) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Expected at least 3 newlines but got " << lineCount << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 6: CSV field should be escaped with quotes
    {
        std::cout << "[TEST] FileHandlerTest::should_escape_csv_field_with_quotes" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"내용에 \"쌍따옴표\" 있음");

            std::string outputPath = fixture.getTempFilePath("test_escape.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string content = fixture.readFileContent(outputPath);
            // Should contain escaped quotes
            bool hasEscapedQuotes = (content.find("\"\"") != std::string::npos);

            if (hasEscapedQuotes) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - CSV field escaping not found" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 7: Empty feedback list should still have header
    {
        std::cout << "[TEST] FileHandlerTest::should_write_header_even_with_empty_feedback_list" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;  // Empty list

            std::string outputPath = fixture.getTempFilePath("test_empty.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string content = fixture.readFileContent(outputPath);
            bool hasHeader = (content.find("text") != std::string::npos);

            if (hasHeader) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - Header not found in empty feedback CSV" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Test 8: CSV content should match buildCsvContent output
    {
        std::cout << "[TEST] FileHandlerTest::should_match_buildCsvContent_when_saved" << std::endl;
        FileHandlerFixture fixture;
        fixture.SetUp();
        try {
            std::vector<Feedback> feedbacks;
            feedbacks.emplace_back(u8"테스트 내용");

            std::string csvContent = fixture.handler.buildCsvContent(feedbacks);
            std::string outputPath = fixture.getTempFilePath("test_content.csv");
            fixture.handler.saveResult(feedbacks, outputPath);

            std::string fileContent = fixture.readFileContent(outputPath);

            if (csvContent == fileContent) {
                std::cout << "[PASS]" << std::endl;
                passed++;
            } else {
                std::cout << "[FAIL] - File content does not match buildCsvContent output" << std::endl;
                failed++;
            }
        } catch (const std::exception& e) {
            std::cout << "[FAIL] - Exception: " << e.what() << std::endl;
            failed++;
        }
        fixture.TearDown();
    }

    // Summary
    std::cout << "\n========================================" << std::endl;
    std::cout << "Total: " << (passed + failed) << " tests" << std::endl;
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;

    return (failed == 0) ? 0 : 1;
}
