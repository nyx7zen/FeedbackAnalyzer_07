# Analysis: main.cpp Coupling

**Phase:** SPEC-02-03  
**Date:** 2026-05-22  
**Scope:** HTTP routing / domain logic coupling in main.cpp

---

## Executive Summary

**main.cpp is a 372-line monolith** mixing HTTP routing, HTML rendering, form parsing, and domain logic. **Each route handler** (5 handlers total) contains tightly-coupled business logic that **cannot be tested without starting an HTTP server**.

**Key Finding:** The file must be decomposed into 4-5 separate components before refactoring can proceed.

---

## 1. Current Architecture: Monolithic main()

```
main.cpp (372 lines)
├── Includes & Global Statics (lines 1-19)
├── Utility Functions (lines 22-231)
│  ├── urlDecode() - URL decoding
│  ├── parseForm() - Form parsing
│  ├── getCurrentTimestamp() - Timestamp generation
│  ├── escapeHtml() - HTML escaping
│  ├── renderPage() - 130-line HTML rendering
│  └── parseCsvLine() - CSV parsing
├── main() Function (lines 233-372)
│  ├── Constants::init()
│  ├── Filters::initFilterKeywords()
│  ├── HTTP Server Setup
│  ├── GET / Handler (lines 240-245)
│  ├── POST /analyze Handler (lines 247-287)
│  ├── POST /upload Handler (lines 289-319)
│  ├── POST /filter Handler (lines 321-353)
│  └── GET /download Handler (lines 355-366)
└── Server Startup (lines 368-372)
```

---

## 2. Route Handler Analysis

### 2.1 GET / (Root)

**Lines:** 240-245  
**Purpose:** Render home page

```cpp
svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
    Session::initSessionStateUgly();                    // Session init
    auto& feedbacks = Session::getOldDataFromSession("current_feedbacks");
    std::string html = renderPage(u8"피드백 분석기 시작", "", "", {}, {}, feedbacks);
    res.set_content(html, "text/html; charset=UTF-8");
});
```

**Coupling Issues:**
1. **Session Management:** Calls `initSessionStateUgly()` (naming indicates design debt)
2. **Direct State Access:** Reads `feedbacks` directly from Session
3. **HTML Rendering:** Calls `renderPage()` (130 lines inline)
4. **Response Formatting:** Manually sets content type

**Testability:** Cannot test route without HTTP server

**Refactoring Target:** Extract to `Handler::root()`

---

### 2.2 POST /analyze (Add Feedback)

**Lines:** 247-287  
**Purpose:** Accept feedback text input and perform analysis

```cpp
svr.Post("/analyze", [](const httplib::Request& req, httplib::Response& res) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();         // Get session state
        auto params = parseForm(req.body);                         // Parse form
        std::string text = params["text"];
        
        if (!text.empty()) {
            // Trim whitespace
            auto start = text.find_first_not_of(" \t\r\n");
            auto end = text.find_last_not_of(" \t\r\n");
            if (start != std::string::npos) {
                text = text.substr(start, end - start + 1);
                feedbacks.push_back(Feedback(text));              // Add to session
            }
        }
        
        // Log all feedbacks (why? unnecessary side effect)
        for (const auto& fb : feedbacks) {
            Logger::logInfo(fb.getText());
        }
        
        // Build result strings
        std::string success = std::to_string(feedbacks.size()) + u8"개의 피드백이 입력되었습니다.";
        std::map<std::string, int> sentimentResults, keywordResults;
        
        // Call domain logic
        if (!feedbacks.empty()) {
            sentimentResults = textAnalyzer.sent(feedbacks);      // COUPLING
            keywordResults = textAnalyzer.kw(feedbacks);          // COUPLING
            Logger::logInfo(u8"감성 분석 완료");
            Logger::logInfo(u8"키워드 분석 완료");
        }
        
        // Render HTML response
        std::string html = renderPage(success, "", "", sentimentResults, keywordResults, feedbacks);
        res.set_content(html, "text/html; charset=UTF-8");
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"오류 발생: ") + e.what());
        std::string html = renderPage("", "", u8"처리 중 오류가 발생했습니다.", {}, {}, {});
        res.set_content(html, "text/html; charset=UTF-8");
    }
});
```

