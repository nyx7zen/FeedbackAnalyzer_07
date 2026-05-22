# FINAL-02-02 실행 프롬프트

## 호출 문구

- `61번 진행`
- `FINAL-02-02 진행`
- `FINAL-02-02 항목을 진행해 주세요`
- `test: run final regression suite 실행`

---

## 프롬프트

````md
Feedback Analyzer 최종 회귀 테스트 실행 전문가 - REPORT 검증 단계

`TODO.md`의 `FINAL-02-02 test: run final regression suite` 항목을 실행하라.

목표는 최종 `cmake --build build`를 실행하고, 가능하면 `ctest --output-on-failure`까지 확인하는 것이다.

제약:
- 테스트 기대값 변경 금지
- 실패를 숨기지 말고 원인과 후속 조치를 기록
- 빌드 설정을 고치려면 명백한 설정 결함일 때만 최소 수정
- 검증 결과를 `docs/final.md`와 `SESSION_NOTES.md`에 기록
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 최종 제출 전 전체 빌드와 테스트 상태를 확인한다.
- 남은 실패 또는 환경 제약을 투명하게 기록한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `CMakeLists.txt`
- `tests/`
- `docs/final.md`
- `SESSION_NOTES.md`

검증 명령:
```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

필요하면 최초 구성:
```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
```

## Task
1. build 폴더와 CMake 구성 상태를 확인한다.
2. `cmake --build build`를 실행한다.
3. 가능하면 `ctest --test-dir build --output-on-failure`를 실행한다.
4. 실패가 있으면 빌드 실패, 테스트 실패, 환경 실패로 분류한다.
5. `docs/final.md`에 최종 회귀 테스트 결과를 기록한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
검증 결과 표:
```md
| 명령 | 결과 | 핵심 로그 | 조치 |
|---|---|---|---|
```

최종 응답에는 실행한 명령, 결과, 실패 요약, `FINAL-02-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: 빌드 구성 상태를 확인한다.
2. Frame: 최종 회귀 검증에 집중한다.
3. Contract: 실패도 결과로 기록한다.
4. Trace: configure/build/test 순서를 확인한다.
5. Write: 필요한 검증 결과를 문서화한다.
6. Verify: 기록한 결과와 실제 출력이 일치하는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


