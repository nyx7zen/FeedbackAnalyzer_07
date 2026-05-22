# SPEC-01-01 실행 프롬프트

## 호출 문구

- `1번 진행`
- `SPEC-01-01 진행`
- `SPEC-01-01 항목을 진행해 주세요`
- `docs: define B_07 branch workflow 실행`

---

## 프롬프트

```md
Feedback Analyzer 브랜치 전략 문서화 전문가 - C++17/CMake 리팩토링 프로젝트

`TODO.md`의 `SPEC-01-01 docs: define B_07 branch workflow` 항목을 실행하라.

너는 레거시 C++ 웹 애플리케이션의 실습 브랜치 전략과 작업 흐름을 문서화하는 기술 문서 작성자다.
이번 작업의 목표는 `B_07` 통합 브랜치를 기준으로 `spec -> red -> green -> refactor -> feature -> final` 단계 흐름과 병합 순서를 명확히 정리하는 것이다.

제약:
- 구현 코드 변경 금지
- 테스트 코드 작성 금지
- 빌드 스크립트 변경 금지
- 브랜치 생성, checkout, merge 같은 Git 상태 변경 금지
- 문서와 세션 로그만 필요한 범위에서 수정
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

`FeedbackAnalyzer_07` 프로젝트의 실습 브랜치 전략을 문서화한다.

문서에는 다음 목적이 드러나야 한다.

- `B_07`이 실습 통합 브랜치라는 점
- `spec`, `red`, `green`, `refactor`, `feature`, `final`가 단계별 작업 브랜치라는 점
- 각 단계가 어떤 산출물과 검증 목표를 갖는지
- 단계별 브랜치가 어떤 순서로 `B_07`에 병합되는지
- 최종적으로 `B_07`에서 `main`으로 반영되는 흐름

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `refs/project_purpose.md`
- `refs/legacy/guide.md`
- `refs/legacy/GEMINI.md`

파일이 없거나 경로가 다르면 저장소의 실제 구조를 우선한다.

프로젝트 전제:

- C++17, CMake 3.14+, cpp-httplib 기반 Feedback Analyzer 웹 애플리케이션이다.
- 주요 목적은 레거시 코드의 구조 개선, 테스트 가능성 확보, 상태 관리 정리, 기능 보강이다.
- 단계별 작업은 `TODO.md` 체크박스 항목과 연결되어야 한다.
- 커밋 메시지는 Conventional Commits 형식을 따른다.
- 최종 산출물과 단계별 보고서는 `docs/` 아래에 둔다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `SPEC-01-01` 항목과 브랜치 전략 섹션을 확인한다.
2. `AGENTS.md`의 Branch And Phase Strategy 지침을 확인한다.
3. `refs/project_purpose.md`에서 프로젝트 목적과 학습 목표를 확인한다.
4. 레거시 지침인 `refs/legacy/guide.md`, `refs/legacy/GEMINI.md`와 현재 지침이 충돌하는지 확인한다.
5. `B_07` 통합 브랜치 중심의 단계별 브랜치 전략을 문서화한다.
6. 문서 변경이 발생하면 `SESSION_NOTES.md`에 세션 로그를 추가한다.
7. 작업 완료 후 `TODO.md`의 `SPEC-01-01` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

문서 산출물은 기존 저장소 구조와 가장 잘 맞는 위치에 작성한다.
이미 브랜치 전략을 담는 문서가 있으면 그 문서를 갱신하고, 없다면 다음 후보 중 가장 적절한 위치를 선택한다.

- `docs/analysis.md`
- `docs/branch_strategy.md`
- `README.md`
- `AGENTS.md`

단, `AGENTS.md`는 작업 지침이므로 중복 설명을 길게 늘리지 않는다.
실습 산출물 성격의 설명은 가능하면 `docs/` 아래에 둔다.

브랜치 전략 문서에는 최소한 다음 섹션을 포함한다.

```md
# Feedback Analyzer 브랜치 전략

## 1. 목적

## 2. 브랜치 구성

| 브랜치 | 역할 | 주요 산출물 |
|---|---|---|

## 3. 단계별 작업 흐름

## 4. 병합 순서

## 5. 커밋 메시지 규칙

## 6. 검증 기준

## 7. TODO 항목과의 연결
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `SPEC-01-01` 완료 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

`TODO.md`, `AGENTS.md`, `refs/project_purpose.md`, `refs/legacy/guide.md`, `refs/legacy/GEMINI.md`를 읽고 현재 브랜치 전략과 문서 기준을 관찰한다.

확인할 질문:

- `B_07`은 어떤 역할인가?
- 단계별 브랜치는 몇 개이며 순서는 무엇인가?
- 각 단계의 책임과 산출물은 무엇인가?
- 기존 문서끼리 충돌하는 지침이 있는가?

## Step 2. Frame

이번 작업의 범위를 브랜치 전략 문서화로 제한한다.

수행하지 말아야 할 일:

- 실제 브랜치 생성
- Git merge 수행
- C++ 코드 변경
- 테스트 추가
- 빌드 설정 변경

## Step 3. Contract

브랜치 전략을 다음 계약으로 고정한다.

- `B_07`: 실습 통합 브랜치
- `spec`: 환경 및 지침 설정, 분석 문서 작성
- `red`: 실패하는 테스트 작성
- `green`: 테스트 통과를 위한 최소 구현
- `refactor`: 동작 유지 상태의 구조 개선
- `feature`: 신규 기능 구현
- `final`: 최종 산출물과 종합 리포트 작성

병합 흐름:

```text
spec -> B_07
red -> B_07
green -> B_07
refactor -> B_07
feature -> B_07
final -> B_07
B_07 -> main
```

## Step 4. Trace

`TODO.md`의 Phase와 브랜치 전략을 연결해 설명한다.

추적 매핑:

| TODO Phase | 브랜치 | 목적 |
|---|---|---|
| Phase-0: SPEC | `spec` | 기준 정리와 구조 분석 |
| Phase-1: RED | `red` | 실패 테스트 작성 |
| Phase-2: GREEN | `green` | 최소 수정으로 테스트 통과 |
| Phase-3: REFACTOR | `refactor` | 구조 개선 |
| Phase-4: FEATURE | `feature` | 기능 보강 |
| Phase-5: FINAL | `final` | 최종 검수와 보고 |

## Step 5. Write

브랜치 전략 문서를 작성하거나 갱신한다.

문장 기준:

- 모호어를 피한다.
- 브랜치 역할과 병합 순서를 명시한다.
- TODO Phase와 연결한다.
- 실제 Git 명령을 실행하라고 지시하지 않는다.
- 향후 작업자가 그대로 따라갈 수 있도록 완료 조건을 적는다.

## Step 6. Verify

작성 후 다음 조건을 자체 검수한다.

- `TODO.md`의 브랜치 전략과 충돌하지 않는다.
- `AGENTS.md`의 Branch And Phase Strategy와 충돌하지 않는다.
- `refs/project_purpose.md`의 프로젝트 목적과 연결된다.
- 단계별 산출물이 명확하다.
- 병합 순서가 단방향으로 이해된다.
- 문서 작업만 수행했으므로 빌드/테스트를 실행하지 않았음을 기록한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 문서화 작업 로그를 추가한다.
- `TODO.md`의 `SPEC-01-01` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일, 완료 여부, 검증 여부, 다음 추천 항목을 간결히 보고한다.
```


