# RED-01-04 실행 프롬프트

## 호출 문구

- `11번 진행`
- `RED-01-04 진행`
- `RED-01-04 항목을 진행해 주세요`
- `test: enforce descriptive test names 실행`

---

## 프롬프트

````md
Feedback Analyzer 테스트 네이밍 규칙 정리 전문가 - GTest 가독성 기준

`TODO.md`의 `RED-01-04 test: enforce descriptive test names` 항목을 실행하라.

너는 테스트 이름이 실패 원인과 기대 동작을 즉시 설명하도록 정리하는 테스트 품질 리뷰어다.
이번 작업의 목표는 새 테스트가 `should_[result]_when_[condition]` 형식을 따르도록 기존 RED 테스트 스켈레톤과 가이드성 코드를 정리하는 것이다.

제약:
- 생산 코드 변경 금지
- 테스트 동작 의미 변경 금지
- 이름 변경은 테스트 의도를 더 분명하게 만드는 범위로 제한
- 새 테스트를 많이 추가하지 말고 네이밍 규칙 정착에 집중
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

RED 단계에서 추가될 모든 테스트의 이름 규칙을 고정한다.

완료 후 다음이 가능해야 한다.

- 테스트 이름만 보고 결과와 조건을 파악할 수 있다.
- 새 테스트가 `should_[result]_when_[condition]` 형식으로 작성된다.
- fixture smoke test 이름도 규칙과 충돌하지 않는다.
- 향후 RED-02 항목들이 같은 패턴으로 확장된다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/`
- `tests/TextAnalyzerTest.cpp`
- `CMakeLists.txt`

프로젝트 테스트 규칙:

- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다.
- 경계값 테스트를 중시한다.
- 테스트는 서로 독립적이어야 한다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-01-04` 항목을 확인한다.
2. `tests/` 아래 기존 GTest 테스트 이름을 조사한다.
3. 규칙과 다른 테스트 이름을 찾는다.
4. 테스트 의미를 유지하며 이름을 변경한다.
5. 필요한 경우 테스트 파일 상단에 짧은 네이밍 기준 주석을 추가한다.
6. 가능한 경우 build와 ctest를 실행한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 테스트 이름 예:

```cpp
TEST_F(TextAnalyzerTest, should_return_neutral_when_input_is_empty)
TEST_F(TextAnalyzerTest, should_not_throw_when_input_has_special_characters)
TEST_F(TextAnalyzerTest, should_return_neutral_when_positive_and_negative_counts_are_equal)
```

피해야 할 이름 예:

```cpp
TEST_F(TextAnalyzerTest, EmptyTest)
TEST_F(TextAnalyzerTest, Test1)
TEST_F(TextAnalyzerTest, SentimentWorks)
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 변경한 테스트 이름 목록
- `RED-01-04` 완료 여부
- 빌드/테스트 실행 여부와 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

기존 테스트 이름을 조사한다.

권장 검색:

```powershell
rg -n "TEST\\(|TEST_F\\(" tests
```

## Step 2. Frame

이번 작업은 테스트 이름 정리다.

수행하지 말아야 할 일:

- 테스트 기대값 변경
- 생산 코드 수정
- 새로운 실패 테스트 대량 추가

## Step 3. Contract

네이밍 계약을 다음처럼 고정한다.

- `should_` 다음에는 기대 결과를 쓴다.
- `when_` 다음에는 조건을 쓴다.
- 한 테스트는 하나의 관찰 가능한 동작만 검증한다.

## Step 4. Trace

테스트 이름과 테스트 본문을 비교한다.

```text
테스트 본문 조건 -> 기대 assertion -> should_result_when_condition 이름
```

## Step 5. Write

규칙에 맞게 테스트 이름을 수정한다.

## Step 6. Verify

가능하면 build와 ctest를 실행해 이름 변경으로 빌드가 깨지지 않았는지 확인한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 네이밍 규칙 정리 로그를 추가한다.
- `TODO.md`의 `RED-01-04` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경된 이름과 검증 결과를 보고한다.
````


