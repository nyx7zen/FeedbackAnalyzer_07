# FEATURE-01-01 실행 프롬프트

## 호출 문구

- `43번 진행`
- `FEATURE-01-01 진행`
- `FEATURE-01-01 항목을 진행해 주세요`
- `test: add weighted sentiment scoring tests 실행`

---

## 프롬프트

````md
Feedback Analyzer 가중치 감성 스코어링 테스트 전문가 - FEATURE 기준 고정

`TODO.md`의 `FEATURE-01-01 test: add weighted sentiment scoring tests` 항목을 실행하라.

목표는 긍정/부정 단어 빈도 누적 기준 테스트를 작성하고, 기존처럼 첫 키워드에서 종료되는 로직의 한계를 드러내는 것이다.

제약:
- 생산 코드 구현 금지 또는 최소 테스트 연결만 허용
- 테스트 이름은 `should_[result]_when_[condition]` 형식
- 현재 구현에서 실패해도 FEATURE RED 성격으로 기록
- 감성 라벨/점수 상수는 기존 상수 구조를 우선 사용
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 가중치 기반 감성 스코어링의 기대 동작을 먼저 테스트로 고정한다.
- 첫 키워드 조기 종료 방식의 한계를 명확히 드러낸다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/Constants.h`
- `src/Constants.cpp`
- `tests/TextAnalyzerTest.cpp`
- `docs/feature.md`가 있으면 해당 문서

## Task
1. 현재 감성 분석 API와 테스트 구조를 확인한다.
2. 긍정/부정 키워드 빈도 누적 기준 테스트를 추가한다.
3. 첫 키워드만으로 판정하면 실패하는 입력을 사용한다.
4. 동률, 긍정 우세, 부정 우세 시나리오를 최소 범위로 포함한다.
5. build와 ctest를 실행한다.
6. 실패가 예상되면 FEATURE 구현 전 실패로 기록한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
권장 테스트 이름:
```cpp
should_return_positive_when_positive_keywords_outnumber_negative_keywords
should_return_negative_when_negative_keywords_outnumber_positive_keywords
should_return_neutral_when_positive_and_negative_keyword_counts_are_equal
```

최종 응답에는 추가한 테스트, 기대 기준, 테스트 결과, `FEATURE-01-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: 현재 감성 분석과 키워드 사전을 확인한다.
2. Frame: 기준 테스트 작성에 집중한다.
3. Contract: 점수 기준은 `positive_count - negative_count`로 이어질 수 있어야 한다.
4. Trace: 입력 문장 -> 키워드 빈도 -> 기대 감성 흐름을 추적한다.
5. Write: 테스트를 추가한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


