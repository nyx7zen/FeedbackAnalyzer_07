# RED-02-02 실행 프롬프트

## 호출 문구

- `13번 진행`
- `RED-02-02 진행`
- `RED-02-02 항목을 진행해 주세요`
- `test: add special character input test 실행`

---

## 프롬프트

````md
Feedback Analyzer 특수문자 입력 테스트 작성 전문가 - RED 경계값 테스트

`TODO.md`의 `RED-02-02 test: add special character input test` 항목을 실행하라.

너는 사용자가 입력할 수 있는 특수문자, 기호, 공백 조합이 분석 로직을 깨뜨리지 않도록 실패 테스트를 먼저 작성하는 테스트 엔지니어다.
이번 작업의 목표는 특수문자 입력 처리 기준을 테스트로 고정하고, 분석 로직이 예외 없이 동작하는지 확인하는 것이다.

제약:
- 생산 코드 수정 금지
- 특수문자 처리를 임의 구현하지 말 것
- 테스트 실패는 RED 단계 결과로 기록
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

특수문자 입력이 분석 로직을 깨뜨리지 않는다는 기대를 테스트로 고정한다.

테스트는 다음 입력군을 고려한다.

- 기호만 있는 문자열
- 공백과 탭
- 쉼표, 따옴표, 줄바꿈
- 한글과 특수문자가 섞인 문장

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/Constants.cpp`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-02-02` 항목을 확인한다.
2. 현재 분석 함수가 문자열을 순회하거나 검색하는 방식을 확인한다.
3. 특수문자 입력 테스트 케이스를 1~3개 추가한다.
4. 예외가 발생하지 않아야 하는 경우 `EXPECT_NO_THROW` 또는 동등한 assertion을 사용한다.
5. 생산 코드는 수정하지 않는다.
6. 가능한 경우 build와 ctest를 실행한다.
7. 실패하면 RED 단계의 의도된 실패인지 기록한다.
8. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름:

```cpp
TEST_F(TextAnalyzerTest, should_not_throw_when_input_has_only_special_characters)
TEST_F(TextAnalyzerTest, should_not_throw_when_input_has_korean_and_symbols)
```

최종 응답에는 다음을 포함한다.

- 추가한 테스트 이름
- 사용한 특수문자 입력 예
- `RED-02-02` 완료 여부
- 빌드/테스트 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

문자열 검색과 파싱 로직을 확인한다.

## Step 2. Frame

이번 작업은 특수문자 경계값 테스트 작성이다. 구현 수정은 하지 않는다.

## Step 3. Contract

특수문자 입력 계약을 다음처럼 고정한다.

- 분석 함수는 예외 없이 반환해야 한다.
- 알 수 없는 기호만 있어도 크래시가 없어야 한다.
- 의미 있는 키워드가 없으면 중립 또는 빈 결과 기준을 따라야 한다.

## Step 4. Trace

```text
special character input -> analyzer -> keyword scan -> sentiment result
```

## Step 5. Write

fixture에 특수문자 경계값 테스트를 추가한다.

## Step 6. Verify

ctest를 실행하고 실패 여부를 RED 결과로 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


