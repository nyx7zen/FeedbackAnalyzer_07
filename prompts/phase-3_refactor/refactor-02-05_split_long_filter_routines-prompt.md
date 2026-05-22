# REFACTOR-02-05 실행 프롬프트

## 호출 문구

- `36번 진행`
- `REFACTOR-02-05 진행`
- `REFACTOR-02-05 항목을 진행해 주세요`
- `refactor: split long filter routines 실행`

---

## 프롬프트

````md
Feedback Analyzer Filter SRP 리팩토링 전문가 - 긴 조건 분기 분해

`TODO.md`의 `REFACTOR-02-05 refactor: split long filter routines` 항목을 실행하라.

목표는 필터 적용 함수의 긴 조건 분기와 판정 책임을 식별하고, 작은 함수로 분리해 테스트와 유지보수가 쉬운 구조로 만드는 것이다.

제약:
- 필터 결과 변경 금지
- 중립 필터 수정 결과 유지
- 필터 조합 테스트 기대값 변경 금지
- 공개 API 변경은 최소화
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 필터 조건 분기를 읽기 쉬운 판단 함수로 분리한다.
- 새 필터 조건 추가 시 변경 범위를 줄인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Filters.cpp`
- `src/Filters.h`
- `src/TextUtils.h`
- `tests/FiltersTest.cpp`
- `docs/bug_fix.md`

## Task
1. 필터 적용 함수의 책임과 조건 분기를 확인한다.
2. include/exclude 판단을 helper 함수로 분리한다.
3. 필터 조합 로직과 라벨 비교 로직을 명확히 한다.
4. build와 ctest를 실행한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 분리한 helper 함수, 필터 테스트 결과, `REFACTOR-02-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: 긴 필터 루틴과 조건 분기를 확인한다.
2. Frame: 동작 보존 리팩토링만 수행한다.
3. Contract: 동일 입력은 동일 필터 결과를 반환한다.
4. Trace: 필터 선택값부터 결과 목록까지 흐름을 확인한다.
5. Write: 작은 판단 함수로 분리한다.
6. Verify: 필터 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


