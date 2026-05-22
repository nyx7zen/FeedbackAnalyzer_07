---
name: run
description: Use when the user invokes $run or asks to execute a specific Feedback Analyzer TODO phase item such as SPEC-01-01, RED-02-04, GREEN-01-01, REFACTOR-03-03, FEATURE-02-02, or FINAL-01-01. Follows TODO.md, AGENTS.md, and SESSION_NOTES.md for phase-based implementation, verification, checkbox updates, and session logging.
metadata:
  short-description: Run a TODO phase item
---

# Run Skill

Use this skill when the user invokes `$run` or asks to proceed with a specific TODO item identifier.

## Scope

This skill is for the Feedback Analyzer project workflow in `C:\DEV\week2_day4\FeedbackAnalyzer_07`.

Expected request examples:

```text
/run FINAL-01-01
/run FINAL-02-02
FINAL-01-03 항목을 진행해 주세요
FINAL-02-03 진행
진행 FINAL-01-05
FEATURE-02-02 항목을 진행해 주세요
1번 실행
2번 실행
60번 실행
62번 실행
```

## Workflow

1. Read `AGENTS.md` and `TODO.md` first.
2. If the request is like `N번 실행`, first resolve `N` using `prompts/INDEX.md`.
3. If `INDEX.md` cannot be read or mapping is missing, read `.agents/skills/status/STATUS_SNAPSHOT.md` and map `N` to `NextItems` entry.
4. Locate the resolved identifier in `TODO.md`.
5. Treat the checkbox line as the intended commit message and the nested bullets as the exact task scope.
6. Read the corresponding prompt document from `prompts/` directory (e.g., `prompts/RED-01-01.md`).
7. Execute the prompt and perform all required tasks.
8. Inspect relevant source, tests, and docs before editing.
9. Keep changes limited to the requested item unless a direct prerequisite is required.
10. Apply code or document changes following existing repository style.
11. Run relevant build/tests when the task changes code or tests. If only documents changed, state that build/tests were not run.
12. **Automatically update the requested checkbox in `TODO.md` from `[ ]` to `[x]` when the item work is complete.**
    - Use the commit message from the prompt document for git commit.
    - Example: `[ ] RED-01-01 ...` becomes `[x] RED-01-01 ...`
    - This ensures the status skill can accurately count completed items.
13. Update `SESSION_NOTES.md` for meaningful code, document, config, or structure changes.
14. Final response must summarize changed files, verification, and any remaining risk.

## Guardrails

- Do not move `Cursor AI_퀴즈 - 문제.docx`; it must stay in the repository root.
- Stage reports and final deliverables under `docs/`.
- Use `refs/` only for reference material.
- Preserve user changes and do not revert unrelated work.
- Do not make large redesigns outside the selected TODO item.
- If `N번 실행` cannot be resolved from `prompts/INDEX.md` and snapshot `NextItems`, ask for explicit TODO id (e.g., `SPEC-01-01`).

## Output Pattern

When starting, mention the selected item and its scope briefly.

When finished, include:

- completed item id and commit-message label
- files changed
- verification command/results, or why tests were not run
- whether `TODO.md` and `SESSION_NOTES.md` were updated
