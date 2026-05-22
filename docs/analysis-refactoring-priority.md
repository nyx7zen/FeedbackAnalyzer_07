# Analysis: Refactoring Priorities

**Phase:** SPEC-02-04  
**Date:** 2026-05-22  
**Scope:** Prioritize refactoring targets and implementation order

---

## Executive Summary

The refactoring effort has **3 critical blockers**, **2 high-priority improvements**, and **2 medium-priority enhancements**.

**Critical Path:**
1. Fix global state (fil_data, Session cleanup)
2. Fix Session lifecycle and binding
3. Extract RequestHandler with dependency injection
4. Implement service layer
5. Extract utilities and HtmlRenderer

**Timeline:** Critical fixes in GREEN phase (blocking everything else)

---

## 1. Critical Issues (BLOCKS REFACTORING)

### Critical Issue #1: Global fil_data State

**Location:** `main.cpp` lines 16, 332, 361

**Problem:**
```cpp
static std::vector<Feedback> fil_data;  // Shared across all routes

// Line 332: /filter writes
fil_data = filtered;

// Line 361: /download reads
for (const auto& iter : fil_data) {
    csv << iter.getText() << "\n";
}
```

**Impact:**
- 🔴 Test isolation impossible
- 🔴 Multi-user data corruption
- 🔴 Flaky order-dependent tests
- ⛔ BLOCKS: GREEN phase tests cannot pass

**Fix Complexity:** LOW (clear, contained)

**Fix Strategy:**
```cpp
// Move to request/session scope
class RequestContext {
    std::vector<Feedback> filteredData;  // Request-scoped
};

// Or move to CsvExporter
class CsvExporter {
    std::vector<Feedback> lastExportData;  // Service-scoped
};
```

**Timeline:** MUST fix in GREEN-01-xx  
**Prerequisite for:** All RED phase tests  
**Enables:** Session-isolated tests

---

### Critical Issue #2: Session Lifecycle (No Cleanup)

**Location:** `Session.cpp` line 3

```cpp
static std::unordered_map<std::string, Session::SessionState> sessions_;
// Never cleaned up, never expires
```

**Problem:**
- 🔴 Sessions accumulate indefinitely → memory leak
- 🔴 Tests share "default" session → contamination
- 🔴 Multi-user broken (all use "default")
- ⛔ BLOCKS: Session isolation tests cannot pass

**Fix Complexity:** MEDIUM (requires lifecycle management)

**Fix Strategy:**
```cpp
class SessionManager {
    // Add expiry tracking
    struct SessionMetadata {
        SessionState state;
        time_t lastAccessedAt;
        int timeoutMinutes;
    };

    // Add cleanup
    void expireSession(const string& id);
    void clearExpiredSessions();  // Call periodically
};
```

**Timeline:** MUST fix in GREEN-01-xx  
**Prerequisite for:** Multi-user scenarios, test cleanup  
**Enables:** Proper session isolation

---

### Critical Issue #3: No Session Reset Between Tests

**Location:** Test teardown (not yet written)

**Problem:**
- 🔴 Session state carries between tests
- 🔴 Global constants may be modified
- 🔴 Test order affects results
- ⛔ BLOCKS: RED phase tests cannot isolate

**Fix Strategy:**
```cpp
class TextAnalyzerTest : public ::testing::Test {
protected:
    void TearDown() override {
        Session::clear("default");        // Clear session
        Constants::resetToDefaults();     // Reset constants
        // Clear other shared state
    }
};
```

**Timeline:** MUST implement in RED phase  
**Prerequisite for:** Test isolation  
**Enables:** Reliable test execution

---

## 2. High-Priority Issues (BLOCKS TESTING)

### High Issue #1: No Dependency Injection

**Location:** `main.cpp` lines 17-18, 274-275, 330, 333-334

```cpp
// Global singletons, cannot mock
static TextAnalyzer textAnalyzer;
static Filters filters;

// Cannot test with mock implementations
sentimentResults = textAnalyzer.sent(feedbacks);
auto filtered = filters.fil(feedbacks, ...);
```

