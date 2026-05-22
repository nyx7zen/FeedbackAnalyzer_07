# REFACTOR-03-04 실행 프롬프트

## 호출 문구

- `40번 진행`
- `REFACTOR-03-04 진행`
- `REFACTOR-03-04 항목을 진행해 주세요`
- `refactor: add feedback session clear api 실행`

---

## 프롬프트

````md
Feedback Analyzer Session 생명주기 API 전문가 - clear 경로 추가

`TODO.md`의 `REFACTOR-03-04 refactor: add feedback session clear api` 항목을 실행하라.

목표는 `FeedbackSession::clear()` 등 생명 주기 수동 제어 API를 제공하고, 테스트와 요청 처리에서 상태 초기화가 가능하도록 하는 것이다.

제약:
- clear API는 명시적이고 테스트 가능해야 함
- 기존 저장/조회 동작을 깨지 말 것
- 새 전역 상태 추가 금지
- clear 후 조회 동작을 테스트로 고정
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 세션 상태 생명주기를 명시적으로 제어한다.
- 테스트 격리와 요청 단위 초기화 경로를 제공한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Session.h`
- `src/Session.cpp`
- `src/main.cpp`
- `tests/`
- `docs/analysis.md`

## Task
1. 현재 Session/FeedbackSession 타입과 API를 확인한다.
2. 전체 clear와 키별 clear 중 필요한 범위를 결정한다.
3. clear API를 선언/구현한다.
4. 테스트 fixture 또는 요청 처리에서 사용할 수 있게 연결한다.
5. clear 동작 테스트를 추가 또는 갱신한다.
6. build와 ctest를 실행한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 추가한 clear API, clear 후 동작, 테스트 결과, `REFACTOR-03-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: Session 생명주기와 호출부를 확인한다.
2. Frame: clear API 추가에 집중한다.
3. Contract: clear 후 이전 값은 조회되지 않아야 한다.
4. Trace: set -> get -> clear -> get 흐름을 확인한다.
5. Write: clear API와 호출부를 추가한다.
6. Verify: Session lifecycle 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


