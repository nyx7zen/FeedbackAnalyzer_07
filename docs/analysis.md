# Feedback Analyzer: Architecture Analysis

**Date:** 2026-05-22  
**Phase:** SPEC-02-01  
**Scope:** Current structure diagnosis, refactoring risks, improvement direction

---

## 1. Current Architecture Overview

The Feedback Analyzer follows a monolithic server pattern with mixed concerns:

```
HTTP Server (main.cpp)
├── HTTP Routing & Request Handling
├── Form Parsing & URL Decoding  
├── HTML Rendering & UI Components
├── State Management (Session)
└── Domain Logic Integration
    ├── TextAnalyzer (sentiment/keyword analysis)
    ├── Filters (filtering logic)
    ├── Constants (keyword definitions)
    └── Logger (logging)
```

### Component Mapping

| Component | Location | Purpose | Scope |
|-----------|----------|---------|-------|
| `main()` | `main.cpp` | HTTP server, route handlers | All routing + rendering |
| `TextAnalyzer` | `TextAnalyzer.{h,cpp}` | Sentiment/keyword analysis | Domain logic |
| `Filters` | `Filters.{h,cpp}` | Filter application logic | Domain logic |
| `Session` | `Session.{h,cpp}` | In-memory state storage | State management |
| `Constants` | `Constants.{h,cpp}` | Keyword definitions | Configuration |
| `Logger` | `Logger.{h,cpp}` | Logging utilities | Instrumentation |
| `FileHandler` | `FileHandler.{h,cpp}` | File I/O operations | File handling |
| `UIComponents` | `UIComponents.{h,cpp}` | UI category definitions | UI metadata |
| `Feedback` | `Feedback.h` | Feedback entity | Data model |

---

## 2. Mixing of Concerns: Critical Issues

### 2.1 HTTP Layer & Business Logic Mixing

**Location:** `main.cpp` (lines 233-372)

**Problem:**
```cpp
int main() {
    // Business initialization
    Constants::init();           // Domain init
    Filters::initFilterKeywords(); // Domain init
    
    // HTTP server setup
    httplib::Server svr;
    
    // Route handler: HTTP + rendering + business logic
    svr.Post("/analyze", [](const httplib::Request& req, httplib::Response& res) {
        // Parse form data (HTTP concern)
        auto params = parseForm(req.body);
        
        // Modify global session state (state mgmt concern)
        auto& feedbacks = Session::getCurrentFeedbacks();
        feedbacks.push_back(Feedback(text));
        
        // Invoke domain logic (business concern)
        sentimentResults = textAnalyzer.sent(feedbacks);
        keywordResults = textAnalyzer.kw(feedbacks);
        
        // Render HTML response (UI concern)
        std::string html = renderPage(success, "", "", sentimentResults, ...);
        res.set_content(html, "text/html; charset=UTF-8");
    });
}
```

**Impact:**
- **Testing:** Cannot test domain logic without HTTP/UI layer
- **Reusability:** Logic tightly coupled to HTTP semantics
- **Maintenance:** Difficult to change UI or API without breaking domain logic

### 2.2 Global Static State Without Isolation

**Location:** `main.cpp` (lines 16-19)

```cpp
static std::vector<Feedback> fil_data;      // Global shared state
static TextAnalyzer textAnalyzer;           // Global singleton
static Filters filters;                     // Global singleton
static FileHandler fileHandler;             // Global singleton
```

**Risks:**
- **Test Isolation Failure:** Multiple tests using same global state → cross-test contamination
- **Session Confusion:** `fil_data` holds filtered results but Session holds current feedback
- **Concurrent Access:** No synchronization → race conditions in multi-session environment
- **State Leakage:** Previous request data persists across sessions

### 2.3 Session State Management Issues

**Location:** `Session.h` (lines 10-14) + `main.cpp` (lines 242, 250)

