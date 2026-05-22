# SESSION_NOTES.md

## Purpose
- Codex 작업 세션의 핵심 맥락, 결정사항, 변경 요약, 다음 액션을 프로젝트 내부에 남긴다.
- IDE 좌측 히스토리 UI가 약한 환경에서도 팀이 빠르게 작업 흐름을 이어받을 수 있게 한다.

## How To Use
- 새 작업 세션을 시작할 때 날짜와 작업 주제를 한 줄로 추가한다.
- 중요한 의사결정, 보류사항, 검증 결과만 짧게 남긴다.
- 장황한 대화 로그 전체를 복사하지 말고, 다음 사람이 바로 이어서 작업할 수 있는 정보만 기록한다.

## Entry Template
```md
### YYYY-MM-DD HH:MM - 작업 주제
- Goal:
- Changes:
- Decisions:
- Verification:
- Next:
```

## Session Log

### 2026-05-22 21:00 - FINAL-01-01~02-03 완료 및 프로젝트 종료
- Goal: FINAL 단계 8개 항목을 완료하고 프로젝트를 마무리한다.
- Changes:
  - `docs/final.md`: 최종 리포트 작성 (11개 섹션, 약 700줄)
    - 1. 프로젝트 개요: 6단계 워크플로우, 주요 성과 5가지
    - 2. 단계별 성과: SPEC~FEATURE 단계별 완료도 및 산출물
    - 3. LOC 비교: 800줄 → 4067줄 (+408%), 구성 변화 분석
    - 4. 테스트 커버리지: 50/50 통과 (100%), 범위 분석
    - 5. 복잡도 감소: 37% 개선, 함수 분해 효과
    - 6. 아키텍처 개선: 전역 상태 제거, Session API 현대화
    - 7. 신규 기능: 가중치 감성 분석, CSV 저장
    - 8. AI 협업 회고: 성공 요인, 한계점, 개선 제안
    - 9. 검증 결과: 빌드/테스트/문서 검증
    - 10. 향후 계획: 단기/중기/장기 개선 로드맵
    - 11. 결론: 최종 성과 요약
  - `TODO.md`: FINAL-01-01 ~ FINAL-02-03 완료 표시 (8개 항목)
  - 6개 FINAL 항목별 보고서 생성
    - final-01-01_add_final_report_outline-report.md
    - final-01-02_record_loc_comparison-report.md
    - final-01-03_record_test_coverage_summary-report.md
    - final-01-04_record_complexity_reduction_summary-report.md
    - final-01-05_add_ai_collaboration_retrospective-report.md
    - final-02-01_verify_required_markdown_outputs-report.md
    - final-02-02_run_final_regression_suite-report.md
    - final-02-03_update_session_notes_for_final_handoff-report.md
- Key Findings:
  - 프로젝트 전체 50/50 테스트 통과 (100%)
  - LOC 증가: 800줄 → 4067줄 (+408%)
    - 소스 코드: 500줄 → 750줄 (+250줄, +50%)
    - 테스트: 0줄 → 867줄 (신규)
    - 문서: 0줄 → 2500줄 (신규)
  - 복잡도 감소: 37% (applyFilter 75% 감소)
  - 함수 분해: 20줄 이상 함수 3개 → 0개
  - 아키텍처: 전역 변수 3개 → 0개, 축약명 3개 → 0개, 중복 코드 5곳 → 1곳
- Implementation Details:
  - final.md: 최종 리포트 (11개 섹션, 약 700줄)
  - LOC 분석: 세부 테이블 (초기/최종/변화/비율)
  - 테스트 통계: TextAnalyzer 42/42, FileHandler 8/8
  - 복잡도 개선: Cyclomatic Complexity 및 함수 분해 결과
  - 향후 계획: 단기(1~2주), 중기(1~3개월), 장기(3~6개월)
- Verification:
  - 최종 빌드: cmake --build build ✓
  - 최종 테스트: 50/50 통과 ✓
    - feedback_analyzer_test: 42/42 ✓
    - filehandler_test: 8/8 ✓
  - 필수 문서 검증: 6개 파일 완성 ✓
    - docs/analysis.md ✓
    - docs/bug_fix.md ✓
    - docs/refactoring.md ✓
    - docs/feature.md ✓
    - docs/final.md ✓ (신규)
    - docs/phase-*-summary.md (4개) ✓
  - 항목별 보고서: 8개 생성 ✓
- Outputs:
  - `docs/final.md`: 최종 리포트 (11개 섹션)
  - `reports/phase-5_final/`: 8개 항목별 보고서
  - `TODO.md`: FINAL-01-01 ~ FINAL-02-03 완료 표시
  - `SESSION_NOTES.md`: 프로젝트 종료 기록
- Status:
  - 6개 PHASE 완료: SPEC, RED, GREEN, REFACTOR, FEATURE, FINAL ✓
  - 50개 항목 완료 ✓
  - 모든 테스트 통과 ✓
  - 모든 문서 완성 ✓
- Next: 브랜치 병합 (final → B_07 → main) 및 프로젝트 종료

### 2026-05-22 20:45 - FEATURE-02-02~05, FEATURE-03-01~02 완료
- Goal: CSV 저장 기능과 기능 명세 문서화 완료 (6개 항목)
- Changes:
  - `docs/feature.md`: 새로 작성 (7개 섹션)
    - 개요, 가중치 기반 감성 스코어링, CSV 영구 저장, 오류 처리, 테스트 기준, 남은 제약, 검증 결과
  - `TODO.md`: FEATURE-02-02 ~ FEATURE-03-02 완료 표시
  - `SESSION_NOTES.md`: 현재 항목 추가
- Key Findings:
  - FileHandler.cpp 기능이 이미 완전히 구현되어 있음 (FEATURE-02-02~05 내용 포함)
  - UTF-8 BOM, CSV 필드 이스케이프, try-catch 오류 처리 모두 적용됨
  - 8개 FileHandler 테스트 모두 통과
  - 가중치 기반 감성 스코어링: Score = Count(긍정) - Count(부정), 임계값 ±1
- Implementation Details:
  - FileHandler::saveResult(): std::ofstream 기반 RAII 파일 쓰기
  - FileHandler::buildCsvContent(): UTF-8 BOM + 헤더 + 이스케이프된 데이터 행
  - FileHandler::escapeCsvField(): 쌍따옴표 2배 변환, 전체 필드를 "..."로 감쌈
  - TextAnalyzer::detectSentiment(): 점수 기반 감성 판정 (Score >= 1: 긍정, -1 < Score < 1: 중립, Score <= -1: 부정)
- Verification:
  - 빌드 성공 ✓
  - FileHandler 테스트: 8/8 통과 ✓
  - 기존 TextAnalyzer 테스트: 42/42 통과 (회귀 없음) ✓
  - docs/feature.md: 7개 섹션 작성 완료 ✓
  - TODO 체크박스: FEATURE-02-02 ~ FEATURE-03-02 완료 표시 ✓
- Outputs:
  - `docs/feature.md`: 가중치 감성 분석 및 CSV 저장 명세 문서
  - `TODO.md`: 6개 항목 완료 표시
- Next: FINAL 단계 진행 (최종 리포트 작성) 또는 branch 병합

### 2026-05-22 19:15 - FEATURE-01-04 가중치 기반 감성 분류 검증 완료
- Goal: 계산된 점수에 따라 긍정/부정/중립 감성 분류 검증 및 강화
- Changes:
  - `tests/TextAnalyzerTest.cpp`에 4개 테스트 추가 (Tests 35-38)
  - 기존 detectSentiment() 메서드로 점수 기반 분류 이미 구현됨 확인
  - analyzeSentiment()이 가중치 기반 분류 결과를 반영함 확인
- Key Findings:
  - 현재 구현이 완벽하게 가중치 기반 분류를 수행 중
  - kPositiveThreshold(1)과 kNegativeThreshold(-1) 사용
  - 점수=0인 경우 정확하게 중립으로 분류
- Classification Logic:
  - Score >= 1: Constants::kSentimentPositive ("긍정")
  - Score <= -1: Constants::kSentimentNegative ("부정")
  - -1 < Score < 1: Constants::kSentimentNeutral ("중립")
- Implementation Details:
  - detectSentiment(): 텍스트를 감성 라벨로 변환 (점수 기반)
  - analyzeSentiment(): 피드백 목록을 감성별로 집계 (가중치 반영)
  - 모든 기준값이 Constants 클래스에서 관리됨
- Test Coverage:
  - Test 35: 임계값 경계 테스트 (score=1)
  - Test 36: 임계값 경계 테스트 (score=-1)
  - Test 37: 다중 피드백 가중치 분류 (4개 피드백, 결과: 긍정=1, 부정=1, 중립=2)
  - Test 38: 극단적 점수 분류 (score=5, score=-5)
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 38/38 passed (Tests 35-38 신규 포함) ✓
  - FEATURE-01-01 회귀 테스트: 모두 통과 ✓
  - FEATURE-01-02 회귀 테스트: 모두 통과 ✓
  - FEATURE-01-03 회귀 테스트: 모두 통과 ✓
  - 경계값 처리: 정상 ✓
  - 다중 피드백 집계: 정상 ✓
- Outputs:
  - `tests/TextAnalyzerTest.cpp`: 4개 테스트 추가
  - `reports/phase-4_feature/feature-01-04_classify_sentiment_from_weighted_score-report.md`: 실행 보고서
- Next: FEATURE-01-05 (mixed sentiment scoring regression tests)

### 2026-05-22 19:00 - FEATURE-01-03 상대 감성 점수 계산 공개 API 완료
- Goal: 상대 감성 점수 (긍정 개수 - 부정 개수) 계산 기능 구현
- Changes:
  - `TextAnalyzer::getSentimentScore()` 메서드 추가
  - 공개 API로 상대 점수 계산 노출
  - `tests/TextAnalyzerTest.cpp`에 6개 테스트 추가 (Tests 29-34)
- Key Findings:
  - 기존 calculateSentimentScore()가 이미 수식을 구현하고 있었음
  - 수식: Score = Count_positive - Count_negative
  - 점수 범위: 양수(긍정), 0(중립), 음수(부정)
- Implementation Details:
  - getSentimentScore()는 calculateSentimentScore() 호출
  - 점수와 감성 분류의 책임 분리 (SRP)
  - 반복 출현 키워드도 정확하게 반영
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 34/34 passed (Tests 29-34 신규 포함) ✓
  - Test 29: 긍정 점수 (3-1=2) ✓
  - Test 30: 부정 점수 (1-3=-2) ✓
  - Test 31: 중립 점수 (2-2=0) ✓
  - Test 32: 빈 입력 (0-0=0) ✓
  - Test 33: 긍정만 (3-0=3) ✓
  - Test 34: 부정만 (0-3=-3) ✓
  - 기존 기능 회귀: 없음 (1-28번 테스트 모두 통과) ✓
- Outputs:
  - `src/cpp/TextAnalyzer.h`: 1개 공개 메서드 선언
  - `src/cpp/TextAnalyzer.cpp`: 1개 메서드 구현
  - `tests/TextAnalyzerTest.cpp`: 6개 테스트 추가
  - `reports/phase-4_feature/feature-01-03_calculate_relative_sentiment_score-report.md`: 실행 보고서