**Impact:**
- 🟡 Cannot mock TextAnalyzer for filtering tests
- 🟡 Cannot mock Filters for analysis tests
- 🟡 Cannot test error scenarios (e.g., analyzer failure)
- ⛔ BLOCKS: Unit testing of service layer

**Fix Complexity:** MEDIUM (requires architectural change)

**Fix Strategy:**
```cpp
class FeedbackService {
    std::shared_ptr<TextAnalyzer> analyzer_;
    std::shared_ptr<Filters> filters_;

public:
    FeedbackService(
        std::shared_ptr<TextAnalyzer> analyzer,
        std::shared_ptr<Filters> filters)
        : analyzer_(analyzer), filters_(filters) {}

    // Now injectable!
};
```

**Timeline:** FIX in GREEN-02-xx after critical issues  
**Prerequisite for:** Unit testing services  
**Enables:** Mock-based testing, error scenario testing

---

### High Issue #2: HTTP Coupling to Session

**Location:** All route handlers access `Session::getCurrentFeedbacks()`

```cpp
// No explicit session ID binding to HTTP request
auto& feedbacks = Session::getCurrentFeedbacks();  // "default" hardcoded
```

**Impact:**
- 🟡 Cannot bind HTTP request → session ID
- 🟡 Cannot implement real session cookies
- 🟡 Multi-user scenarios impossible
- ⛔ BLOCKS: Multi-user feature work

**Fix Complexity:** MEDIUM (requires middleware/context)

**Fix Strategy:**
```cpp
struct RequestContext {
    std::string sessionId;
    Session& sessionManager;

    std::vector<Feedback>& getCurrentFeedbacks() {
        return sessionManager.currentFeedbacks(sessionId);
    }
};

void handleAnalyze(const RequestContext& ctx, ...) {
    auto& feedbacks = ctx.getCurrentFeedbacks();
}
```

**Timeline:** FIX in GREEN-02-xx after critical issues  
**Prerequisite for:** Multi-user support  
**Enables:** Session cookie binding, proper isolation

---

## 3. Medium-Priority Issues (IMPROVES TESTABILITY)

### Medium Issue #1: HTML Rendering Mixed with Routes

**Location:** `main.cpp` lines 81-211 (renderPage function, 130 lines)

```cpp
// HTML generation inline in main()
std::string html = renderPage(success, warning, error, ...);
```

**Impact:**
- 🟡 Cannot test HTML structure independently
- 🟡 Cannot change UI without touching route logic
- 🟡 Cannot unit test page generation
- ⚠️ BLOCKS: UI/presentation testing

**Fix Complexity:** MEDIUM (extract to component)

**Fix Strategy:**
```cpp
class HtmlRenderer {
    std::string renderPage(
        const std::string& success,
        const std::string& warning,
        const std::string& error,
        const std::map<std::string, int>& sentimentResults,
        const std::map<std::string, int>& keywordResults,
        const std::vector<Feedback>& feedbacks) const;
};
```

**Timeline:** Extract in REFACTOR phase  
**Prerequisite for:** UI-independent testing  
**Enables:** HTML snapshot testing, UI refactoring

---

### Medium Issue #2: Utility Functions Mixed with Routes

**Location:** `main.cpp` lines 22-231

```cpp
// Form parsing, URL decoding, CSV parsing all inline
static std::string urlDecode(const std::string& str) { ... }
static std::map<std::string, std::string> parseForm(const std::string& body) { ... }
static std::vector<std::string> parseCsvLine(const std::string& line) { ... }
```

**Impact:**
- 🟡 Cannot unit test parsing independently
- 🟡 Cannot reuse utilities elsewhere
- 🟡 Cannot test error cases for parsing
- ⚠️ BLOCKS: Utility function testing

**Fix Complexity:** LOW (simple extraction)

