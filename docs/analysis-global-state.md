# Analysis: Global State Risks

**Phase:** SPEC-02-02  
**Date:** 2026-05-22  
**Scope:** Identify global state issues and test isolation failure scenarios

---

## Executive Summary

The Feedback Analyzer has **4 global static variables** in `main.cpp` (lines 16-19) and **1 global session map** in `Session.cpp` (line 3) that create **test isolation failures** and **cross-request contamination**. These blocks must be fixed before any refactoring work.

---

## 1. Global Static Variables in main.cpp

### 1.1 Current State

```cpp
// main.cpp lines 16-19
static std::vector<Feedback> fil_data;      // Shared across all requests
static TextAnalyzer textAnalyzer;           // Global singleton
static Filters filters;                     // Global singleton
static FileHandler fileHandler;             // Global singleton
```

### 1.2 Lifetime

**Creation:** Program startup (line 16-19 static initialization)  
**Destruction:** Program shutdown (automatic destruction of static objects)  
**Scope:** Application-wide (shared across all requests, all tests, all sessions)  
**Cleanup:** Never (persists for entire program lifetime)

---

## 2. Detailed Risk Analysis

### Risk #1: fil_data Cross-Request Contamination

**Location:** `main.cpp` line 16 + line 332

**Usage Pattern:**
```cpp
// Line 332: POST /filter route stores filtered results globally
fil_data = filtered;  // Store in global

// Line 361-362: GET /download uses fil_data
for (const auto& iter : fil_data) {
    csv << iter.getText() << "\n";
}
```

**Contamination Scenario:**

| Step | User/Test | Action | State | Problem |
|------|-----------|--------|-------|---------|
| 1 | User A | POST /filter → sentiment="긍정" | `fil_data = [FB1, FB2]` | — |
| 2 | User B | POST /filter → sentiment="부정" | `fil_data = [FB3, FB4]` | ❌ Overwrites A's data! |
| 3 | User A | GET /download | CSV contains `[FB3, FB4]` | ❌ Wrong data! A gets B's results |

**Isolation Failure:**
```cpp
// Test 1
TEST(FilterTests, PositiveFiltering) {
    // Filters to positive feedback, stores in fil_data
    filters.fil(feedbacks, "긍정", "전체");
    // fil_data = [positive items only]
}

// Test 2 (runs after Test 1)
TEST(FilterTests, NegativeFiltering) {
    // Filters to negative feedback
    filters.fil(feedbacks, "부정", "전체");
    // fil_data = [negative items only]
    
    // But now fil_data was modified by Test 1!
    // Global state contamination
}
```

**Risk Level:** 🔴 CRITICAL

---

### Risk #2: TextAnalyzer Singleton Coupling

**Location:** `main.cpp` lines 17, 274-275, 333-334

**Usage Pattern:**
```cpp
static TextAnalyzer textAnalyzer;  // Line 17

// POST /analyze handler (lines 274-275)
sentimentResults = textAnalyzer.sent(feedbacks);
keywordResults = textAnalyzer.kw(feedbacks);

// POST /filter handler (lines 333-334)
auto sentimentResults = textAnalyzer.sent(filtered);
auto keywordResults = textAnalyzer.kw(filtered);
```

**Problem:**

While TextAnalyzer itself is stateless (pure logic), creating it as a global singleton:

1. **Test Interference via Constants:**
   ```cpp
   // TextAnalyzer.cpp uses Constants::SENTIMENT_KEYWORDS
   // If test modifies Constants, all tests see the change
   ```

2. **Test Coupling:**
   - Cannot run tests in parallel (shared global instance)
   - Cannot mock TextAnalyzer for dependency injection
   - Cannot measure per-test performance

3. **Memory Overhead:**
   - One instance for entire application lifetime
   - Shared across all requests (unnecessary overhead)

**Test Scenario:**
```cpp
TEST(TextAnalyzerTests, SentimentAnalysis_Positive) {
    TextAnalyzer analyzer;
    // Might affect global textAnalyzer instance indirectly
}

TEST(TextAnalyzerTests, SentimentAnalysis_Negative) {
    // If tests modify Constants::SENTIMENT_KEYWORDS
    // This test sees modified state
}
```

**Risk Level:** 🟡 HIGH

---

### Risk #3: Filters Singleton State

**Location:** `main.cpp` line 18, 330

**Usage Pattern:**
```cpp
static Filters filters;  // Line 18

// POST /filter route (line 330)
auto filtered = filters.fil(feedbacks, sentiment, keyword);
```

**Issue:**

