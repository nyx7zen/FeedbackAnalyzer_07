# FEATURE-01-02 실행 보고서

**실행 날짜:** 2026-05-22

**작업 항목 ID:** FEATURE-01-02

**작업 제목:** feat: count positive and negative keywords

---

## 목표 (Goal)

단순히 첫 키워드에서 종료되는 로직을 폐기하고, 문장 전체를 순회하며 긍정/부정 단어 빈도를 누적 카운트하는 것.

---

## 수행 작업 (Changes)

### 1. 현재 구현 분석

기존 `calculateSentimentScore()` 함수는 이미 다음을 수행하고 있었음을 확인:
- `TextUtils::countKeywordOccurrences()`를 사용하여 모든 키워드의 누적 횟수 계산
- 첫 키워드에서 조기 종료하지 않고 전체 문장 순회
- 긍정/부정 키워드 개수를 각각 카운트하여 점수 계산

### 2. 공개 API 추가

**TextAnalyzer.h에 새로운 메서드 선언:**
```cpp
int getPositiveKeywordCount(const std::string& text) const;
int getNegativeKeywordCount(const std::string& text) const;
```

**TextAnalyzer.cpp에 구현:**
- 내부 헬퍼 함수:
  - `getPositiveKeywordCountHelper()` - 긍정 키워드 누적 카운트
  - `getNegativeKeywordCountHelper()` - 부정 키워드 누적 카운트
  
- 공개 메서드:
  - `TextAnalyzer::getPositiveKeywordCount()` - 긍정 키워드 개수 반환
  - `TextAnalyzer::getNegativeKeywordCount()` - 부정 키워드 개수 반환

### 3. 키워드 카운트 동작

**긍정 키워드 카운트:**
- `TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentPositive])`
- 문장 내 모든 긍정 키워드의 총 출현 횟수 반환
- 반복 출현 포함 (예: "좋아요 좋아요" = 2 counts)

**부정 키워드 카운트:**
- `TextUtils::countKeywordOccurrences(text, Constants::SENTIMENT_KEYWORDS[Constants::kSentimentNegative])`
- 문장 내 모든 부정 키워드의 총 출현 횟수 반환
- 반복 출현 포함 (예: "별로 별로" = 2 counts)

### 4. 테스트 추가

**Test 25-28:** 새로운 공개 메서드 검증
```
Test 25: should_count_all_positive_keywords_in_text
  - "좋아요 만족 감사 좋아요" → 4개 확인 ✓

Test 26: should_count_all_negative_keywords_in_text
  - "별로 실망 불만 별로" → 4개 확인 ✓

Test 27: should_count_positive_and_negative_keywords_separately
  - "좋아요 만족 별로 실망 좋아요" → positive=3, negative=2 확인 ✓

Test 28: should_return_zero_when_counting_keywords_in_empty_text
  - "" → 0, 0 확인 ✓
```

---

## 생성된 산출물 (Outputs)

- **src/cpp/TextAnalyzer.h**: 2개 공개 메서드 선언 추가
- **src/cpp/TextAnalyzer.cpp**: 4개 함수 구현 추가 (헬퍼 2개, 공개 2개)
- **tests/TextAnalyzerTest.cpp**: 4개 테스트 추가 (Tests 25-28)
- **보고서**: 본 파일 (feature-01-02_count_positive_and_negative_keywords-report.md)

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
Total: 28 tests
Passed: 28 ✅
Failed: 0
========================================
```

**모든 테스트 통과** ✓

### 테스트 커버리지
- **기존 테스트 (1-24)**: 24/24 통과 ✓
- **신규 테스트 (25-28)**: 4/4 통과 ✓
  - Test 25: 긍정 키워드 누적 카운트 ✓
  - Test 26: 부정 키워드 누적 카운트 ✓
  - Test 27: 긍정/부정 분리 카운트 ✓
  - Test 28: 빈 입력 처리 ✓

### 기존 기능 회귀 검증
- 감성 판정 로직: 정상 ✓
- Session 관리: 정상 ✓
- 키워드 분석: 정상 ✓
- 필터 처리: 정상 ✓

---

## 핵심 발견사항 (Key Findings)

1. **첫 키워드 조기 종료 로직은 없었음**
   - 기존 구현이 이미 문장 전체 순회 수행
   - `TextUtils::countKeywordOccurrences()` 함수가 모든 키워드 누적 카운트

2. **공개 API 추가로 의도 명확화**
   - `getPositiveKeywordCount()` - 명시적 긍정 카운트 메서드
   - `getNegativeKeywordCount()` - 명시적 부정 카운트 메서드
   - 향후 상대 점수 계산에 직접 사용 가능

3. **누적 카운트 동작 명확화**
   - 반복 출현 키워드는 횟수만큼 카운트
   - 예: "좋아요 좋아요 좋아요" = 3 counts
   - 첫 키워드에서 즉시 반환하지 않음

4. **감성 점수 계산 공식**
   - 점수 = 긍정 개수 - 부정 개수
   - 긍정: 점수 >= 1
   - 부정: 점수 <= -1
   - 중립: -1 < 점수 < 1

---

## 다음 단계 (Next Steps)

다음 TODO 항목:
- **FEATURE-01-03**: `feat: calculate relative sentiment score`
  - 상대 점수 기반 감성 분류 구현
  - 공개 API 활용하여 점수 계산 메서드 작성

실행 명령:
```bash
/run FEATURE-01-03
```

---

## 요약 (Summary)

FEATURE-01-02가 성공적으로 완료되었습니다.

긍정/부정 키워드 빈도 누적 카운트 기능을 공개 API로 노출했습니다. 기존 구현이 이미 전체 문장을 순회하며 누적 카운트하고 있었으며, 새로운 메서드를 통해 이 기능을 명시적으로 사용할 수 있게 되었습니다.

- 공개 메서드 추가: 2개 ✓
- 테스트 추가: 4개 ✓
- 모든 테스트 통과: 28/28 tests passed ✓
- 빌드 성공: ✓