**Coupling Issues:**
1. **Session Access:** Direct reference to session state
2. **Form Parsing:** Manual form data extraction
3. **String Trimming:** Business logic (trimming) in route handler
4. **Domain Logic:** Calls `textAnalyzer.sent()` and `.kw()` directly
5. **Logging:** Multiple log calls scattered throughout
6. **HTML Rendering:** Builds response HTML inline
7. **Error Handling:** Generic catch-all with no specific error translation

**Testability:** Cannot test feedback analysis without HTTP server

**Refactoring Target:** Extract to `FeedbackService::addFeedback()`

---

### 2.3 POST /upload (CSV Upload)

**Lines:** 289-319  
**Purpose:** Accept CSV file upload and parse feedback from it

```cpp
svr.Post("/upload", [](const httplib::Request& req, httplib::Response& res) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();         // Session state
        if (req.form.has_file("file")) {
            const auto file = req.form.get_file("file");
            if (!file.content.empty()) {
                std::istringstream stream(file.content);
                std::string line;
                bool firstLine = true;
                while (std::getline(stream, line)) {
                    if (!line.empty() && line.back() == '\r') line.pop_back();
                    if (firstLine) { firstLine = false; continue; }
                    if (line.empty()) continue;
                    auto fields = parseCsvLine(line);              // CSV parsing
                    if (!fields.empty() && !fields[0].empty()) {
                        feedbacks.push_back(Feedback(fields[0]));
                    }
                }
                Logger::logInfo(u8"파일이 성공적으로 업로드되었습니다.");
            }
        }
        std::string success = std::to_string(feedbacks.size()) + u8"개의 피드백이 입력되었습니다.";
        std::string html = renderPage(success, "", "", {}, {}, feedbacks);
        res.set_content(html, "text/html; charset=UTF-8");
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"파일 업로드 오류: ") + e.what());
        std::string html = renderPage("", "", u8"파일 업로드 중 오류가 발생했습니다.", {}, {}, {});
        res.set_content(html, "text/html; charset=UTF-8");
    }
});
```

**Coupling Issues:**
1. **Session Access:** Direct state modification
2. **CSV Parsing:** Inline logic (`parseCsvLine()`)
3. **File Handling:** Manual file processing
4. **HTML Rendering:** Response HTML hardcoded
5. **Error Handling:** Generic error response

**Testability:** Cannot test CSV parsing or file upload without HTTP server

**Refactoring Target:** Extract to `FileService::uploadCsv()`

---

### 2.4 POST /filter (Apply Filters)

**Lines:** 321-353  
**Purpose:** Apply sentiment and keyword filters to feedback

```cpp
svr.Post("/filter", [](const httplib::Request& req, httplib::Response& res) {
    try {
        auto& feedbacks = Session::getCurrentFeedbacks();         // Session state
        auto params = parseForm(req.body);                         // Form parsing
        std::string sentiment = params["sentiment"];
        std::string keyword = params["keyword"];
        
        if (!feedbacks.empty()) {
            auto filtered = filters.fil(feedbacks, sentiment, keyword);  // COUPLING
            if (!filtered.empty()) {
                fil_data = filtered;                               // Global state!
                auto sentimentResults = textAnalyzer.sent(filtered);  // COUPLING
                auto keywordResults = textAnalyzer.kw(filtered);      // COUPLING
                Logger::logInfo(u8"필터링 결과: " + std::to_string(filtered.size()) + u8"개의 피드백");
                std::string html = renderPage("", "", "", sentimentResults, keywordResults, filtered);
                res.set_content(html, "text/html; charset=UTF-8");
            } else {
                Logger::logWarning(u8"필터링 결과가 없습니다.");
                std::string html = renderPage("", u8"필터링 결과가 없습니다.", "", {}, {}, {});
                res.set_content(html, "text/html; charset=UTF-8");
            }
        } else {
            Logger::logWarning(u8"분석할 피드백이 없습니다.");
            std::string html = renderPage("", u8"분석할 피드백이 없습니다.", "", {}, {}, {});
            res.set_content(html, "text/html; charset=UTF-8");
        }
    } catch (const std::exception& e) {
        Logger::logError(std::string(u8"오류 발생: ") + e.what());
        std::string html = renderPage("", "", u8"처리 중 오류가 발생했습니다.", {}, {}, {});
        res.set_content(html, "text/html; charset=UTF-8");
    }
});
```