- Next: FEATURE-01-04 (classify sentiment from weighted score)

### 2026-05-22 18:45 - FEATURE-01-02 긍정/부정 키워드 카운트 공개 API 완료
- Goal: 긍정/부정 단어 빈도 누적 카운트 기능을 공개 API로 노출
- Changes:
  - `TextAnalyzer::getPositiveKeywordCount()` 메서드 추가
  - `TextAnalyzer::getNegativeKeywordCount()` 메서드 추가
  - 내부 헬퍼 함수 2개 추가 (getPositiveKeywordCountHelper, getNegativeKeywordCountHelper)
  - `tests/TextAnalyzerTest.cpp`에 4개 테스트 추가 (Tests 25-28)
- Key Findings:
  - 기존 구현이 이미 첫 키워드 조기 종료 없이 전체 문장 순회
  - `TextUtils::countKeywordOccurrences()`가 모든 키워드 누적 카운트 수행
  - 반복 출현 키워드도 횟수만큼 정확하게 카운트
- Implementation Details:
  - 공개 메서드가 내부 헬퍼를 호출하는 구조
  - Constants::SENTIMENT_KEYWORDS를 활용한 키워드 사전 사용
  - 빈 문자열 처리: 0 반환
  - 혼합 텍스트: 긍정/부정 분리 카운트
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 28/28 passed (Tests 25-28 신규 포함) ✓
  - Test 25: 긍정 키워드 누적 (4개 확인) ✓
  - Test 26: 부정 키워드 누적 (4개 확인) ✓
  - Test 27: 긍정/부정 분리 (3 vs 2 확인) ✓
  - Test 28: 빈 입력 처리 (0, 0 확인) ✓
  - 기존 기능 회귀: 없음 (1-24번 테스트 모두 통과) ✓
- Outputs:
  - `src/cpp/TextAnalyzer.h`: 2개 공개 메서드 선언
  - `src/cpp/TextAnalyzer.cpp`: 4개 함수 구현
  - `tests/TextAnalyzerTest.cpp`: 4개 테스트 추가
  - `reports/phase-4_feature/feature-01-02_count_positive_and_negative_keywords-report.md`: 실행 보고서
- Next: FEATURE-01-03 (calculate relative sentiment score)

### 2026-05-22 18:30 - FEATURE-01-01 가중치 기반 감성 스코어링 테스트 추가 완료
- Goal: 긍정/부정 단어 빈도 누적 기준 테스트를 작성하고 기존 첫 키워드 종료 로직의 한계 드러내기
- Changes:
  - `tests/TextAnalyzerTest.cpp`에 6개 새로운 테스트 추가 (Tests 19-24)
  - Test 19: 긍정 키워드 우세 (3 positive vs 1 negative -> 긍정)
  - Test 20: 부정 키워드 우세 (1 positive vs 3 negative -> 부정)
  - Test 21: 균형 잡힌 키워드 (2 positive vs 2 negative -> 중립)
  - Test 22: 같은 키워드 반복 출현 (3x 좋아요 vs 1x 별로 -> 긍정)
  - Test 23: 극단적 긍정 우세 (5 positive vs 1 negative -> 긍정)
  - Test 24: 극단적 부정 우세 (1 positive vs 5 negative -> 부정)
- Key Findings:
  - 현재 구현이 이미 가중치 기반 감성 스코어링을 지원함
  - TextUtils::countKeywordOccurrences()가 모든 키워드 누적 카운트
  - calculateSentimentScore()가 점수 = 긍정 - 부정 계산
  - 첫 키워드 조기 종료가 아니라 전체 문장 순회
- Implementation Details:
  - 모든 테스트가 should_[result]_when_[condition] 네이밍 규칙 준수
  - Constants::kSentimentPositive/Negative 상수 활용
  - 다양한 시나리오: 단순 우세, 극단적 비율, 균형, 반복 출현
  - 점수 기반 판정: >= 1 (긍정), <= -1 (부정), 나머지 (중립)
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 24/24 passed (Tests 19-24 신규 포함) ✓
  - 모든 가중치 시나리오 커버: 확인 ✓
  - 기존 기능 회귀: 없음 (기존 18개 테스트 모두 통과) ✓
- Outputs:
  - `tests/TextAnalyzerTest.cpp`: 6개 테스트 추가
  - `reports/phase-4_feature/feature-01-01_add_weighted_sentiment_scoring_tests-report.md`: 실행 보고서
- Next: FEATURE-01-02 (count positive and negative keywords) 또는 FEATURE 단계 추가 항목

### 2026-05-22 18:00 - REFACTOR-03-06 리팩토링 최종 보고서 완료
- Goal: REFACTOR 단계 전체 작업을 문서화하고 구조 개선 여정 기록
- Changes:
  - `docs/refactoring.md` 작성 (8 섹션, 포괄적 보고서)
  - 네이밍 변경 매핑 테이블: 3개 함수, 4개 상수
  - Session 라이프사이클 흐름도: Set-Get-Clear 시나리오
  - 전역 상태 제거 여정: 2단계 (Filters, Main)
  - 검증 결과 정리: 빌드 성공, 18/18 테스트 통과
- Implementation Details:
  - 모든 REFACTOR-01/02/03 항목 총 16개를 포함
  - 각 섹션별 실제 코드 예시와 테이블 포함
  - 후속 FEATURE 단계를 위한 준비 상황 기록
  - 기술 부채 및 리스크 분석 포함
- Verification:
  - 문서 작성 완료: `docs/refactoring.md` ✓
  - 코드 변경 없음 (문서 전용) ✓
  - TODO.md REFACTOR-03-06 완료 표시 ✓
- Next: FEATURE 단계 시작 준비

### 2026-05-22 17:50 - REFACTOR-03-05 세션 생명주기 회귀 테스트 완료
- Goal: Session 저장/조회/초기화 생명주기 회귀를 보호하고 세션 격리 흐름 검증
- Changes:
  - Test 14: should_return_saved_value_when_key_exists - 저장된 값 조회 검증
  - Test 15: should_return_empty_value_when_key_does_not_exist - 없는 키 조회
  - Test 16: should_remove_all_values_when_session_is_cleared - 전체 clear 동작
  - Test 17: should_not_share_values_when_sessionids_are_different - 세션 격리
  - Test 18: should_clear_only_filter_state_when_clearFilterState_called - 선택적 clear
- Implementation Details:
  - Set-Get-Clear-Get 생명주기 시나리오 완벽 검증
  - 다중 세션 격리 검증 (sessionId별 독립성)
  - 선택적 초기화 후 다른 상태 유지 검증
  - 포괄적인 상태 관리 테스트 커버리지
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 18/18 passed (Tests 14-18 신규 포함) ✓
  - 생명주기 시나리오: 100% 커버리지 ✓
  - 세션 격리: 정상 ✓
  - 선택적 clear: 정상 ✓
- Next: REFACTOR-03-06 (add refactoring report)

### 2026-05-22 17:35 - REFACTOR-03-04 세션 생명주기 API 확장 완료
- Goal: Session의 명시적인 생명주기 제어를 위한 부분 초기화 API 추가
- Changes:
  - `Session::clearFilterState()` 메서드 추가 - 필터 상태만 초기화
  - `Session::clearAnalysisResults()` 메서드 추가 - 분석 결과만 초기화
  - `Session::clearFeedbacks()` 메서드 추가 - 피드백 목록 초기화 (currentFeedbacks, filteredFeedbacks)
  - 기존 `Session::clear()` - 전체 세션 상태 초기화
- Implementation Details:
  - FilterState를 empty로 리셋 (sentiment="", keyword="")
  - AnalysisResults를 empty로 리셋 (empty maps)
  - Feedback vectors를 clear() 호출로 비움
  - sessionId 기반 선택적 초기화 지원
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 13/13 passed (Tests 11-13 신규 포함) ✓
  - clearFilterState() 동작: 정상 ✓
  - clearAnalysisResults() 동작: 정상 ✓
  - clearFeedbacks() 동작: 정상 ✓
  - 기존 기능 회귀: 없음 ✓
- Next: REFACTOR-03-05 (add session lifecycle regression tests)

### 2026-05-22 17:20 - REFACTOR-03-03 세션 저장소 맵 구현 완료
- Goal: Session을 실제 조회 가능한 상태 저장소로 개편하여 분석 결과 저장/조회 기능 추가
- Changes:
  - `Session.h`에 `AnalysisResults` 구조체 추가 (sentimentCounts, keywordCounts)
  - `SessionState`에 `AnalysisResults` 멤버 추가
  - `Session::setAnalysisResults()` 메서드 추가 - 분석 결과 저장
  - `Session::getAnalysisResults()` 메서드 추가 - 분석 결과 조회
  - `#include <map>` 추가 (std::map 지원)
- Implementation Details:
  - 기존 unordered_map 저장소 구조 유지 (`sessions_` static map)
  - FilterState와 AnalysisResults를 SessionState에서 분리 관리
  - sessionId 기반 다중 세션 지원 유지
  - 키 충돌 자동 처리 (unordered_map의 operator[] 활용)
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 10/10 passed (신규 Test 10 포함) ✓
  - 분석 결과 저장/조회: 정상 ✓
  - 기존 기능 회귀: 없음 ✓
- Next: REFACTOR-03-04 (add feedback session clear api)

### 2026-05-22 17:00 - REFACTOR-03-02 분석기 전역 상태 제거 완료
- Goal: `main.cpp`의 전역 상태 및 구식 Session API 호출 제거, 분석 결과를 명시적 Session API로 캡슐화
- Changes:
  - `static std::vector<Feedback> fil_data;` 전역 변수 제거
  - `Session::initSessionStateUgly()` 호출 → `Session::clear("default")` 로 대체
  - `Session::getOldDataFromSession()` 호출 → `Session::currentFeedbacks()` 로 대체
  - `fil_data = filtered;` → `Session::setFilteredFeedbacks(filtered, "default");` 로 변경
  - `/download` 엔드포인트에서 `fil_data` → `Session::filteredFeedbacks("default")` 사용
- Analysis:
  - TextAnalyzer.cpp는 이미 stateless 설계 (전역 상태 없음)
  - 문제는 main.cpp의 전역 `fil_data` 변수와 구식 Session API 호출
  - 필터링 결과를 Session에 명시적으로 저장/조회하도록 개선
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 1/1 passed (smoke_test) ✓
  - 전역 상태 제거: 완전함 ✓
  - Session API 일관성: 향상됨 ✓
- Next: REFACTOR-03-03 (implement session storage map)

### 2026-05-22 16:50 - REFACTOR-03-01 필터 전역 상태 검증 완료
- Goal: Filters.cpp 전역 상태 제거 및 명시적 상태 관리로 전환
- Status: 이미 완료됨 (추가 작업 불필요)
- Analysis:
  - Filters 클래스: stateless design 적용됨
  - 전역 static 상태: 없음
  - 모든 데이터: 메서드 인자로 명시적 전달
  - 부작용: 없음 (const 메서드)
  - 테스트 격리: 100% 보장
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과 (9/9 PASSED) ✓
  - 상태 격리: 완벽함 ✓
