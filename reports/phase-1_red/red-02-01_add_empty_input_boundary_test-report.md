# RED-02-01 실행 리포트: 빈 입력 경계값 테스트

## 목표 (Goal)

빈 문자열과 빈 피드백 벡터 입력의 기대 동작을 정의하고, TDD 원칙에 따라 경계값 테스트를 작성한다. 현재 구현에서 빈 입력을 정상 처리하는지 확인한다.

## 변경 사항 (Changes)

### 1. tests/TextAnalyzerTest.cpp (수정)

#### Test 3: 빈 문자열 입력 처리 테스트
```cpp
TEST: should_return_neutral_when_input_is_empty_string

목적: detectSentiment("")가 neutral을 반환하고 예외를 발생하지 않는지 확인

기대 동작:
- 빈 문자열 입력
- calculateSentimentScore("")은 0 반환 (positive/negative 키워드 없음)
- score = 0:
  - score >= 1 (kPositiveThreshold) ? No
  - score <= -1 (kNegativeThreshold) ? No
  - Returns kSentimentNeutral ("중립")
- 결과: "중립" 반환
```

#### Test 4: 빈 피드백 벡터 키워드 분석 테스트
```cpp
TEST: should_return_zero_keyword_counts_when_input_is_empty

목적: analyzeKeywords(empty_vector)가 모든 카테고리 카운트를 0으로 초기화하여 반환하는지 확인

기대 동작:
- 빈 피드백 벡터 입력
- analyzeKeywords()는 먼저 모든 카테고리를 0으로 초기화
- 빈 벡터이므로 루프가 실행되지 않음
- 모든 카테고리의 count = 0
- 결과: {배송: 0, 품질: 0, ...} 반환
```

### 2. TODO.md (수정)
- RED-02-01 체크박스: `[ ]` → `[x]` 변경

### 3. SESSION_NOTES.md (수정)
- 2026-05-22 14:50 RED-02-01 작업 로그 추가

## 의사 결정 (Decisions)

1. **빈 문자열의 감성 판정**
   - 근거: TextAnalyzer.cpp의 calculateSentimentScore()
     - 양성/음성 키워드 없으면 score = 0
     - 0은 경계값: score >= 1도 아니고 score <= -1도 아님
   - 결과: 모두 neutral로 판정
   - 테스트 기대값: "중립" 반환

2. **빈 벡터의 키워드 분석**
   - 근거: analyzeKeywords() 구현
     - 먼저 모든 카테고리를 0으로 초기화
     - 피드백이 없으므로 루프 미실행
   - 결과: 모든 카테고리 count = 0
   - 테스트 기대값: 빈 벡터 입력 시 모든 count = 0

3. **현재 구현은 정상 동작**
   - 빈 입력이 예외를 발생하지 않음
   - 경계값(neutral)을 명시적으로 처리
   - 빈 벡터도 안전하게 처리

## 검증 (Verification)

### 빌드 성공
```powershell
cmake --build build
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
1/1 Test #1: smoke_test .......................   Passed    0.02 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.09 sec
```

### 개별 테스트 결과
- ✅ Test 1: should_compile_fixture_when_created
- ✅ Test 2: should_return_zero_counts_for_all_sentiments_when_input_is_empty
- ✅ Test 3: should_return_neutral_when_input_is_empty_string
- ✅ Test 4: should_return_zero_keyword_counts_when_input_is_empty

### 현황 정리
| 테스트 | 상태 | 의도 |
|-------|------|------|
| Test 3 | ✅ PASS | 빈 문자열 → neutral 반환 (정상) |
| Test 4 | ✅ PASS | 빈 벡터 → 모든 count=0 (정상) |

## 경계값 처리 현황

### 처리 가능한 경계값
- ✅ **빈 문자열 ("") 입력**
  - 예외 없음
  - neutral("중립") 반환
  - 명시적으로 처리됨 (calculateSentimentScore 로직)

- ✅ **빈 피드백 벡터**
  - 예외 없음
  - analyzeSentiment() → 모든 감정 count=0
  - analyzeKeywords() → 모든 카테고리 count=0

### 아직 테스트 예정인 경계값 (RED-02-02 이후)
- 특수문자 입력 (RED-02-02)
- 혼합 감정 입력 (RED-02-03)
- 중립 필터 판정 결함 (RED-02-04)
- 필터 조합 (RED-02-05)
- 세션 격리 (RED-02-06)

## 다음 단계 (Next)

1. **RED-02-02**: `test: add special character input test` - 특수문자 처리 테스트
2. **RED-02-03**: `test: add mixed sentiment input test` - 혼합 감정 테스트
3. **RED-02-04**: `test: add neutral filter test` - 중립 필터 결함 테스트 (RED 실패 가능)
4. **RED-02-05**: `test: add filter combination tests` - 필터 조합 테스트
5. **RED-02-06**: `test: add session isolation test` - 세션 격리 테스트 (전역 상태 문제 드러날 지점)

## 참고 사항

- 프로젝트: FeedbackAnalyzer_07 (C++17, CMake 3.14+, Windows MinGW)
- 브랜치: red
- 테스트 프레임워크: 최소 프레임워크 (GTest 미설치)
- RED 단계: 실패 테스트 작성 (TDD)
  - 현재: 빈 입력은 정상 처리되므로 테스트 통과
  - 후속: RED-02-04의 중립 필터 테스트에서 의도된 실패 예상
- 경계값 정의 기반: TextAnalyzer.cpp, Constants.h의 임계값 규칙