**Coupling Issues:**
1. **Session Access:** Direct state retrieval
2. **Form Parsing:** Manual parameter extraction
3. **Domain Logic:** Calls `filters.fil()`, `textAnalyzer.sent()`, `.kw()`
4. **Global State:** Sets `fil_data` for download endpoint
5. **Conditional Rendering:** Multiple HTML responses for different outcomes
6. **Logging:** Scattered log calls

**Testability:** Cannot test filtering logic without HTTP server

**Refactoring Target:** Extract to `FilterService::applyFilters()`

---

### 2.5 GET /download (CSV Download)

**Lines:** 355-366  
**Purpose:** Download filtered feedback as CSV

```cpp
svr.Get("/download", [](const httplib::Request&, httplib::Response& res) {
    std::ostringstream csv;
    // UTF-8 BOM
    csv << "\xEF\xBB\xBF";
    csv << "text\n";
    for (const auto& iter : fil_data) {              // Uses global fil_data!
        csv << iter.getText() << "\n";
    }
    res.set_header("Content-Disposition", "attachment; filename=\"filtered_feedback.csv\"");
    res.set_content(csv.str(), "text/csv; charset=UTF-8");
});
```

**Coupling Issues:**
1. **Global State:** Reads from `fil_data` (set by /filter route)
2. **CSV Formatting:** Hard-coded UTF-8 BOM, manual CSV building
3. **No CSV Library:** Manual CSV generation (fragile)

**Testability:** Cannot test CSV download without HTTP server

**Refactoring Target:** Extract to `CsvExporter::export()`

---

## 3. Coupling Analysis Summary

### Dependency Graph

```
main.cpp
├─ HTTP Framework (httplib)
├─ Session (reads/writes)
├─ TextAnalyzer (sends data, receives results)
├─ Filters (sends data, receives results)
├─ Constants (reads sentiment/category keywords)
├─ Logger (sends log messages)
├─ FileHandler (?)
├─ UIComponents (reads categories)
├─ Feedback (data model)
└─ Global State (fil_data)
```

### Coupling Types

| Type | Location | Impact |
|------|----------|--------|
| **Hard Coupling** | Session state access | Cannot test without HTTP |
| **Hard Coupling** | Global `fil_data` | Multi-user broken |
| **Hard Coupling** | TextAnalyzer calls | Cannot mock |
| **Hard Coupling** | Filters calls | Cannot mock |
| **Tight Coupling** | HTML rendering inline | Cannot change UI independently |
| **Tight Coupling** | Form parsing inline | Cannot test parsing separately |
| **Tight Coupling** | CSV parsing inline | Cannot test CSV separately |

---

## 4. Mixed Concerns in main.cpp

### Concern #1: HTTP Request/Response Handling
- Route registration
- Request parsing (form, headers, files)
- Response formatting

**Lines:** 233-366

### Concern #2: Business Logic Orchestration
- Session state management
- Feedback addition
- Filtering application
- Analysis invocation

**Lines:** 250-287, 324-335, etc.

### Concern #3: HTML Rendering
- Page template (130+ lines)
- Dynamic content generation
- Form building

**Lines:** 81-211 (`renderPage()`)

### Concern #4: Utility Functions
- URL decoding
- Form parsing
- CSV parsing
- HTML escaping

**Lines:** 22-231

### Concern #5: Data Persistence
- CSV file upload/parsing
- CSV download/export

**Lines:** 289-319, 355-366

---

## 5. Refactoring Decomposition Plan

### Target Architecture

