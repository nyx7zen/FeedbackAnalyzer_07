# SPEC-02-02 Execution Report: Analyze Global State Risks

**Task ID:** SPEC-02-02  
**Type:** Documentation  
**Description:** `docs: analyze global state risks`  
**Date Completed:** 2026-05-22  
**Status:** ✅ COMPLETED

---

## Goal

Create `docs/analysis-global-state.md` analyzing all global state variables in the Feedback Analyzer, identifying test isolation failures, and documenting multi-user contamination scenarios.

---

## Changes Made

### Created `docs/analysis-global-state.md` (New File)

**Purpose:** Detailed analysis of global state coupling and test isolation risks

**Contents:**

1. **Global Static Variables Inventory** (Section 1)
   - 4 static globals in main.cpp (lines 16-19)
   - 1 global session map in Session.cpp (line 3)
   - Lifetime and scope analysis

2. **Risk #1: fil_data Cross-Request Contamination** (Section 2.1)
   - Usage: Line 332 (set), Line 361-362 (read)
   - Scenario: User A filter result overwritten by User B
   - Test failure: Filter tests contaminate each other

3. **Risk #2: TextAnalyzer Singleton** (Section 2.2)
   - Cannot mock for testing
   - Couples to Constants global state
   - Blocks parallel test execution

4. **Risk #3: Filters Singleton** (Section 2.3)
   - No injection, global coupling
   - Dead code risk if never extended

5. **Risk #4: FileHandler Singleton** (Section 2.4)
   - Unused but instantiated globally
   - Potential dead code

6. **Session::sessions_ Global Map** (Section 3)
   - **3.1:** No cleanup → memory leak
   - **3.2:** Test contamination via "default" session
   - **3.3:** Multi-user data corruption

7. **Test Isolation Failure Scenarios** (Section 4)
   - Scenario A: fil_data overwrite sequence
   - Scenario B: Session state leakage
   - Scenario C: Constants modification during tests

8. **Multi-User Scenario** (Section 5)
   - Timeline showing cross-contamination
   - Data corruption with concurrent users

9. **Root Cause Analysis** (Section 6)
   - Why globals were chosen (simplicity)
   - Why it's problematic (testing, concurrency, maintenance)

10. **Cleanup Strategy** (Section 7)
    - **Immediate (GREEN Phase):**
      - Session::clear() in test TearDown
      - fil_data clear mechanism
      - Constants reset
    - **Long-Term (REFACTOR Phase):**
      - Move to RequestContext
      - Implement SessionManager with lifecycle
      - Automatic HTTP → Session binding

11. **Risk Summary Table** (Section 8)
    - Risk matrix for each global
    - Test isolation vs. multi-user impact
    - Fix complexity assessment

12. **RED Phase Test Requirements** (Section 9)
    - fil_data isolation test (must fail)
    - Session isolation test (must fail)
    - Concurrent session test (must fail)
    - Constants stability test (must fail)

---

## Key Findings

### Critical (🔴) Risks

1. **fil_data Contamination**
   - Shared across all requests and tests
   - User A → User B sees User A's data
   - Test order affects results (flaky tests)
   - **Impact:** Wrong CSV downloads, test isolation impossible

2. **Session::sessions_ No Cleanup**
   - Sessions never expire
   - Memory leak on server
   - All users share "default" session
   - **Impact:** Data corruption, multi-user broken

### High (🟡) Risks

3. **TextAnalyzer Singleton**
   - Cannot mock or inject
   - Couples to Constants modifications
   - Blocks parallel testing

4. **No HTTP → Session Binding**
   - All requests hardcoded to "default"
   - Cannot implement real session IDs
   - Multi-user impossible

### Medium (🟡) Risks

5. **Filters & FileHandler Singletons**
   - Future extensibility blocked
   - No dependency injection

---

## Test Scenarios Described

| Test | Current Behavior | Expected | Status |
|------|------------------|----------|--------|
| Filter positive + download | Downloads last filter result | Downloads current filter | FAILS |
| Filter negative after positive | Downloads negative | Downloads positive from before | FAILS |
| Session isolation test 1 + 2 | Test 2 has Test 1 data | Test 2 empty | FAILS |
| Constants modification | Later tests see modified constants | Original constants | FAILS |
| Multi-user concurrent | User B data overwrites A | Each user has own data | FAILS |

---

## Implications for Phases

### RED Phase
- **Must write tests that expose each risk**
- Tests should initially FAIL to demonstrate problems
- Create test scenarios from Section 4 and 5

### GREEN Phase
- **Critical:** Remove fil_data or move to request scope
- **Critical:** Implement Session cleanup in tests
- **High:** Add Constants::reset() method for test isolation
- **High:** Add per-test session clear via TearDown

### REFACTOR Phase
- Implement RequestContext for request-scoped globals
- Implement SessionManager with proper lifecycle
- Add automatic HTTP request → session binding
- Enable dependency injection for TextAnalyzer, Filters

---

## Verification

### Content Validation
- ✅ All 5 globals analyzed (fil_data, textAnalyzer, filters, fileHandler, sessions_)
- ✅ Line numbers and file locations specified
- ✅ Detailed contamination scenarios with specific code examples
- ✅ Multi-user timeline showing data corruption
- ✅ Test isolation failure scenarios with code samples
- ✅ Risk matrix with severity levels
- ✅ Cleanup strategy for both immediate and long-term

### Quality Checks
- ✅ Document is comprehensive (10 sections)
- ✅ Clear separation of risks by severity
- ✅ Concrete scenarios (not abstract)
- ✅ Actionable for RED/GREEN/REFACTOR phases
- ✅ Connected to other SPEC tasks
- ✅ Test requirements specified for RED phase

---

## Related Documentation

- [docs/analysis.md](../../docs/analysis.md) - General architecture overview
- [SPEC-02-01 Report](spec-02-01_add_architecture_analysis-report.md) - Architecture analysis
- [TODO.md](../../TODO.md) - Phase breakdown

---

**Status:** ✅ Ready for commit and push