**Fix Strategy:**
```cpp
namespace HttpUtils {
    std::string urlDecode(const std::string& str);
    std::map<std::string, std::string> parseForm(const std::string& body);
}

namespace CsvUtils {
    std::vector<std::string> parseCsvLine(const std::string& line);
}
```

**Timeline:** Extract in REFACTOR phase  
**Prerequisite for:** Utility testing  
**Enables:** Code reuse, parsing error tests

---

## 4. Priority Matrix

### Blocking Order (What blocks what)

```
fil_data removal
    ↓
Session cleanup
    ↓
Test isolation (session/fil_data clear in TearDown)
    ↓ (enables RED phase)
Dependency injection (TextAnalyzer, Filters)
    ↓
Request context (session binding)
    ↓ (enables service layer testing)
HTML renderer extraction
    ↓
Utility extraction
    ↓ (enables REFACTOR phase)
REFACTOR can proceed
```

### Critical Path

```
Start: RED Phase
  ↓
Write failing tests (expose global state issues)
  ↓
GREEN: Fix #1 (fil_data) - CRITICAL
  ↓
GREEN: Fix #2 (Session cleanup) - CRITICAL
  ↓
GREEN: Fix #3 (Test TearDown) - CRITICAL
  ↓
Tests now pass!
  ↓
GREEN: Fix #4 (Dependency Injection) - HIGH
  ↓
GREEN: Fix #5 (Request Context) - HIGH
  ↓
REFACTOR: Extract HtmlRenderer - MEDIUM
  ↓
REFACTOR: Extract Utilities - MEDIUM
  ↓
Done: Clean architecture!
```

---

## 5. Implementation Roadmap

### Phase: RED (Failing Tests)

**Objective:** Expose all identified risks

| Test | Exposes | Phase Item |
|------|---------|-----------|
| fil_data isolation | Critical #1 | RED-02-04 |
| Session contamination | Critical #2 | RED-02-06 |
| Constants stability | Critical #3 | (new) |
| Singleton mocking | High #1 | (new) |
| Session binding | High #2 | (new) |

**Output:** All tests FAIL initially

---

### Phase: GREEN (Critical Fixes)

**Items:** GREEN-01-01, 01-02, 01-03, 01-04

#### GREEN-01-01: Fix fil_data
- Move from global to request/session scope
- May require CsvExporter state
- Tests: fil_data isolation test passes

#### GREEN-01-02: Add Session cleanup
- Implement `Session::clear()` method
- Call in test TearDown
- Tests: Session isolation test passes

#### GREEN-01-03: Add Constants reset
- Implement `Constants::resetToDefaults()`
- Call in test TearDown
- Tests: Constants stability test passes

#### GREEN-01-04: Reset shared state in tests
- Implement proper test fixtures with TearDown
- Clear all global state between tests
- Tests: Order-independent, repeatable

#### GREEN-02-01 (Future): Dependency Injection
- Inject TextAnalyzer, Filters into services
- Make singletons optional
- Tests: Mock-based tests pass

#### GREEN-02-02 (Future): Request Context
- Extract session ID from request
- Create RequestContext with sessionId
- Tests: Multi-user simulation tests pass

---

### Phase: REFACTOR (Structure)

#### REFACTOR-01-01: Extract RequestHandler
- Move 140 lines from main() to class
- Create public methods for each route
- Tests: RequestHandler unit tests

#### REFACTOR-01-02: Extract HtmlRenderer
- Move 130-line renderPage() to class
- Make as stateless utility
- Tests: HTML snapshot/structure tests

#### REFACTOR-01-03: Extract Utilities
- Create HttpUtils namespace
- Create CsvUtils namespace
- Tests: Utility unit tests

#### REFACTOR-02-01: Implement service layer
- FeedbackService
- FilterService
- FileService
- CsvExporter
- Tests: Service layer tests

---

## 6. Critical Path Analysis

### What blocks GREEN phase?
**Nothing:** Can start immediately

