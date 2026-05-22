#include "Session.h"

std::unordered_map<std::string, Session::SessionState> Session::sessions_;

Session::SessionState& Session::state(const std::string& sessionId) {
    return sessions_[sessionId];
}

void Session::clear(const std::string& sessionId) {
    sessions_[sessionId] = SessionState{};
}

std::vector<Feedback>& Session::currentFeedbacks(const std::string& sessionId) {
    return state(sessionId).currentFeedbacks;
}

std::vector<Feedback>& Session::filteredFeedbacks(const std::string& sessionId) {
    return state(sessionId).filteredFeedbacks;
}

void Session::setCurrentFeedbacks(const std::vector<Feedback>& feedbacks, const std::string& sessionId) {
    state(sessionId).currentFeedbacks = feedbacks;
}

void Session::setFilteredFeedbacks(const std::vector<Feedback>& feedbacks, const std::string& sessionId) {
    state(sessionId).filteredFeedbacks = feedbacks;
}

void Session::setFilterState(
    const std::string& sentiment,
    const std::string& keyword,
    const std::string& sessionId) {
    state(sessionId).filterState = FilterState{sentiment, keyword};
}

Session::FilterState Session::getFilterState(const std::string& sessionId) {
    return state(sessionId).filterState;
}

void Session::setAnalysisResults(
    const std::map<std::string, int>& sentiment,
    const std::map<std::string, int>& keyword,
    const std::string& sessionId) {
    state(sessionId).analysisResults.sentimentCounts = sentiment;
    state(sessionId).analysisResults.keywordCounts = keyword;
}

Session::AnalysisResults Session::getAnalysisResults(const std::string& sessionId) {
    return state(sessionId).analysisResults;
}

void Session::clearFilterState(const std::string& sessionId) {
    state(sessionId).filterState = FilterState{};
}

void Session::clearAnalysisResults(const std::string& sessionId) {
    state(sessionId).analysisResults = AnalysisResults{};
}

void Session::clearFeedbacks(const std::string& sessionId) {
    state(sessionId).currentFeedbacks.clear();
    state(sessionId).filteredFeedbacks.clear();
}
