# FEATURE-02-01 실행 프롬프트

## 호출 문구

- `48번 진행`
- `FEATURE-02-01 진행`
- `FEATURE-02-01 항목을 진행해 주세요`
- `test: add csv persistence tests 실행`

---

## 프롬프트

````md
Feedback Analyzer CSV 영구 저장 테스트 전문가 - FileHandler FEATURE 기준 고정

`TODO.md`의 `FEATURE-02-01 test: add csv persistence tests` 항목을 실행하라.

목표는 CSV 저장 파일 생성 테스트를 작성하고, 기본 행 출력과 저장 결과를 검증하는 것이다.

제약:
- 생산 코드 구현은 하지 말고 테스트 기준을 먼저 고정
- 테스트 파일은 임시 경로를 사용하고 정리 경로를 제공
- 파일 시스템 테스트는 독립적이어야 함
- 테스트 이름은 `should_[result]_when_[condition]` 형식
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 콘솔 덤프 Stub를 실제 파일 저장으로 대체하기 전 기대 동작을 테스트로 고정한다.
- CSV 저장의 기본 행과 파일 생성 여부를 검증한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/FileHandler.h`
- `src/FileHandler.cpp`
- `tests/`
- `docs/feature.md`가 있으면 해당 문서

## Task
1. 현재 FileHandler API와 Stub 동작을 확인한다.
2. 임시 CSV 경로를 사용하는 테스트를 작성한다.
3. 파일 생성 여부와 기본 행 내용을 검증한다.
4. 테스트 후 생성 파일을 정리한다.
5. build와 ctest를 실행한다.
6. 실패가 예상되면 FEATURE 구현 전 실패로 기록한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
권장 테스트 이름:
```cpp
should_create_csv_file_when_feedback_is_saved
should_write_default_row_when_feedback_is_saved
```

최종 응답에는 추가한 테스트, 임시 파일 처리 방식, 테스트 결과, `FEATURE-02-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: FileHandler API와 현재 저장 동작을 확인한다.
2. Frame: CSV 저장 기준 테스트 작성에 집중한다.
3. Contract: 저장 호출 후 파일이 존재하고 기대 행이 있어야 한다.
4. Trace: save call -> file path -> file content 흐름을 확인한다.
5. Write: 파일 생성 테스트를 작성한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