```
After Refactoring:
├─ main.cpp (40 lines)
│  ├─ Constants::init()
│  ├─ Create HttpServer
│  ├─ Register routes via Router
│  └─ Server::listen()
│
├─ HttpServer.h/cpp
│  └─ Server lifecycle
│
├─ Router.h/cpp
│  └─ Route registration and dispatch
│
├─ RequestHandler.h/cpp
│  ├─ GET /
│  ├─ POST /analyze → FeedbackService
│  ├─ POST /upload → FileService
│  ├─ POST /filter → FilterService
│  └─ GET /download → CsvExporter
│
├─ Service Layer
│  ├─ FeedbackService.h/cpp (addFeedback, analyze)
│  ├─ FilterService.h/cpp (applyFilters)
│  ├─ FileService.h/cpp (uploadCsv)
│  └─ CsvExporter.h/cpp (export)
│
├─ Utility Layer
│  ├─ HttpUtils.h/cpp (urlDecode, parseForm)
│  ├─ CsvUtils.h/cpp (parseCsvLine, format)
│  ├─ HtmlRenderer.h/cpp (renderPage)
│  └─ HtmlEscaper.h/cpp (escapeHtml)
│
└─ Domain Layer (unchanged)
   ├─ TextAnalyzer
   ├─ Filters
   ├─ Constants
   └─ Others
```

---

## 6. Decomposition Details

### Component 1: RequestHandler

**Responsibility:** Map HTTP requests to service methods

```cpp
class RequestHandler {
public:
    // Inject dependencies
    RequestHandler(
        std::shared_ptr<FeedbackService> feedbackService,
        std::shared_ptr<FilterService> filterService,
        std::shared_ptr<FileService> fileService,
        std::shared_ptr<CsvExporter> csvExporter,
        std::shared_ptr<HtmlRenderer> renderer);

    // Route handlers
    void handleRoot(httplib::Response& res);
    void handleAnalyze(const httplib::Request& req, httplib::Response& res);
    void handleUpload(const httplib::Request& req, httplib::Response& res);
    void handleFilter(const httplib::Request& req, httplib::Response& res);
    void handleDownload(httplib::Response& res);
};
```

**Before:** 140 lines inline in main()  
**After:** 140 lines in RequestHandler class (separated, testable via dependency injection)

### Component 2: FeedbackService

**Responsibility:** Manage feedback addition and analysis

```cpp
class FeedbackService {
public:
    FeedbackService(
        std::shared_ptr<TextAnalyzer> analyzer,
        std::shared_ptr<Session> session);

    struct Result {
        std::string successMessage;
        std::map<std::string, int> sentimentResults;
        std::map<std::string, int> keywordResults;
        std::vector<Feedback> feedbacks;
    };

    Result addFeedback(const std::string& text);
    Result addFeedbacksFromCsv(const std::vector<std::string>& rows);
};
```

**Testability:** ✅ Can test with mock TextAnalyzer and Session

### Component 3: FilterService

**Responsibility:** Apply filters to feedback

```cpp
class FilterService {
public:
    FilterService(
        std::shared_ptr<Filters> filters,
        std::shared_ptr<TextAnalyzer> analyzer,
        std::shared_ptr<Session> session);

    struct Result {
        bool success;
        std::string message;
        std::vector<Feedback> filtered;
        std::map<std::string, int> sentimentResults;
        std::map<std::string, int> keywordResults;
    };

    Result applyFilters(const std::string& sentiment, const std::string& keyword);
};
```

**Testability:** ✅ Can test with mock Filters

### Component 4: CsvExporter

**Responsibility:** Export feedback as CSV

```cpp
class CsvExporter {
public:
    CsvExporter(std::shared_ptr<Session> session);
    
    std::string exportToCSV(const std::vector<Feedback>& feedbacks);
    std::vector<std::string> getHeaders() const;
};
```

**Testability:** ✅ Can test CSV format independently

### Component 5: HtmlRenderer

**Responsibility:** Render HTML pages

```cpp
class HtmlRenderer {
public:
    std::string renderPage(
        const std::string& success,
        const std::string& warning,
        const std::string& error,
        const std::map<std::string, int>& sentimentResults,
        const std::map<std::string, int>& keywordResults,
        const std::vector<Feedback>& feedbacks) const;
};
```