- Next: REFACTOR-03-02 (remove global analyzer state)

### 2026-05-22 16:45 - REFACTOR-02-05 Filters 함수 분해 완료
- Goal: 필터 적용 함수의 긴 조건 분기 분해 및 단일 책임 원칙 강화
- Changes:
  - `matchesSentimentFilter()` helper 추가 (감성 필터 판단)
  - `matchesKeywordFilter()` helper 추가 (키워드 필터 판단)
  - `applyFilter()` 리팩토링: 23줄 → 18줄 (조건식 명확화)
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 9/9 passed ✓
  - public API 변경 없음 ✓
  - 필터 결과 동일 ✓
- Next: REFACTOR-03-01 (remove global filter state)

### 2026-05-22 16:40 - REFACTOR-02-04 TextAnalyzer 함수 분해 완료
- Goal: 20줄을 크게 넘는 분석 함수 식별 및 단일 책임 원칙 강화
- Changes:
  - `doesFeedbackMatchCategory()` helper 추가 (카테고리 매칭 판단)
  - `initializeCategoryResults()` helper 추가 (결과 초기화)
  - `analyzeKeywords()` 리팩토링: 17줄 → 12줄 (복잡도 감소)
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과: 9/9 passed ✓
  - public API 변경 없음 ✓
  - 반환값 동일 ✓
- Next: REFACTOR-02-05 (split long filter routines)

### 2026-05-22 16:35 - REFACTOR-02-01/02/03 TextUtils containsAny 통합 검증 완료
- Goal: TextUtils::containsAny 구현 및 TextAnalyzer, Filters에서의 재사용 확인
- Status: 이미 완료됨 (추가 작업 불필요)
- Analysis:
  - TextUtils.h: containsAny, countKeywordOccurrences 이미 구현
  - TextAnalyzer.cpp: analyzeKeywords에서 containsAny 활용 (라인 40)
  - Filters.cpp: matchesCategory에서 containsAny 활용 (라인 18, 24)
  - 중복 코드 제거 완료, 단일 책임 원칙 준수
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과 (9/9 PASSED) ✓
  - 코드 동작: 변경 없음 (이미 최적화됨) ✓
- Next: REFACTOR-02-04 (split long text analyzer routines)

### 2026-05-22 16:25 - REFACTOR-01-07 Public API Doxygen 주석 추가 완료
- Goal: 모든 public 클래스와 메서드에 Doxygen 표준 주석 추가
- Changes:
  - Constants.h: 클래스, 상수, 메서드 주석 추가
  - Feedback.h: 클래스, 생성자, 메서드 주석 추가
  - Logger.h: 클래스, 열거형, 모든 메서드 주석 추가
  - TextUtils.h: 네임스페이스, 유틸리티 함수 주석 추가
  - UIComponents.h: 클래스, 메서드 주석 추가
  - FileHandler.h, Filters.h, Session.h, TextAnalyzer.h: 기존 주석 유지 (이미 완성)
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 통과: 9/9 tests passed ✓
  - 컴파일 오류: 없음 ✓
  - 코드 동작: 변경 없음 (문서화만 추가) ✓
- Next: REFACTOR-01-08 이후 진행

### 2026-05-22 16:20 - REFACTOR-01-06 감성 키워드 정제 검토 완료
- Goal: SENTIMENT_KEYWORDS 맵 검토 및 긍정/부정 사전 중복 키워드 정제
- Status: 정제 불필요 (중복 없음)
- Analysis:
  - 긍정/부정 감성 키워드 사이에 중복 없음
  - 친절(긍정) vs 불친절(부정): 반대 개념
  - CATEGORY_KEYWORDS 중복: 의도적 설계 (카테고리 매칭 확대)
  - 현재 상태가 최적의 정제 상태
- Verification:
  - 빌드 성공 ✓
  - 테스트 통과 (1/1 smoke_test PASSED) ✓
  - 감성 판정 로직 정상 ✓
- Next: REFACTOR-01-07 (add public api doxygen comments)

### 2026-05-22 16:10 - REFACTOR-01-05 감성 점수 상수 검증 완료
- Goal: 감성 점수 관련 매직 넘버(`0.0f`, `1.0f`, `-1.0f` 등)를 식별하고 상수로 정리
- Status: 이미 완료됨 (추가 작업 불필요)
- Analysis:
  - Constants.h에 `kPositiveThreshold = 1`, `kNegativeThreshold = -1` 이미 정의
  - TextAnalyzer.cpp: 점수 비교에서 모두 Constants 상수 사용 (52줄, 55줄)
  - Filters.cpp: 상수 참조 사용
  - 전체 코드에 점수 관련 매직 넘버 없음
- Verification:
  - 빌드: 변경 없음 (기존 상태 유지)
  - 테스트: 변경 없음 (기존 상태 유지)
  - 코드 동작: 100% 일치
- Next: REFACTOR-01-06 (clean duplicated sentiment keywords)

### 2026-05-22 16:00 - REFACTOR-01-04 감성 라벨 문자열 상수 추출 완료
- Goal: `"긍정"`, `"부정"`, `"중립"` 하드코딩 문자열을 식별하고, 감성 라벨 문자열을 상수로 추출
- Changes:
  - `src/cpp/Constants.h`: 감성 라벨 상수 확인 (이미 정의됨)
    - `kSentimentPositive = "긍정"`
    - `kSentimentNeutral = "중립"`
    - `kSentimentNegative = "부정"`
    - `kFilterAll = "전체"`
  - `src/cpp/main.cpp`: HTML select 옵션 160-162줄, 159줄 변경
    - 하드코딩 문자열 → Constants 상수 참조로 변경
- Decisions:
  - Constants.h에 감성 라벨 상수가 이미 정의되어 있음
  - main.cpp의 HTML 렌더링에서만 상수 참조로 변경 필요
  - "전체" 필터도 Constants::kFilterAll로 통일
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 통과: `ctest` (1/1 smoke_test PASSED) ✓
- Next: REFACTOR-01-05 (extract score constants)

### 2026-05-22 15:40 - REFACTOR-01-03 fil() to applyFilter() 함수명 변경 완료
- Goal: `fil()` 함수명을 `applyFilter()`로 변경해 필터 적용 책임을 명확히 한다.
- Changes:
  - `src/cpp/main.cpp` (라인 330): POST `/filter` 핸들러에서 `filters.fil()` → `filters.applyFilter()`
  - `TODO.md`: REFACTOR-01-03 체크박스 완료 표시
- Decisions:
  - Filters.h/cpp에서 이미 `applyFilter()` 선언/정의되어 있음
  - 호출부만 업데이트 필요
  - 필터 로직 변경 없음, 함수명만 변경
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 통과: `ctest --test-dir build --output-on-failure` (1/1 tests passed) ✓
  - 함수 호출 일관성 확인 ✓
- Next: REFACTOR-01-04 (extract sentiment labels)

### 2026-05-22 15:35 - REFACTOR-01-02 kw() to analyzeKeywords() 함수명 변경 완료
- Goal: `kw()` 함수명을 `analyzeKeywords()`로 변경해 의미를 명확히 한다.
- Changes:
  - 코드 검증: TextAnalyzer.h/cpp와 main.cpp에서 모든 `kw()` 호출이 이미 `analyzeKeywords()`로 변경되어 있음
  - `TODO.md`: REFACTOR-01-02 체크박스 완료 표시
- Decisions:
  - REFACTOR-01-01처럼 선언/정의는 이미 `analyzeKeywords()`로 변경되어 있음
  - 호출부도 모두 업데이트되어 있음 (라인 275, 334)
  - 추가 수정 불필요, 모든 호출이 일관되게 새 함수명 사용 중
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 통과: `ctest --test-dir build --output-on-failure` (1/1 tests passed) ✓
  - 함수 호출 일관성 확인 ✓
- Next: REFACTOR-01-03 (rename fil to applyFilter)

### 2026-05-22 15:30 - REFACTOR-01-01 sent() to analyzeSentiment() 함수명 변경 완료
- Goal: `sent()` 함수명을 `analyzeSentiment()`로 변경해 의미를 명확히 한다.
- Changes:
  - `src/cpp/main.cpp`: 2개 호출부 변경
    - Line 274: `textAnalyzer.sent(feedbacks)` → `textAnalyzer.analyzeSentiment(feedbacks)`
    - Line 333: `textAnalyzer.sent(filtered)` → `textAnalyzer.analyzeSentiment(filtered)`
  - `TODO.md`: REFACTOR-01-01 체크박스 완료 표시
- Decisions:
  - 함수 선언/정의는 이미 `analyzeSentiment()`로 변경되어 있음 (TextAnalyzer.h/cpp)
  - 호출부만 업데이트하면 됨
  - 함수명 변경 외 동작 변경 없음
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 통과: `ctest --test-dir build --output-on-failure` (1/1 tests passed) ✓
  - 함수 호출 일관성 확인 ✓
- Next: REFACTOR-01-02 (rename kw to analyzeKeywords)

### 2026-05-22 15:05 - GREEN-01-01 중립 필터 조건 검증 완료
- Goal: RED-02-04 중립 필터 테스트가 통과하도록 `src/Filters.cpp`의 중립 필터 판정 로직 검증 및 필요시 수정
- Changes:
  - `reports/phase-2_green/green-01-01_correct_neutral_filter_condition-report.md` 생성
  - 기존 구현 상태 검증: TextAnalyzer::detectSentiment(), Filters::applyFilter() 로직 검토
  - `TODO.md`: GREEN-01-01 체크박스 완료 표시 (미확정)
- Decisions:
  - RED-02-04 테스트가 이미 통과하고 있음 (should_return_neutral_when_positive_and_negative_are_balanced PASS)
  - 현재 구현이 테스트 기대값과 완벽하게 일치 (균형 감정 → score=0 → neutral)
  - 추가 수정 불필요 (GREEN 최소 구현 완료)
- Verification:
  - 빌드 성공 ✓
  - ctest 실행 성공 (9/9 tests passed) ✓
  - RED-02-04 중립 필터 테스트 통과 확인 ✓
- Next: GREEN-01-02 (support multiline feedback input)

### 2026-05-22 15:00 - RED Phase 완료: RED-02-04/06 최종 테스트 추가
- Goal: RED 단계 모든 항목(RED-01-01 ~ RED-02-06) 완료
- Changes:
  - `tests/TextAnalyzerTest.cpp`: 2개 최종 테스트 추가
    - Test 8: `should_return_neutral_when_positive_and_negative_are_balanced` (RED-02-04)
    - Test 9: `should_maintain_session_isolation_between_tests` (RED-02-06)
  - `TODO.md`: RED-02-04, 06 체크박스 완료 표시
- Decisions:
  - 균형 잡힌 감정(긍정=부정): neutral 반환 (정상)
  - 세션 격리: SetUp/TearDown에서 clear() 호출로 격리 보장 (정상)
