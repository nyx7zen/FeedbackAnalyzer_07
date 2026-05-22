# GREEN-02-01 실행 프롬프트

## 호출 문구

- `22번 진행`
- `GREEN-02-01 진행`
- `GREEN-02-01 항목을 진행해 주세요`
- `docs: add bug fix report 실행`

---

## 프롬프트

````md
Feedback Analyzer 버그 수정 보고서 작성 전문가 - GREEN 결과 문서화

`TODO.md`의 `GREEN-02-01 docs: add bug fix report` 항목을 실행하라.

너는 RED 테스트와 GREEN 수정의 원인, 변경 내용, 동작 차이를 추적 가능한 문서로 정리하는 기술 보고서 작성자다.
이번 작업의 목표는 `docs/bug_fix.md`를 작성하고, 버그 수정 전후 논리식과 동작 차이를 기록하는 것이다.

제약:
- 코드 변경은 원칙적으로 하지 말 것
- 문서 작성과 필요한 검토만 수행
- 실제 수정 내용과 테스트 결과에 근거해 작성
- 추측은 추정으로 표시
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

GREEN 단계에서 수정한 버그와 검증 기준을 문서화한다.

문서에는 다음 목적이 드러나야 한다.

- 어떤 RED 테스트가 버그를 드러냈는지
- 수정 전 조건식 또는 동작이 무엇이었는지
- 수정 후 조건식 또는 동작이 어떻게 바뀌었는지
- 어떤 테스트로 수정이 검증되었는지
- 남은 리스크와 후속 리팩토링 연결은 무엇인지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `src/Filters.cpp`
- `src/Logger.cpp`
- `src/main.cpp`
- `src/Session.cpp`
- `tests/`
- `SESSION_NOTES.md`

수정된 파일이 다르면 실제 git diff를 우선한다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-02-01` 항목을 확인한다.
2. `git diff` 또는 관련 파일을 확인해 GREEN 단계 수정 내용을 파악한다.
3. RED 테스트와 GREEN 수정의 연결을 정리한다.
4. `docs/bug_fix.md`를 작성한다.
5. 수정 전후 논리식과 동작 차이를 표로 정리한다.
6. 문서 변경이 발생하면 `SESSION_NOTES.md`에 로그를 추가한다.
7. 작업 완료 후 `TODO.md`의 `GREEN-02-01` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

`docs/bug_fix.md`는 다음 형식을 따른다.

```md
# 버그 수정 보고서

## 1. 개요

## 2. 관련 RED 테스트

| 테스트 | 실패 원인 | 연결 버그 |
|---|---|---|

## 3. 수정 대상

## 4. 수정 전 동작

## 5. 수정 후 동작

| 항목 | 수정 전 | 수정 후 |
|---|---|---|

## 6. 검증 기준

## 7. 남은 리스크와 후속 작업
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 문서에 기록한 주요 버그
- `GREEN-02-01` 완료 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

GREEN 수정 diff와 RED 테스트 실패 이력을 확인한다.

## Step 2. Frame

이번 작업은 버그 수정 보고서 작성이다.

수행하지 말아야 할 일:

- 새 버그 수정
- 테스트 기대값 변경
- 리팩토링 수행

## Step 3. Contract

보고서 계약을 다음처럼 고정한다.

- 수정 전후 차이는 실제 코드 근거로 작성한다.
- 테스트 이름과 결과를 연결한다.
- 남은 리스크는 후속 TODO ID로 연결한다.

## Step 4. Trace

```text
RED test failure -> root cause -> GREEN code change -> passing verification -> final
```

## Step 5. Write

`docs/bug_fix.md`를 작성한다.

## Step 6. Verify

문서가 실제 수정 내용과 충돌하지 않는지 확인한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


