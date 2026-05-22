# FEATURE-01-04 실행 프롬프트

## 호출 문구

- `46번 진행`
- `FEATURE-01-04 진행`
- `FEATURE-01-04 항목을 진행해 주세요`
- `feat: classify sentiment from weighted score 실행`

---

## 프롬프트

````md
Feedback Analyzer 가중치 점수 기반 감성 분류 전문가

`TODO.md`의 `FEATURE-01-04 feat: classify sentiment from weighted score` 항목을 실행하라.

목표는 계산된 점수에 따라 긍정/부정/중립 결과를 반환하고, 점수 기준값은 상수화된 값을 사용하는 것이다.

제약:
- 라벨 문자열은 기존 감성 라벨 상수를 사용
- 점수 기준값은 매직 넘버로 직접 쓰지 말 것
- FEATURE-01-01 테스트 기대값을 통과하도록 구현
- 기존 경계값 테스트를 깨지 말 것
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 상대 점수를 사용자에게 의미 있는 감성 라벨로 변환한다.
- 동률과 경계값 기준을 명확히 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Constants.h`
- `tests/TextAnalyzerTest.cpp`
- `docs/feature.md`가 있으면 해당 문서

## Task
1. 상대 점수 계산 로직을 확인한다.
2. 점수가 양수면 긍정, 음수면 부정, 0이면 중립으로 분류한다.
3. 기준값은 상수로 사용한다.
4. 감성 분석 public API가 가중치 결과를 반환하도록 연결한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 분류 기준, 사용한 상수, 통과한 테스트, `FEATURE-01-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: 점수와 라벨 상수 구조를 확인한다.
2. Frame: 점수 기반 분류 구현에 집중한다.
3. Contract: score > 0 긍정, score < 0 부정, score == 0 중립.
4. Trace: text -> counts -> score -> label 흐름을 확인한다.
5. Write: 분류 로직을 구현한다.
6. Verify: FEATURE 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


