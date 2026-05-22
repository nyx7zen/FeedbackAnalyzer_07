# FEATURE-01-01 실행 보고서

**실행 날짜:** 2026-05-22

**작업 항목 ID:** FEATURE-01-01

**작업 제목:** test: add weighted sentiment scoring tests

---

## 목표 (Goal)

긍정/부정 단어 빈도 누적 기준 테스트를 작성하고, 기존처럼 첫 키워드에서 종료되는 로직의 한계를 드러낸다.

---

## 수행 작업 (Changes)

### 1. 현재 구현 분석

- **TextAnalyzer.cpp의 calculateSentimentScore()** 함수는 이미 가중치 기반 감성 스코어링을 지원:
  ```cpp
  const int positiveCount = TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentPositive]);
  const int negativeCount = TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentNegative]);
  return positiveCount - negativeCount;
  ```
  
- **TextUtils::countKeywordOccurrences()** 함수는 모든 키워드의 누적 횟수를 계산

- **detectSentiment()** 함수는 점수 기반으로 감성 판정:
  - 점수 >= 1: 긍정
  - 점수 <= -1: 부정
  - -1 < 점수 < 1: 중립

### 2. 가중치 기반 감성 스코어링 테스트 추가

tests/TextAnalyzerTest.cpp에 다음 6개의 새로운 테스트를 추가:

#### Test 19: 긍정 키워드가 부정 키워드보다 많을 때
```cpp
should_return_positive_when_positive_keywords_outnumber_negative_keywords
입력: "좋아요 만족 감사 별로" (긍정 3개, 부정 1개)
기대값: 긍정
점수: 3 - 1 = 2 (>= 1)
```

#### Test 20: 부정 키워드가 긍정 키워드보다 많을 때
```cpp
should_return_negative_when_negative_keywords_outnumber_positive_keywords
입력: "좋아요 별로 실망 불만" (긍정 1개, 부정 3개)
기대값: 부정
점수: 1 - 3 = -2 (<= -1)
```

#### Test 21: 긍정/부정 키워드 개수가 같을 때
```cpp
should_return_neutral_when_positive_and_negative_keyword_counts_are_equal
입력: "좋아요 만족 별로 실망" (긍정 2개, 부정 2개)
기대값: 중립
점수: 2 - 2 = 0 (-1 < 0 < 1)
```

#### Test 22: 같은 키워드 반복 출현 카운트
```cpp
should_count_multiple_occurrences_of_same_keyword
입력: "좋아요 좋아요 좋아요 별로" (긍정 3개, 부정 1개)
기대값: 긍정
점수: 3 - 1 = 2 (>= 1)
```

#### Test 23: 긍정 키워드가 크게 우세할 때
```cpp
should_return_positive_when_positive_keywords_significantly_outnumber_negative
입력: "좋아요 만족 감사 친절 추천 별로" (긍정 5개, 부정 1개)
기대값: 긍정
점수: 5 - 1 = 4 (>= 1)
```

#### Test 24: 부정 키워드가 크게 우세할 때
```cpp
should_return_negative_when_negative_keywords_significantly_outnumber_positive
입력: "좋아요 별로 실망 불만 불편 최악" (긍정 1개, 부정 5개)
기대값: 부정
점수: 1 - 5 = -4 (<= -1)
```

---

## 생성된 산출물 (Outputs)

- **tests/TextAnalyzerTest.cpp**: 6개의 새로운 테스트 추가 (Tests 19-24)
- **보고서**: 본 파일 (feature-01-01_add_weighted_sentiment_scoring_tests-report.md)

---

## 검증 결과 (Verification)

### 빌드 결과
```
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
```
결과: **성공** ✓

### 테스트 실행 결과
```
./build/feedback_analyzer_test.exe
```

결과:
```
========================================
Total: 24 tests
Passed: 24
Failed: 0
========================================
```

**모든 테스트 통과** ✓

### 각 테스트 상태:
- Test 1-18: 기존 테스트 - 모두 통과 ✓
- Test 19 (should_return_positive_when_positive_keywords_outnumber_negative_keywords): 통과 ✓
- Test 20 (should_return_negative_when_negative_keywords_outnumber_positive_keywords): 통과 ✓
- Test 21 (should_return_neutral_when_positive_and_negative_keyword_counts_are_equal): 통과 ✓
- Test 22 (should_count_multiple_occurrences_of_same_keyword): 통과 ✓
- Test 23 (should_return_positive_when_positive_keywords_significantly_outnumber_negative): 통과 ✓
- Test 24 (should_return_negative_when_negative_keywords_significantly_outnumber_positive): 통과 ✓

---

## 핵심 발견사항 (Key Findings)

1. **현재 구현은 이미 가중치 기반 감성 스코어링을 지원**
   - calculateSentimentScore() 함수가 긍정/부정 키워드의 모든 출현을 누적 카운트
   - 단순히 첫 번째 키워드에서 종료되는 방식이 아님

2. **점수 기반 판정 로직이 올바르게 구현됨**
   - 점수 = 긍정 개수 - 부정 개수
   - 임계값 기반 분류가 정확하게 동작

3. **모든 테스트가 예상대로 통과**
   - 다양한 시나리오에서 가중치 기반 계산이 정확하게 동작
   - 반복 출현, 극단적 비율, 균형 상황 모두 올바르게 처리

---

## 다음 단계 (Next Steps)

다음 TODO 항목:
- **FEATURE-01-02**: `feat: count positive and negative keywords`
  - 실제 기능 구현 (필요시)
  - 점수 기반 감성 분류 강화

실행 명령:
```bash
/run FEATURE-01-02
```

---

## 요약 (Summary)

FEATURE-01-01이 성공적으로 완료되었습니다.

가중치 기반 감성 스코어링의 기대 동작을 6개의 포괄적인 테스트로 정의했으며, 현재 구현이 모든 시나리오에서 올바르게 동작함을 확인했습니다.

- 긍정 키워드 우세 시나리오 ✓
- 부정 키워드 우세 시나리오 ✓
- 균형 잡힌 시나리오 ✓
- 반복 출현 시나리오 ✓
- 극단적 비율 시나리오 ✓

모든 테스트 통과 (24/24 tests passed)