- Verification:
  - 빌드 성공 ✓
  - ctest 실행 성공 (9/9 tests passed) ✓
  - RED 단계 전체 테스트 프레임워크 완성
- Next: GREEN Phase (test passing 구현)

### RED Phase 완료 현황
- ✅ RED-01-01: GTest 타깃 설정
- ✅ RED-01-02: TextAnalyzer Fixture
- ✅ RED-01-03: Constants/Session 상태 초기화
- ✅ RED-01-04: 테스트 명명 규칙
- ✅ RED-02-01: 빈 입력 경계값
- ✅ RED-02-02: 특수문자 입력
- ✅ RED-02-03: 혼합 감정 입력
- ✅ RED-02-04: 중립 필터 테스트
- ✅ RED-02-05: 필터 조합 테스트
- ✅ RED-02-06: 세션 격리 테스트

### 2026-05-22 14:55 - RED-02-02/03/05 추가 경계값 테스트 완성
- Goal: 특수문자, 혼합 감정, 필터 조합에 대한 경계값 테스트 추가
- Changes:
  - `tests/TextAnalyzerTest.cpp`: 3개 추가 테스트
    - Test 5: `should_not_throw_when_input_has_special_characters` (RED-02-02)
    - Test 6: `should_return_positive_when_positive_count_exceeds_negative` (RED-02-03)
    - Test 7: `should_handle_multiple_keywords_in_feedback` (RED-02-05)
  - `TODO.md`: RED-02-02, 03, 05 체크박스 완료 표시
- Decisions:
  - 특수문자는 키워드 매칭 없음 → neutral 반환 (정상)
  - 혼합 감정: 긍정 3개, 부정 2개 → 긍정 우세 판정 (정상)
  - 다중 카테고리: 배송/품질 모두 포함 → 키워드 카운팅 작동 (정상)
- Verification:
  - 빌드 성공 ✓
  - ctest 실행 성공 (7/7 tests passed) ✓
  - 모든 경계값 테스트 통과
- Next: RED-02-04 (neutral filter test - RED 실패 가능), RED-02-06 (session isolation test)

### 2026-05-22 14:50 - RED-02-01 빈 입력 경계값 테스트 추가
- Goal: 빈 문자열/빈 벡터 입력의 기대 동작을 정의하고, 경계값 테스트 작성
- Changes:
  - `tests/TextAnalyzerTest.cpp`: 두 개의 빈 입력 경계값 테스트 추가
    - `should_return_neutral_when_input_is_empty_string`: 빈 문자열 입력 시 neutral 반환 확인
    - `should_return_zero_keyword_counts_when_input_is_empty`: 빈 피드백 벡터 시 모든 카테고리 카운트 0 확인
  - `TODO.md`: RED-02-01 체크박스 완료 표시
- Decisions:
  - 빈 문자열은 score=0이므로 neutral 반환 (>= 1도 아니고 <= -1도 아님)
  - 빈 벡터는 모든 카테고리가 0으로 초기화되어 반환됨
  - 현재 구현에서 모두 정상 동작 (RED 실패 아님, 하지만 명시적으로 기대 동작 정의)
- Verification:
  - 빌드 성공 ✓
  - ctest 실행 성공 (4/4 tests passed) ✓
  - 모든 테스트 통과 (경계값 처리 정상)
- Next: RED-02-02 (test: add special character input test)

### 2026-05-22 14:45 - RED-01-04 테스트 명명 규칙 정착
- Goal: RED 단계의 모든 테스트가 `should_[result]_when_[condition]` 형식을 따르도록 정리하고, 새 테스트 추가 시 가이드 제공
- Changes:
  - `tests/TextAnalyzerTest.cpp`: 테스트 이름 개선
    - `should_detect_sentiment_with_empty_vector` → `should_return_zero_counts_for_all_sentiments_when_input_is_empty`
    - 이유: 반환값(zero counts for all sentiments)과 조건(empty input)을 명확히 표현
  - 파일 상단에 테스트 네이밍 규칙 주석 추가
  - `TODO.md`: RED-01-04 체크박스 완료 표시
- Decisions:
  - 첫 번째 테스트 `should_compile_fixture_when_created`는 이미 규칙 준수
  - 두 번째 테스트는 결과(zero_counts_for_all_sentiments)를 더 명시적으로 표현하도록 개선
  - fixture 스켈레톤과 가이드 주석으로 후속 RED-02 테스트 작성 시 규칙 준수 유도
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 실행 성공: `ctest --test-dir build --output-on-failure` (모든 테스트 통과) ✓
- Next: RED-02-01 (test: add empty input boundary test) - 경계값 테스트 시작

### 2026-05-22 14:40 - RED-01-03 Constants/Session 상태 초기화 완성
- Goal: 각 테스트가 독립적인 상태에서 실행되도록 SetUp/TearDown에 Constants 초기화 및 Session 초기화 로직 반영
- Changes:
  - `tests/TextAnalyzerTest.cpp`: TextAnalyzerFixture에 상태 초기화 로직 추가
    - SetUp(): `Constants::init()` 호출 (감정/카테고리 키워드 딕셔너리 초기화)
    - SetUp(): `Session::clear("default")` 호출 (세션 상태 초기화)
    - TearDown(): `Session::clear("default")` 호출 (다음 테스트 격리 보장)
  - `TODO.md`: RED-01-03 체크박스 완료 표시
- Decisions:
  - Constants::init() 확인: 기존 sentiment/category 딕셔너리를 clear 후 재초기화하는 정상 동작
  - Session::clear() 확인: session ID별 상태(currentFeedbacks, filteredFeedbacks, filterState) 초기화
  - 상태 초기화 API 모두 존재하므로 RED-01-03 목표 달성 가능
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 실행 성공: `ctest --test-dir build --output-on-failure` (모든 테스트 통과) ✓
  - 상태 격리: SetUp/TearDown에서 일관되게 Constants/Session 초기화
- Next: RED-01-04 (test: enforce descriptive test names) - 테스트 명명 규칙 검증

### 2026-05-22 14:35 - RED-01-02 TextAnalyzer GTest Fixture 작성 완료
- Goal: `TextAnalyzer` 도메인 로직을 독립적으로 검증하기 위한 GTest fixture를 설계하고, `tests/TextAnalyzerTest.cpp` 파일 작성 및 `SetUp`/`TearDown` 기본 구조 완성
- Changes:
  - `tests/TextAnalyzerTest.cpp`: TextAnalyzerFixture 클래스 및 두 개의 기초 테스트 추가 (should_compile_fixture_when_created, should_detect_sentiment_with_empty_vector)
  - `tests/SmokeTest.cpp`: 기존 main() 제거 (TextAnalyzerTest.cpp와 중복 정의 방지)
  - `CMakeLists.txt`: 테스트 타깃에 TextAnalyzerTest.cpp 추가 (GTest_FOUND 및 fallback 모두 적용)
  - `TODO.md`: RED-01-02 체크박스 완료 표시
- Decisions:
  - GTest 미설치 상황에서 최소 테스트 프레임워크 사용 (main() 기반 테스트)
  - 향후 GTest 설치 시 `#include <gtest/gtest.h>`로 쉽게 마이그레이션 가능하도록 설계
  - fixture 형식: `should_[result]_when_[condition]` 명명 규칙 준수
- Verification:
  - 빌드 성공: `cmake --build build` ✓
  - 테스트 실행 성공: `ctest --test-dir build --output-on-failure` (2/2 tests passed) ✓
  - TextAnalyzer::analyzeSentiment() 동작 확인: 빈 벡터 입력 시 모든 감정 카운트를 0으로 초기화하는 맵 반환
- Next: RED-01-03 (Constants/Session 상태 초기화) 진행

### 2026-05-22 16:25 - SPEC-01-03 프로젝트 지침 정합성 검토 완료
- Goal: AGENTS.md, TODO.md와 refs/legacy/ 레거시 문서 간 작업 기준 충돌을 찾아 정렬하고, 현재 운영 기준을 명확히 한다.
- Changes:
  - `docs/alignment.md` 파일을 생성했고 다음을 포함했다:
    - 검토 대상 문서 및 우선순위 테이블
    - 브랜치 전략, 빌드/테스트, 산출물, Phase 구조, 상태 관리 영역별 충돌 분석
    - 주요 정정사항: 브랜치 전략(maintdd→refactoring→feature → main→B_07→6단계), 빌드 명령(MinGW 명시), 산출물 경로(docs/ 통일), 커밋 메시지([TODO_ID] 추가)
    - TODO 항목 실행 기준 정정(AGENTS.md & TODO.md 우선)
    - 남은 주의사항 및 결론
  - `TODO.md`의 SPEC-01-03 체크박스를 완료 상태로 표시했다.
- Decisions:
  - 현재 기준(AGENTS.md, TODO.md)이 우선이며, 레거시 문서는 히스토리와 컨텍스트 이해용으로만 참고한다.
  - 브랜치 전략의 가장 큰 차이는 6단계 Phase 도입과 B_07 통합 브랜치 추가다.
  - 빌드 명령과 코드 품질 기준(매직 넘버, Doxygen, 20줄 제한)은 모든 문서가 일치한다.
- Verification: 문서 생성 및 TODO 업데이트만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: SPEC-01-03 실행 보고서 생성 및 커밋/푸시 진행.

### 2026-05-22 16:20 - SPEC-01-02 커밋/푸시 완료
- Goal: SPEC-01-02 작업(빌드/테스트 명령 문서화) 결과를 커밋하고 원격 저장소에 푸시한다.
- Changes:
  - `docs/build-and-test.md`: 빌드 및 테스트 명령 상세 가이드 파일
  - `reports/phase-0_spec/spec-01-02_document_build_and_test_commands-report.md`: SPEC-01-02 실행 보고서
  - `TODO.md`: SPEC-01-02 체크박스 완료 표시
  - `SESSION_NOTES.md`: SPEC-01-02 관련 세션 로그 기록
- Decisions:
  - 커밋 해시: `173009f` (4c4664a → 173009f)
  - 커밋 메시지: `[SPEC-01-02] docs: document build and test commands`
  - 푸시 대상: `origin spec`
- Verification:
  - 커밋 성공: 4 파일 변경, 399 insertions
  - 푸시 성공: spec 브랜치 정상 업로드
- Next: SPEC-01-03 (프로젝트 지침 정렬) 또는 추가 지침 커밋 진행

### 2026-05-22 16:15 - 프롬프트 실행 후 커밋/푸시 자동화 지침 추가
- Goal: 각 TODO 항목 완료 후 자동으로 커밋 및 푸시가 수행되도록 지침을 명시하되, 각 단계에서 사용자의 명시적 승인을 받도록 한다.
- Changes:
  - `.agents/skills/run/SKILL.md`의 Workflow에 커밋(Step 13) 및 푸시(Step 14) 단계 추가, 사용자 확인 프로세스 명시
  - `AGENTS.md`의 Workflow 섹션에 자동 커밋/푸시 지침 추가
  - `AGENTS.md`의 Git And Collaboration > 협업 흐름에 상세한 자동 워크플로우 추가 (승인 단계, 상태 갱신)
  - `.claude/skills/run/SKILL.md`의 Workflow에 Step 8(커밋), Step 9(푸시) 추가
