# B_07 Branch Workflow

## 개요

B_07은 Feedback Analyzer 리팩토링 프로젝트의 **실습 통합 브랜치**입니다. 단계별 학습 워크플로우의 중심이 되며, 모든 단계별 작업 브랜치가 B_07에 병합됩니다.

---

## 브랜치 전략

### 브랜치 계층 구조

```
main (프로덕션 코드)
  └─ B_07 (실습 통합 브랜치)
      ├─ spec (Phase-0: 환경 설정, 분석)
      ├─ red (Phase-1: 실패 테스트)
      ├─ green (Phase-2: 테스트 통과)
      ├─ refactor (Phase-3: 구조 개선)
      ├─ feature (Phase-4: 신규 기능)
      └─ final (Phase-5: 최종 산출물)
```

### 단계별 브랜치 목적

| Phase | 브랜치 | 목적 | 산출물 |
|-------|--------|------|--------|
| 0 | `spec` | 환경 설정, 프로젝트 분석 | 분석 문서, 지침 정렬 |
| 1 | `red` | 실패하는 테스트 작성 | 테스트 타깃, 실패 테스트 |
| 2 | `green` | 테스트 통과 구현 | 버그 수정, 최소 구현 |
| 3 | `refactor` | 구조 개선 (동작 유지) | 리팩토링 완료, 정리 |
| 4 | `feature` | 신규 기능 구현 | 새 기능, 통합 테스트 |
| 5 | `final` | 최종 산출물, 리포트 | 종합 리포트, 검증 |

---

## 병합 흐름 (Merge Flow)

### 순차적 병합

각 단계가 완료되면 B_07에 병합합니다:

```
1. spec → B_07      (분석, 지침 정렬 완료)
2. red → B_07       (실패 테스트 작성 완료)
3. green → B_07     (테스트 통과, 버그 수정 완료)
4. refactor → B_07  (리팩토링, 정리 완료)
5. feature → B_07   (신규 기능 구현 완료)
6. final → B_07     (최종 리포트, 검증 완료)
7. B_07 → main      (전체 실습 결과 최종 반영)
```

### 병합 원칙

- 각 단계 작업이 완료되면 PR 또는 직접 병합
- B_07은 모든 단계의 누적 결과물
- main은 B_07의 최종 통합 결과만 받음
- 각 단계 브랜치는 독립적으로 작업, 단계 순서 유지

---

## 작업 흐름 (Workflow)

### 각 단계별 작업 사이클

1. **단계 브랜치 생성**
   ```bash
   git checkout B_07
   git checkout -b {phase_branch}  # spec, red, green, ...
   ```

2. **TODO 항목 실행**
   ```bash
   /run {ITEM_ID}  # 예: /run SPEC-01-01
   ```

3. **변경사항 커밋**
   ```bash
   git add <files>
   git commit -m "feat: ..."  # Conventional Commits
   ```

4. **B_07에 병합**
   ```bash
   git checkout B_07
   git merge {phase_branch}
   ```

5. **다음 단계로 전환**
   ```bash
   git checkout -b {next_phase_branch}
   ```

---

## 작업 항목 식별자

### 명명 규칙

`{브랜치대문자}-{서브섹션순번}-{항목순번}`

**예시:**
- `SPEC-01-01`: SPEC 브랜치, 섹션 1, 항목 1
- `RED-02-04`: RED 브랜치, 섹션 2, 항목 4
- `REFACTOR-03-03`: REFACTOR 브랜치, 섹션 3, 항목 3

### 호출 문법

```bash
/run SPEC-01-01           # 직접 ID로 호출
SPEC-01-02 진행           # 한국어 명령
/run spec REFACTOR-01-01  # 단계 + ID
```

---

## 상태 추적 (Status Tracking)

### 진행 상황 확인

```bash
/status              # 전체 상태 (스냅샷 기반)
/status spec         # SPEC 단계만 (자동 갱신)
상태갱신             # 전체 상태 새로고침
```

### 문서 업데이트

- **TODO.md:** 체크박스 항목 완료 체크
- **SESSION_NOTES.md:** 각 세션 작업 로그 기록

---

## 주요 산출물 위치

- `docs/analysis.md` - 프로젝트 분석 (SPEC)
- `docs/bug_fix.md` - 버그 수정 리포트 (GREEN)
- `docs/refactoring.md` - 리팩토링 리포트 (REFACTOR)
- `docs/feature.md` - 기능 명세 (FEATURE)
- `docs/final.md` - 최종 리포트 (FINAL)

---

## 예시: 첫 번째 사이클

```bash
# 1. B_07 생성 및 spec 브랜치 생성
git checkout -b B_07
git checkout -b spec

# 2. SPEC-01-01 실행
/run SPEC-01-01
# → docs/b07-branch-workflow.md 작성
# → TODO.md의 SPEC-01-01 완료 체크
# → SESSION_NOTES.md 갱신

# 3. 커밋
git add docs/b07-branch-workflow.md TODO.md SESSION_NOTES.md
git commit -m "docs: define B_07 branch workflow"

# 4. 병합
git checkout B_07
git merge spec

# 5. 다음 단계 준비
git checkout -b red
```

---

## 참고

자세한 프로젝트 지침은 [AGENTS.md](../AGENTS.md) 참조.

todo 항목 전체는 [TODO.md](../TODO.md) 참조.
