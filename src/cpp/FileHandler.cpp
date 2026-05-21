#include "FileHandler.h"

#include <fstream>
#include <stdexcept>

void FileHandler::saveResult(const std::vector<Feedback>& data, const std::string& outputPath) const {
    const std::string csvContent = buildCsvContent(data);

    try {
        std::ofstream output(outputPath, std::ios::binary);
        if (!output.is_open()) {
            throw std::runtime_error("failed to open output file");
        }

        output << csvContent;
        if (!output.good()) {
            throw std::runtime_error("failed to write csv content");
        }
    } catch (const std::exception&) {
        throw;
    }
}

void FileHandler::save(const std::vector<Feedback>& data) const {
    saveResult(data, "filtered_feedback.csv");
}

std::string FileHandler::buildCsvContent(const std::vector<Feedback>& data) const {
    std::string csv = "\xEF\xBB\xBF";
    csv += "text\n";

    for (const auto& feedback : data) {
        csv += escapeCsvField(feedback.getText());
        csv += '\n';
    }

    return csv;
}

std::string FileHandler::escapeCsvField(const std::string& value) const {
    std::string escaped = "\"";
    for (const char ch : value) {
        if (ch == '"') {
            escaped += "\"\"";
        } else {
            escaped += ch;
        }
    }
    escaped += "\"";
    return escaped;
}
