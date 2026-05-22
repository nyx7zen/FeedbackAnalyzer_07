# RED-02-03 실행 프롬프트

## 호출 문구

- `14번 진행`
- `RED-02-03 진행`
- `RED-02-03 항목을 진행해 주세요`
- `test: add mixed sentiment input test 실행`

---

## 프롬프트

````md
Feedback Analyzer 혼합 감성 테스트 작성 전문가 - RED 기준 고정

`TODO.md`의 `RED-02-03 test: add mixed sentiment input test` 항목을 실행하라.

너는 긍정/부정 키워드가 한 문장에 함께 등장할 때 감성 판정 기준이 드러나도록 실패 테스트를 작성하는 TDD 테스트 엔지니어다.
이번 작업의 목표는 긍정/부정 혼재 문장 시나리오를 작성하고, 기존 첫 키워드 중심 판정의 한계를 테스트로 드러내는 것이다.

제약:
- 생산 코드 수정 금지
- 감성 점수 계산 로직 구현 금지
- 테스트 실패는 RED 단계 결과로 기록
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

혼합 감성 문장의 기대 동작을 테스트로 고정한다.

테스트는 다음 기준을 드러내야 한다.

- 긍정과 부정이 모두 있을 때 첫 키워드만으로 판단하면 안 된다.
- 긍정/부정 빈도 또는 상대 점수 기준이 필요하다.
- 동률일 때 중립 처리 기준이 필요하다.
- 후속 FEATURE 단계의 가중치 기반 스코어링과 연결된다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/Constants.cpp`
- `docs/analysis.md`

후속 연결:

- `FEATURE-01-01 test: add weighted sentiment scoring tests`
- `FEATURE-01-02 feat: count positive and negative keywords`
- `FEATURE-01-03 feat: calculate relative sentiment score`
- `FEATURE-01-04 feat: classify sentiment from weighted score`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-03` 항목을 확인한다.
2. 긍정/부정 키워드 목록을 확인한다.
3. 긍정과 부정이 함께 있는 테스트 문장을 만든다.
4. 기대 감성 결과를 명확히 정한다.
5. `tests/TextAnalyzerTest.cpp`에 테스트를 추가한다.
6. 생산 코드는 수정하지 않는다.
7. 가능한 경우 build와 ctest를 실행한다.
8. 실패하면 RED 단계의 의도된 실패인지 기록한다.
9. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(TextAnalyzerTest, should_return_neutral_when_positive_and_negative_keywords_are_balanced)
TEST_F(TextAnalyzerTest, should_return_negative_when_negative_keywords_outnumber_positive_keywords)
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 사용한 혼합 감성 문장
- 기대 결과와 근거
- `RED-02-03` 완료 여부
- 빌드/테스트 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

감성 키워드와 현재 판정 로직을 확인한다.

## Step 2. Frame

이번 작업은 기준을 드러내는 실패 테스트 작성이다.

## Step 3. Contract

혼합 감성 계약을 다음처럼 고정한다.

- 긍정/부정이 동률이면 중립이어야 한다.
- 더 많이 등장한 감성 키워드가 결과에 영향을 주어야 한다.
- 첫 키워드만으로 조기 반환하는 동작은 위험이다.

## Step 4. Trace

```text
mixed sentence -> positive count -> negative count -> expected sentiment
```

## Step 5. Write

혼합 감성 테스트를 작성한다.

## Step 6. Verify

ctest를 실행하고 실패를 RED 결과로 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


