# SPEC-02-03 Execution Report: Analyze main.cpp Coupling

**Task ID:** SPEC-02-03  
**Type:** Documentation  
**Description:** `docs: analyze main coupling`  
**Date Completed:** 2026-05-22  
**Status:** ✅ COMPLETED

---

## Goal

Create `docs/analysis-main-coupling.md` analyzing how main.cpp couples HTTP routing to domain logic, preventing unit testing of business logic without starting an HTTP server.

---

## Changes Made

### Created `docs/analysis-main-coupling.md` (New File)

**Purpose:** Detailed analysis of main.cpp architectural coupling and decomposition plan

**Contents:**

1. **Current Monolithic Architecture** (Section 1)
   - 372-line main.cpp breakdown
   - 250 lines of utilities mixed with logic
   - 5 route handlers (GET /, POST /analyze, /upload, /filter, GET /download)

2. **Route Handler Analysis** (Section 2)
   - **2.1 GET /:** Session access, HTML rendering
   - **2.2 POST /analyze:** Form parsing, domain logic, response rendering (40 lines)
   - **2.3 POST /upload:** CSV parsing, file handling, response rendering (30 lines)
   - **2.4 POST /filter:** Filtering logic, global state, re-analysis (33 lines)
   - **2.5 GET /download:** Global fil_data access, CSV formatting (11 lines)

3. **Coupling Issues by Route** (Section 2)
   - Hard coupling to Session
   - Hard coupling to TextAnalyzer
   - Hard coupling to Filters
   - Hard coupling to global fil_data
   - Tight coupling to HTML rendering
   - Inline form/CSV parsing

4. **Dependency Graph** (Section 3)
   - main.cpp depends on 9+ components
   - No abstraction between HTTP and domain layers

5. **Mixed Concerns Breakdown** (Section 4)
   - Concern #1: HTTP Request/Response Handling (lines 233-366)
   - Concern #2: Business Logic Orchestration (lines 250-287, 324-335)
   - Concern #3: HTML Rendering (lines 81-211)
   - Concern #4: Utility Functions (lines 22-231)
   - Concern #5: Data Persistence (lines 289-319, 355-366)

6. **Refactoring Decomposition Plan** (Section 5)
   - Target architecture with 5+ separate components
   - Component breakdown showing responsibility and interfaces

7. **Component Design Details** (Section 6)
   - RequestHandler: Maps HTTP to services (140 lines)
   - FeedbackService: Feedback addition and analysis (testable)
   - FilterService: Filter application (testable)
   - CsvExporter: CSV export (testable)
   - HtmlRenderer: HTML page rendering (testable)

8. **Coupling Reduction Table** (Section 7)
   - Before/After comparison for each coupling type
   - Dependency injection as solution

9. **Main Coupling Issues Detail** (Section 8)
   - Issue #1: Service Locator Pattern (no DI)
   - Issue #2: Response Rendering in Routes
   - Issue #3: Implicit Session ID ("default")

10. **RED Phase Test Requirements** (Section 9)
    - Test feedback addition without HTTP
    - Test filtering without HTTP
    - Test CSV export without routes
    - Test HTML rendering without routes

11. **Refactoring Path** (Section 10)
    - GREEN phase: Request context, SessionManager, DI
    - REFACTOR phase: Component extraction
    - FEATURE phase: Multi-user, persistence, API

---

## Key Findings

### Mixing of Concerns

| Concern | Lines | Issue |
|---------|-------|-------|
| HTTP routing | 233-366 | Couples to domain logic |
| Business logic | 250-287, 324-335 | Hardcoded to routes |
| HTML rendering | 81-211 | 130 lines inline |
| Form parsing | 44-55 | Couples to route handlers |
| CSV parsing | 214-231 | Couples to upload handler |

### Coupling Types Identified

1. **Hard Coupling to Session**
   - Direct reference to `Session::getCurrentFeedbacks()`
   - No abstraction layer
   - Cannot test without Session initialized

2. **Hard Coupling to TextAnalyzer**
   - Calls `textAnalyzer.sent()` and `.kw()` directly
   - Cannot mock for testing
   - Global singleton prevents dependency injection

3. **Hard Coupling to Filters**
   - Calls `filters.fil()` directly
   - Cannot mock for testing
   - Global singleton prevents dependency injection