While Filters is also stateless, the global singleton creates coupling to:
- Cannot mock for testing
- Cannot inject dependencies
- Cannot run tests in parallel without synchronization

If future implementation adds state (e.g., caching, statistics), the global becomes a bottleneck.

**Risk Level:** 🟡 MEDIUM

---

### Risk #4: FileHandler Singleton

**Location:** `main.cpp` line 19

**Problem:**

`FileHandler` is instantiated globally but never used in visible code paths. This suggests:
- Dead code that should be removed, OR
- Unused initialization that creates unnecessary coupling

**Test Risk:**
- Tests cannot initialize FileHandler differently
- FileHandler state (if any) leaks between tests

**Risk Level:** 🟡 MEDIUM

---

## 3. Session State Global Map

**Location:** `Session.cpp` line 3

```cpp
static std::unordered_map<std::string, Session::SessionState> sessions_;
```

### 3.1 Lifecycle Issues

**Problem:**
- Sessions **never cleaned up** → memory leak
- No expiry mechanism → sessions accumulate indefinitely
- No per-session cleanup between tests

**Scenario:**
```
Startup → Create default session → Add feedbacks
    ↓
HTTP Request 1 → Uses "default" session
HTTP Request 2 → Uses "default" session  
HTTP Request 3 → Uses "default" session
    ↓
Day later...
    ↓
Unread sessions: 1000+
Memory: Leaking
Sessions: Never expired
```

### 3.2 Test Isolation via Session

**Problem:**
```cpp
// Test 1
TEST(FeedbackTests, AddFeedback) {
    auto& feedbacks = Session::currentFeedbacks("default");
    feedbacks.push_back(Feedback("test1"));
    // Session::sessions_["default"] now has 1 item
}

// Test 2 (runs after Test 1)
TEST(FeedbackTests, FilterEmpty) {
    auto& feedbacks = Session::currentFeedbacks("default");
    // feedbacks.size() == 1 (still has item from Test 1!)
    // Expected: 0, Got: 1
    // TEST FAILS due to contamination
}
```

### 3.3 Multi-User Scenario

**Current Code:**
```cpp
// All routes use implicit "default" session:
auto& feedbacks = Session::getCurrentFeedbacks();  // Uses "default"

// Multiple concurrent users ALL share "default" session!
User A → Session::sessions_["default"] ← User B
    ↓
Data Corruption
```

**Risk Level:** 🔴 CRITICAL

---

## 4. Test Isolation Failure Scenarios

### Scenario A: Global fil_data Contamination

```
Test Suite Run:
├─ Test_FilterPositive
│  └─ Call filters.fil(...) → stores result in fil_data
│
├─ Test_DownloadCSV (depends on fil_data)
│  └─ Expected: Previous filter result
│  └─ Actual: fil_data from last test that used it
│  └─ FLAKY TEST (order-dependent)
│
└─ Test_FilterNegative
   └─ Overwrites fil_data again
   └─ Test_DownloadCSV now sees wrong data
```

### Scenario B: Session State Leakage

```
Test Suite Run:
├─ Test_AnalyzeFeedback_1
│  └─ Session::currentFeedbacks("default").push_back(Feedback("test1"))
│
├─ Test_AnalyzeFeedback_2
│  └─ Session::currentFeedbacks("default")
│  └─ Expected: empty vector
│  └─ Actual: contains item from Test 1
│  └─ TEST FAILS
│
└─ Test_FilterEmpty
   └─ auto& feedbacks = Session::currentFeedbacks("default")
   └─ Expected: 0 items
   └─ Actual: 1+ items (accumulated from previous tests)
   └─ TEST FAILS
```

### Scenario C: Constants Modification During Tests

```
Test Suite:
├─ Test_CustomSentimentKeywords
│  └─ Modify Constants::SENTIMENT_KEYWORDS["긍정"].push_back("amazing")
│  └─ TextAnalyzer uses modified keywords
│
├─ Test_StandardSentiment (runs after)
│  └─ Uses standard keywords
│  └─ But Constants was modified by previous test!
│  └─ TEST GIVES WRONG RESULT
│
└─ Test_NeutralClassification
   └─ Depends on "amazing" NOT being positive
   └─ But it was added by earlier test
   └─ TEST FAILS
```

---

## 5. Multi-User Scenario

### Current Behavior

**All routes use single implicit session:**

```cpp
svr.Post("/analyze", [](const httplib::Request& req, httplib::Response& res) {
    auto& feedbacks = Session::currentFeedbacks();  // "default" always
    // ...
});

svr.Post("/filter", [](const httplib::Request& req, httplib::Response& res) {
    auto& feedbacks = Session::currentFeedbacks();  // "default" always
    // ...
});
```