**RED phase prerequisite:**
- Write tests that expose global state issues
- Tests must FAIL to demonstrate problems

### What blocks REFACTOR phase?
- ✅ GREEN phase must complete (critical fixes)
- ✅ All RED tests must pass

### What blocks FEATURE phase?
- ✅ REFACTOR phase must complete (structure ready)
- ✅ Multi-user support requires Request Context

---

## 7. Risk vs. Effort Matrix

| Issue | Severity | Fix Effort | Risk if Unfixed | Priority |
|-------|----------|------------|-----------------|----------|
| fil_data | 🔴 CRITICAL | LOW | Blocks all tests | **1** |
| Session cleanup | 🔴 CRITICAL | MEDIUM | Memory leak, contamination | **2** |
| Test TearDown | 🔴 CRITICAL | LOW | Flaky tests | **3** |
| Dependency injection | 🟡 HIGH | MEDIUM | Cannot mock | **4** |
| Request context | 🟡 HIGH | MEDIUM | No multi-user | **5** |
| HTML extraction | 🟡 MEDIUM | LOW | Cannot test UI | **6** |
| Utils extraction | 🟡 MEDIUM | LOW | Cannot test parsing | **7** |

---

## 8. Quick Start: What to Fix First

### If you have 1 day:
1. ✅ Fix fil_data (move to CsvExporter state)
2. ✅ Implement Session::clear() 
3. ✅ Add test TearDown

→ GREEN-01-01, 01-02, 01-03 → RED tests pass

### If you have 3 days:
1-3. (above) + 
4. ✅ Add Constants::resetToDefaults()
5. ✅ Extract RequestHandler with dependency injection

→ GREEN-01-01 through GREEN-02-01 → Ready for REFACTOR

### If you have 1 week:
1-5. (above) +
6. ✅ Extract HtmlRenderer
7. ✅ Extract HttpUtils, CsvUtils
8. ✅ Implement service layer

→ GREEN and REFACTOR phases → Clean architecture

---

## 9. Dependency Graph

```
RED Tests Write
    ↓
fil_data fix (LOW effort, HIGH impact)
    ↓
Session cleanup (MEDIUM effort, HIGH impact)
    ↓
Test TearDown clear (LOW effort, HIGH impact)
    ↓ (RED tests pass)
Dependency injection (MEDIUM effort, MEDIUM impact)
    ↓
Request context (MEDIUM effort, MEDIUM impact)
    ↓ (GREEN phase complete)
HTML extraction (LOW effort, LOW impact)
    ↓
Utilities extraction (LOW effort, LOW impact)
    ↓ (REFACTOR complete)
Service layer (MEDIUM effort, MEDIUM impact)
    ↓
Ready for FEATURE phase
```

---

## 10. Rollout Strategy

### For Development
1. Work through critical path in order
2. Each item has clear pass/fail criteria
3. Cannot skip critical issues

### For Testing
- RED: Tests fail initially (expected)
- GREEN: Tests pass after fixes
- REFACTOR: Tests still pass (structure only)

### For Code Review
- Each Green fix should pass all RED tests
- REFACTOR changes should pass all GREEN tests
- No test regressions at any phase

---

## Summary

**Refactoring is unblocked after 3 critical fixes:**
1. Move fil_data to request/session scope (LOW effort)
2. Implement Session cleanup mechanism (MEDIUM effort)
3. Add per-test state clearing (LOW effort)

**High-priority improvements after critical fixes:**
4. Add dependency injection (MEDIUM effort)
5. Add request context/session binding (MEDIUM effort)

**Medium-priority improvements in REFACTOR:**
6. Extract HtmlRenderer (LOW effort)
7. Extract utilities (LOW effort)

**Total effort estimate:**
- Critical fixes: 1-2 days
- High-priority: 2-3 days
- Medium-priority: 1-2 days
- **Total: 4-7 days for full refactoring**

---

**Next:** Execute RED phase tests using this priority order