4. **Hard Coupling to Global fil_data**
   - GET /download reads from global `fil_data`
   - POST /filter writes to global `fil_data`
   - Cross-route coupling (extremely fragile)

5. **Tight Coupling to HTML Rendering**
   - 130-line `renderPage()` function inline
   - Cannot test page structure independently
   - Cannot change UI without touching route logic

### Testability Impact

**Current State:** Cannot test any business logic without HTTP server
- Cannot unit test feedback addition
- Cannot unit test filtering
- Cannot unit test CSV export
- Cannot unit test HTML generation

**Root Cause:** Service logic is embedded in route handlers

---

## Decomposition Blueprint

### After Refactoring

```
main.cpp (40 lines)
├─ Constants::init()
├─ Create services
├─ Register routes
└─ Server::listen()

RequestHandler (140 lines)
├─ handleRoot()
├─ handleAnalyze()
├─ handleUpload()
├─ handleFilter()
└─ handleDownload()

FeedbackService (40 lines)
├─ addFeedback(text)
└─ addFeedbacksFromCsv(rows)

FilterService (30 lines)
└─ applyFilters(sentiment, keyword)

CsvExporter (20 lines)
└─ exportToCSV(feedbacks)

HtmlRenderer (130 lines)
└─ renderPage(success, warning, error, ...)
```

**Before:** All 370 lines in main.cpp  
**After:** Logic distributed across 5 focused components

---

## Service Layer Design

Each service accepts injected dependencies:

```cpp
FeedbackService(
    std::shared_ptr<TextAnalyzer> analyzer,
    std::shared_ptr<Session> session
);

FilterService(
    std::shared_ptr<Filters> filters,
    std::shared_ptr<TextAnalyzer> analyzer,
    std::shared_ptr<Session> session
);
```

**Benefit:** Services become testable via dependency injection

---

## Implications for Phases

### RED Phase
- **Must write tests** for each service in isolation
- Tests should FAIL with current code (hardcoded dependencies)
- Create mock TextAnalyzer, Filters, Session implementations

### GREEN Phase
- **Critical:** Extract RequestHandler from main()
- **Critical:** Create service layer (FeedbackService, FilterService, etc.)
- **High:** Move Session access to SessionManager
- **High:** Implement dependency injection
- **Medium:** Extract utilities (HttpUtils, CsvUtils, HtmlRenderer)

### REFACTOR Phase
- Move hardcoded dependencies to constructor injection
- Implement RequestContext for request → service binding
- Enable multi-user session support
- Prepare for API endpoints (JSON responses)

---

## Test Scenarios for RED Phase

| Test | Current | Expected | Status |
|------|---------|----------|--------|
| FeedbackService::addFeedback() | Fails (no DI) | Passes | FAILS |
| FilterService::applyFilters() | Fails (no DI) | Passes | FAILS |
| CsvExporter::exportToCSV() | Fails (no DI) | Passes | FAILS |
| HtmlRenderer::renderPage() | Works (pure function) | Works | PASSES |
| RequestHandler with mocks | Fails (hardcoded) | Passes | FAILS |

---

## Verification

### Content Validation
- ✅ All 5 route handlers analyzed in detail
- ✅ Specific line number references
- ✅ Code snippets showing coupling points
- ✅ Dependency graph showing component relationships
- ✅ Detailed decomposition plan with interfaces
- ✅ Before/after coupling comparison
- ✅ Service layer design with DI
- ✅ RED phase test requirements

### Quality Checks
- ✅ Document is comprehensive (10 sections)
- ✅ Identifies both problems and solutions
- ✅ Provides concrete refactoring blueprint
- ✅ Actionable for GREEN and REFACTOR phases
- ✅ Connected to previous analysis documents
- ✅ Test scenarios specified

---

## Related Documentation

- [docs/analysis.md](../../docs/analysis.md) - Overall architecture overview
- [docs/analysis-global-state.md](../../docs/analysis-global-state.md) - Global state risks
- [SPEC-02-01 Report](spec-02-01_add_architecture_analysis-report.md) - Architecture analysis
- [SPEC-02-02 Report](spec-02-02_analyze_global_state_risks-report.md) - Global state analysis
- [TODO.md](../../TODO.md) - Phase breakdown

---

**Status:** ✅ Ready for commit and push
