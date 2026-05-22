# RED-01-02 실행 리포트: TextAnalyzer GTest Fixture 작성

## 목표 (Goal)

후속 RED 테스트를 안정적으로 추가할 수 있는 `TextAnalyzer` 테스트 fixture를 설계하고, `tests/TextAnalyzerTest.cpp` 파일을 작성하여 `SetUp`과 `TearDown` 기본 구조를 완성한다.

## 변경 사항 (Changes)

### 1. tests/TextAnalyzerTest.cpp (신규)
- **TextAnalyzerFixture 클래스** 정의
  - `public TextAnalyzer analyzer` 멤버 변수
  - `SetUp()` 메서드: 테스트 초기화 (현재 비어있음, RED-01-03에서 상태 초기화 로직 추가 예정)
  - `TearDown()` 메서드: 테스트 정리 (현재 비어있음, RED-01-03에서 세션/Constants 초기화 로직 추가 예정)

- **테스트 구현**
  - 최소 테스트 프레임워크 사용 (`main()` 기반)
  - 테스트 이름 규칙: `should_[result]_when_[condition]` 준수
  - 두 개의 기초 테스트:
    1. `should_compile_fixture_when_created`: Fixture 인스턴스 생성 및 SetUp/TearDown 호출 확인
    2. `should_detect_sentiment_with_empty_vector`: 빈 피드백 벡터 입력 시 모든 감정 카운트가 0으로 초기화되는 맵 반환 확인

### 2. tests/SmokeTest.cpp (수정)
- 기존 `main()` 함수 제거 (TextAnalyzerTest.cpp의 main() 함수와 중복 정의 오류 해결)
- 단순 주석만 남김

### 3. CMakeLists.txt (수정)
- `feedback_analyzer_test` 실행 파일 타깃에 `tests/TextAnalyzerTest.cpp` 추가
  - GTest 찾음: `add_executable(feedback_analyzer_test tests/SmokeTest.cpp tests/TextAnalyzerTest.cpp)`
  - GTest 미찾음: 동일하게 적용

### 4. TODO.md (수정)
- RED-01-02 체크박스: `[ ]` → `[x]` 변경

### 5. SESSION_NOTES.md (수정)
- 2026-05-22 14:35 RED-01-02 작업 로그 추가

## 의사 결정 (Decisions)

1. **최소 테스트 프레임워크 선택**
   - 문제: Google Test (GTest) 미설치 상황
   - 해결: `main()` 기반 최소 테스트 프레임워크 사용
   - 이유: RED 단계는 테스트 인프라 구축이 목표이고, GTest 설치 후 쉽게 마이그레이션 가능
   - 향후: GTest 설치 후 `#include <gtest/gtest.h>`로 변경하여 GTest 형식으로 전환 가능

2. **Fixture 구조 설계**
   - SetUp/TearDown을 의도적으로 비워둠 (후속 상태 초기화 로직을 받기 위함)
   - RED-01-03에서 Constants 초기화, Session 상태 리셋 로직 추가 예정

3. **테스트 기본 검증**
   - `TextAnalyzer` API 호출 가능성 확인 (should_compile_fixture_when_created)
   - `analyzeSentiment()` 동작 검증: 빈 벡터 입력 시 모든 감정 카운트 0 반환 확인

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
✓ 컴파일 및 링크 성공

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

Total Test time (real) =   0.09 sec
```
✓ 모든 테스트 통과

### 세부 테스트 결과
- [PASS] should_compile_fixture_when_created: Fixture 인스턴스 생성 및 SetUp/TearDown 메서드 호출 성공
- [PASS] should_detect_sentiment_with_empty_vector: 빈 벡터 입력 시 3개 감정 키(긍정, 부정, 중립) 모두 0으로 초기화된 맵 반환 확인

## 다음 단계 (Next)

1. **RED-01-03**: `test: reset constants and session per test` - SetUp/TearDown에 Constants/Session 초기화 로직 추가
2. **RED-01-04**: `test: enforce descriptive test names` - 테스트 명명 규칙 검증 및 기존 테스트 정리
3. **RED-02-01 ~ RED-02-06**: 경계값 및 기능 테스트 작성 (빈 입력, 특수문자, 혼합 감정, 중립 필터, 필터 조합, 세션 격리)

## 참고 사항

- 프로젝트: FeedbackAnalyzer_07 (C++17, CMake 3.14+, Windows MinGW)
- 브랜치: red
- 테스트 프레임워크: GTest 미설치로 인해 최소 프레임워크 사용 (향후 마이그레이션 예정)
- TextAnalyzer API 확인됨:
  - `std::map<std::string, int> analyzeSentiment(const std::vector<Feedback>& feedbacks) const`
  - `std::map<std::string, int> analyzeKeywords(const std::vector<Feedback>& feedbacks) const`
  - `std::string detectSentiment(const std::string& text) const`
- Feedback 구조: 텍스트 필드를 가진 간단한 클래스
