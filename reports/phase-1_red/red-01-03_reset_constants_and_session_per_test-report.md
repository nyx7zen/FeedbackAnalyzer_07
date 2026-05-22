# RED-01-03 실행 리포트: Constants/Session 상태 초기화

## 목표 (Goal)

각 테스트가 독립적인 상태에서 실행되도록 fixture 초기화 경로를 설계하고, `Constants` 초기화 및 `Session` 상태 격리/reset 로직을 테스트 준비 단계에 반영한다.

## 변경 사항 (Changes)

### 1. tests/TextAnalyzerTest.cpp (수정)

#### 헤더 추가
```cpp
#include "Constants.h"
#include "Session.h"
```

#### SetUp() 메서드 구현
```cpp
void SetUp() {
    // Initialize Constants for each test (sentiment/keyword dictionaries)
    Constants::init();

    // Reset session state to ensure test isolation
    Session::clear("default");
}
```

#### TearDown() 메서드 구현
```cpp
void TearDown() {
    // Cleanup after each test
    // Clear session to prevent state leakage to next test
    Session::clear("default");
}
```

#### 기능 설명
- **Constants::init()**: 감정(긍정/부정) 및 카테고리(배송/품질 등) 키워드 딕셔너리를 clear 후 재초기화
  - 테스트 간 감정 분석 사전 상태를 격리
- **Session::clear("default")**: 기본 세션 ID의 모든 상태 초기화
  - currentFeedbacks, filteredFeedbacks, filterState 리셋
  - SetUp에서 호출: 테스트 시작 전 깨끗한 상태 보장
  - TearDown에서 호출: 테스트 후 상태 누수 방지

### 2. TODO.md (수정)
- RED-01-03 체크박스: `[ ]` → `[x]` 변경

### 3. SESSION_NOTES.md (수정)
- 2026-05-22 14:40 RED-01-03 작업 로그 추가

## 의사 결정 (Decisions)

1. **Constants::init() 선택 근거**
   - 문제: 감정/카테고리 키워드 사전이 static 전역 변수
   - 확인: Constants.cpp의 init() 함수가 clear() 후 재초기화하는 정상 동작
   - 해결: 각 테스트 SetUp에서 Constants::init() 호출
   - 장점: 기존 코드 수정 최소, 명시적 초기화

2. **Session::clear() 선택 근거**
   - 확인: Session.h에 `static void clear(const std::string& sessionId = "default")` 메서드 존재
   - 구조: unordered_map<sessionId, SessionState>로 session별 관리
   - 해결: SetUp/TearDown에서 Session::clear() 호출
   - 장점: API 설계가 이미 test isolation을 고려함

3. **SetUp과 TearDown 모두에서 clear() 호출**
   - SetUp: 이전 테스트 오염 방지
   - TearDown: 다음 테스트 오염 방지
   - 이중 보안으로 상태 격리 강화

## 검증 (Verification)

### 빌드 성공
```powershell
cmake --build build
```
결과:
```
[ 72%] Built target feedback_analyzer_lib
[ 81%] Building CXX object CMakeFiles/feedback_analyzer_test.dir/tests/TextAnalyzerTest.cpp.obj
[ 90%] Linking CXX executable feedback_analyzer_test.exe
[100%] Built target feedback_analyzer_test
```
✓ Constants.h 및 Session.h 포함 컴파일 성공

### 테스트 실행 성공
```powershell
ctest --test-dir build --output-on-failure
```
결과:
```
Test project C:/DEV/week2_day4/FeedbackAnalyzer_07/build
    Start 1: smoke_test
1/1 Test #1: smoke_test .......................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.04 sec
```
✓ 모든 테스트 통과

### 상태 초기화 추적
- SetUp: Constants::init() → SENTIMENT_KEYWORDS, CATEGORY_KEYWORDS 재초기화
- SetUp: Session::clear("default") → currentFeedbacks, filteredFeedbacks, filterState 초기화
- TearDown: Session::clear("default") → 후속 테스트 격리

## 테스트 격리 현황

### 초기화 가능한 상태
- ✅ **Constants 사전**: Constants::init()로 test마다 일관되게 초기화
- ✅ **Session 상태**: Session::clear()로 test마다 일관되게 초기화
  - currentFeedbacks 벡터
  - filteredFeedbacks 벡터
  - filterState (sentiment, keyword 필터 선택)

### 아직 초기화 불가능한 상태
- ⚠️ **전역 static 변수** (TextAnalyzer, Filters 등): 제거 대기 (REFACTOR Phase)
  - RED-02-06 (session isolation test)에서 이 한계가 드러날 예정
  - 세션별로 독립적인 상태 저장소 구현은 REFACTOR-03-01/02 범위

## 다음 단계 (Next)

1. **RED-01-04**: `test: enforce descriptive test names` - 테스트 명명 규칙 검증
2. **RED-02-01 ~ RED-02-05**: 경계값 및 기능 테스트 작성
3. **RED-02-06**: `test: add session isolation test` - 상태 격리 검증 (전역 상태 문제 드러날 지점)
4. **GREEN Phase**: Constants/Session 초기화로 인한 테스트 통과 여부 검증

## 참고 사항

- 프로젝트: FeedbackAnalyzer_07 (C++17, CMake 3.14+, Windows MinGW)
- 브랜치: red
- Constants API: `static void init()` - 감정/카테고리 사전 초기화
- Session API: `static void clear(const std::string& sessionId = "default")` - session 상태 리셋
- 테스트 격리 계약:
  - SetUp: 이전 테스트 누수 정리 + 현재 테스트 준비
  - TearDown: 현재 테스트 정리 + 다음 테스트 격리 보장
