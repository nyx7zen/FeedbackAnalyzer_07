# RED-02-05 실행 프롬프트

## 호출 문구

- `16번 진행`
- `RED-02-05 진행`
- `RED-02-05 항목을 진행해 주세요`
- `test: add filter combination tests 실행`

---

## 프롬프트

````md
Feedback Analyzer 필터 조합 테스트 작성 전문가 - RED 경계값 시나리오

`TODO.md`의 `RED-02-05 test: add filter combination tests` 항목을 실행하라.

너는 긍정/부정/중립 필터 조합이 기대한 결과 집합을 반환하는지 경계값 중심으로 검증하는 테스트 작성자다.
이번 작업의 목표는 필터 조합 시나리오를 테스트로 고정하고, 단일 필터와 복수 필터의 결과 차이를 명확히 하는 것이다.

제약:
- 생산 코드 수정 금지
- 필터 로직 구현 또는 수정 금지
- 테스트 실패는 RED 단계 결과로 기록
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

필터 조합 동작을 테스트로 고정한다.

테스트는 다음 조합을 우선 고려한다.

- 긍정만 선택
- 부정만 선택
- 중립만 선택
- 긍정 + 부정 선택
- 긍정 + 중립 선택
- 부정 + 중립 선택
- 전체 또는 필터 없음

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/FiltersTest.cpp` 또는 기존 테스트 파일
- `src/Filters.h`
- `src/Filters.cpp`
- `src/Constants.h`
- `docs/analysis.md`

후속 연결:

- `GREEN-01-01 fix: correct neutral filter condition`
- `REFACTOR-02-05 refactor: split long filter routines`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-05` 항목을 확인한다.
2. 필터 API와 입력 데이터 구조를 확인한다.
3. 긍정/부정/중립 샘플 데이터를 준비한다.
4. 필터 조합별 기대 결과를 테스트로 작성한다.
5. 생산 코드는 수정하지 않는다.
6. 가능한 경우 build와 ctest를 실행한다.
7. 실패하면 RED 단계의 의도된 실패인지 기록한다.
8. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(FiltersTest, should_return_positive_items_when_positive_filter_is_selected)
TEST_F(FiltersTest, should_return_positive_and_negative_items_when_positive_and_negative_filters_are_selected)
TEST_F(FiltersTest, should_return_all_items_when_no_filter_is_selected)
```

권장 기대값 형식:

```text
입력 3건: 긍정 1, 부정 1, 중립 1
필터: 긍정 + 중립
기대: 긍정 1건과 중립 1건만 포함
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 검증한 필터 조합
- `RED-02-05` 완료 여부
- 빌드/테스트 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

필터 입력/출력 계약을 확인한다.

## Step 2. Frame

이번 작업은 필터 조합 실패 테스트 작성이다. 구현 수정은 하지 않는다.

## Step 3. Contract

필터 조합 계약을 다음처럼 고정한다.

- 선택한 감성 라벨만 결과에 포함한다.
- 여러 필터 선택은 OR 집합으로 해석한다.
- 필터가 없으면 전체를 반환하거나 기존 명세 기준을 따른다.

## Step 4. Trace

```text
items -> selected filters -> predicate per item -> filtered result
```

## Step 5. Write

조합별 테스트를 작성한다.

## Step 6. Verify

ctest를 실행하고 실패를 RED 결과로 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


