# RED-02-01 실행 프롬프트

## 호출 문구

- `12번 진행`
- `RED-02-01 진행`
- `RED-02-01 항목을 진행해 주세요`
- `test: add empty input boundary test 실행`

---

## 프롬프트

````md
Feedback Analyzer 빈 입력 경계값 테스트 작성 전문가 - RED 실패 테스트

`TODO.md`의 `RED-02-01 test: add empty input boundary test` 항목을 실행하라.

너는 텍스트 분석 로직의 경계값 동작을 실패 테스트로 먼저 고정하는 TDD 테스트 작성자다.
이번 작업의 목표는 빈 문자열 입력의 기대 동작을 정의하고, 현재 구현에서 실패할 수 있는 경계값 테스트를 작성하는 것이다.

제약:
- 생산 코드 수정 금지
- 테스트 실패는 RED 단계에서 허용되며, 의도된 실패인지 명확히 기록
- 기대 동작은 문서와 코드 근거를 확인한 뒤 테스트 이름과 assertion에 반영
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

빈 입력 처리 기준을 테스트로 고정한다.

테스트는 다음 질문에 답해야 한다.

- 빈 문자열은 예외 없이 처리되는가?
- 빈 문자열의 감성 결과는 무엇이어야 하는가?
- 키워드 결과는 비어 있어야 하는가?
- 필터나 세션 상태에 영향을 주지 않는가?

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/Constants.cpp`
- `docs/analysis.md`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-01` 항목을 확인한다.
2. 현재 TextAnalyzer API로 빈 문자열을 분석하는 방법을 확인한다.
3. 빈 입력의 기대 동작을 테스트 이름과 assertion으로 표현한다.
4. `tests/TextAnalyzerTest.cpp`에 경계값 테스트를 추가한다.
5. 생산 코드는 수정하지 않는다.
6. 가능한 경우 build와 ctest를 실행한다.
7. 실패하면 RED 단계의 의도된 실패인지 기록한다.
8. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(TextAnalyzerTest, should_return_neutral_when_input_is_empty)
TEST_F(TextAnalyzerTest, should_return_no_keywords_when_input_is_empty)
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 기대 동작
- `RED-02-01` 완료 여부
- ctest 결과와 실패가 의도된 RED인지 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

빈 문자열이 현재 코드에서 어떻게 처리되는지 읽는다.

## Step 2. Frame

이번 작업은 실패 테스트 작성이다. 구현 수정은 하지 않는다.

## Step 3. Contract

빈 입력 계약을 다음처럼 고정한다.

- 예외나 크래시가 없어야 한다.
- 감성 결과는 명시적으로 정의되어야 한다.
- 키워드 결과는 비어 있거나 명시 기준을 따라야 한다.

## Step 4. Trace

```text
empty string -> analyze sentiment -> analyze keywords -> expected stable result
```

## Step 5. Write

fixture에 빈 입력 경계값 테스트를 추가한다.

## Step 6. Verify

ctest를 실행하고 실패 여부를 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


