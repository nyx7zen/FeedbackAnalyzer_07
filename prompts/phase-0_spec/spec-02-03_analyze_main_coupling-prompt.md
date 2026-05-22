# SPEC-02-03 실행 프롬프트

## 호출 문구

- `6번 진행`
- `SPEC-02-03 진행`
- `SPEC-02-03 항목을 진행해 주세요`
- `docs: analyze main coupling 실행`

---

## 프롬프트

````md
Feedback Analyzer main.cpp 결합도 분석 전문가 - 라우팅/UI/도메인 분리 관점

`TODO.md`의 `SPEC-02-03 docs: analyze main coupling` 항목을 실행하라.

너는 C++ 웹 애플리케이션의 `main.cpp`가 라우팅, UI 렌더링, 도메인 로직, 상태 관리를 과도하게 함께 담당하는지 분석하는 구조 리뷰어다.
이번 작업의 목표는 `main.cpp`와 핵심 도메인 로직 간 결합도를 진단하고, 라우팅/UI 렌더링과 분석 로직이 섞인 영역을 `docs/analysis.md`에 기록하는 것이다.

제약:
- 구현 코드 변경 금지
- 테스트 코드 작성 금지
- 라우팅 구조 변경 금지
- HTML 문자열 리팩토링 금지
- 분석은 실제 코드 흐름과 함수 호출 근거를 기반으로 작성
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

`main.cpp`의 책임 집중과 도메인 결합을 문서화한다.

문서에는 다음 목적이 드러나야 한다.

- `main.cpp`가 담당하는 책임 목록
- HTTP 라우팅과 HTML 렌더링이 어디에서 수행되는지
- 텍스트 분석, 필터링, 저장 같은 도메인 작업을 직접 호출하는지
- 도메인 로직을 테스트하기 어렵게 만드는 결합 지점
- 이후 REFACTOR 단계에서 어떤 분리 전략을 사용할지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `src/main.cpp`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Filters.cpp`
- `src/Filters.h`
- `src/FileHandler.cpp`
- `src/FileHandler.h`
- `src/Session.cpp`
- `src/Session.h`

파일이 없거나 경로가 다르면 저장소의 실제 구조를 우선한다.

분석 관점:

- 라우팅 책임
- 요청 파라미터 파싱 책임
- HTML 문자열 생성 책임
- 도메인 분석 호출 책임
- 필터 조건 판단 책임
- 저장 또는 출력 책임
- 상태 초기화 책임

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `SPEC-02-03` 항목을 확인한다.
2. `src/main.cpp`의 route handler를 식별한다.
3. 각 route handler가 어떤 모듈 함수를 호출하는지 기록한다.
4. HTML 생성과 도메인 분석 호출이 같은 함수 안에 섞여 있는지 확인한다.
5. 요청 파라미터 검증, 필터링, 분석 결과 조립이 어디에서 수행되는지 확인한다.
6. `docs/analysis.md`에 `main.cpp` 결합도 분석 섹션을 추가하거나 갱신한다.
7. 문서 변경이 발생하면 `SESSION_NOTES.md`에 로그를 추가한다.
8. 작업 완료 후 `TODO.md`의 `SPEC-02-03` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

`docs/analysis.md`에 다음 섹션을 추가한다.

```md
## main.cpp 결합도 분석

### 현재 책임

| 책임 | main.cpp 내 위치 | 연결 모듈 | 문제점 |
|---|---|---|---|

### 요청 처리 흐름

### UI 렌더링과 도메인 로직 결합 지점

### 분리 후보

| 분리 후보 | 현재 문제 | 기대 효과 | 후속 TODO |
|---|---|---|---|
```

후속 TODO 연결에는 다음 항목을 우선 검토한다.

- `GREEN-01-02 fix: support multiline feedback input`
- `REFACTOR-02-04 refactor: split long text analyzer routines`
- `REFACTOR-02-05 refactor: split long filter routines`
- `REFACTOR-03-04 refactor: add feedback session clear api`

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `SPEC-02-03` 완료 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

`src/main.cpp`를 읽고 route handler와 helper 함수를 찾는다.

확인할 질문:

- `httplib::Server` 설정은 어디에 있는가?
- GET/POST route는 몇 개인가?
- HTML은 어디에서 조립되는가?
- 분석 함수 호출이 route handler 안에 직접 있는가?
- 필터 적용이 UI 코드와 섞여 있는가?

## Step 2. Frame

이번 작업은 결합도 분석 문서화다.

수행하지 말아야 할 일:

- route handler 분리
- HTML 템플릿 분리
- 분석 함수 이동
- 테스트 추가

## Step 3. Contract

결합도 판단 기준을 다음처럼 고정한다.

- 하나의 함수가 HTTP, HTML, 분석, 저장을 함께 담당하면 책임 집중이다.
- UI 문자열 생성 중 도메인 판단이 있으면 결합 지점이다.
- 도메인 함수를 호출하기 위해 웹 요청 객체가 필요하면 테스트성 위험이다.
- 분리 후보는 실제 후속 TODO와 연결되어야 한다.

## Step 4. Trace

route별 호출 흐름을 추적한다.

```text
route handler -> request parsing -> domain call -> filter call -> response rendering
```

실제 흐름이 다르면 실제 코드를 우선한다.

## Step 5. Write

`docs/analysis.md`를 갱신한다.

문장 기준:

- “main이 크다” 대신 어떤 책임이 섞였는지 적는다.
- route handler 이름이나 코드 위치를 근거로 쓴다.
- 분리 후보는 Boundary, Domain, Rendering 같은 역할로 나눠 제시한다.

## Step 6. Verify

작성 후 다음 조건을 자체 검수한다.

- `main.cpp` 현재 책임 표가 포함되어 있다.
- UI/도메인 결합 지점이 설명되어 있다.
- 분리 후보가 후속 TODO와 연결되어 있다.
- 문서 작업만 수행했다면 빌드/테스트 미실행을 기록한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 main 결합도 분석 로그를 추가한다.
- `TODO.md`의 `SPEC-02-03` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일, 완료 여부, 검증 여부, 다음 추천 항목을 간결히 보고한다.
````


