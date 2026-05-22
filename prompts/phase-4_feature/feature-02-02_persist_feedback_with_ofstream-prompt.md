# FEATURE-02-02 실행 프롬프트

## 호출 문구

- `49번 진행`
- `FEATURE-02-02 진행`
- `FEATURE-02-02 항목을 진행해 주세요`
- `feat: persist feedback with ofstream 실행`

---

## 프롬프트

````md
Feedback Analyzer CSV 파일 저장 구현 전문가 - std::ofstream RAII

`TODO.md`의 `FEATURE-02-02 feat: persist feedback with ofstream` 항목을 실행하라.

목표는 `src/FileHandler.cpp`의 콘솔 덤프(Stub) 로직을 제거하고, `std::ofstream` 기반 파일 쓰기 로직을 적용하는 것이다.

제약:
- RAII 기반 `std::ofstream` 사용
- 콘솔 출력만 하던 Stub 동작을 실제 파일 쓰기로 대체
- 파일 경로와 API 계약은 기존 구조를 우선
- CSV 이스케이프와 BOM은 후속 항목과 충돌하지 않게 최소 구현
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 피드백 데이터를 물리 CSV 파일로 저장한다.
- `FEATURE-02-01` 테스트를 통과시키는 최소 파일 쓰기 구현을 제공한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/FileHandler.h`
- `src/FileHandler.cpp`
- `tests/`
- `src/Logger.*`가 있으면 해당 파일

## Task
1. FileHandler Stub 로직을 확인한다.
2. `std::ofstream`으로 파일을 열고 내용을 쓴다.
3. 기본 CSV 행 또는 기존 테스트 기대 형식을 출력한다.
4. 파일 닫기는 RAII에 맡긴다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 수정한 저장 함수, CSV 출력 형식, 테스트 결과, `FEATURE-02-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: 기존 Stub 출력과 테스트 기대값을 확인한다.
2. Frame: ofstream 기반 파일 쓰기만 구현한다.
3. Contract: 저장 호출 후 실제 파일에 데이터가 기록되어야 한다.
4. Trace: feedback data -> ofstream -> csv file 흐름을 확인한다.
5. Write: 파일 쓰기 로직을 구현한다.
6. Verify: CSV persistence 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


