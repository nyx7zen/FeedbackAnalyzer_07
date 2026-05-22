# RED-02-06 실행 프롬프트

## 호출 문구

- `17번 진행`
- `RED-02-06 진행`
- `RED-02-06 항목을 진행해 주세요`
- `test: add session isolation test 실행`

---

## 프롬프트

````md
Feedback Analyzer 세션 격리 실패 테스트 작성 전문가 - RED 상태 관리 검증

`TODO.md`의 `RED-02-06 test: add session isolation test` 항목을 실행하라.

너는 테스트 간 공유 상태가 남지 않아야 한다는 요구를 실패 테스트로 고정하는 상태 관리 테스트 엔지니어다.
이번 작업의 목표는 상태 초기화 시나리오를 작성하고, Session 또는 전역 상태가 테스트 간 누수되지 않아야 함을 검증하는 RED 테스트를 만드는 것이다.

제약:
- 생산 코드 수정 금지
- Session 저장소 구현 금지
- clear/reset API를 새로 구현하지 말 것
- 실패는 RED 단계 결과로 기록하고 후속 GREEN/REFACTOR 항목과 연결
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

세션과 공유 상태의 격리 요구를 테스트로 고정한다.

테스트는 다음 위험을 드러내야 한다.

- 이전 테스트에서 저장한 값이 다음 테스트에 남는 문제
- Session key가 무시되는 문제
- clear/reset 경로가 없는 문제
- 필터 또는 분석 결과 전역 상태가 다음 실행에 영향을 주는 문제

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/Session.h`
- `src/Session.cpp`
- `src/Filters.cpp`
- `src/TextAnalyzer.cpp`
- `docs/analysis.md`

후속 연결:

- `GREEN-01-04 fix: reset shared state in tests`
- `REFACTOR-03-03 refactor: implement session storage map`
- `REFACTOR-03-04 refactor: add feedback session clear api`
- `REFACTOR-03-05 test: add session lifecycle regression tests`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-06` 항목을 확인한다.
2. `Session` API의 저장/조회/초기화 동작을 확인한다.
3. 서로 다른 키 또는 테스트 실행 간 상태 격리를 검증하는 테스트를 설계한다.
4. 현재 API로 표현 가능한 실패 테스트를 작성한다.
5. clear/reset API가 없으면 그 한계를 테스트 이름 또는 주석으로 명확히 한다.
6. 생산 코드는 수정하지 않는다.
7. 가능한 경우 build와 ctest를 실행한다.
8. 실패하면 RED 단계의 의도된 실패인지 기록한다.
9. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(TextAnalyzerTest, should_not_share_session_values_when_keys_are_different)
TEST_F(TextAnalyzerTest, should_start_with_empty_session_when_test_is_reset)
TEST_F(TextAnalyzerTest, should_not_reuse_previous_analysis_when_session_is_cleared)
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 검증한 상태 격리 시나리오
- 현재 실패 원인
- `RED-02-06` 완료 여부
- 빌드/테스트 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

Session과 전역 상태 후보를 확인한다.

권장 검색:

```powershell
rg -n "Session|static|global|clear|reset|set|get" src tests
```

## Step 2. Frame

이번 작업은 상태 격리 실패 테스트 작성이다. 구현 수정은 하지 않는다.

## Step 3. Contract

세션 격리 계약을 다음처럼 고정한다.

- 서로 다른 키의 값은 섞이지 않아야 한다.
- 테스트 시작 시 이전 테스트 상태가 남아 있지 않아야 한다.
- 명시적 clear 또는 reset이 있으면 비운 뒤 조회 결과가 비어야 한다.
- API가 더미라면 실패 테스트로 드러낸다.

## Step 4. Trace

```text
test A stores state -> reset/next test -> test B reads state -> expected empty or isolated value
```

## Step 5. Write

세션 격리 테스트를 작성한다.

## Step 6. Verify

ctest를 실행하고 실패를 RED 결과로 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


