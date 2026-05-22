# GREEN-01-04 실행 프롬프트

## 호출 문구

- `21번 진행`
- `GREEN-01-04 진행`
- `GREEN-01-04 항목을 진행해 주세요`
- `fix: reset shared state in tests 실행`

---

## 프롬프트

````md
Feedback Analyzer 공유 상태 초기화 구현 전문가 - GREEN 테스트 격리

`TODO.md`의 `GREEN-01-04 fix: reset shared state in tests` 항목을 실행하라.

너는 RED 단계에서 작성한 상태 격리 테스트를 통과시키기 위해 전역 또는 세션 상태 초기화 경로를 최소 보강하는 C++ 테스트 주도 개발자다.
이번 작업의 목표는 테스트 간 전역 또는 세션 상태가 누수되지 않도록 초기화 경로를 보강하는 것이다.

제약:
- RED 상태 격리 테스트 통과를 위한 최소 변경
- 새 전역 상태 추가 금지
- Session을 더미 API로 방치하지 않도록 후속 REFACTOR 연결을 고려
- 대규모 상태 관리 재설계는 `REFACTOR-03-*`로 미룰 것
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

테스트 간 공유 상태 누수를 막는다.

완료 후 다음이 만족되어야 한다.

- `RED-02-06` 상태 격리 테스트가 통과하거나, 남은 실패가 명확히 분류된다.
- fixture의 `SetUp`/`TearDown`이 상태 초기화 경로를 사용한다.
- `Constants`, `Session`, 필터/분석 전역 상태 초기화가 가능한 범위에서 정리된다.
- 남은 구조 개선은 `REFACTOR-03-*` 항목과 연결된다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `tests/FiltersTest.cpp`
- `src/Session.h`
- `src/Session.cpp`
- `src/Constants.h`
- `src/Constants.cpp`
- `src/Filters.cpp`
- `src/TextAnalyzer.cpp`
- `docs/analysis.md`

후속 연결:

- `REFACTOR-03-01 refactor: remove global filter state`
- `REFACTOR-03-02 refactor: remove global analyzer state`
- `REFACTOR-03-03 refactor: implement session storage map`
- `REFACTOR-03-04 refactor: add feedback session clear api`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-01-04` 항목을 확인한다.
2. `RED-02-06` 상태 격리 테스트의 실패 원인을 확인한다.
3. 현재 초기화 API가 있는 상태와 없는 상태를 구분한다.
4. 가능한 최소 clear/reset API 또는 테스트 fixture 초기화 경로를 보강한다.
5. 테스트 기대값을 낮추지 않고 실패를 해결한다.
6. build와 ctest를 실행한다.
7. 남은 상태 관리 한계를 `SESSION_NOTES.md`에 기록한다.
8. 작업 완료 후 `TODO.md`의 `GREEN-01-04` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

수정 후보:

- `src/Session.h`
- `src/Session.cpp`
- `tests/TextAnalyzerTest.cpp`
- `tests/FiltersTest.cpp`
- `src/Constants.*`는 기존 초기화 방식이 있을 때만 수정

검증 명령:

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 추가한 초기화/clear 경로
- 통과한 상태 격리 테스트
- 남은 상태 관리 리스크
- `GREEN-01-04` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

상태 격리 테스트 실패 원인을 확인한다.

## Step 2. Frame

이번 작업은 테스트 격리를 위한 최소 GREEN 구현이다.

수행하지 말아야 할 일:

- 전체 세션 아키텍처 재설계
- 필터/분석 모듈 대규모 리팩토링
- 테스트 기대값 완화

## Step 3. Contract

공유 상태 초기화 계약을 다음처럼 고정한다.

- 테스트 시작 전 상태는 비어 있어야 한다.
- 테스트 종료 후 다음 테스트에 영향을 주면 안 된다.
- 상태 초기화는 명시적 API 또는 fixture에서 수행한다.

## Step 4. Trace

```text
previous test state -> fixture reset -> current test reads state -> expected isolated value
```

## Step 5. Write

초기화 경로를 최소 구현하고 fixture에 연결한다.

## Step 6. Verify

상태 격리 테스트와 전체 회귀 테스트를 실행한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