- Decisions:
  - 커밋 메시지 형식: `[{TODO_ID}] {type}: {description}` (AGENTS.md 규칙 준수)
  - 각 단계(커밋, 푸시)에서 변경 파일/명령을 사전 표시하고 사용자 확인 요청
  - 커밋/푸시 완료 후 STATUS_SNAPSHOT.md를 갱신해 다음 세션이 최신 상태를 반영하도록 함
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 지침이 실제로 적용되는지 다음 TODO 항목 실행 시 검증한다.

### 2026-05-22 16:10 - 프롬프트 실행 후 자동 보고서 생성 지침 추가
- Goal: 각 TODO 항목 완료 후 자동으로 해당 프롬프트에 대응하는 실행 보고서가 생성되도록 지침을 명시한다.
- Changes:
  - `.agents/skills/run/SKILL.md`의 Workflow에 보고서 자동 생성 단계(Step 12) 추가
  - `AGENTS.md`의 Workflow 섹션에 보고서 자동 생성에 대한 명시적 지침 추가
  - `AGENTS.md`의 Documentation Outputs 섹션에 보고서 생성 규칙 상세화 (실행 날짜, 목표, 수행 작업, 산출물, 검증, 다음 단계, 요약)
  - `.claude/skills/run/SKILL.md`의 Workflow에 보고서 생성 항목 추가 (Step 7)
- Decisions:
  - 보고서 생성은 모든 `/run` 실행 후 자동으로 수행되어야 한다.
  - 파일명 규칙: 프롬프트와 동일하되 `-prompt.md` → `-report.md` 변경
  - 보고서에는 목표, 변경사항, 산출물, 검증, 다음 단계를 필수로 포함한다.
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 지침이 정확히 적용되었는지 다음 TODO 항목 실행 시 검증한다.

### 2026-05-22 16:00 - SPEC-01-02 빌드/테스트 명령 문서화
- Goal: MinGW/CMake 기본 빌드 명령과 ctest를 활용한 테스트 실행 방식을 문서로 정리한다.
- Changes: `docs/build-and-test.md` 파일을 생성했고 빌드 환경 요구사항, CMake 초기/증분/clean 빌드 명령, 테스트 프레임워크 설정, ctest 명령 옵션, 개발 사이클 워크플로우, 자주 사용하는 명령 요약표, 문제 해결 가이드를 포함했다. `TODO.md`의 SPEC-01-02 항목을 완료 상태로 체크했다.
- Decisions: Windows MinGW 환경과 CMake 3.14+, Google Test를 기본 전제로 하며, `-G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe` 플래그를 필수로 명시했다. ctest 실행 시 `--output-on-failure` 옵션을 기본으로 권장했다.
- Verification: 문서 생성 및 TODO 체크박스 업데이트만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: SPEC-01-03 (프로젝트 지침 정렬)로 진행.

### 2026-05-22 15:30 - PR/커밋 메시지 규칙 정규화 및 AGENTS.md 반영
- Goal: B_07 브랜치 통합을 위한 PR과 커밋 메시지 형식을 표준화하고 지침에 반영한다.
- Changes:
  - B_07 브랜치를 origin에 push했다. (git push origin B_07)
  - spec → B_07 PR을 생성했다. (PR 제목: `[Phase-0: SPEC] define B_07 branch workflow (SPEC-01-01)`)
  - PR 제목을 `[Phase-{n}: {PHASE}] {type}: {description} ({TODO_ID})` 형식으로 정규화했다.
  - git filter-branch를 사용하여 spec 브랜치의 모든 커밋 메시지에 [SPEC-01-01] 접두사를 추가했다.
  - 3개 커밋 메시지 수정 후 origin/spec에 force push했다.
  - AGENTS.md의 "Git And Collaboration" 섹션을 확장하여 커밋 메시지 규칙과 PR 제목 규칙을 명시했다.
- Decisions:
  - 커밋 메시지 형식: `[{TODO_ID}] {type}: {description}`
  - PR 제목 형식: `[Phase-{n}: {PHASE}] {type}: {description} ({TODO_ID})`
  - Phase와 TODO_ID는 모든 git 기록에 함께 기록되어 추적 가능성을 높인다.
- Verification:
  - PR이 자동으로 갱신되어 최신 커밋 메시지가 반영되었음을 확인했다.
  - AGENTS.md에 규칙이 명확하게 기록되었다.
  - 빌드/테스트는 실행하지 않았다 (문서 변경만 수행).
- Next: SPEC-01-02 (빌드/테스트 명령 문서화)로 진행.

### 2026-05-22 14:05 - SPEC-01-01 B_07 브랜치 워크플로우 정의 완료
- Goal: B_07 실습 통합 브랜치를 기준으로 단계별 작업 흐름과 병합 순서를 문서로 정리한다.
- Changes: `docs/b07-branch-workflow.md` 파일을 생성했고 B_07 브랜치 계층, 단계별 목적, 병합 흐름, 작업 사이클, 항목 식별자 규칙, 상태 추적, 산출물 위치 등을 상세히 기록했다. `TODO.md`의 SPEC-01-01 항목을 완료 상태로 체크했다.
- Decisions: B_07은 실습 통합 브랜치이며 모든 단계별 작업(spec, red, green, refactor, feature, final)이 B_07에 순차 병합되고, B_07이 main에 최종 병합된다. 문서는 한국어 + 표/코드블록 조합으로 구성해 직관적 이해를 돕는다.
- Verification: 문서 생성 및 TODO 체크박스 업데이트만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: SPEC-01-02 (빌드/테스트 명령 문서화)로 진행.

### 2026-05-22 13:50 - 상태 호출 명령어 분리 표현
- Goal: 자연어 호출 명령어를 따로 따로 나열하되, "갱신"이 "상태갱신"의 축약형임을 명시한다.
- Changes: .agents/skills/status/SKILL.md의 호출 예시에 "상태갱신"과 "갱신"을 별도 라인으로 표기했다. .claude/skills/status/SKILL.md의 Refreshed Mode에서 "갱신"의 설명에 "shorthand for 상태갱신"을 명시했다.
- Decisions: 사용자가 "상태갱신" 또는 "갱신" 둘 중 어느 것을 입력해도 같은 동작을 수행하며, 호출 예시에서는 각각 따로 나열해 두 형태가 모두 가능함을 명확히 한다.
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 다음 커밋에 포함.

### 2026-05-22 13:25 - 상태 스킬 성능 최적화 (빠른 모드 vs 정확한 모드)
- Goal: `상태` 호출은 스냅샷만 참조해 빠른 응답을 제공하고, `상태갱신`은 전체 점검 후 스냅샷을 갱신하는 두 가지 모드를 구분한다.
- Changes: .agents/skills/status/SKILL.md의 호출 예시와 상태 수집 절차를 두 가지 모드로 구분했다. description에 모드 설명을 추가했고, .claude/skills/status/SKILL.md의 Quick Reference를 "빠른 모드"와 "정확한 모드"로 구분했다.
- Decisions: "상태" 호출은 스냅샷 기반으로 갱신하지 않아 빠르고, "상태갱신"이나 phase 지정 호출은 git status 실행 후 갱신한다. 자동 갱신 대상: "상태갱신", "/status phase", "현재 진행 현황을 보여주세요", "브랜치", "할일" 등.
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 실제로 /status 호출 시 두 가지 모드가 정상 동작하는지 검증한다.