**Problem:**
```cpp
// In main.cpp:
svr.Get("/", [...](const httplib::Request&, httplib::Response& res) {
    Session::initSessionStateUgly();  // <-- NAME indicates this is problematic
    auto& feedbacks = Session::getOldDataFromSession("current_feedbacks");
});

// Session implementation uses string IDs with no lifecycle management
static std::unordered_map<std::string, SessionState> sessions_;
```

**Issues:**
- **No Session Cleanup:** Sessions never expire → memory leak
- **Implicit Defaults:** "default" sessionId used everywhere, no proper request → session binding
- **No Session ID Validation:** Any string works as sessionId
- **Method Naming:** Methods called `initSessionStateUgly()` and `getOldDataFromSession()` suggest known design debt

### 2.4 Inline Utilities in main.cpp

**Location:** `main.cpp` (lines 22-78)

```cpp
// Utility functions defined in main.cpp:
static std::string urlDecode(const std::string& str) { ... }
static std::map<std::string, std::string> parseForm(const std::string& body) { ... }
static std::string getCurrentTimestamp() { ... }
static std::string escapeHtml(const std::string& s) { ... }
static std::string renderPage(...) { ... }  // 130+ lines of HTML
static std::vector<std::string> parseCsvLine(const std::string& line) { ... }
```

**Impact:**
- **Clutter:** ~250 lines of utility/UI code in main function file
- **Reusability:** URL decoding, form parsing, CSV parsing are duplicated/unavailable elsewhere
- **Testability:** Cannot unit-test these utilities without starting HTTP server

---

## 3. Domain Logic Architecture (Clean Areas)

These components follow good separation of concerns:

### 3.1 TextAnalyzer (Well-Isolated)
- **Input:** `vector<Feedback>` or single text string
- **Output:** Analysis results (sentiment, keyword counts)
- **Dependencies:** `Constants`, `TextUtils`
- **Testability:** Pure logic, no I/O or state
- **Status:** ✅ Ready for testing

### 3.2 Filters (Well-Isolated)
- **Input:** Feedback list + filter criteria
- **Output:** Filtered feedback list
- **Dependencies:** `TextAnalyzer`, `Constants`, `TextUtils`
- **Testability:** Pure logic, deterministic behavior
- **Status:** ✅ Ready for testing

### 3.3 Constants (Immutable Globals)
- **Design:** Centralized keyword definitions
- **Safety:** Static initialization, read-only access
- **Status:** ✅ Good pattern for configuration

---

## 4. Refactoring Risk Assessment

### 🔴 Critical Risks (Block Refactoring)

1. **Global Static Coupling**
   - `fil_data` shared across all requests
   - No way to isolate tests
   - **Risk Level:** CRITICAL
   - **Impact:** Cannot write reliable tests

2. **Session Lifecycle Management**
   - Sessions never cleaned up
   - Memory leak on long-running server
   - **Risk Level:** CRITICAL
   - **Impact:** Production stability issue

3. **main.cpp Monolithic Size & Complexity**
   - 372 lines mixing HTTP, rendering, parsing, domain logic
   - 130-line HTML rendering inline
   - **Risk Level:** HIGH
   - **Impact:** Difficult to test, maintain, refactor

### 🟡 High Risks (Refactoring Prerequisite)

4. **No HTTP Request → Session Binding**
   - All requests use "default" sessionId
   - Cannot support real multi-user scenarios
   - **Risk Level:** HIGH
   - **Impact:** Must fix before feature work

5. **Naming Smells (Design Debt Indicators)**
   - `initSessionStateUgly()`
   - `getOldDataFromSession()`
   - These names signal known bad design
   - **Risk Level:** MEDIUM
   - **Impact:** Technical debt increases maintenance cost

6. **HTML Rendering Mixed with Logic**
   - 130+ line `renderPage()` function
   - String concatenation for HTML (no templating)
   - Hardcoded Korean strings throughout
   - **Risk Level:** MEDIUM
   - **Impact:** Difficult to change UI independently

### 🟢 Low Risks (Ready for Testing)

7. **TextAnalyzer & Filters**
   - Pure logic components
   - No global state dependencies (except Constants)
   - Can be tested independently
   - **Risk Level:** LOW
   - **Status:** ✅ Ready for unit testing

