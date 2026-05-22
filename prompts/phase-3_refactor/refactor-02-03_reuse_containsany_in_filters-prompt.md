# REFACTOR-02-03 실행 프롬프트

## 호출 문구

- `34번 진행`
- `REFACTOR-02-03 진행`
- `REFACTOR-02-03 항목을 진행해 주세요`
- `refactor: reuse containsAny in filters 실행`

---

## 프롬프트

````md
Feedback Analyzer Filters 중복 제거 전문가 - containsAny 적용

`TODO.md`의 `REFACTOR-02-03 refactor: reuse containsAny in filters` 항목을 실행하라.

목표는 `src/Filters.cpp`의 문자열 검색 중복 로직을 찾고, 해당 로직을 공용 `TextUtils::containsAny` 호출로 통합하는 것이다.

제약:
- 필터 결과 변경 금지
- 중립 필터 수정 결과를 깨지 말 것
- 조건 분기 구조 대규모 변경은 `REFACTOR-02-05`로 미룰 것
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- Filters 내부 검색 로직을 TextAnalyzer와 같은 유틸리티로 통합한다.
- 중복 문자열 검색 구현을 줄인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextUtils.h`
- `src/Filters.cpp`
- `src/Filters.h`
- `tests/FiltersTest.cpp`
- `docs/bug_fix.md`

## Task
1. `Filters.cpp`의 문자열 검색 중복 패턴을 찾는다.
2. `TextUtils.h`를 include한다.
3. 동작 보존이 가능한 위치만 `containsAny`로 교체한다.
4. 필터 조합 테스트와 중립 필터 테스트를 실행한다.
5. 전체 테스트를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 대체한 위치, 필터 테스트 결과, `REFACTOR-02-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: Filters의 검색 로직을 확인한다.
2. Frame: 검색 유틸리티 재사용만 수행한다.
3. Contract: 기존 필터 결과를 유지한다.
4. Trace: selected filter와 item predicate 흐름을 확인한다.
5. Write: `containsAny` 호출로 교체한다.
6. Verify: 필터 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


