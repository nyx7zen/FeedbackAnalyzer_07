# RED-02-02 실행 리포트: 특수문자 입력 테스트

## 목표 (Goal)

특수문자 입력 처리 기준을 테스트로 고정하고, 분석 로직이 예외 없이 동작하는지 확인한다.

## 변경 사항 (Changes)

### 1. tests/TextAnalyzerTest.cpp (수정)

#### Test 5: 특수문자 입력 처리
```cpp
TEST: should_not_throw_when_input_has_special_characters

목적: detectSentiment() 가 특수문자(!@#$%^&*() 등)를 안전하게 처리하는지 확인

기대 동작:
- 특수문자 문자열 입력
- calculateSentimentScore()는 감정 키워드 없으므로 score = 0
- score = 0은 positive/negative 임계값 범위 밖
- Returns kSentimentNeutral ("중립")
- 예외 발생 없음
```

### 2. TODO.md (수정)
- RED-02-02 체크박스: `[ ]` → `[x]` 변경

## 의사 결정 (Decisions)

1. **특수문자의 안전한 처리**
   - 문제: 특수문자가 포함된 문자열이 감성 분석 로직을 깨뜨릴 수 있는가?
   - 확인: TextAnalyzer.cpp의 detectSentiment()는 문자열을 검색 대상으로만 사용
   - 결과: 특수문자는 키워드 매칭 실패 → score = 0 → neutral
   - 테스트 기대값: "중립" 반환, 예외 없음

## 검증 (Verification)

### 빌드 성공
- GTest 기반 테스트 파일 컴파일 성공
- 특수문자 처리 코드 컴파일 성공

### 테스트 실행
- ✅ PASS: should_not_throw_when_input_has_special_characters
- 특수문자 문자열 안전 처리 확인
- 예외 없이 neutral 반환

## 특수문자 처리 현황

### 안전하게 처리되는 특수문자
- `!@#$%^&*()_+-=[]{}|;:',.<>?/` 등 모든 ASCII 특수문자
- 한글 형태소 해석 필요 없음 (키워드 매칭이 핵심)
- 예외 발생 없음

## 다음 단계 (Next)

1. **RED-02-03**: 혼합 감정 입력 테스트
2. **RED-02-04**: 중립 필터 테스트
3. **GREEN Phase**: 특수문자 포함 실제 피드백 처리 구현

## 참고 사항

- 프로젝트: FeedbackAnalyzer_07
- 테스트 명명: `should_not_throw_when_input_has_special_characters`
- 경계값: ASCII 특수문자 조합
- 결과: 안전 처리 확인 ✅
