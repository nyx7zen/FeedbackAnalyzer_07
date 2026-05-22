# REFACTOR-03-03 실행 프롬프트

## 호출 문구

- `39번 진행`
- `REFACTOR-03-03 진행`
- `REFACTOR-03-03 항목을 진행해 주세요`
- `refactor: implement session storage map 실행`

---

## 프롬프트

````md
Feedback Analyzer Session 저장소 현대화 전문가 - unordered_map 기반 상태 저장

`TODO.md`의 `REFACTOR-03-03 refactor: implement session storage map` 항목을 실행하라.

목표는 `Session.cpp/.h`에 `std::unordered_map` 구조를 도입하고, `Session`을 키를 무시하는 더미 API가 아니라 실제 조회 가능한 상태 저장소로 개편하는 것이다.

제약:
- Session public API 의도를 유지하되 더미 동작은 제거
- 테스트 격리 요구를 만족해야 함
- 새 전역 상태 추가 금지
- 키 충돌과 없는 키 조회 동작을 명확히 할 것
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- Session이 실제 key-value 저장소로 동작하게 한다.
- 상태 격리 테스트와 후속 clear API의 기반을 만든다.

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
1. 현재 Session API와 더미 동작을 확인한다.
2. 필요한 저장 타입을 결정한다.
3. `std::unordered_map` 기반 저장소를 도입한다.
4. set/get/exists 등 기존 API 의미를 실제 저장/조회로 구현한다.
5. Session 관련 테스트를 추가 또는 갱신한다.
6. build와 ctest를 실행한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 변경한 Session API/동작, 없는 키 처리 방식, 테스트 결과, `REFACTOR-03-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: 현재 Session 구현과 호출부를 확인한다.
2. Frame: Session 저장소 구현에 집중한다.
3. Contract: 키별 저장/조회가 실제로 동작해야 한다.
4. Trace: set -> get -> clear 후보 흐름을 확인한다.
5. Write: unordered_map 기반 구현을 추가한다.
6. Verify: Session 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


