# SPEC-02-02 실행 프롬프트

## 호출 문구

- `5번 진행`
- `SPEC-02-02 진행`
- `SPEC-02-02 항목을 진행해 주세요`
- `docs: analyze global state risks 실행`

---

## 프롬프트

````md
Feedback Analyzer 전역 상태 위험 분석 전문가 - 테스트 격리 관점

`TODO.md`의 `SPEC-02-02 docs: analyze global state risks` 항목을 실행하라.

너는 C++ 레거시 코드에서 전역 `static` 상태, 싱글턴성 상태, 공유 컨테이너가 테스트 격리와 요청 간 독립성을 해치는 지점을 분석하는 리뷰어다.
이번 작업의 목표는 전역 상태 사용 지점을 조사하고, 테스트 격리 실패 위험성을 `docs/analysis.md`에 기록하는 것이다.

제약:
- 구현 코드 변경 금지
- 테스트 코드 작성 금지
- 상태 구조 변경 금지
- 분석은 실제 코드 검색 결과와 파일 근거를 기반으로 작성
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

전역 상태와 공유 상태가 테스트와 런타임 동작에 주는 위험을 문서화한다.

문서에는 다음 목적이 드러나야 한다.

- 전역 `static` 변수 또는 파일 스코프 상태가 어디에 있는지
- 해당 상태가 어떤 함수에서 읽히고 쓰이는지
- 테스트 간 상태 누수 위험이 있는지
- HTTP 요청 간 상태 공유 위험이 있는지
- 이후 REFACTOR 단계에서 어떤 항목으로 해소할지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Filters.cpp`
- `src/Filters.h`
- `src/Session.cpp`
- `src/Session.h`
- `src/Constants.cpp`
- `src/Constants.h`
- `src/main.cpp`

파일이 없거나 경로가 다르면 저장소의 실제 구조를 우선한다.

검색 기준:

- `static`
- 전역 변수
- 파일 스코프 컨테이너
- `global`
- `Session`
- `clear`
- `reset`
- 공유 상태로 보이는 `std::vector`, `std::map`, `std::unordered_map`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `SPEC-02-02` 항목을 확인한다.
2. `rg`로 전역 상태 후보를 검색한다.
3. 후보별로 선언 위치, 읽기 위치, 쓰기 위치를 확인한다.
4. 상태 위험을 다음 기준으로 분류한다.
   - 테스트 간 상태 누수
   - 요청 간 상태 공유
   - 초기화 순서 의존
   - 병렬 실행 위험
   - 상태 초기화 API 부재
5. `docs/analysis.md`에 전역 상태 위험 분석 섹션을 추가하거나 갱신한다.
6. 문서 변경이 발생하면 `SESSION_NOTES.md`에 로그를 추가한다.
7. 작업 완료 후 `TODO.md`의 `SPEC-02-02` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

`docs/analysis.md`에 다음 섹션을 추가한다.

```md
## 전역 상태 및 테스트 격리 위험

| 상태 후보 | 위치 | 읽기/쓰기 경로 | 위험 | 개선 후보 |
|---|---|---|---|---|

### 테스트 격리 관점

### 요청 처리 관점

### 후속 TODO 연결
```

후속 TODO 연결에는 다음 항목을 우선 검토한다.

- `RED-02-06 test: add session isolation test`
- `GREEN-01-04 fix: reset shared state in tests`
- `REFACTOR-03-01 refactor: remove global filter state`
- `REFACTOR-03-02 refactor: remove global analyzer state`
- `REFACTOR-03-03 refactor: implement session storage map`
- `REFACTOR-03-04 refactor: add feedback session clear api`
- `REFACTOR-03-05 test: add session lifecycle regression tests`

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `SPEC-02-02` 완료 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

전역 상태 후보를 검색하고 실제 선언부를 확인한다.

권장 검색:

```powershell
rg -n "static|global|Session|clear|reset|std::map|std::unordered_map|std::vector" src
```

확인할 질문:

- 파일 스코프 `static` 변수가 있는가?
- 함수 호출 후 결과가 어딘가에 남는가?
- 테스트별 초기화 경로가 있는가?
- 세션 키가 실제로 사용되는가?

## Step 2. Frame

이번 작업은 위험 분석 문서화다.

수행하지 말아야 할 일:

- 전역 변수 제거
- Session API 변경
- 테스트 추가
- 동작 수정

## Step 3. Contract

상태 위험 판단 기준을 다음처럼 고정한다.

- 테스트가 독립적으로 실행되지 못하게 하면 위험이다.
- 요청 간 결과가 섞일 수 있으면 위험이다.
- 명시적 초기화 또는 `clear()` 경로가 없으면 위험이다.
- 키를 받지만 저장/조회에 사용하지 않으면 더미 API 위험이다.

## Step 4. Trace

각 상태 후보의 흐름을 추적한다.

```text
선언 위치 -> 값 변경 함수 -> 값 조회 함수 -> 호출자 -> 테스트/요청 영향
```

## Step 5. Write

`docs/analysis.md`를 갱신한다.

문장 기준:

- 상태 후보마다 파일명과 변수명을 적는다.
- 위험은 구체적인 실패 시나리오로 쓴다.
- 개선 방향은 후속 TODO ID와 연결한다.

## Step 6. Verify

작성 후 다음 조건을 자체 검수한다.

- 전역 상태 후보 표가 포함되어 있다.
- 테스트 격리 위험이 별도로 설명되어 있다.
- 후속 TODO 연결이 명확하다.
- 문서 작업만 수행했다면 빌드/테스트 미실행을 기록한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 전역 상태 분석 로그를 추가한다.
- `TODO.md`의 `SPEC-02-02` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일, 완료 여부, 검증 여부, 다음 추천 항목을 간결히 보고한다.
````


