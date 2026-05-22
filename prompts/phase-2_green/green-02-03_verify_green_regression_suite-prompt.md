# GREEN-02-03 실행 프롬프트

## 호출 문구

- `24번 진행`
- `GREEN-02-03 진행`
- `GREEN-02-03 항목을 진행해 주세요`
- `test: verify green regression suite 실행`

---

## 프롬프트

````md
Feedback Analyzer GREEN 회귀 테스트 검증 전문가 - RED 테스트 전체 통과 확인

`TODO.md`의 `GREEN-02-03 test: verify green regression suite` 항목을 실행하라.

너는 RED 단계에서 작성한 실패 테스트가 GREEN 단계 수정 후 모두 통과하는지 확인하고, 필요한 회귀 테스트를 보강하는 테스트 검증 담당자다.
이번 작업의 목표는 RED 단계 테스트가 모두 GREEN이 되었는지 확인하고, 필요한 회귀 테스트를 보강하는 것이다.

제약:
- 테스트 기대값을 낮춰서 통과시키지 말 것
- 생산 코드 수정은 검증 중 발견된 명백한 GREEN 범위 결함에만 제한
- 대규모 리팩토링 금지
- 테스트 보강은 기존 버그 재발 방지에 필요한 최소 범위로 수행
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

GREEN 단계 수정이 RED 실패 테스트를 실제로 통과시켰는지 확인한다.

완료 후 다음이 만족되어야 한다.

- RED 단계에서 추가한 테스트 목록이 확인된다.
- GREEN 수정 후 각 테스트 결과가 기록된다.
- 실패가 남아 있으면 원인과 후속 TODO가 분류된다.
- 필요한 회귀 테스트가 최소 범위로 보강된다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/`
- `docs/bug_fix.md`
- `SESSION_NOTES.md`
- `src/Filters.cpp`
- `src/Session.cpp`
- `src/TextAnalyzer.cpp`
- `src/main.cpp`

RED 테스트 연결:

- `RED-02-01`
- `RED-02-02`
- `RED-02-03`
- `RED-02-04`
- `RED-02-05`
- `RED-02-06`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-02-03` 항목을 확인한다.
2. `tests/` 아래 RED 단계 테스트 목록을 확인한다.
3. `cmake --build build`를 실행한다.
4. `ctest --test-dir build --output-on-failure`를 실행한다.
5. 실패 테스트가 있으면 다음으로 분류한다.
   - GREEN 범위에서 고쳐야 하는 결함
   - REFACTOR 단계로 넘길 구조 문제
   - FEATURE 단계에서 구현할 기능 기준
   - 테스트 자체의 기대값 오류
6. 필요한 회귀 테스트를 최소 보강한다.
7. `docs/bug_fix.md` 또는 `SESSION_NOTES.md`에 결과를 기록한다.
8. 작업 완료 후 `TODO.md`의 `GREEN-02-03` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

검증 결과 표:

```md
| 테스트 그룹 | 관련 TODO | 결과 | 비고 |
|---|---|---|---|
```

실행 명령:

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 실행한 명령
- 통과/실패 테스트 요약
- 보강한 회귀 테스트가 있다면 테스트 이름
- 남은 실패와 후속 TODO
- `GREEN-02-03` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

RED 테스트 목록과 GREEN 수정 이력을 확인한다.

## Step 2. Frame

이번 작업은 회귀 테스트 검증과 최소 보강이다.

수행하지 말아야 할 일:

- 리팩토링 선행
- 테스트 삭제
- 기대값 완화
- 기능 확장 구현

## Step 3. Contract

GREEN 회귀 계약을 다음처럼 고정한다.

- RED에서 정의한 버그 수정 테스트는 GREEN에서 통과해야 한다.
- FEATURE 단계 기능 테스트는 아직 실패할 수 있으며 별도 분류한다.
- 실패를 숨기지 않고 원인과 후속 항목을 남긴다.

## Step 4. Trace

```text
RED test -> GREEN fix -> build -> ctest -> pass/fail classification -> final
```

## Step 5. Write

필요한 회귀 테스트를 최소 보강하고 검증 결과를 문서화한다.

## Step 6. Verify

전체 테스트를 다시 실행해 최종 상태를 확인한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