---

## 5. Refactoring Priorities

### Phase Breakdown (RED → GREEN → REFACTOR)

#### Phase-1: RED (Test Framework & Failing Tests)
- [ ] Set up Google Test framework with proper test fixtures
- [ ] Create tests that expose global state coupling
- [ ] Create tests that expose session isolation failures
- [ ] **Must fail initially** to drive refactoring need

#### Phase-2: GREEN (Minimum Fixes)
1. **Fix Global State Isolation** (CRITICAL)
   - Remove global `fil_data`, `textAnalyzer`, `filters`, `fileHandler`
   - Move to request-scoped or session-scoped instances
   
2. **Fix Session Lifecycle** (CRITICAL)
   - Implement proper session timeout/cleanup
   - Bind HTTP request → session automatically
   
3. **Add Logger Level Control** (PREREQUISITE)
   - Quiet logs during tests
   - Enable detailed logs during development

4. **Reset Session State Per Test** (PREREQUISITE)
   - Clear global state between tests
   - Ensure test isolation

#### Phase-3: REFACTOR (Structure Improvements)
1. **Extract HTTP Utilities**
   - Create `HttpUtils.cpp` for URL decoding, form parsing
   - Create `HtmlRenderer.cpp` for page rendering
   
2. **Separate Concerns**
   - Move domain logic calls out of route handlers
   - Create service layer (e.g., `FeedbackService`)
   
3. **Improve Constants Management**
   - Consider separate config files for keywords
   - Investigate runtime keyword loading
   
4. **Multi-User Session Support**
   - Implement proper session ID generation
   - Add cookie-based session binding
   - Implement session expiry

---

## 6. Detailed Risk Analysis by Component

### 6.1 main.cpp: Routing & Rendering

**Lines:** 1-372 (entire file)

**Current Responsibility:**
- HTTP server initialization and lifecycle
- Route registration and handling (GET /, POST /analyze, POST /upload, POST /filter, GET /download)
- Request parsing (form data, CSV)
- Response rendering (HTML generation)
- Domain logic integration
- Global state management

**Coupling Issues:**
```cpp
// Every route touches these globals:
static std::vector<Feedback> fil_data;      // Line 16
static TextAnalyzer textAnalyzer;           // Line 17
static Filters filters;                     // Line 18
static FileHandler fileHandler;             // Line 19

// Every route reads/writes Session without proper ID:
Session::initSessionStateUgly();            // Line 241
auto& feedbacks = Session::getCurrentFeedbacks();  // Line 242, 250, 292, 324
```

**Refactoring Target:** Extract into 4-5 separate components:
1. `HttpServer` class: Server lifecycle
2. `RequestHandler` class: Route dispatch
3. `HtmlRenderer` class: Page rendering
4. `HttpUtils` class: Parsing/decoding utilities
5. `FeedbackService` class: Business logic orchestration

### 6.2 Session: State Management

**Issues:**
1. **No Lifecycle:** `std::unordered_map<string, SessionState>` grows unbounded
2. **No HTTP Binding:** Route handlers manually manage "default" sessionId
3. **Ugly Naming:** `initSessionStateUgly()` indicates known design debt
4. **No Multi-Tenancy:** Cannot safely support multiple concurrent users

**Refactoring Target:**
```cpp
class SessionManager {
public:
    // Auto-bind to HTTP request context
    string generateSessionId();
    SessionState& getSession(const string& sessionId);
    
    // Lifecycle management
    void expireSession(const string& sessionId, int timeoutMinutes);
    void clearExpiredSessions();
    
private:
    struct SessionMetadata {
        SessionState state;
        time_t createdAt;
        time_t lastAccessedAt;
    };
    std::unordered_map<string, SessionMetadata> sessions_;
};
```

### 6.3 Global State Coupling