**Testability:** ✅ Can test HTML output independently

---

## 7. Coupling Reduction

### Before → After

| Coupling | Before | After |
|----------|--------|-------|
| HTTP → Session | Hard | Injected |
| HTTP → TextAnalyzer | Hard | Via FeedbackService |
| HTTP → Filters | Hard | Via FilterService |
| HTTP → Global fil_data | Hard | Via CsvExporter state |
| HTML → Business Logic | Tight | Separate HtmlRenderer |
| Form Parsing → Routes | Tight | Separate HttpUtils |
| CSV Parsing → Routes | Tight | Separate CsvUtils |

---

## 8. Main Coupling Issues

### Issue #1: Service Locator Pattern
```cpp
// Currently: direct global access
auto& feedbacks = Session::getCurrentFeedbacks();
sentimentResults = textAnalyzer.sent(feedbacks);
```

**Problem:** No dependency injection, hardcoded dependencies

**Solution:** Inject services in constructor

```cpp
RequestHandler(std::shared_ptr<FeedbackService> service) : service_(service) {}
auto result = service_->addFeedback(text);
```

### Issue #2: Response Rendering in Routes
```cpp
// Currently: HTML generation mixed with logic
std::string html = renderPage(success, "", "", sentimentResults, ...);
res.set_content(html, "text/html; charset=UTF-8");
```

**Problem:** Cannot change UI without touching route logic

**Solution:** Separate rendering

```cpp
HtmlRenderer renderer;
std::string html = renderer.renderPage(success, "", "", sentimentResults, ...);
res.set_content(html, "text/html; charset=UTF-8");
```

### Issue #3: Implicit Session ID
```cpp
// Currently: all routes use "default"
auto& feedbacks = Session::getCurrentFeedbacks();  // "default" hardcoded
```

**Problem:** Cannot support real multi-user sessions

**Solution:** Extract session ID from request, pass context

```cpp
class RequestContext {
    std::string sessionId;
    Session& session;
};

void handleAnalyze(const RequestContext& ctx, ...) {
    auto& feedbacks = ctx.session.getCurrentFeedbacks(ctx.sessionId);
}
```

---

## 9. RED Phase Test Requirements

To expose coupling issues, tests must:

1. **Test Feedback Addition Without HTTP**
   - Create FeedbackService mock
   - Verify addFeedback() works
   - Currently FAILS (hardcoded to Session)

2. **Test Filtering Without HTTP**
   - Create FilterService mock
   - Verify applyFilters() works
   - Currently FAILS (hardcoded to TextAnalyzer)

3. **Test CSV Export Without Routes**
   - Create CsvExporter
   - Test CSV format
   - Currently FAILS (hardcoded to GET /download)

4. **Test HTML Rendering Without Routes**
   - Create HtmlRenderer
   - Test page HTML structure
   - Currently FAILS (hardcoded to route handlers)

---

## 10. Refactoring Path

### Phase: GREEN (Critical Fixes)
1. Add request context with session ID
2. Move Session access to SessionManager
3. Add dependency injection for services

### Phase: REFACTOR (Structure Improvements)
1. Extract RequestHandler from main()
2. Extract service layer (FeedbackService, FilterService, etc.)
3. Extract utility layer (HttpUtils, CsvUtils, HtmlRenderer)
4. Remove global state coupling

### Phase: FEATURE (New Capabilities)
1. Multi-user session support
2. Authentication/authorization
3. Persistent storage
4. API endpoints (JSON responses)

---

## Summary

**Critical Finding:** main.cpp **couples HTTP routing to business logic** through **direct Session access** and **global state dependencies**.

**All 5 route handlers** contain intermingled concerns:
- HTTP semantics (request parsing, response formatting)
- Business logic (feedback analysis, filtering)
- UI rendering (HTML generation)
- Data utilities (form/CSV parsing)

**Cannot write unit tests** because domain logic is trapped inside route handlers.

**Next:** SPEC-02-04 prioritizes which coupling issues to fix first in GREEN phase.