**Multi-User Scenario:**

```
Time  | User A                 | User B                 | Session State
------|------------------------|------------------------|-------------------
T1    | POST /analyze "great"  |                        | default: [great]
T2    |                        | POST /analyze "bad"    | default: [great, bad]
T3    | GET (expects "great")  |                        | default: [great, bad]
      | GETS WRONG DATA!       |                        | ❌ CROSS-CONTAMINATION
T4    |                        | POST /filter negative   | default: [bad]
T5    | GET /download          |                        | Gets "bad" not "great"
      | WRONG DATA!            |                        | ❌ DATA CORRUPTION
```

---

## 6. Root Cause Analysis

### Why Global State Was Chosen

1. **Simplicity:** Single global instance is easier to write initially
2. **Convenience:** No dependency injection complexity
3. **No Framework:** httplib is header-only, no built-in DI container

### Why It's Problematic

1. **Testing:** Impossible to isolate tests
2. **Concurrency:** Race conditions in multi-user scenarios
3. **Maintenance:** Hidden coupling makes refactoring dangerous
4. **Scalability:** Single instance bottleneck

---

## 7. Cleanup Strategy

### Immediate Action (GREEN Phase)

1. **Add Session Reset Per Test**
   ```cpp
   void TearDown() override {
       Session::clear("default");  // Clear between tests
   }
   ```

2. **Add fil_data Clear Per Test**
   ```cpp
   // Must add public clear method
   // Then call in TearDown
   ```

3. **Add Constants Reset**
   ```cpp
   void TearDown() override {
       Constants::resetToDefaults();  // If implementing this
   }
   ```

### Long-Term Fix (REFACTOR Phase)

1. **Move Globals to Request Context**
   ```cpp
   class RequestContext {
       std::vector<Feedback> fil_data;  // Request-scoped
       std::unique_ptr<TextAnalyzer> analyzer;  // Per-request
       std::unique_ptr<Filters> filters;  // Per-request
   };
   ```

2. **Implement Proper Session Lifecycle**
   ```cpp
   class SessionManager {
       void expireSession(const string& id, int timeoutMinutes);
       void clearExpiredSessions();
   };
   ```

3. **Bind HTTP Request → Session Automatically**
   - Extract session ID from cookie or URL
   - Create request context with session ID
   - Pass context through route handlers

---

## 8. Test Isolation Risks Summary

| Global | Type | Test Risk | Multi-User Risk | Fix Complexity |
|--------|------|-----------|-----------------|-----------------|
| `fil_data` | Data | 🔴 CRITICAL | 🔴 CRITICAL | MEDIUM (clear) |
| `textAnalyzer` | Singleton | 🟡 HIGH | 🟡 MEDIUM | HIGH (DI) |
| `filters` | Singleton | 🟡 MEDIUM | 🟡 MEDIUM | HIGH (DI) |
| `fileHandler` | Singleton | 🟡 MEDIUM | 🟡 MEDIUM | HIGH (DI) |
| `sessions_` map | Map | 🔴 CRITICAL | 🔴 CRITICAL | HIGH (lifecycle) |

---

## 9. RED Phase Test Requirements

To expose these risks, RED phase must write tests that:

1. **fil_data Isolation Test**
   - Filter positive → check download contains positives only
   - Filter negative → check download contains negatives only
   - **Must FAIL** with current code (data gets overwritten)

2. **Session State Isolation Test**
   - Add feedback in Test 1
   - Test 2 expects empty session
   - **Must FAIL** with current code (state carries over)

3. **Concurrent Session Test**
   - Simulate 2 concurrent requests with different sessionIds
   - **Must FAIL** with "default" hardcoding

4. **Constants Stability Test**
   - Verify sentiment keywords unchanged after test
   - **Must FAIL** if test modifies Constants

---

## 10. Dependency on Other SPEC Tasks

- **SPEC-02-03:** Main coupling analysis will show how routes access globals
- **SPEC-02-04:** Prioritization will show which globals to fix first
- **RED Phase:** Tests will expose each global state problem
- **GREEN Phase:** Fixes will move globals to request/session scope

---

## Summary

**Critical Finding:** Global state is the #1 refactoring blocker.

- **fil_data:** Shared across requests → wrong data downloads, test isolation fails
- **textAnalyzer, filters, fileHandler:** Singletons → no DI, test coupling
- **Session::sessions_:** Never cleaned up → memory leak, multi-user broken

**Cannot write reliable tests** until global state is moved to request/session scope.

**Next:** SPEC-02-03 analyzes main.cpp coupling to these globals.
