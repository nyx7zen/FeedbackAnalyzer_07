# RED-02-04 실행 프롬프트

## 호출 문구

- `15번 진행`
- `RED-02-04 진행`
- `RED-02-04 항목을 진행해 주세요`
- `test: add neutral filter test 실행`

---

## 프롬프트

````md
Feedback Analyzer 중립 필터 결함 재현 테스트 전문가 - RED 실패 테스트

`TODO.md`의 `RED-02-04 test: add neutral filter test` 항목을 실행하라.

너는 필터 조건의 논리 연산자와 분기 오류를 실패 테스트로 재현하는 테스트 엔지니어다.
이번 작업의 목표는 `중립` 필터 판정 결함을 드러내는 테스트를 작성하고, 논리 연산자 및 분기 조건 오류를 검증 대상으로 고정하는 것이다.

제약:
- 생산 코드 수정 금지
- 필터 조건을 고치지 말 것
- 실패 테스트는 RED 결과로 기록
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

중립 필터가 중립 피드백만 올바르게 통과시키는지 테스트로 고정한다.

테스트는 다음 결함을 드러내야 한다.

- `중립` 필터가 긍정 또는 부정 피드백을 잘못 포함하는지
- 논리 연산자 `&&`/`||` 혼동이 있는지
- 필터 선택값과 감성 라벨 비교가 올바른지
- 후속 `GREEN-01-01`에서 수정할 기대 동작이 명확한지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp` 또는 필터 전용 테스트 파일
- `src/Filters.h`
- `src/Filters.cpp`
- `src/TextAnalyzer.h`
- `src/Constants.h`
- `docs/analysis.md`

후속 연결:

- `GREEN-01-01 fix: correct neutral filter condition`
- `RED-02-05 test: add filter combination tests`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-04` 항목을 확인한다.
2. `Filters.cpp`에서 중립 필터 조건을 확인한다.
3. 필터 API 호출 방식을 파악한다.
4. 중립 피드백은 통과하고 긍정/부정 피드백은 제외되는 테스트를 작성한다.
5. 필요하면 `tests/FiltersTest.cpp`를 생성하거나 기존 fixture에 추가한다.
6. 생산 코드는 수정하지 않는다.
7. 가능한 경우 build와 ctest를 실행한다.
8. 실패하면 `GREEN-01-01`에서 해결할 RED 실패로 기록한다.
9. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(FiltersTest, should_include_neutral_feedback_when_neutral_filter_is_selected)
TEST_F(FiltersTest, should_exclude_positive_feedback_when_neutral_filter_is_selected)
TEST_F(FiltersTest, should_exclude_negative_feedback_when_neutral_filter_is_selected)
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 중립 필터 기대 동작
- 실패한 assertion이 있다면 요약
- `RED-02-04` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

필터 조건과 감성 라벨 비교 방식을 확인한다.

## Step 2. Frame

이번 작업은 결함 재현 테스트 작성이다. 구현 수정은 하지 않는다.

## Step 3. Contract

중립 필터 계약을 다음처럼 고정한다.

- 필터가 `중립`이면 감성 라벨이 `중립`인 항목만 포함한다.
- 긍정/부정 항목은 제외한다.
- 전체 필터와 개별 필터 동작은 구분한다.

## Step 4. Trace

```text
feedback item -> sentiment label -> selected filter -> included/excluded
```

## Step 5. Write

필터 테스트를 작성한다.

## Step 6. Verify

ctest를 실행하고 실패를 RED 결과로 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