**Current Issue:**
```cpp
// In main.cpp:
static std::vector<Feedback> fil_data;  // Shared across all requests!
static TextAnalyzer textAnalyzer;       // Shared instance
static Filters filters;                 // Shared instance
static FileHandler fileHandler;         // Shared instance
```

**Test Isolation Failure Scenario:**
```cpp
TEST(FilterTests, NeutralFilter_ShouldPass) {
    // Test 1 runs, filters data, stores in fil_data
    std::vector<Feedback> input = {Feedback("good"), Feedback("ok")};
    filters.applyFilter(input, "중립", "전체");
    // fil_data is now updated
}

TEST(FilterTests, AnotherTest) {
    // Test 2 runs, but fil_data still has data from Test 1!
    // Cross-test contamination
}
```

**Refactoring Target:**
- Move instances into SessionState or request handler
- Each session gets its own TextAnalyzer instance (or share thread-safe singleton)
- Each request gets scoped component instances

---

## 7. Code Quality Metrics

### Lines of Code (LOC)

| File | LOC | Issues |
|------|-----|--------|
| `main.cpp` | 372 | Too large, mixed concerns |
| `TextAnalyzer.cpp` | 60 | Clean, focused |
| `Filters.cpp` | 51 | Clean, focused |
| `Session.cpp` | 39 | Simple implementation, but design debt |
| `Constants.cpp` | Variable | Keyword initialization |
| `Logger.cpp` | Variable | Logging only |
| `FileHandler.cpp` | Variable | File I/O only |
| `UIComponents.cpp` | Variable | UI metadata only |

**Observation:** main.cpp is ~6-10x larger than most other files. It's the bottleneck.

### Cyclomatic Complexity (Estimated)

- `renderPage()`: ~15 (HIGH - many conditional HTML sections)
- `main()` lambda handlers: ~8-12 each (HIGH - complex business logic in lambdas)
- Domain logic (TextAnalyzer, Filters): ~2-3 (LOW - clean logic)

---

## 8. Improvement Direction Summary

### Before: Monolithic Server
```
main.cpp (372 LOC)
├── HTTP routes
├── Request parsing
├── HTML rendering
├── Global state
├── Business logic calls
└── Session management
```

### After: Layered Architecture
```
Server Layer
├── HttpServer (lifecycle)
├── RequestHandler (routing dispatch)
└── RequestContext (per-request state)

Service Layer
├── FeedbackService (orchestration)
└── SessionManager (state lifecycle)

Domain Layer (unchanged, testable)
├── TextAnalyzer
├── Filters
└── Constants

Utility Layer
├── HttpUtils (parsing, decoding)
├── HtmlRenderer (rendering)
├── Logger
└── FileHandler
```

### Key Design Principles

1. **Separation of Concerns**
   - HTTP/rendering code separate from business logic
   - Testable domain layer isolated from framework

2. **Dependency Injection**
   - Pass components explicitly, no global singletons
   - Enable testing with mock implementations

3. **Session Lifecycle**
   - Automatic binding to HTTP requests
   - Proper timeout/cleanup mechanism

4. **Pure Functions**
   - Domain logic (TextAnalyzer, Filters) as pure functions
   - No side effects, deterministic behavior

---

## 9. Next Steps

1. **RED Phase (SPEC-02-02 → SPEC-02-04)**
   - Write tests that expose each identified risk
   - Tests must initially FAIL to demonstrate problems

2. **Prepare for GREEN Phase**
   - Global state removal (most critical)
   - Session isolation fixes
   - Logger level control

3. **Prepare for REFACTOR Phase**
   - Component extraction plan
   - Interface design (abstract boundaries)
   - Dependency injection strategy

---

## Summary

The Feedback Analyzer has a **clean domain layer** (TextAnalyzer, Filters) but a **monolithic, tightly-coupled server layer** (main.cpp). The primary refactoring risk is **global state coupling** and **test isolation failure**.

**Status:** CRITICAL - Cannot safely refactor without addressing global state and session lifecycle issues first.

**Recommended Action:** Proceed to SPEC-02-02 (global state risks) to detail the specific refactoring requirements.
