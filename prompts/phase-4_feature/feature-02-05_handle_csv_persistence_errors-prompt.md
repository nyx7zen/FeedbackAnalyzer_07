# FEATURE-02-05 실행 프롬프트

## 호출 문구

- `52번 진행`
- `FEATURE-02-05 진행`
- `FEATURE-02-05 항목을 진행해 주세요`
- `feat: handle csv persistence errors 실행`

---

## 프롬프트

````md
Feedback Analyzer CSV 저장 오류 처리 전문가 - 예외/로그 경로 보강

`TODO.md`의 `FEATURE-02-05 feat: handle csv persistence errors` 항목을 실행하라.

목표는 파일 쓰기 실패 상황을 `try-catch`로 처리하고, 예외 처리와 로그 경로를 추가하는 것이다.

제약:
- 실패를 조용히 삼키지 말 것
- 기존 API가 반환값을 가질 수 있으면 성공/실패를 명확히 표현
- Logger가 있으면 기존 로그 API를 우선 사용
- 테스트하기 어려운 OS 권한 상황은 가능한 작은 단위로 검증
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- CSV 저장 실패를 호출자가 알 수 있게 한다.
- 파일 시스템 오류가 애플리케이션 전체를 불필요하게 중단시키지 않게 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/FileHandler.cpp`
- `src/FileHandler.h`
- `src/Logger.h`
- `src/Logger.cpp`
- `tests/`

## Task
1. FileHandler의 오류 처리 현재 상태를 확인한다.
2. ofstream open/write 실패를 감지한다.
3. 필요한 경우 `try-catch`와 로그 경로를 추가한다.
4. 실패 시나리오 테스트를 추가하거나 수동 검증 방법을 기록한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 오류 처리 방식, 로그 경로, 검증 결과, `FEATURE-02-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: FileHandler의 예외/오류 반환 구조를 확인한다.
2. Frame: CSV 저장 오류 처리에 집중한다.
3. Contract: 실패는 로그 또는 반환값으로 드러나야 한다.
4. Trace: invalid path -> write attempt -> catch/log/return 흐름을 확인한다.
5. Write: 오류 처리와 로그를 추가한다.
6. Verify: 실패 시나리오와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


