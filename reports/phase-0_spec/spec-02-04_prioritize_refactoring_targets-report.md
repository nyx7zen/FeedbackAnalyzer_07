# SPEC-02-04 Execution Report: Prioritize Refactoring Targets

**Task ID:** SPEC-02-04  
**Type:** Documentation  
**Description:** `docs: prioritize refactoring targets`  
**Date Completed:** 2026-05-22  
**Status:** ✅ COMPLETED

---

## Goal

Create `docs/analysis-refactoring-priority.md` identifying which refactoring issues are critical, high-priority, or medium-priority, and establishing the implementation order for RED → GREEN → REFACTOR phases.

---

## Changes Made

### Created `docs/analysis-refactoring-priority.md` (New File)

**Purpose:** Prioritization framework and roadmap for refactoring effort

**Contents:**

1. **Critical Issues (Blocks Refactoring)** (Section 1)
   - **#1 Global fil_data:** Shared across routes, blocks test isolation
   - **#2 Session lifecycle:** No cleanup, memory leak, blocks multi-user
   - **#3 No test reset:** Shared state between tests, flaky tests
   - All 3 have specific fix strategies and remediation paths

2. **High-Priority Issues (Blocks Testing)** (Section 2)
   - **#1 No dependency injection:** Cannot mock TextAnalyzer/Filters
   - **#2 HTTP/Session coupling:** No request → session binding
   - Both require architectural changes

3. **Medium-Priority Issues (Improves Testability)** (Section 3)
   - **#1 HTML rendering inline:** Cannot test UI independently
   - **#2 Utilities mixed with routes:** Cannot test parsing

4. **Priority Matrix** (Section 4)
   - Blocking order (what enables what)
   - Critical path through RED/GREEN/REFACTOR
   - Visual dependency graph

5. **Implementation Roadmap** (Section 5)
   - **RED phase:** Tests that expose risks
   - **GREEN phase:** Critical and high-priority fixes
   - **REFACTOR phase:** Structure improvements
   - Specific items (GREEN-01-01, etc.) with success criteria

6. **Critical Path Analysis** (Section 6)
   - What can start immediately (RED)
   - What requires GREEN completion (REFACTOR)
   - What enables FEATURE work

7. **Risk vs. Effort Matrix** (Section 7)
   - All 7 issues ranked by severity, effort, risk
   - Priority number for implementation order

8. **Quick Start Timeline** (Section 8)
   - 1-day plan (critical fixes only)
   - 3-day plan (critical + high-priority)
   - 1-week plan (full refactoring)

9. **Dependency Graph** (Section 9)
   - Visual flow from fil_data fix through REFACTOR
   - Shows effort and impact for each step

10. **Rollout Strategy** (Section 10)
    - Development approach
    - Testing strategy
    - Code review criteria

11. **Summary with Effort Estimates** (Section 11)
    - Critical: 1-2 days
    - High: 2-3 days
    - Medium: 1-2 days
    - **Total: 4-7 days**

---

## Key Findings

### Critical Issues (🔴) - BLOCKS REFACTORING

| Issue | Fix Effort | Timeline |
|-------|-----------|----------|
| fil_data global | LOW | GREEN-01-01 |
| Session cleanup | MEDIUM | GREEN-01-02 |
| Test reset | LOW | GREEN-01-03 |

**All must be fixed before GREEN phase can succeed**

### High-Priority Issues (🟡) - BLOCKS TESTING

| Issue | Fix Effort | Timeline |
|-------|-----------|----------|
| Dependency injection | MEDIUM | GREEN-02-01 |
| Request context | MEDIUM | GREEN-02-02 |

**Required for service layer testing**

### Medium-Priority Issues (🟡) - IMPROVES ARCHITECTURE

| Issue | Fix Effort | Timeline |
|-------|-----------|----------|
| HTML rendering | LOW | REFACTOR-01-02 |
| Utilities | LOW | REFACTOR-01-03 |

**Can be deferred, improves maintainability**

---

## Blocking Relationships

```
RED tests expose issues
  ↓
fil_data fix (enables test isolation)
  ↓
Session cleanup (enables proper lifecycle)
  ↓
Test TearDown (enables repeatable tests)
  ↓
RED PHASE PASSES
  ↓
Dependency injection (enables mocking)
  ↓
Request context (enables multi-user)
  ↓
GREEN PHASE PASSES
  ↓
HTML/Utils extraction (improves structure)
  ↓
REFACTOR PHASE COMPLETE
```

