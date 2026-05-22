# FEATURE-01-05 실행 프롬프트

## 호출 문구

- `47번 진행`
- `FEATURE-01-05 진행`
- `FEATURE-01-05 항목을 진행해 주세요`
- `test: add mixed sentiment scoring regression 실행`

---

## 프롬프트

````md
Feedback Analyzer 혼합 감성 스코어링 회귀 테스트 전문가

`TODO.md`의 `FEATURE-01-05 test: add mixed sentiment scoring regression` 항목을 실행하라.

목표는 긍정/부정 혼재 문장에 대한 회귀 테스트를 추가하고, 경계값과 동률 점수 처리 기준을 검증하는 것이다.

제약:
- 테스트 이름은 `should_[result]_when_[condition]` 형식
- 이미 있는 테스트와 중복하지 말 것
- 구현을 통과시키기 위해 기대값을 낮추지 말 것
- 경계값과 동률 기준을 명확히 표현
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 가중치 감성 스코어링 기능의 회귀를 보호한다.
- 동률과 미세한 카운트 차이를 테스트로 고정한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/TextAnalyzer.cpp`
- `src/Constants.cpp`
- `docs/feature.md`가 있으면 해당 문서

## Task
1. 기존 혼합 감성 테스트를 확인한다.
2. 중복되지 않는 회귀 시나리오를 선정한다.
3. 긍정 우세, 부정 우세, 동률 경계값 테스트를 보강한다.
4. build와 ctest를 실행한다.
5. 필요하면 `docs/feature.md`의 검증 기준과 연결한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 추가한 테스트 이름, 검증한 경계값, 테스트 결과, `FEATURE-01-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: 기존 감성 테스트 커버리지를 확인한다.
2. Frame: 회귀 테스트 보강에 집중한다.
3. Contract: 동률은 중립, 카운트 우세는 해당 감성으로 분류한다.
4. Trace: 입력별 count/score/label을 확인한다.
5. Write: 회귀 테스트를 추가한다.
6. Verify: 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


