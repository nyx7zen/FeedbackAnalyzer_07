# REFACTOR-03-05 실행 프롬프트

## 호출 문구

- `41번 진행`
- `REFACTOR-03-05 진행`
- `REFACTOR-03-05 항목을 진행해 주세요`
- `test: add session lifecycle regression tests 실행`

---

## 프롬프트

````md
Feedback Analyzer Session 라이프사이클 회귀 테스트 전문가

`TODO.md`의 `REFACTOR-03-05 test: add session lifecycle regression tests` 항목을 실행하라.

목표는 상태 초기화 시나리오 회귀 테스트를 추가하고, 세션 격리 흐름이 유지되는지 검증하는 것이다.

제약:
- 테스트 이름은 `should_[result]_when_[condition]` 형식
- 생산 코드 수정은 테스트 실패 원인이 명백한 경우에만 최소 수행
- 테스트 간 독립성 유지
- Session API 실제 동작을 검증
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- Session 저장/조회/초기화 생명주기 회귀를 보호한다.
- 후속 기능 추가 시 상태 누수가 재발하지 않게 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Session.h`
- `src/Session.cpp`
- `tests/`
- `docs/analysis.md`

## Task
1. 현재 Session API와 clear API를 확인한다.
2. 저장, 조회, 없는 키, clear, 키별 격리 시나리오를 테스트로 작성한다.
3. fixture에서 테스트별 초기화를 보장한다.
4. build와 ctest를 실행한다.
5. 실패가 있으면 원인을 분류하고 필요한 최소 수정만 수행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
권장 테스트 이름:
```cpp
should_return_saved_value_when_key_exists
should_return_empty_value_when_key_does_not_exist
should_remove_all_values_when_session_is_cleared
should_not_share_values_when_keys_are_different
```

최종 응답에는 추가한 테스트 이름, 검증한 시나리오, 테스트 결과, `REFACTOR-03-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: Session API와 기존 테스트를 확인한다.
2. Frame: 라이프사이클 회귀 테스트 작성에 집중한다.
3. Contract: 저장/조회/clear/격리 동작을 명확히 검증한다.
4. Trace: 각 테스트의 상태 흐름을 확인한다.
5. Write: 테스트를 추가한다.
6. Verify: 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


