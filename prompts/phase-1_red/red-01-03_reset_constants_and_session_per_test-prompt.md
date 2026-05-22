# RED-01-03 실행 프롬프트

## 호출 문구

- `10번 진행`
- `RED-01-03 진행`
- `RED-01-03 항목을 진행해 주세요`
- `test: reset constants and session per test 실행`

---

## 프롬프트

````md
Feedback Analyzer 테스트 격리 준비 전문가 - Constants/Session 초기화

`TODO.md`의 `RED-01-03 test: reset constants and session per test` 항목을 실행하라.

너는 테스트 간 공유 상태가 누수되지 않도록 fixture 초기화 경로를 설계하는 테스트 엔지니어다.
이번 작업의 목표는 `Constants` 초기화 경로와 `Session` 상태 격리 또는 Reset 로직을 테스트 준비 단계에 반영하는 것이다.

제약:
- 생산 코드 변경은 최소화하고, 가능하면 기존 초기화 API를 사용
- 새 전역 상태 추가 금지
- 후속 GREEN/REFACTOR에서 고칠 결함을 RED 단계에서 임의로 해결하지 말 것
- 테스트 독립성 의도를 코드와 문서에 명확히 남길 것
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

각 테스트가 독립적인 상태에서 실행되도록 준비한다.

완료 후 다음이 가능해야 한다.

- `TextAnalyzerTest`의 `SetUp`/`TearDown`에 초기화 의도가 반영된다.
- `Constants` 초기화가 필요한 경우 테스트마다 일관되게 수행된다.
- `Session` 상태를 초기화할 수 없는 경우 그 한계를 RED 실패 또는 TODO로 드러낸다.
- 상태 격리 문제가 후속 `RED-02-06`, `GREEN-01-04`, `REFACTOR-03-*`와 연결된다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `tests/TextAnalyzerTest.cpp`
- `src/Constants.h`
- `src/Constants.cpp`
- `src/Session.h`
- `src/Session.cpp`
- `src/TextAnalyzer.cpp`
- `docs/analysis.md`

검색 기준:

```powershell
rg -n "Constants|Session|reset|clear|init|initialize|static|global" src tests
```

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-01-03` 항목을 확인한다.
2. `Constants` 초기화 API 또는 초기화 패턴을 확인한다.
3. `Session` 상태 초기화 API 또는 한계를 확인한다.
4. `tests/TextAnalyzerTest.cpp`의 fixture에 초기화 경로를 반영한다.
5. 초기화 API가 없다면 TODO성 주석 또는 실패 테스트 후보를 명확히 남긴다.
6. 가능한 경우 build와 ctest를 실행한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

fixture 구조 예:

```cpp
class TextAnalyzerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Constants/Session reset path goes here when available.
    }

    void TearDown() override {
        // Keep tests isolated from shared state.
    }
};
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `RED-01-03` 완료 여부
- 초기화 가능한 상태와 아직 불가능한 상태
- 빌드/테스트 실행 여부와 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

상태 초기화 지점을 찾는다.

확인할 질문:

- `Constants`는 명시적 초기화 함수가 있는가?
- `Session`은 키별 상태 저장소인가, 더미 API인가?
- 테스트마다 clear/reset할 수 있는가?
- 초기화가 없어서 의도적으로 실패시켜야 할 테스트가 있는가?

## Step 2. Frame

이번 작업은 테스트 준비 단계 보강이다.

수행하지 말아야 할 일:

- Session 저장소 재설계
- 전역 상태 제거
- 감성 분석 로직 수정

## Step 3. Contract

상태 격리 계약을 다음처럼 고정한다.

- 테스트는 이전 테스트 실행 결과에 의존하지 않는다.
- 초기화 API가 있으면 fixture에서 호출한다.
- 초기화 API가 없으면 후속 TODO와 실패 테스트로 드러낸다.

## Step 4. Trace

공유 상태 흐름을 추적한다.

```text
SetUp -> Constants 초기화 -> 테스트 본문 -> Session 사용 -> TearDown -> 상태 제거
```

## Step 5. Write

fixture에 초기화 경로를 작성하고 필요한 최소 테스트를 조정한다.

## Step 6. Verify

가능하면 build와 ctest를 실행한다. 실패가 상태 초기화 API 부재 때문이면 RED 단계 결과로 기록한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 상태 초기화 준비 로그를 추가한다.
- `TODO.md`의 `RED-01-03` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 초기화 가능/불가능 상태를 명확히 보고한다.
````


