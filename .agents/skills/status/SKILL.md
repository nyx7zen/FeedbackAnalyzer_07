---
name: status
description: Use when the user invokes /status or asks to show current Feedback Analyzer branch, phase, TODO progress, changed files, verification state, or next recommended TODO item. Two modes: quick snapshot-based status ("상태"), or refreshed current status with full inspection ("상태갱신" or phase-specified). Reads git status plus AGENTS.md, TODO.md, and SESSION_NOTES.md to summarize project progress without making changes.
metadata:
  short-description: Show project progress status (quick or refreshed)
---

# FeedbackAnalyzer_07 - Status Skill 지침

이 스킬은 사용자가 `/status`를 호출하거나 "상태", "상태갱신", "현재 진행 현황"을 요청할 때 프로젝트 진행 상태를 일관된 형식으로 보여주기 위한 용도다.

두 가지 모드를 지원한다:
- 빠른 상태: "상태" (스냅샷 참조, 갱신 안 함)
- 정확한 상태: "상태갱신" 또는 phase 지정 (전체 점검 후 갱신)

## 프로젝트 범위

- 저장소: `C:\DEV\week2_day4\FeedbackAnalyzer_07`
- 기준 문서: `AGENTS.md`, `TODO.md`, `SESSION_NOTES.md`
- 목적: 현재 브랜치/Phase/TODO/검증 상태를 짧고 실행 가능한 형태로 보고한다.

---

## 호출 예시

빠른 상태 확인 (스냅샷 기반)
```text
/status
상태
현재 상태를 보여주세요.
```

정확한 최신 상태 (전체 점검 후 갱신)
```text
상태갱신
갱신
상태 새로고침
현재 진행 현황을 보여주세요
/status final
/status FINAL-02
/status FINAL-02-02
브랜치
할일
```

---

## 상태 수집 절차

### 모드 1: 빠른 상태 확인 ("상태" 호출)

1. `.agents/skills/status/STATUS_SNAPSHOT.md`를 읽는다.
2. 직전 상태를 그대로 표시한다.
3. 갱신하지 않는다 (빠른 응답).

### 모드 2: 정확한 최신 상태 ("상태갱신" 또는 phase 지정)

1. `git status --short --branch` 실행한다.
2. `TODO.md`를 부분 또는 전체 조회한다.
   - **각 Phase의 체크박스 상태를 기준으로 완료 개수를 계산한다.**
   - `[x]` 체크박스를 가진 항목만 완료로 카운트한다.
3. `.agents/skills/status/STATUS_SNAPSHOT.md`와 비교해 변경점(delta)를 파악한다.
4. 사용자가 phase/prefix를 지정한 경우 해당 범위만 상세 조회한다.
5. `SESSION_NOTES.md`에서 최신 검증 상태 1개를 확인한다.
6. 최신 상태를 출력하고 `STATUS_SNAPSHOT.md`에 갱신한다.

공통 사항
- 원칙적으로 네트워크/원격 조회 없이 로컬 정보만 사용한다.

---

## 상태 출력 형식 (권장 순서)

상태 요청 시 아래 항목을 가능한 한 이 순서대로 제시한다.

1. 브랜치 진행 현황 (트리 블록)
2. Working tree changes
3. Current phase or requested phase
4. Completed TODO items
5. Pending TODO items
6. 진행할 항목 (번호 테이블)
7. Last known verification status
8. Notes or risks

TODO 항목이 많으면 전체를 나열하지 말고 요청된 Phase/접두사 주변 항목만 압축해 보여준다.

브랜치 진행 현황은 아래와 같은 코드 블록 형태를 우선 사용한다.

```text
main
 └── B_07
      ├── spec (✅ SPEC Phase 완료)
      ├── red (📍 RED Phase 진행 중 / 🔴 시작 준비)
      ├── green (⏳ GREEN Phase 예정)
      ├── refactor (⏳ REFACTOR Phase 예정)
      ├── feature (⏳ FEATURE Phase 예정)
      └── final (⏳ FINAL Phase 예정)
```

상태 기호:
- ✅ Phase 완료 (모든 TODO 항목 완료 및 B_07으로 머지됨)
- 📍 현재 작업 중인 브랜치
- 🔴 시작 준비 (브랜치 생성됨, 작업 시작 전)
- 🟡 작업 진행 중 (일부 TODO 항목 완료)
- ⏳ 예정 (아직 생성되지 않음)

진행할 항목은 아래 테이블 형식을 우선 사용한다.

| 순서 | 작업 | 방법 |
|------|------|------|
| 1 | 작업명 | Codex 실행 / GitHub 웹 직접 |
| 2 | 작업명 | Codex 실행 / GitHub 웹 직접 |

---

## Phase 해석 규칙

- `TODO.md`의 Phase 섹션명을 기준으로 현재 단계를 해석한다.
  - `Phase-0: SPEC`
  - `Phase-1: RED`
  - `Phase-2: GREEN`
  - `Phase-3: REFACTOR`
  - `Phase-4: FEATURE`
  - `Phase-5: FINAL`
- 항목 식별자(`RED-02-04` 등)가 요청되면 해당 접두사 범위를 우선 요약한다.

---

## Guardrails

- This is a read-only skill by default.
- Do not mark checkboxes, move files, or run destructive commands.
- Prefer `rg` and `git status --short` for quick inspection.
- If build/test status is unknown, say so instead of guessing.
- 상태 확인을 위해 GitHub 접속/원격 API 조회를 기본 동작으로 사용하지 않는다.

---

## Output Pattern

답변은 짧고 실행 가능하게 유지한다. 진행률 과장이나 추측은 금지하고, 불명확한 항목은 "확인 필요"로 표시한다.

---

## Snapshot Format

스냅샷 파일: `.agents/skills/status/STATUS_SNAPSHOT.md`

권장 템플릿:

```md
# STATUS SNAPSHOT
- UpdatedAt: YYYY-MM-DD HH:MM
- Branch: main
- Phase: Phase-0: SPEC
- LastVerification: 문서 변경만 수행, 빌드/테스트 미실행

## WorkingTree
- M AGENTS.md
- ?? .agents/

## NextItems
1. SPEC-01-01
2. SPEC-01-02
```
