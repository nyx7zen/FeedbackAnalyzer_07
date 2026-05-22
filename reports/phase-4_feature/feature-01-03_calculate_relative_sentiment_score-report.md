# FEATURE-01-03 실행 보고서

**실행 날짜:** 2026-05-22

**작업 항목 ID:** FEATURE-01-03

**작업 제목:** feat: calculate relative sentiment score

---

## 목표 (Goal)

`Score_sentiment = Count_positive - Count_negative` 수식을 적용하고, 상대적 감성 평가 반환 로직을 구현하는 것.

---

## 수행 작업 (Changes)

### 1. 현재 구현 분석

기존 `calculateSentimentScore()` 함수는 이미 상대 감성 점수를 계산하고 있었음:
```cpp
int calculateSentimentScore(const std::string& text) {
    const int positiveCount = getPositiveKeywordCountHelper(text);
    const int negativeCount = getNegativeKeywordCountHelper(text);
    return positiveCount - negativeCount;
}
```

### 2. 공개 API 추가

**TextAnalyzer.h에 새로운 메서드 선언:**
```cpp
/**
 * @brief 텍스트의 상대 감성 점수를 계산합니다.
 * @param text 분석할 텍스트
 * @return 상대 감성 점수 (긍정 개수 - 부정 개수)
 * @note 점수 > 0: 긍정 경향, 점수 = 0: 중립, 점수 < 0: 부정 경향
 */
int getSentimentScore(const std::string& text) const;
```

**TextAnalyzer.cpp에 구현:**
```cpp
int TextAnalyzer::getSentimentScore(const std::string& text) const {
    return calculateSentimentScore(text);
}
```

### 3. 상대 감성 점수 계산 로직

**수식:** `Score = Count_positive - Count_negative`

**점수의 의미:**
- 점수 > 0: 긍정 경향 (긍정 키워드가 부정 키워드보다 많음)
- 점수 = 0: 중립 (긍정과 부정 키워드 개수 동일)
- 점수 < 0: 부정 경향 (부정 키워드가 긍정 키워드보다 많음)

**사용 흐름:**
1. 입력 텍스트에서 긍정 키워드 개수 계산 (getPositiveKeywordCountHelper)
2. 입력 텍스트에서 부정 키워드 개수 계산 (getNegativeKeywordCountHelper)
3. 상대 점수 = 긍정 개수 - 부정 개수

### 4. 테스트 추가

**Test 29-34:** 상대 감성 점수 계산 검증

```
Test 29: should_calculate_positive_sentiment_score
  - "좋아요 만족 감사 별로" → score=2 (3-1) ✓

Test 30: should_calculate_negative_sentiment_score
  - "좋아요 별로 실망 불만" → score=-2 (1-3) ✓

Test 31: should_calculate_neutral_sentiment_score
  - "좋아요 만족 별로 실망" → score=0 (2-2) ✓

Test 32: should_return_zero_score_for_empty_text
  - "" → score=0 (0-0) ✓

Test 33: should_calculate_score_with_only_positive_keywords
  - "좋아요 만족 감사" → score=3 (3-0) ✓

Test 34: should_calculate_score_with_only_negative_keywords
  - "별로 실망 불만" → score=-3 (0-3) ✓
```

---

## 생성된 산출물 (Outputs)

- **src/cpp/TextAnalyzer.h**: 1개 공개 메서드 선언 추가
- **src/cpp/TextAnalyzer.cpp**: 1개 메서드 구현 추가
- **tests/TextAnalyzerTest.cpp**: 6개 테스트 추가 (Tests 29-34)
- **보고서**: 본 파일 (feature-01-03_calculate_relative_sentiment_score-report.md)

---

## 검증 결과 (Verification)

### 빌드 결과
```
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
Total: 34 tests
Passed: 34 ✅
Failed: 0
========================================
```

**모든 테스트 통과** ✓

### 테스트 커버리지
- **기존 테스트 (1-28)**: 28/28 통과 ✓
- **신규 테스트 (29-34)**: 6/6 통과 ✓
  - Test 29: 긍정 점수 (score=2) ✓
  - Test 30: 부정 점수 (score=-2) ✓
  - Test 31: 중립 점수 (score=0) ✓
  - Test 32: 빈 입력 (score=0) ✓
  - Test 33: 긍정만 (score=3) ✓
  - Test 34: 부정만 (score=-3) ✓

### 기존 기능 회귀 검증
- 감성 판정 로직: 정상 ✓
- 키워드 카운트: 정상 ✓
- Session 관리: 정상 ✓

---

## 핵심 발견사항 (Key Findings)

1. **점수 계산 공식 명확화**
   - 상대 감성 점수 = 긍정 개수 - 부정 개수
   - 정수형 점수로 반환 (부동소수점 불필요)

2. **점수 범위의 의미**
   - 극단적 긍정: score >= 3
   - 확실한 긍정: score >= 1
   - 중립: score = 0
   - 확실한 부정: score <= -1
   - 극단적 부정: score <= -3

3. **후속 감성 분류 기준**
   - FEATURE-01-04에서 점수에 따른 감성 분류 구현
   - 현재는 점수 계산만 담당 (SRP 준수)

4. **API 설계의 장점**
   - 공개 메서드로 점수를 직접 접근 가능
   - 감성 판정과 점수 계산 분리
   - 테스트 용이성 증가

---

## 다음 단계 (Next Steps)

다음 TODO 항목:
- **FEATURE-01-04**: `feat: classify sentiment from weighted score`
  - 계산된 점수에 따라 긍정/부정/중립 결과 반환
  - 점수 기준값 (Constants::kPositiveThreshold, kNegativeThreshold) 활용

실행 명령:
```bash
/run FEATURE-01-04
```

---

## 요약 (Summary)

FEATURE-01-03이 성공적으로 완료되었습니다.

상대 감성 점수 계산 기능을 공개 API로 노출했습니다. `Score = Count_positive - Count_negative` 수식을 적용하여 정수형 상대 점수를 반환합니다.

- 공개 메서드 추가: 1개 ✓
- 테스트 추가: 6개 ✓
- 모든 테스트 통과: 34/34 tests passed ✓
- 빌드 성공: ✓
- 기존 기능 회귀: 없음 ✓

점수 계산과 감성 분류이 완벽하게 분리되어 있으며, 다음 단계인 FEATURE-01-04에서 점수 기반 감성 분류를 구현할 준비가 완료되었습니다.