---

## Implementation Order

### Priority 1 (Critical): fil_data
- **Why:** Test isolation impossible without fix
- **Effort:** LOW (clear, contained change)
- **Phase:** GREEN-01-01
- **Success:** fil_data isolation test passes

### Priority 2 (Critical): Session cleanup
- **Why:** Memory leak, session contamination
- **Effort:** MEDIUM (lifecycle management)
- **Phase:** GREEN-01-02
- **Success:** Session isolation test passes

### Priority 3 (Critical): Test reset
- **Why:** Flaky order-dependent tests
- **Effort:** LOW (TearDown implementation)
- **Phase:** GREEN-01-03
- **Success:** Tests pass repeatedly in any order

### Priority 4 (High): Dependency injection
- **Why:** Cannot mock for testing
- **Effort:** MEDIUM (architectural change)
- **Phase:** GREEN-02-01
- **Success:** Mock-based tests pass

### Priority 5 (High): Request context
- **Why:** No multi-user support, no session binding
- **Effort:** MEDIUM (middleware/context layer)
- **Phase:** GREEN-02-02
- **Success:** Multi-user tests pass

### Priority 6 (Medium): HTML extraction
- **Why:** Better maintainability, UI testing
- **Effort:** LOW (simple extraction)
- **Phase:** REFACTOR-01-02
- **Success:** HTML tests pass

### Priority 7 (Medium): Utilities extraction
- **Why:** Code reuse, isolated testing
- **Effort:** LOW (namespace extraction)
- **Phase:** REFACTOR-01-03
- **Success:** Utility tests pass

---

## Timeline Estimates

### Fast Track (1 Day)
- Fix #1: fil_data (1-2 hours)
- Fix #2: Session cleanup (2-3 hours)
- Fix #3: Test reset (1 hour)
- **Result:** Critical fixes done, RED tests pass

### Standard (3 Days)
- Day 1: Critical fixes (above)
- Day 2: Dependency injection + Request context
- **Result:** GREEN phase complete, ready for REFACTOR

### Comprehensive (1 Week)
- Days 1-2: Critical fixes
- Day 3: High-priority fixes
- Days 4-5: HTML/Utils extraction
- Day 6: Service layer implementation
- Day 7: Testing, review, polish

---

## Verification

### Content Validation
- ✅ 7 issues identified (3 critical, 2 high, 2 medium)
- ✅ Fix strategies provided for each
- ✅ Effort estimates (LOW/MEDIUM)
- ✅ Timeline mapping (GREEN-01-xx, etc.)
- ✅ Success criteria defined
- ✅ Blocking relationships documented
- ✅ Dependency graph shown

### Quality Checks
- ✅ Document is comprehensive (10 sections)
- ✅ Actionable priorities (ranked 1-7)
- ✅ Multiple timeline options (1-day, 3-day, 1-week)
- ✅ Effort estimates realistic
- ✅ Connected to previous analysis documents
- ✅ Clear success criteria for each phase

---

## SPEC Phase Summary

The SPEC phase has completed 4 diagnostic documents:

| Task | Document | Focus |
|------|----------|-------|
| SPEC-02-01 | analysis.md | Overall architecture overview |
| SPEC-02-02 | analysis-global-state.md | Global state risks and test contamination |
| SPEC-02-03 | analysis-main-coupling.md | HTTP/domain coupling and decomposition |
| SPEC-02-04 | analysis-refactoring-priority.md | Implementation roadmap and priorities |

**Total SPEC output:** 4 analysis documents, 2600+ lines of detailed analysis

---

## Ready for RED Phase

With SPEC phase complete, RED phase can now:

1. **Write failing tests** that expose critical issues
2. **Use priority list** to order test items
3. **Reference analysis** for test scenarios
4. **Target specific issues** identified in SPEC phase

---

## Related Documentation

- [docs/analysis.md](../../docs/analysis.md) - Architecture overview
- [docs/analysis-global-state.md](../../docs/analysis-global-state.md) - Global state analysis
- [docs/analysis-main-coupling.md](../../docs/analysis-main-coupling.md) - Coupling analysis
- [SPEC Reports](../phase-0_spec/) - Execution reports
- [TODO.md](../../TODO.md) - Phase breakdown

---

**Status:** ✅ SPEC phase complete. Ready for RED phase.
