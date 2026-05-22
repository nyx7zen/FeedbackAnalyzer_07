# REFACTOR-02-02 실행 프롬프트

## 호출 문구

- `33번 진행`
- `REFACTOR-02-02 진행`
- `REFACTOR-02-02 항목을 진행해 주세요`
- `refactor: reuse containsAny in text analyzer 실행`

---

## 프롬프트

````md
Feedback Analyzer TextAnalyzer 중복 제거 전문가 - containsAny 적용

`TODO.md`의 `REFACTOR-02-02 refactor: reuse containsAny in text analyzer` 항목을 실행하라.

목표는 `src/TextAnalyzer.cpp`의 문자열 검색 중복 로직을 찾고, 해당 로직을 `TextUtils::containsAny` 호출로 대체하는 것이다.

제약:
- 감성 분석 결과 변경 금지
- 키워드 탐색 순서가 결과에 영향을 주면 반드시 보존
- 과도한 함수 분리는 `REFACTOR-02-04`로 미룰 것
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- TextAnalyzer 내부의 반복적인 `find`/loop 패턴을 공용 유틸리티로 통합한다.
- 검색 로직의 중복과 유지보수 부담을 줄인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextUtils.h`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Constants.cpp`
- `tests/TextAnalyzerTest.cpp`

## Task
1. `TextAnalyzer.cpp`의 문자열 검색 루프를 찾는다.
2. `TextUtils.h`를 include한다.
3. 동작을 보존할 수 있는 위치만 `containsAny`로 대체한다.
4. 대체가 부적절한 위치는 이유를 기록한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 대체한 검색 패턴, 유지한 예외 위치, 테스트 결과, `REFACTOR-02-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: TextAnalyzer의 검색 루프를 확인한다.
2. Frame: 검색 중복 대체만 수행한다.
3. Contract: 분석 결과와 키워드 결과는 유지한다.
4. Trace: 키워드 목록과 반환 흐름을 확인한다.
5. Write: `containsAny` 호출로 교체한다.
6. Verify: TextAnalyzer 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


