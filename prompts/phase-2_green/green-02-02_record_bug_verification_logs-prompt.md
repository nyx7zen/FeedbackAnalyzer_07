# GREEN-02-02 실행 프롬프트

## 호출 문구

- `23번 진행`
- `GREEN-02-02 진행`
- `GREEN-02-02 항목을 진행해 주세요`
- `docs: record bug verification logs 실행`

---

## 프롬프트

````md
Feedback Analyzer 버그 검증 로그 기록 전문가 - 테스트 결과 문서화

`TODO.md`의 `GREEN-02-02 docs: record bug verification logs` 항목을 실행하라.

너는 수정 후 실행한 빌드/테스트 명령과 결과를 추적 가능한 문서로 남기는 검증 기록 담당자다.
이번 작업의 목표는 수정 후 실행한 테스트 명령을 `docs/bug_fix.md`에 남기고, 테스트 검증 로그와 결과를 기록하는 것이다.

제약:
- 가능하면 실제 명령을 실행하고 결과를 기록
- 실행하지 못한 명령은 이유를 명확히 기록
- 긴 로그 전체를 붙이지 말고 핵심 결과와 실패 요약을 남길 것
- 코드 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

GREEN 수정 검증 이력을 재현 가능하게 남긴다.

문서에는 다음이 드러나야 한다.

- 어떤 명령을 실행했는지
- 언제 실행했는지
- 성공/실패 결과는 무엇인지
- 실패가 있다면 어떤 테스트 또는 빌드 단계에서 발생했는지
- 남은 조치가 무엇인지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `docs/bug_fix.md`
- `CMakeLists.txt`
- `tests/`
- `SESSION_NOTES.md`

검증 명령 후보:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
ctest --test-dir build --output-on-failure
```

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-02-02` 항목을 확인한다.
2. `docs/bug_fix.md`의 기존 검증 섹션을 확인한다.
3. 필요한 빌드/테스트 명령을 실행한다.
4. 명령별 결과를 요약한다.
5. `docs/bug_fix.md`에 검증 로그 섹션을 추가하거나 갱신한다.
6. `SESSION_NOTES.md`에 검증 로그 기록 작업을 남긴다.
7. 작업 완료 후 `TODO.md`의 `GREEN-02-02` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

`docs/bug_fix.md`에 다음 섹션을 추가한다.

```md
## 검증 로그

| 일시 | 명령 | 결과 | 비고 |
|---|---|---|---|

### 실패 또는 경고 요약

### 남은 확인 사항
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 실행한 명령
- 검증 결과 요약
- `GREEN-02-02` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

현재 `docs/bug_fix.md`와 테스트 구성 상태를 확인한다.

## Step 2. Frame

이번 작업은 검증 로그 기록이다.

수행하지 말아야 할 일:

- 코드 수정
- 테스트 기대값 변경
- 실패를 숨기기 위한 로그 축약

## Step 3. Contract

검증 로그 계약을 다음처럼 고정한다.

- 명령은 실제 실행 문자열 그대로 기록한다.
- 결과는 pass/fail과 핵심 원인을 함께 적는다.
- 실행하지 못한 경우도 “미실행”으로 기록한다.

## Step 4. Trace

```text
build command -> build result -> ctest command -> test result -> bug_fix.md log
```

## Step 5. Write

검증 로그를 `docs/bug_fix.md`에 기록한다.

## Step 6. Verify

기록한 명령과 실제 실행 결과가 일치하는지 확인한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


