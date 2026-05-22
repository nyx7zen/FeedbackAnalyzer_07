# GREEN-01-02 실행 프롬프트

## 호출 문구

- `19번 진행`
- `GREEN-01-02 진행`
- `GREEN-01-02 항목을 진행해 주세요`
- `fix: support multiline feedback input 실행`

---

## 프롬프트

````md
Feedback Analyzer 다중 행 피드백 입력 수정 전문가 - HTML 입력 폼 GREEN 구현

`TODO.md`의 `GREEN-01-02 fix: support multiline feedback input` 항목을 실행하라.

너는 cpp-httplib 기반 C++ 웹 애플리케이션에서 사용자 입력 폼을 안전하게 개선하는 프론트엔드/백엔드 경계 담당자다.
이번 작업의 목표는 `src/main.cpp` 입력 폼 UI를 단일 라인 `input`에서 `textarea`로 변경해 여러 줄 피드백 입력이 가능하도록 하는 것이다.

제약:
- 입력 폼 변경은 최소 범위로 제한
- 라우팅 구조 전체 재작성 금지
- 분석 로직 변경 금지
- HTML 문자열 수정 시 기존 name/id 파라미터 계약 유지
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

사용자가 여러 줄 피드백을 입력할 수 있도록 UI 입력 요소를 수정한다.

완료 후 다음이 만족되어야 한다.

- 피드백 입력 폼이 `textarea`를 사용한다.
- 기존 서버 요청 파라미터 이름이 유지된다.
- 줄바꿈이 서버로 전달될 수 있다.
- 기존 분석/저장 흐름은 깨지지 않는다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `src/main.cpp`
- `src/TextAnalyzer.cpp`
- `src/FileHandler.cpp`
- `README.md`
- `docs/analysis.md`

확인할 키워드:

- `<input`
- `<textarea`
- `feedback`
- `req.get_param_value`
- `Post`
- `Get`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-01-02` 항목을 확인한다.
2. `src/main.cpp`에서 피드백 입력 폼 HTML을 찾는다.
3. 단일 라인 `input`을 `textarea`로 변경한다.
4. 기존 form의 `name`, route, method, submit 동작을 유지한다.
5. 줄바꿈 입력이 request parameter로 전달되는지 코드 흐름을 확인한다.
6. 가능한 경우 build를 실행한다.
7. 웹 UI 수동 확인이 어려우면 코드 기준 검증 내용을 기록한다.
8. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 HTML 방향:

```html
<textarea name="feedback" ...></textarea>
```

단, 실제 `name` 값과 스타일은 현재 코드에 맞춘다.

검증 명령:

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- input에서 textarea로 바꾼 위치
- 파라미터 계약 유지 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

`main.cpp`의 HTML 렌더링과 request parameter 처리 흐름을 관찰한다.

## Step 2. Frame

이번 작업은 입력 UI 최소 수정이다.

수행하지 말아야 할 일:

- 템플릿 엔진 도입
- 라우팅 분리
- 분석 로직 수정
- CSS 대규모 변경

## Step 3. Contract

다중 행 입력 계약을 다음처럼 고정한다.

- 사용자 입력 필드는 `textarea`다.
- 기존 서버 파라미터 이름은 유지한다.
- 줄바꿈이 분석 대상 텍스트 일부로 보존될 수 있어야 한다.

## Step 4. Trace

```text
textarea input -> form submit -> request param -> text analyzer -> rendered result
```

## Step 5. Write

`src/main.cpp`의 폼 HTML을 최소 수정한다.

## Step 6. Verify

가능하면 빌드와 테스트를 실행하고, UI 수동 확인이 불가능하면 코드 경로 검증을 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


