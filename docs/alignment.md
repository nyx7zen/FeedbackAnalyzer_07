# 프로젝트 지침 정합성 검토 (SPEC-01-03)

## 1. 검토 대상

| 문서 | 위치 | 상태 | 역할 |
|------|------|------|------|
| AGENTS.md | 루트 | 현재 | 프로젝트 전체 작업 기준 (우선) |
| TODO.md | 루트 | 현재 | Phase별 실행 항목 정의 (우선) |
| refs/project_purpose.md | refs/ | 참고 | 프로젝트 목적, 학습 목표 |
| refs/legacy/guide.md | refs/legacy/ | 레거시 | 구 Cursor AI 실습 가이드 |
| refs/legacy/GEMINI.md | refs/legacy/ | 레거시 | 구 Gemini CLI 컨텍스트 정의 |
| refs/legacy/CLAUDE.md | refs/legacy/ | 레거시 | 구 Claude 프로젝트 개요 |

---

## 2. 현재 문서 우선순위

| 우선순위 | 문서 | 역할 |
|---:|---|---|
| 1 | AGENTS.md | 현재 프로젝트의 작업 규칙, 브랜치 전략, 커밋 규칙, 산출물 정의 |
| 2 | TODO.md | Phase-0~5 단계, 각 단계 내 작업 항목, 체크박스 관리 |
| 3 | CLAUDE.md | Claude Code 표준 설정 (AGENTS.md 참조 링크 포함) |
| 4 | refs/project_purpose.md | 프로젝트 목적, 학습 목표 참고 자료 |
| 5 | refs/legacy/* | 과거 기준, 히스토리 참고용 (현재 기준 X) |

---

## 3. 충돌 항목 분석 및 조치

### 3.1 브랜치 전략

| 영역 | 레거시 기준 | 현재 기준 | 충돌 여부 | 조치 |
|------|-----------|---------|---------|------|
| 브랜치 구조 | `maintdd` → `refactoring` → `feature` | `main` → `B_07` → `spec/red/green/refactor/feature/final` | **충돌** | AGENTS.md 우선 적용. B_07 통합 브랜치 기반 6단계 워크플로우 채택. |
| 병합 원칙 | GitHub PR 기반 검토 후 병합 | PR 기반 + 단계별 순차 병합 | **일치** | PR 기반 협업 원칙은 동일. 현재 B_07 통합 브랜치 추가. |
| 커밋 메시지 | Conventional Commits (feat, fix, refactor 등) | Conventional Commits + [TODO_ID] 접두사 | **확장** | 현재 기준에서 TODO_ID를 추가하여 추적성 향상. 레거시는 TODO_ID 없음. |

### 3.2 빌드/테스트 명령

| 영역 | 레거시 기준 | 현재 기준 | 충돌 여부 | 조치 |
|------|-----------|---------|---------|------|
| CMake 구성 | `cmake -B build && cmake --build build` | `cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=...` | **충돌** | AGENTS.md & docs/build-and-test.md 기준 명시적 MinGW 경로 필수. Windows 환경 호환성 확보. |
| 테스트 실행 | `ctest --output-on-failure` | `ctest --output-on-failure` | **일치** | 동일하게 유지. |
| 프레임워크 | Google Test (GTest) | Google Test (GTest) | **일치** | 동일하게 유지. |

### 3.3 문서 산출물 경로

| 영역 | 레거시 기준 | 현재 기준 | 충돌 여부 | 조치 |
|------|-----------|---------|---------|------|
| 분석 문서 | `analysis.md` (루트 또는 docs/) | `docs/analysis.md` | **명확화** | 현재는 docs/ 폴더 내 명시. 레거시는 위치 불분명. |
| 버그 리포트 | `bug_fix.md` | `docs/bug_fix.md` | **명확화** | 현재는 docs/ 폴더 내 명시. |
| 리팩토링 리포트 | `refactoring.md` | `docs/refactoring.md` | **명확화** | 현재는 docs/ 폴더 내 명시. |
| 기능 명세 | `feature.md` | `docs/feature.md` | **명확화** | 현재는 docs/ 폴더 내 명시. |
| 최종 리포트 | `report.md` | `docs/final.md` | **변경** | 레거시 report.md → 현재 final.md로 변경. Phase-5 최종 산출물 역할. |

### 3.4 Phase 구조

| 영역 | 레거시 기준 | 현재 기준 | 충돌 여부 | 조치 |
|------|-----------|---------|---------|------|
| Phase 수 | 명시적 단계 없음 (refactoring, feature만 언급) | Phase-0 ~ Phase-5 (6단계) | **추가** | 현재 AGENTS.md에서 명확히 정의: SPEC, RED, GREEN, REFACTOR, FEATURE, FINAL. |
| 테스트 포함 | refactoring 단계에 GTest 기초 구축만 언급 | RED(Phase-1)에서 실패 테스트 작성 전담 | **구조화** | 현재 TDD 워크플로우 명시: RED → GREEN → REFACTOR → FEATURE → FINAL. |
| 코드 품질 | 리팩토링 대상 스멜만 언급 | AGENTS.md에서 Code Quality Rules 명시 | **구조화** | 매직 넘버 상수화, Doxygen 문서화, 함수 20줄 등 규칙 명시. |

### 3.5 상태 관리 및 세션 로깅

| 영역 | 레거시 기준 | 현재 기준 | 충돌 여부 | 조치 |
|------|-----------|---------|---------|------|
| 세션 로그 | 언급 없음 | SESSION_NOTES.md 기반 추적 | **추가** | AGENTS.md Workflow 섹션에서 SESSION_NOTES.md 갱신 의무화. |
| 상태 스냅샷 | 언급 없음 | .agents/skills/status/STATUS_SNAPSHOT.md | **추가** | 현재 /status skill에서 스냅샷 기반 상태 추적. |
| 커밋/푸시 자동화 | 언급 없음 | run skill에서 커밋/푸시 + 보고서 자동 생성 | **추가** | AGENTS.md & run skill SKILL.md에서 단계별 워크플로우 정의. |

---

## 4. TODO 항목 실행 기준 정정

### Step 1: 항목 확인
```
/run {TODO_ID}  (예: /run SPEC-01-03)
```

### Step 2: 지침 확인 순서
1. **AGENTS.md** 읽기: 현재 작업 규칙 확인
2. **TODO.md** 읽기: 해당 Phase와 항목 확인
3. **prompts/INDEX.md** 참조: 프롬프트 파일 위치 확인
4. **refs/legacy/** 참고: 과거 기준 이해 (현재 기준 우선)

### Step 3: 작업 수행
- AGENTS.md 기준 준수 (코드 품질, 커밋 메시지, 산출물)
- TODO.md 항목 범위 내에서만 작업
- 문서 변경은 한국어로 작성

### Step 4: 산출물 생성
- 실행 보고서: `reports/{phase_folder}/{todo_id_lower}-report.md`
- 추가 문서: 필요 시 `docs/` 내 추가

### Step 5: 커밋/푸시
- 커밋 메시지: `[{TODO_ID}] {type}: {description}`
- 사용자 승인 후 진행

---

## 5. 남은 주의사항

### 5.1 레거시 문서의 위치와 역할

- **refs/legacy/guide.md**: 구 Cursor AI 기반 가이드. 현재 B_07 전략과 다름. 참고용만 사용.
- **refs/legacy/GEMINI.md**: 구 Gemini CLI 기반 컨텍스트. 코드 스멜 분석 참고용.
- **refs/legacy/CLAUDE.md**: 구 프로젝트 개요. 초기 기술 스택은 동일(C++17, CMake, GTest)하나, 브랜치 전략과 리팩토링 단계는 현재와 다름.

**권장사항:**
- 레거시 문서는 **히스토리와 컨텍스트 이해**용으로만 참고
- 작업 기준은 **항상 AGENTS.md와 TODO.md** 우선
- 명확하지 않은 부분은 현재 기준(AGENTS.md)으로 해석

### 5.2 기술 스택 일관성

| 항목 | 상태 |
|------|------|
| C++ 표준 | ✅ C++17 (모든 문서 일치) |
| 빌드 시스템 | ✅ CMake 3.14+ (모든 문서 일치) |
| 테스트 프레임워크 | ✅ Google Test (모든 문서 일치) |
| 웹 라이브러리 | ✅ cpp-httplib (모든 문서 일치) |
| 코딩 표준 | ⚠️ AGENTS.md Code Quality Rules 준수 (레거시와 보완) |

### 5.3 커밋 메시지 체계

**현재 기준 (AGENTS.md):**
```
[{TODO_ID}] {type}: {description}

예: [SPEC-01-03] docs: align project instructions
예: [RED-02-04] test: add neutral filter test
```

**레거시 기준 (guide.md, GEMINI.md):**
```
{type}: {description}

예: docs: align project instructions
```

→ **현재 기준에서 [TODO_ID] 추가**하여 추적성 향상.

### 5.4 코드 품질 기준

모든 문서가 다음을 공통으로 강조:
- ✅ 매직 넘버 상수화
- ✅ Doxygen 문서화 (public 클래스/메서드)
- ✅ 함수 20줄 제한
- ✅ 테스트 네이밍: `should_[결과]_when_[조건]`

→ **충돌 없음**. AGENTS.md Code Quality Rules 섹션에서 현재 기준 명시.

---

## 6. 결론

### 6.1 주요 정정사항

| 항목 | 레거시 → 현재 |
|------|-------------|
| 브랜치 전략 | `maintdd → refactoring → feature` → **`main → B_07 → spec/red/green/refactor/feature/final`** |
| Phase 수 | 3단계 → **6단계** |
| 빌드 명령 | `cmake -B build` → **`cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=...`** |
| 산출물 경로 | `docs/`와 루트 혼재 → **`docs/` 통일** |
| 최종 리포트 | `report.md` → **`docs/final.md`** |
| 커밋 메시지 | `feat:` 형식 → **`[TODO_ID] feat:` 형식** |

### 6.2 현재 운영 기준 (변경 없음)

- ✅ 모든 작업은 **AGENTS.md와 TODO.md를 우선** 참고
- ✅ **PR 기반 협업** 유지
- ✅ **Conventional Commits + [TODO_ID] 접두사** 사용
- ✅ **Google Test + CMake** 기반 빌드/테스트
- ✅ **한국어 문서** 작성

---

## 7. 참고 문서

- **현재 기준:** AGENTS.md (루트), TODO.md (루트)
- **작업 참고:** CLAUDE.md, prompts/INDEX.md
- **히스토리 참고:** refs/legacy/ 폴더

---

**검토 완료일:** 2026-05-22  
**작성:** Claude Code 기반 SPEC-01-03 실행  
**상태:** 정합성 검토 완료, 충돌 조치 명시
