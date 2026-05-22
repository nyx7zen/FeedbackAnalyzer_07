# REFACTOR-02-04 실행 프롬프트

## 호출 문구

- `35번 진행`
- `REFACTOR-02-04 진행`
- `REFACTOR-02-04 항목을 진행해 주세요`
- `refactor: split long text analyzer routines 실행`

---

## 프롬프트

````md
Feedback Analyzer TextAnalyzer SRP 리팩토링 전문가 - 긴 분석 함수 분해

`TODO.md`의 `REFACTOR-02-04 refactor: split long text analyzer routines` 항목을 실행하라.

목표는 20줄을 크게 넘는 분석 함수를 식별하고, 서브루틴으로 추출해 단일 책임 원칙(SRP)을 강화하는 것이다.

제약:
- 분석 결과 변경 금지
- 공개 API 변경은 최소화
- 새 추상화는 실제 중복 또는 책임 분리에 도움이 될 때만 추가
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 긴 분석 루틴을 작은 책임 단위로 나눈다.
- 후속 가중치 감성 스코어링을 적용하기 쉬운 구조로 만든다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/TextUtils.h`
- `tests/TextAnalyzerTest.cpp`
- `docs/analysis.md`

## Task
1. `TextAnalyzer.cpp`에서 긴 함수와 복합 책임을 식별한다.
2. 입력 검증, 감성 판정, 키워드 추출 등 책임을 구분한다.
3. private/helper 함수로 최소 분해한다.
4. 기존 public API와 결과를 유지한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 분해한 함수명, 유지한 public API, 테스트 결과, `REFACTOR-02-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: 긴 분석 함수를 찾는다.
2. Frame: 동작 보존 리팩토링만 수행한다.
3. Contract: public API와 테스트 결과를 유지한다.
4. Trace: 입력에서 결과까지 호출 흐름을 확인한다.
5. Write: helper 함수로 분해한다.
6. Verify: 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


