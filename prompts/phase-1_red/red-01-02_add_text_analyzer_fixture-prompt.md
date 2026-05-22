# RED-01-02 실행 프롬프트

## 호출 문구

- `9번 진행`
- `RED-01-02 진행`
- `RED-01-02 항목을 진행해 주세요`
- `test: add text analyzer fixture 실행`

---

## 프롬프트

````md
Feedback Analyzer TextAnalyzer GTest Fixture 작성 전문가 - RED 단계

`TODO.md`의 `RED-01-02 test: add text analyzer fixture` 항목을 실행하라.

너는 텍스트 분석 도메인 로직을 독립적으로 검증하기 위한 Google Test fixture를 설계하는 테스트 엔지니어다.
이번 작업의 목표는 `tests/TextAnalyzerTest.cpp` 파일을 작성하고, `SetUp`/`TearDown` 기본 구조를 만드는 것이다.

제약:
- 생산 코드 동작 변경 금지
- 테스트 파일과 필요한 CMake 연결만 수정
- 아직 구체 경계값 테스트를 과도하게 추가하지 말 것
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

후속 RED 테스트를 안정적으로 추가할 수 있는 `TextAnalyzer` 테스트 fixture를 만든다.

완료 후 다음이 가능해야 한다.

- `tests/TextAnalyzerTest.cpp`가 존재한다.
- TextAnalyzer 관련 헤더를 포함하고 컴파일된다.
- `SetUp`과 `TearDown`이 준비되어 후속 상태 초기화 테스트를 받을 수 있다.
- 최소 테스트는 fixture 실행 경로를 검증한다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `CMakeLists.txt`
- `tests/` 내 기존 테스트
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/Constants.h`
- `src/Session.h`

프로젝트 전제:

- 테스트는 Google Test 기반이다.
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다.
- 테스트는 서로 독립적이어야 한다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-01-02` 항목을 확인한다.
2. 기존 테스트 타깃이 `RED-01-01`에서 구성되었는지 확인한다.
3. `TextAnalyzer`의 public API와 현재 호출 방식을 확인한다.
4. `tests/TextAnalyzerTest.cpp`를 작성한다.
5. Fixture 클래스에 `SetUp`과 `TearDown`을 추가한다.
6. 컴파일만 확인할 수 있는 최소 테스트를 추가한다.
7. 테스트 파일이 CMake 테스트 타깃에 포함되도록 연결한다.
8. 가능한 경우 build와 ctest를 실행한다.
9. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

테스트 파일 기본 형태:

```cpp
#include <gtest/gtest.h>

class TextAnalyzerTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(TextAnalyzerTest, should_compile_fixture_when_created) {
    SUCCEED();
}
```

실제 API가 확인되면 위 스켈레톤을 프로젝트 구조에 맞게 조정한다.

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `RED-01-02` 완료 여부
- 빌드/테스트 실행 여부와 결과
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

TextAnalyzer API와 테스트 타깃 연결 방식을 확인한다.

확인할 질문:

- 분석 함수가 클래스 메서드인가, 자유 함수인가?
- 헤더 include 경로는 어떻게 잡혀 있는가?
- 테스트에서 초기화해야 할 공유 상태가 있는가?

## Step 2. Frame

이번 작업은 fixture 기반 만들기다.

수행하지 말아야 할 일:

- 빈 입력/특수문자/혼합 감성 테스트를 미리 추가
- 생산 코드 수정
- 전역 상태 제거

## Step 3. Contract

Fixture 계약을 다음처럼 고정한다.

- 모든 TextAnalyzer 테스트는 `TextAnalyzerTest` fixture를 우선 사용한다.
- `SetUp`/`TearDown`은 후속 초기화 로직을 넣을 수 있게 비워 두거나 최소 초기화만 수행한다.
- 테스트 이름은 `should_` 형식으로 작성한다.

## Step 4. Trace

테스트 실행 흐름을 추적한다.

```text
CTest -> GTest executable -> TextAnalyzerTest fixture -> SetUp -> test body -> TearDown
```

## Step 5. Write

`tests/TextAnalyzerTest.cpp`와 필요한 CMake 연결을 작성한다.

## Step 6. Verify

가능하면 다음을 실행한다.

```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 fixture 작성 로그를 추가한다.
- `TODO.md`의 `RED-01-02` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일과 검증 결과를 보고한다.
````


