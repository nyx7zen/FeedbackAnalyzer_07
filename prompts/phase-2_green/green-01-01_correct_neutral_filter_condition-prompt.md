# GREEN-01-01 실행 프롬프트

## 호출 문구

- `18번 진행`
- `GREEN-01-01 진행`
- `GREEN-01-01 항목을 진행해 주세요`
- `fix: correct neutral filter condition 실행`

---

## 프롬프트

````md
Feedback Analyzer 중립 필터 수정 전문가 - GREEN 최소 구현

`TODO.md`의 `GREEN-01-01 fix: correct neutral filter condition` 항목을 실행하라.

너는 RED 단계에서 작성한 중립 필터 실패 테스트를 통과시키기 위해 최소 수정만 수행하는 C++ 테스트 주도 개발자다.
이번 작업의 목표는 `src/Filters.cpp`의 `중립` 필터 판정 처리 로직 결함을 수정하고, 논리 연산자와 분기 조건을 테스트 기대값에 맞추는 것이다.

제약:
- RED 테스트를 통과시키기 위한 최소 변경만 수행
- 필터 API의 공개 계약을 불필요하게 바꾸지 말 것
- 새 전역 상태 추가 금지
- 관련 없는 리팩토링 금지
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

중립 필터가 중립 항목만 포함하도록 수정한다.

완료 후 다음이 만족되어야 한다.

- `RED-02-04`의 중립 필터 테스트가 통과한다.
- 긍정/부정 항목은 `중립` 필터 결과에서 제외된다.
- 기존 긍정/부정 필터 동작은 유지된다.
- 필터 조합 테스트가 있다면 기존 기대값과 충돌하지 않는다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/FiltersTest.cpp` 또는 필터 관련 테스트 파일
- `src/Filters.h`
- `src/Filters.cpp`
- `src/Constants.h`
- `src/Constants.cpp`
- `docs/analysis.md`

후속 문서 연결:

- `docs/bug_fix.md`
- `GREEN-02-01 docs: add bug fix report`
- `GREEN-02-02 docs: record bug verification logs`

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-01-01` 항목을 확인한다.
2. `RED-02-04`에서 추가된 중립 필터 테스트와 기대 동작을 확인한다.
3. `src/Filters.cpp`에서 중립 필터 조건을 찾는다.
4. 논리 연산자와 분기 조건을 최소 수정한다.
5. 관련 테스트를 실행한다.
6. 가능하면 전체 테스트를 실행한다.
7. 변경 내용과 검증 결과를 `SESSION_NOTES.md`에 기록한다.
8. 작업 완료 후 `TODO.md`의 `GREEN-01-01` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

수정 후보:

- `src/Filters.cpp`
- `src/Filters.h`는 공개 계약 변경이 정말 필요한 경우에만 수정
- `SESSION_NOTES.md`
- `TODO.md`

검증 명령:

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 수정한 조건식 요약
- 통과한 테스트와 실패한 테스트
- `GREEN-01-01` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

중립 필터 테스트와 현재 필터 조건을 관찰한다.

확인할 질문:

- `중립` 라벨은 어떤 문자열 상수 또는 리터럴로 표현되는가?
- 필터 조건이 `&&`와 `||`를 잘못 사용하고 있는가?
- 필터 없음 또는 전체 필터는 어떻게 처리되는가?

## Step 2. Frame

이번 작업은 GREEN 최소 구현이다.

수행하지 말아야 할 일:

- 필터 모듈 전체 리팩토링
- 상수화 작업 선행
- 테스트 기대값 변경으로 통과시키기

## Step 3. Contract

중립 필터 계약을 다음처럼 고정한다.

- 선택 필터가 `중립`이면 감성 결과가 `중립`인 항목만 포함한다.
- 긍정과 부정 항목은 제외한다.
- 여러 필터 조합은 기존 명세 또는 RED 테스트 기대값을 따른다.

## Step 4. Trace

```text
feedback item -> sentiment label -> selected filter -> include/exclude decision
```

## Step 5. Write

`src/Filters.cpp`의 조건식을 최소 수정한다.

## Step 6. Verify

관련 테스트와 전체 테스트를 실행한다. 실패가 남으면 원인과 다음 항목을 구분한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


