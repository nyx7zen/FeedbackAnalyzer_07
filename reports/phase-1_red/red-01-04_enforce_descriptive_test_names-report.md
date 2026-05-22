# RED-01-04 실행 리포트: 테스트 명명 규칙 정착

## 목표 (Goal)

RED 단계에서 추가될 모든 테스트의 이름 규칙을 고정하고, `should_[result]_when_[condition]` 형식으로 작성하도록 가이드한다. 테스트 이름만 보고도 기대 동작과 실패 조건을 파악할 수 있도록 한다.

## 변경 사항 (Changes)

### 1. tests/TextAnalyzerTest.cpp (수정)

#### 테스트 이름 개선

**Test 1**: 이미 규칙 준수
```cpp
// 수정 없음: 형식이 이미 should_[result]_when_[condition] 준수
should_compile_fixture_when_created
```

**Test 2**: 결과를 명시적으로 표현
```cpp
// 변경 전
should_detect_sentiment_with_empty_vector
// 문제: "detect_with"는 모호한 표현, 반환값이 명확하지 않음

// 변경 후
should_return_zero_counts_for_all_sentiments_when_input_is_empty
// 개선: 반환값(zero counts for all sentiments)과 조건(input is empty) 명확
```

#### 테스트 파일 상단 주석 추가
```cpp
// TextAnalyzerTest Fixture implementation
// This will be migrated to Google Test once GTest is installed
// Format follows the testing convention: should_[result]_when_[condition]
```

### 2. TODO.md (수정)
- RED-01-04 체크박스: `[ ]` → `[x]` 변경

### 3. SESSION_NOTES.md (수정)
- 2026-05-22 14:45 RED-01-04 작업 로그 추가

## 의사 결정 (Decisions)

1. **이름 변경 범위 최소화**
   - 첫 번째 테스트: 이미 규칙 준수하므로 수정하지 않음
   - 두 번째 테스트: 반환값을 더 명시적으로 표현하도록 개선
   - 테스트 동작은 변경하지 않음 (의미 보존)

2. **"should_[result]_when_[condition]" 형식 강화**
   - Result 부분: 반환값 또는 동작 결과를 구체적으로 기술
     - ✅ Good: `return_zero_counts_for_all_sentiments`
     - ❌ Bad: `detect_sentiment`, `work`
   - When 부분: 조건을 명확하게 기술
     - ✅ Good: `when_input_is_empty`
     - ❌ Bad: `with_empty_vector`

3. **가이드성 주석으로 후속 테스트 유도**
   - 파일 상단에 네이밍 규칙 명시
   - RED-02-01 ~ 06에서 같은 패턴으로 테스트 작성 가능하도록

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
✓ 컴파일 성공

### 테스트 실행 성공
```powershell
ctest --test-dir build --output-on-failure
```
결과:
```
Test project C:/DEV/week2_day4/FeedbackAnalyzer_07/build
    Start 1: smoke_test
1/1 Test #1: smoke_test .......................   Passed    0.03 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.09 sec
```
✓ 모든 테스트 통과

### 테스트 이름 확인
- [PASS] should_compile_fixture_when_created
- [PASS] should_return_zero_counts_for_all_sentiments_when_input_is_empty

## 네이밍 규칙 현황

### 준수 현황
| 테스트 이름 | 형식 준수 | 설명 |
|-----------|---------|------|
| should_compile_fixture_when_created | ✅ | Fixture 생성 및 SetUp/TearDown 호출 가능성 확인 |
| should_return_zero_counts_for_all_sentiments_when_input_is_empty | ✅ | 빈 입력 시 모든 감정 카운트 0 반환 확인 |

### 규칙 가이드
- ✅ **좋은 예시**:
  - `should_return_positive_when_text_contains_positive_keyword`
  - `should_throw_exception_when_input_is_null`
  - `should_filter_empty_results_when_no_match`

- ❌ **피해야 할 예시**:
  - `should_work` (동작 설명 불충분)
  - `should_detect` (반환값 불명확)
  - `test_sentiment` (should_ 형식 미사용)
  - `Test1`, `Test2` (의미 없음)

## 다음 단계 (Next)

1. **RED-02-01**: `test: add empty input boundary test` - 경계값 테스트 시작 (같은 네이밍 규칙 적용)
2. **RED-02-02 ~ RED-02-06**: 추가 경계값/기능 테스트 (네이밍 규칙 준수)
3. **GREEN Phase**: 테스트 통과를 위한 기능 구현 (테스트 이름 기반 개발)

## 참고 사항

- 프로젝트: FeedbackAnalyzer_07 (C++17, CMake 3.14+, Windows MinGW)
- 브랜치: red
- 네이밍 규칙 문서: tests/TextAnalyzerTest.cpp 상단 주석
- 테스트 프레임워크: 최소 프레임워크 (GTest 미설치, 향후 마이그레이션 예정)
- RED-01-01 ~ 04: 테스트 인프라 구축 완료 (fixture, 상태 초기화, 네이밍 규칙)
- RED-02-01 ~ 06: 경계값 및 기능 테스트 추가 예정
