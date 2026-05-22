# FEATURE-01-03 실행 프롬프트

## 호출 문구

- `45번 진행`
- `FEATURE-01-03 진행`
- `FEATURE-01-03 항목을 진행해 주세요`
- `feat: calculate relative sentiment score 실행`

---

## 프롬프트

````md
Feedback Analyzer 상대 감성 점수 구현 전문가 - Count_positive minus Count_negative

`TODO.md`의 `FEATURE-01-03 feat: calculate relative sentiment score` 항목을 실행하라.

목표는 `Score_sentiment = Count_positive - Count_negative` 수식을 적용하고, 상대적 감성 평가 반환 로직을 구현하는 것이다.

제약:
- 기존 카운트 로직을 재사용
- 점수 기준값은 기존 상수 구조와 충돌하지 않게 관리
- 감성 분류까지 과도하게 구현하지 말고 필요한 책임을 분리
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 긍정/부정 빈도를 단일 상대 점수로 변환한다.
- 후속 감성 분류의 기준 입력을 제공한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Constants.h`
- `tests/TextAnalyzerTest.cpp`

## Task
1. 긍정/부정 카운트 함수 또는 로직을 확인한다.
2. `positiveCount - negativeCount` 점수 계산 함수를 구현한다.
3. 필요한 테스트를 추가하거나 기존 FEATURE 테스트를 연결한다.
4. 동률 점수 `0` 처리 기준을 확인하되 분류는 다음 항목과 충돌하지 않게 한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 점수 계산 함수, 수식 적용 위치, 테스트 결과, `FEATURE-01-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: 카운트 결과가 어디에서 만들어지는지 확인한다.
2. Frame: 점수 계산 책임만 구현한다.
3. Contract: `score = positiveCount - negativeCount`를 따른다.
4. Trace: counts -> score 흐름을 확인한다.
5. Write: 상대 점수 계산 로직을 추가한다.
6. Verify: 점수 관련 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