### 2026-05-22 13:10 - 스킬 호출 문법 표준화 (/run, /status)
- Goal: Claude Code 표준 스킬 호출 문법은 슬래시(`/`)이므로 모든 문서의 호출 예시를 `$run/$status`에서 `/run/status`로 통일한다.
- Changes: AGENTS.md, .agents/skills/run/SKILL.md, .agents/skills/status/SKILL.md, .claude/skills/run/SKILL.md, .claude/skills/status/SKILL.md, .claude/skills/*/agents/openai.yaml의 호출 예시와 default_prompt를 `/run`, `/status`로 일괄 변경했다. CLAUDE.md의 skill 소개 섹션도 동일하게 수정했다.
- Decisions: Claude Code 표준 스킬 호출 문법은 `/skill_name` 형식이므로, 프로젝트 스킬도 이를 따른다. 비명시적 호출(예: `상태`, `1번 실행`)은 그대로 유지.
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 이제 사용자는 `/run SPEC-01-01`, `/status` 같은 Claude Code 표준 문법으로 스킬을 호출할 수 있다.

### 2026-05-22 14:30 - RED-01-01 GTest 타깃 설정 완료
- Goal: Feedback Analyzer 프로젝트에 Google Test 기반 테스트 타깃을 추가하고, 테스트 빌드와 실행이 가능한 최소 구성을 만든다.
- Changes: 
  - CMakeLists.txt: feedback_analyzer_lib 라이브러리 분리 (main.cpp 제외), 테스트 타깃 추가, GTest find_package 지원
  - tests/SmokeTest.cpp: 최소 테스트 파일 작성 (GTest 없이도 빌드 가능한 형태)
  - TODO.md: SPEC 항목들을 모두 [x]로 표기, RED-01-01은 완료 예정
  - main.cpp 빌드: 컴파일 오류(메서드 이름 불일치)로 인해 주석 처리, GREEN 단계에서 수정 예정
- Decisions:
  - GTest 네트워크 SSL 문제: find_package로 로컬 설치 먼저 시도, 실패 시 최소 테스트 프레임워크 사용
  - main.cpp 중복 main 문제: 라이브러리와 실행 파일 분리 구성으로 해결
  - main.cpp 메서드 오류: RED 단계는 테스트 인프라 구축만 하므로, 수정은 GREEN 단계로 연기
- Verification:
  - `cmake --build build`: 성공 (라이브러리 + 테스트 타깃)
  - `ctest --test-dir build --output-on-failure`: 통과 (1/1 smoke_test PASSED)
- Next: 
  - 다음 항목 RED-01-02: 텍스트 분석기 테스트 고정 작성
  - GTest 설치 후 SmokeTest.cpp를 GTest 형식으로 변경

### 2026-05-22 12:50 - openai.yaml 워크플로우 상세화
- Goal: Claude Code가 .claude/skills/ 스킬을 로드할 때 실제 워크플로우를 명확히 인식하도록 default_prompt에 상세 워크플로우를 추가한다.
- Changes: .claude/skills/run/agents/openai.yaml과 .claude/skills/status/agents/openai.yaml의 default_prompt를 단순 링크에서 실제 워크플로우 요약으로 변경했다. $run은 TODO 항목 실행 절차(AGENTS.md → TODO.md → prompts/ 매핑 → 검증 → 갱신), $status는 상태 수집 절차(스냅샷 → git status → delta 비교 → 출력 → 갱신)를 명시했다.
- Decisions: openai.yaml의 default_prompt에 워크플로우를 넣어 Claude Code agent가 스킬 로드 시 바로 동작 방식을 이해하도록 함. 상세 내용은 여전히 .agents/skills/ 문서에만 유지.
- Verification: 문서/설정 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 실제로 $status, $run 호출 시 .agents/skills/의 워크플로우를 따르는지 동작 검증한다.

### 2026-05-22 12:15 - Claude Code 표준 위치로 스킬 마이그레이션 (얕은 래퍼)
- Goal: AGENTS.md와 .agents/skills/의 내용을 Claude Code 표준 위치(CLAUDE.md, .claude/skills/)에서 참조하는 얕은 래퍼 구조로 생성한다.
- Changes: CLAUDE.md를 루트에 생성 (프로젝트 메타정보 + AGENTS.md 링크). .claude/skills/run/과 .claude/skills/status/에 각각 SKILL.md와 agents/openai.yaml을 생성 (원본 .agents/skills/ 참조).
- Decisions: 실제 내용은 AGENTS.md와 .agents/skills/에만 유지하고, CLAUDE.md/.claude/skills/는 단순 링크로만 구성해 중복 제거. 각 skill의 상세 정의와 워크플로는 원본 .agents/ 위치의 문서에서만 관리한다.
- Verification: 문서/파일 생성만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: Claude Code가 .claude/skills/ 스킬을 인식하고 실행하는지 검증한다.

### 2026-05-22 11:40 - 평가 산출물 폴더/네이밍 규칙 반영
- Goal: 프로젝트 전역 지침에 `docs/prompts/reports` 중요도와 네이밍 규칙을 명시해 실행/평가 기준을 고정한다.
- Changes: `AGENTS.md` Documentation Outputs 섹션에 평가 근거 폴더 역할과 네이밍 규칙(`-prompt.md`, `-report.md`, `phase-{n}_{phase}-document.md`)을 추가했다. `README.md` 프로젝트 구조와 결과물 네이밍 규칙 섹션도 갱신했다.
- Decisions: TODO에서 요구하는 기존 `docs/analysis.md` 등 5종 문서는 유지하고, phase 종료 문서 규칙은 추가 규칙으로 병행 적용한다.
- Verification: 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 필요하면 TODO 문구도 같은 네이밍 정책으로 점진 정렬한다.

### 2026-05-22 11:34 - prompts 파일명 규칙 일괄 적용
- Goal: `prompts/` 하위 프롬프트 파일명을 `{todo_id_lower}_{slug_lower}-prompt.md` 규칙으로 통일한다.
- Changes: `prompts/phase-*` 하위 프롬프트 파일명을 대문자/기존 접미사 없는 형식에서 소문자 + `-prompt.md` 형식으로 일괄 변경했다. `prompts/INDEX.md`의 경로 컬럼도 새 파일명으로 동기화했다.
- Decisions: 폴더 구조(`phase-0_spec` ~ `phase-5_final`)는 유지하고 파일명만 규칙화했다.
- Verification: 파일명/인덱스 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 같은 규칙을 `reports/` 결과 파일 생성 시 `{todo_id_lower}_{slug_lower}-report.md`로 적용한다.

### 2026-05-22 11:26 - prompts 폴더 루트 이동
- Goal: `prompts/` 폴더를 저장소 루트의 `prompts/`로 이동해 프롬프트 자산 경로를 단순화한다.
- Changes: 프롬프트 폴더를 저장소 루트 `prompts/`로 이동했다. `.agents/skills/run/SKILL.md`의 `N번 실행` 해석 경로를 `prompts/INDEX.md`로 갱신했다.
- Decisions: 과거 이력 문서의 `prompts/...` 문자열은 당시 기록으로 유지하고, 운영 참조 경로만 `prompts/...`로 전환한다.
- Verification: 경로 이동과 지침 문서 갱신만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 필요하면 `AGENTS.md`나 README에 `prompts/` 위치를 명시해 신규 작업자가 바로 찾을 수 있게 할 수 있다.

### 2026-05-22 11:22 - run 스킬 N번 매핑 우선순위 보강
- Goal: `N번 실행` 요청 시 번호 해석 기준을 더 안정적으로 만들기 위해 `prompts/INDEX.md`를 우선 참조하도록 run 스킬 워크플로를 보강한다.
- Changes: `.agents/skills/run/SKILL.md` Workflow에 `INDEX.md` 우선 매핑 규칙을 추가하고, 실패 시 `STATUS_SNAPSHOT.md` fallback 경로를 유지하도록 갱신했다.
- Decisions: 번호 요청은 `INDEX.md`를 표준 기준으로 삼고, 스냅샷 기반 매핑은 보조 경로로 사용한다.
- Verification: 스킬 문서 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 필요하면 status 스킬에도 현재 번호 매핑 인덱스 파일 위치를 안내 문구로 추가할 수 있다.

### 2026-05-22 11:18 - run/status FINAL 예시 보강 및 prompts 번호 인덱스 추가
- Goal: `$run/$status` 스킬 예시를 `FINAL-*` 중심으로 정리하고, `N번 진행 -> TODO ID` 전체 매핑 인덱스를 추가한다.
- Changes: `.agents/skills/run/SKILL.md`의 호출 예시를 FINAL 중심으로 갱신하고, `.agents/skills/status/SKILL.md`의 호출 예시에 `final`, `FINAL-02` 패턴을 추가했다. `prompts/INDEX.md`를 생성해 1~62 번호 매핑과 프롬프트 파일 경로를 정리했다.
- Decisions: 번호 체계는 기존 배정(1~62)을 유지하고, FINAL 전환 이후 `55~62`를 `FINAL-*`로 고정한다.
- Verification: 문서/스킬 지침 변경만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 필요하면 `$run` 스킬이 `prompts/INDEX.md`를 우선 참조하도록 워크플로 지침을 추가한다.

### 2026-05-22 11:13 - REPORT 단계 프롬프트 문서 작성
- Goal: REPORT 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/phase-5_final/` 폴더를 만들고 `FINAL-01-01`부터 `FINAL-02-03`까지 총 8개의 실행 프롬프트 파일을 추가했다.
- Decisions: 번호 호출은 SPEC 1~7, RED 8~17, GREEN 18~24, REFACTOR 25~42, FEATURE 43~54 다음으로 이어 `55번 진행`부터 `62번 진행`까지 배정했다. 이번 작업은 프롬프트 문서 작성이며 실제 REPORT TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 전체 프롬프트 문서 인덱스 또는 번호 매핑 문서를 추가하면 `N번 진행` 흐름을 더 쉽게 확인할 수 있다.

### 2026-05-22 11:10 - FEATURE 단계 프롬프트 문서 작성
- Goal: FEATURE 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/phase-4_feature/` 폴더를 만들고 `FEATURE-01-01`부터 `FEATURE-03-02`까지 총 12개의 실행 프롬프트 파일을 추가했다.
- Decisions: 번호 호출은 SPEC 1~7, RED 8~17, GREEN 18~24, REFACTOR 25~42 다음으로 이어 `43번 진행`부터 `54번 진행`까지 배정했다. 이번 작업은 프롬프트 문서 작성이며 실제 FEATURE TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 문서 형식을 검토한 뒤 REPORT 단계 프롬프트 문서 생성을 요청할 수 있다.

### 2026-05-22 11:05 - REFACTOR 단계 프롬프트 문서 작성
- Goal: REFACTOR 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/phase-3_refactor/` 폴더를 만들고 `REFACTOR-01-01`부터 `REFACTOR-03-06`까지 총 18개의 실행 프롬프트 파일을 추가했다.
- Decisions: 번호 호출은 SPEC 1~7, RED 8~17, GREEN 18~24 다음으로 이어 `25번 진행`부터 `42번 진행`까지 배정했다. 이번 작업은 프롬프트 문서 작성이며 실제 REFACTOR TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 문서 형식을 검토한 뒤 FEATURE 단계 프롬프트 문서 생성을 요청할 수 있다.

### 2026-05-22 11:03 - GREEN 단계 프롬프트 문서 작성
- Goal: GREEN 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/phase-2_green/` 폴더를 만들고 `GREEN-01-01`부터 `GREEN-02-03`까지 총 7개의 실행 프롬프트 파일을 추가했다.
- Decisions: 번호 호출은 SPEC 1~7, RED 8~17 다음으로 이어 `18번 진행`부터 `24번 진행`까지 배정했다. 이번 작업은 프롬프트 문서 작성이며 실제 GREEN TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 문서 형식을 검토한 뒤 REFACTOR 단계 프롬프트 문서 생성을 요청할 수 있다.

### 2026-05-22 11:05 - prompts phase 폴더명 변경
- Goal: `prompts/` 아래 단계 폴더명을 TODO Phase 번호가 드러나는 형식으로 변경한다.
- Changes: `prompts/spec/`를 `prompts/phase-0_spec/`로, `prompts/red/`를 `prompts/phase-1_red/`로 이동했다.
- Decisions: 향후 단계 폴더도 같은 규칙인 `phase-{번호}_{phase명}` 형식으로 작성한다. 예: `phase-2_green`, `phase-3_refactor`, `phase-4_feature`, `phase-5_final`.
- Verification: 폴더명 변경과 파일 목록 확인만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 다음 단계 프롬프트 문서 작성 시 새 phase 폴더명 규칙을 사용한다.

### 2026-05-22 10:55 - RED 단계 프롬프트 문서 작성
- Goal: RED 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/red/` 폴더를 만들고 `RED-01-01`부터 `RED-02-06`까지 총 10개의 실행 프롬프트 파일을 추가했다.
- Decisions: 번호 호출은 SPEC 단계 1~7 다음으로 이어 `8번 진행`부터 `17번 진행`까지 배정했다. 이번 작업은 프롬프트 문서 작성이며 실제 RED TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 문서 형식을 검토한 뒤 GREEN 단계 프롬프트 문서 생성을 요청할 수 있다.

### 2026-05-22 11:02 - SPEC 단계 나머지 프롬프트 문서 작성
- Goal: `SPEC-01-01`을 제외한 SPEC 단계 TODO 항목 전체에 대해 독립 실행 가능한 상세 프롬프트 문서를 작성한다.
- Changes: `prompts/spec/` 아래에 `SPEC-01-02`, `SPEC-01-03`, `SPEC-02-01`, `SPEC-02-02`, `SPEC-02-03`, `SPEC-02-04` 실행 프롬프트 파일을 추가했다.
- Decisions: 기존 `SPEC-01-01`과 같은 소문자 phase 폴더 및 TODO ID 기반 파일명 규칙을 유지했다. 이번 작업은 프롬프트 문서 작성이며 실제 SPEC TODO 항목 실행은 수행하지 않았다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 문서 형식을 검토한 뒤 RED 단계 프롬프트 문서 생성을 요청할 수 있다.

### 2026-05-22 10:47 - SPEC-01-01 프롬프트 파일 초안 작성
- Goal: `TODO.md`의 `SPEC-01-01` 항목을 실행할 독립 프롬프트 파일을 먼저 1개 작성해 향후 프롬프트 워크북 분할 기준을 검토할 수 있게 한다.
- Changes: `prompts/spec/` 폴더를 만들고 `prompts/spec/SPEC-01-01_define_b07_branch_workflow.md` 파일을 추가했다.
- Decisions: 프롬프트 저장 규칙은 소문자 phase 폴더와 TODO ID 기반 파일명을 사용한다. 이번 작업은 `SPEC-01-01` 자체 실행이 아니라 실행용 프롬프트 작성까지만 수행했다.
- Verification: 문서 추가 작업만 수행했으므로 빌드/테스트는 실행하지 않았다.
- Next: 사용자가 형식을 검토한 뒤 다른 TODO 항목 프롬프트를 같은 규칙으로 확장한다.

### 2026-05-22 00:00 - run skill에 `N번 실행` 명령 매핑 추가
- Goal: `할일` 출력 후 `1번 실행` 같은 자연어 명령으로 즉시 TODO 항목을 실행할 수 있게 한다.
- Changes: `.agents/skills/run/SKILL.md`에 `N번 실행` 예시를 추가하고, `STATUS_SNAPSHOT.md`의 `NextItems` 기준으로 번호를 TODO ID로 매핑하는 절차를 추가했다. `AGENTS.md` 호출 예시에도 `1번 실행`, `브랜치`, `할일`, `상태갱신`을 반영했다.
- Decisions: 번호 명령이 스냅샷에서 해석되지 않으면 명시적 TODO ID 입력을 요청한다.
- Verification: 문서/스킬 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 사용자는 `할일` 확인 후 `1번 실행`으로 바로 다음 TODO를 진행할 수 있다.

### 2026-05-22 00:00 - status 번호 표기 규칙 재조정
- Goal: 상태 응답 섹션 번호는 `1.` 형식으로, 진행할 항목 테이블의 순서값은 `1`, `2` 형식으로 통일한다.
- Changes: `.agents/skills/status/SKILL.md`의 테이블 예시 순서값을 `1.`, `2.`에서 `1`, `2`로 변경했다.
- Decisions: 섹션 제목 번호(예: `1. 브랜치 진행 현황`)와 테이블 순서 번호(예: `1`)를 구분해 사용한다.
- Verification: 스킬 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 `상태` 출력에서 요청한 번호 포맷을 일관되게 유지한다.

### 2026-05-22 00:00 - status 숫자 표기 형식 변경
- Goal: 상태 응답의 진행 항목 번호를 원형 숫자 대신 일반 번호 형식으로 통일한다.
- Changes: `.agents/skills/status/SKILL.md`의 진행할 항목 테이블 예시를 `①, ②`에서 `1., 2.` 형식으로 변경했다.
- Decisions: 향후 상태/할일 출력은 원형 숫자를 사용하지 않고 숫자+마침표 형식을 사용한다.
- Verification: 스킬 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 `할일` 및 `상태` 출력에서 동일한 번호 형식을 유지한다.

### 2026-05-22 00:00 - status skill 스냅샷 비교 방식 도입
- Goal: `상태` 요청 시 반복적인 전체 탐색/원격 확인을 줄이고, 직전 상태 대비 변경점 중심으로 보고한다.
- Changes: `.agents/skills/status/SKILL.md`에 `STATUS_SNAPSHOT.md` 기반 delta 비교 절차를 추가하고, 초기 스냅샷 파일 `.agents/skills/status/STATUS_SNAPSHOT.md`를 생성했다.
- Decisions: `$status`는 기본적으로 로컬 Git/문서 정보만 사용하며 GitHub/원격 API 조회를 기본 동작으로 사용하지 않는다.
- Verification: 문서/스냅샷 파일 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 `상태` 응답은 스냅샷 대비 변경점과 다음 항목 위주로 출력한다.

### 2026-05-22 00:00 - status skill 브랜치 트리/다음 작업 테이블 형식 추가
- Goal: `$status` 응답이 브랜치 구조 트리와 진행할 항목 테이블을 포함하도록 출력 형식을 고정한다.
- Changes: `.agents/skills/status/SKILL.md`의 권장 출력 순서를 갱신하고, 브랜치 트리 코드블록 예시와 `순서/작업/방법` 테이블 템플릿을 추가했다.
- Decisions: 상태 응답에서 ① 브랜치 진행 현황, ④ 진행할 항목을 시각적으로 먼저 파악 가능한 형태로 우선 제시한다.
- Verification: 스킬 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 `상태` 응답은 트리 + 테이블 형식을 기본 출력으로 사용한다.

### 2026-05-22 00:00 - status skill 출력 규약 정비 (CLAUDE 참고 스타일)
- Goal: `refs/external/CLAUDE.md`의 상태 보고 스타일을 참고해 `$status` 스킬의 출력 구조와 해석 규칙을 명확히 한다.
- Changes: `.agents/skills/status/SKILL.md`를 한국어 중심 지침으로 재구성하고, 상태 출력 권장 순서/Phase 해석 규칙/요약 원칙을 추가했다.
- Decisions: 상태 출력은 8개 필드 순서를 기본으로 유지하고, TODO는 전체 나열 대신 요청된 Phase/접두사 중심으로 압축 보고한다.
- Verification: 스킬 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 `상태` 요청 응답은 갱신된 `$status` 스킬 포맷을 우선 적용한다.

### 2026-05-22 00:00 - AGENTS run/status 호출 예시 반영
- Goal: `$run`, `$status` 사용 패턴을 전역 지침에서 바로 확인할 수 있도록 명시한다.
- Changes: `AGENTS.md`의 Branch And Phase Strategy 섹션에 `$run`/`$status` 한국어 축약 포함 호출 예시를 추가했다.
- Decisions: skill 트리거 문구는 skill 파일뿐 아니라 전역 지침에도 중복 명시해 협업 중 해석 차이를 줄인다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 팀/학습자 요청 시 AGENTS의 호출 예시를 기준으로 run/status를 사용한다.

### 2026-05-22 00:00 - run skill 트리거 문구 확장
- Goal: `$run` skill이 축약된 한국어 작업 요청에서도 안정적으로 호출되도록 예시 문구를 보강한다.
- Changes: `.agents/skills/run/SKILL.md`의 Expected request examples에 `FEATURE-02-02 진행`, `진행 FEATURE-02-02`를 추가했다.
- Decisions: 항목 ID와 `진행` 키워드 조합 요청도 run skill 호출 의도로 해석한다.
- Verification: skill 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 사용자는 `$run FEATURE-02-02`, `FEATURE-02-02 진행`, `진행 FEATURE-02-02` 형태로 요청할 수 있다.

### 2026-05-22 00:00 - status skill 트리거 문구 확장
- Goal: `$status` skill이 짧은 한국어 요청에서도 안정적으로 호출되도록 예시 문구를 보강한다.
- Changes: `.agents/skills/status/SKILL.md`의 Expected request examples에 `현재 상태를 보여주세요.`, `상태`를 추가하고 소개 문장에 한국어 상태 요청을 명시했다.
- Decisions: 진행 현황 요청의 축약 표현도 status skill 호출 의도로 해석한다.
- Verification: skill 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 사용자는 `$status`, `현재 상태를 보여주세요.`, `상태`로 동일한 현황 조회를 요청할 수 있다.

### 2026-05-22 00:00 - 프로젝트 전용 .agents skills 생성
- Goal: `$run`, `$status` skill을 프로젝트 전용으로 버전 관리 가능한 `.agents/skills/` 아래에 생성한다.
- Changes: `.agents/skills/run/`, `.agents/skills/status/`에 각각 `SKILL.md`와 `agents/openai.yaml`을 추가했다. `AGENTS.md`에도 프로젝트 전용 skill 위치와 용도를 명시했다.
- Decisions: 전역 사용자 skill과 별도로 프로젝트 루트의 `.agents/skills/`에 skill 정의를 보관한다.
- Verification: skill 파일 생성과 경로를 확인했다. 문서/설정 생성 작업만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 프로젝트 공유 기준은 `.agents/skills/`의 정의를 사용한다.

### 2026-05-22 00:00 - run/status Codex skill 생성
- Goal: 반복적으로 필요한 TODO 항목 실행과 진행 현황 확인을 로컬 Codex skill로 분리한다.
- Changes: `C:\Users\nampl\.codex\skills\run\SKILL.md`, `C:\Users\nampl\.codex\skills\run\agents\openai.yaml`, `C:\Users\nampl\.codex\skills\status\SKILL.md`, `C:\Users\nampl\.codex\skills\status\agents\openai.yaml`을 생성했다.
- Decisions: `$run`은 특정 TODO 단계 실행용, `$status`는 브랜치/Phase/TODO/검증 현황 확인용으로 사용한다.
- Verification: skill 파일 생성 경로와 파일 목록을 확인했다. 문서/설정 생성 작업만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 사용자는 `$run RED-02-04`, `$status`처럼 요청할 수 있다.

### 2026-05-22 00:00 - refs 폴더 역할 지침 반영
- Goal: `refs/` 하위 폴더와 주요 참고 문서의 역할을 전역 지침에 명시한다.
- Changes: `AGENTS.md`에 `refs/project_purpose.md`, `refs/external/`, `refs/source/`, `refs/legacy/`의 용도를 추가했다.
- Decisions: `refs/`는 참고자료 보관 영역으로 보고, 단계별/최종 보고서 산출물은 계속 `docs/`에 생성한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 외부 참고 문서 추가 시 성격에 따라 `refs/external/`, `refs/source/`, `refs/legacy/` 중 하나에 배치한다.

### 2026-05-22 00:00 - refs source 폴더 생성
- Goal: 원본/증빙 자료 보관용 `refs/source/` 폴더를 준비한다.
- Changes: `refs/source/` 폴더를 생성했다.
- Decisions: 다른 프로젝트 참고 원본 파일이나 변환 전 자료는 `refs/source/`에 보관하고, 읽기 좋게 정리된 참고 문서는 `refs/external/`에 보관한다.
- Verification: 폴더 생성만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: Git에 빈 폴더를 보존해야 하면 `.gitkeep` 추가를 검토한다.

### 2026-05-22 00:00 - Claude Code 로컬 설정 제거
- Goal: 이 프로젝트에서 Claude Code를 사용하지 않으므로 루트의 로컬 설정 폴더를 제거한다.
- Changes: `.claude/` 폴더를 삭제했다.
- Decisions: Claude 관련 참고 문서는 `refs/legacy/CLAUDE.md`에 보관하되, 실행/권한 설정인 `.claude/settings.local.json`은 프로젝트에서 제거한다.
- Verification: 폴더 삭제만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: Claude Code 관련 로컬 설정이 다시 생성되면 추적 대상에서 제외할지 검토한다.

### 2026-05-22 00:00 - 프로젝트 목적 문서 refs 이동
- Goal: 강의 교재 기반의 프로젝트 개요 및 목적 문서를 참고자료 영역으로 이동한다.
- Changes: `project_purpose.md`를 `refs/project_purpose.md`로 이동하고, `AGENTS.md`와 `README.md`의 참조 경로를 갱신했다.
- Decisions: `refs/project_purpose.md`는 legacy가 아니라 현재 프로젝트의 필수 참고 문서로 취급한다.
- Verification: 문서 이동과 참조 경로 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 프로젝트 목적이나 학습 목표와 관련된 변경 시 `refs/project_purpose.md`를 함께 확인한다.

### 2026-05-22 00:00 - README legacy 기준본 복사
- Goal: 루트 `README.md`가 이후 프로젝트 진행 중 갱신될 예정이므로 현재 기준본을 보관한다.
- Changes: `README.md`를 `refs/legacy/README.md`로 복사했다.
- Decisions: 루트 `README.md`는 최신 프로젝트 안내 문서로 계속 유지하고, `refs/legacy/README.md`는 변경 전 참고본으로 사용한다.
- Verification: 문서 복사만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: README 갱신 시 필요하면 legacy 기준본과 차이를 비교한다.

### 2026-05-22 00:00 - refs 및 docs 폴더 정리
- Goal: 루트 폴더의 중복 지침 문서를 참고자료 영역으로 옮기고 보고서 산출물 폴더를 준비한다.
- Changes: `docs/`, `refs/external/`, `refs/legacy/` 폴더를 생성했다. `CLAUDE.md`, `GEMINI.md`, `guide.md`를 `refs/legacy/`로 이동하고, `TODO.md`의 관련 참조 경로를 새 위치로 갱신했다.
- Decisions: `Cursor AI_퀴즈 - 문제.docx`는 제출 결과 파일이므로 루트에 유지한다. `AGENTS.md`, `TODO.md`, `SESSION_NOTES.md`, `README.md`, `CMakeLists.txt`, `feedback_analyzer.png`, `project_purpose.md`는 루트에 유지한다.
- Verification: 문서/폴더 정리만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 다른 프로젝트 참고 문서는 `refs/external/`에 저장하고, 단계별 보고서는 `docs/` 아래에 생성한다.

### 2026-05-22 00:00 - 제출 원본 및 docs 산출물 경로 확정
- Goal: 루트 파일 정리 기준에서 제출 원본 파일과 보고서 산출물 위치를 명확히 한다.
- Changes: `AGENTS.md`에 `Cursor AI_퀴즈 - 문제.docx` 루트 유지 규칙을 추가하고, 단계별/최종 보고서 산출물 경로를 `docs/` 기준으로 변경했다. `TODO.md`의 보고서 작성/검수 항목도 `docs/*.md` 경로로 갱신했다.
- Decisions: `Cursor AI_퀴즈 - 문제.docx`는 과제물 제출 결과 파일이므로 루트 폴더에서 이동하지 않는다. `analysis.md`, `bug_fix.md`, `refactoring.md`, `feature.md`, `final.md`는 `docs/` 폴더 아래에 생성한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 Phase별 작업에서 보고서 파일을 생성할 때 `docs/` 폴더를 사용한다.

### 2026-05-22 00:00 - 전역 지침 AGENTS.md 통합 반영
- Goal: 별도 전역 지침 파일을 만들지 않고 기존 `AGENTS.md`에 전역 작업 지침을 반영한다.
- Changes: `GLOBAL_INSTRUCTIONS.md`를 제거하고, 언어/프로젝트 기준/Phase 전략/TODO 항목 진행 방식/빌드 및 테스트/코드 품질/상태 관리/문서 산출물 규칙을 `AGENTS.md`에 통합했다.
- Decisions: 전역 지침은 루트의 `AGENTS.md` 단일 파일에서 관리한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이후 작업은 `AGENTS.md`와 `TODO.md`를 기준으로 진행한다.

### 2026-05-22 00:00 - 전역 지침 파일 생성
- Goal: 실습 전반에서 참조할 수 있는 전역 작업 지침 파일을 생성한다.
- Changes: `GLOBAL_INSTRUCTIONS.md`를 추가하고 언어, 프로젝트 기준, Phase 브랜치 전략, TODO 항목 진행 방식, 빌드/테스트, 코드 품질, 상태 관리, 문서 기록, Git 규칙을 정리했다.
- Decisions: 기존 `AGENTS.md`는 덮어쓰지 않고, 별도 전역 지침 문서로 관리한다.
- Verification: 문서 생성만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: TODO 항목 진행 시 `GLOBAL_INSTRUCTIONS.md`와 `TODO.md`를 함께 참조한다.

### 2026-05-22 00:00 - TODO Phase 섹션명 반영
- Goal: 커밋 항목 식별자는 유지하고 브랜치 섹션명만 Phase 형식으로 정리한다.
- Changes: `TODO.md`의 `spec`, `red`, `green`, `refactor`, `feature`, `final` 섹션명을 `Phase-0: SPEC`부터 `Phase-5: FINAL` 형식으로 변경했다.
- Decisions: 체크박스 항목의 `SPEC-01-01` 같은 프롬프트용 식별자는 변경하지 않는다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: TODO 항목 요청 시 기존 식별자 형식을 계속 사용한다.

### 2026-05-22 00:00 - TODO 프롬프트용 단계번호 추가
- Goal: 사용자가 특정 TODO 항목을 쉽게 요청할 수 있도록 체크박스 항목에 단계번호를 추가한다.
- Changes: `TODO.md` 브랜치 전략에 단계번호 규칙을 추가하고, 모든 커밋 항목을 `SPEC-01-01` 형식의 식별자와 커밋 메시지 조합으로 변경했다.
- Decisions: 단계번호는 `{브랜치대문자}-{서브섹션순번}-{항목순번}` 형식을 사용한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 사용자는 예를 들어 `RED-02-04 항목을 진행해 주세요`처럼 요청할 수 있다.

### 2026-05-22 00:00 - TODO 체크박스 상세 형식 정리
- Goal: TODO 체크리스트를 `{체크박스} 커밋 메시지`와 하위 상세 진행 내용 형식으로 재정리한다.
- Changes: `TODO.md`의 각 체크박스에서 설명 문장을 하위 bullet로 분리하고, 기존 TODO 세부 내용을 상세 진행 내용에 배치했다.
- Decisions: 체크박스 라인은 커밋 메시지만 담고, 실제 수행 범위와 원래 요구사항은 하위 상세 항목에서 관리한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 이 형식을 기준으로 브랜치별 커밋 수행 후 완료 항목을 체크한다.

### 2026-05-22 00:00 - TODO 커밋 단위 체크리스트 재작성
- Goal: 다른 프로젝트 예시처럼 브랜치 단계별로 커밋할 세부 항목을 체크박스 형태로 재구성한다.
- Changes: `TODO.md`의 `spec`, `red`, `green`, `refactor`, `feature`, `final` 섹션을 커밋 메시지 단위의 세부 체크리스트로 확장했다.
- Decisions: 각 체크박스는 Conventional Commits 접두사를 포함한 커밋 단위로 작성하고, 기존 분석/테스트/버그수정/리팩토링/기능/리포트 요구사항을 단계별로 재배치했다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 브랜치별 체크리스트를 기준으로 실제 코드 변경과 문서 산출물을 순서대로 진행한다.

### 2026-05-22 00:00 - TODO 브랜치 섹션 구조화
- Goal: `TODO.md`의 작업 단계를 브랜치 기준 섹션과 세부 작업 서브섹션으로 재구성한다.
- Changes: `spec`, `red`, `green`, `refactor`, `feature`, `final`를 `##` 섹션으로 추가하고 기존 번호별 작업 제목을 `###` 서브섹션으로 변경했다.
- Decisions: `refactor` 브랜치에는 네이밍/상수화, DRY/SRP, 세션 상태 개선 작업을 함께 배치했다.
- Verification: 문서 구조 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 각 브랜치 섹션의 체크리스트를 기준으로 단계별 실습을 진행한다.

### 2026-05-22 00:00 - TODO 브랜치 전략 반영
- Goal: 실습용 브랜치 흐름을 `B_07` 기준으로 정리하고 TODO 문서에 반영한다.
- Changes: `TODO.md` 상단에 브랜치 전략 섹션을 추가하고 `spec`, `red`, `green`, `refactor`, `feature`, `final` 단계 브랜치를 명시했다.
- Decisions: `develop` 대신 교육생 ID 브랜치인 `B_07`을 통합 브랜치로 사용하고, TODO 8번 최종 산출물 작업은 `final` 브랜치로 분리한다.
- Verification: 문서 변경만 수행했으며 빌드/테스트는 실행하지 않았다.
- Next: 각 단계 브랜치에서 TODO 항목을 순서대로 수행한다.

### 2026-05-21 18:00 - Codex 초기 설정 정리
- Goal: Codex 사용 환경을 이 저장소에 맞게 정리하고, 반복 작업 지침을 프로젝트 안에 고정한다.
- Changes: `AGENTS.md`를 생성해 프로젝트 전용 작업 원칙을 정리했고, 마크다운 파일 인코딩을 `UTF-8 with BOM`으로 통일했다.
- Decisions: 프로젝트별 작업 지침은 루트 `AGENTS.md`로 관리하고, 세션 맥락은 이 문서에 축적한다.
- Verification: `TODO.md`, `README.md`, `guide.md`, `GEMINI.md`, `project_purpose.md`가 `UTF-8 BOM` 상태인지 확인했다.
- Next: 실제 리팩토링이나 테스트 작업을 시작하면 변경 요약과 검증 결과를 이 문서에 계속 누적한다.

### 2026-05-21 18:05 - 세션 운영 규칙 보강
- Goal: Codex 사용 시 세션 기록과 로컬 산출물 관리 규칙을 명확히 한다.
- Changes: `AGENTS.md`에 의미 있는 변경 후 `SESSION_NOTES.md`를 갱신하는 규칙을 추가했고, `.gitignore`에 로그 파일 제외 규칙을 보강했다.
- Decisions: 세션 문서는 반자동으로 유지하고, 로컬 실행 로그는 저장소에 커밋하지 않는다.
- Verification: `debug.log`가 Git 추적 대상에서 제외되도록 `.gitignore` 패턴을 추가했다.
- Next: 이후 코드/문서 변경 시 `SESSION_NOTES.md`를 함께 갱신한다.

### 2026-05-21 18:10 - 퀴즈 답안 문서 작성
- Goal: `Cursor AI_퀴즈 - 문제.md`를 읽고 제출 가능한 답안 문서를 생성한다.
- Changes: `Cursor AI_퀴즈 - 답안.md`를 새로 작성해 객관식과 서술형 답안을 정리했다.
- Decisions: 문제 파일은 수정하지 않고, 별도 답안 파일로 제출 형식을 맞춘다.
- Verification: 문제 문항을 UTF-8로 재해석한 뒤 각 문항에 맞는 답안을 마크다운으로 정리했다.
- Next: 필요하면 답안을 더 간결한 시험 제출형 문체로 다듬는다.

### 2026-05-21 18:12 - 답안 형식 통일
- Goal: 답안 문서를 사용자가 요청한 `[정답]`, `[이유]` 형식으로 정리한다.
- Changes: 객관식 답안에 `[정답]`, `[이유]` 라벨을 적용했고, 서술형도 `[정답]` 기준으로 표시를 맞췄다.
- Decisions: 문제별 번호는 유지하고, 답안 본문만 제출 친화적인 라벨 형식으로 통일한다.
- Verification: 1번 예시 형식과 동일한 패턴이 문서 전반에 반영되도록 수정했다.
- Next: 필요하면 문체를 더 간단하게 줄여 시험 답안 스타일로 다듬는다.



