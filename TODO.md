# Feedback Analyzer 리팩토링 TO DO 리스트

이 문서는 `GEMINI.md` 및 `guide.md`를 기반으로 작성된 프로젝트 리팩토링 및 기능 개선을 위한 작업 목록입니다. 각 단계별로 작업을 완료하며 체크해 나갈 수 있습니다.

## 1. 프로젝트 구조 및 문제점 진단 (Analysis)
- [ ] `analysis.md` 작성: 
  - [ ] 전역 static 변수 사용으로 인한 테스트 격리 실패 위험성 분석.
  - [ ] `main.cpp`와 핵심 도메인 로직 간의 결합도 진단.
  - [ ] 네이밍 스멜 및 중복 코드 집중 영역 도출 및 개선 우선순위 기록.

## 2. 테스트 프레임워크 구축 (Test Framework)
- [ ] `tests/TextAnalyzerTest.cpp` 파일 작성 (GTest 기반).
- [ ] Fixture(`SetUp`, `TearDown`)를 통한 `Constants` 초기화 및 `Session` 상태 격리(Reset) 로직 추가.
- [ ] 네이밍 규칙 준수: `should_[결과]_when_[조건]` 포맷 엄수.
- [ ] 빈 문자열, 특수문자, 긍정/부정 혼재 등 다양한 경계값 테스트 케이스 작성.

## 3. 긴급 버그 수정 (Bug Fixes)
- [ ] `src/Filters.cpp`: '중립' 필터 판정 처리 로직 결함(논리 연산자 및 분기 조건) 수정.
- [ ] `src/main.cpp`: 입력 폼 UI 텍스트 입력창을 단일 라인(input)에서 `textarea` 기반 멀티라인으로 수정.
- [ ] `src/Logger.cpp`: 동적 로그 레벨 제어(warning/error/info) 기능 구현으로 불필요한 로그 노출 차단.
- [ ] `bug_fix.md` 작성: 버그 수정 전후 논리식 대조 및 테스트 검증 로그 기록.

## 4. 명명 규칙 개선 및 매직 넘버 상수화 (Refactoring - Naming)
- [ ] 축약형 메서드명 정제:
  - `sent()` -> `analyzeSentiment()`
  - `kw()` -> `analyzeKeywords()`
  - `fil()` -> `applyFilter()`
- [ ] 매직 넘버 및 하드코딩 문자열("긍정", "부정", "중립", 0.0f, 1.0f 등)을 `static constexpr` 및 `const` 상수로 추출.
- [ ] `src/Constants.cpp`: `SENTIMENT_KEYWORDS` 맵 내 긍정/부정 사전 중복 키워드(예: "만족", "좋다") 검출 및 정제.
- [ ] 모든 public 클래스, 메서드에 Doxygen 표준 규칙(`@brief`, `@param`, `@return`) 기반 주석 추가.

## 5. 중복 코드 제거 및 단일 책임 함수화 (Refactoring - DRY & SRP)
- [ ] `src/TextUtils.h` 헤더 파일 생성 및 `containsAny` 인라인 유틸리티 함수 구현 (`std::any_of` 및 `std::string::find` 활용).
- [ ] `src/TextAnalyzer.cpp` 및 `src/Filters.cpp` 내 산재된 문자열 검색 로직을 `TextUtils::containsAny` 호출로 대체.
- [ ] 20줄을 초과하는 모든 함수 식별 및 서브루틴으로 추출(Extract Method)하여 단일 책임 원칙(SRP) 확보.

## 6. 전역 상태 해체 및 Session API 현대화 (Refactoring - State)
- [ ] `Session.cpp`, `TextAnalyzer.cpp`, `Filters.cpp` 내 전역 static 변수(`fil_data`, `globalSent` 등) 전면 제거.
- [ ] `Session.cpp/.h`: `std::unordered_map` 구조를 도입하여 독립된 세션 상태 추적 및 관리되도록 개편.
- [ ] `FeedbackSession::clear()` 등 생명 주기 수동 제어 API 제공.
- [ ] `refactoring.md` 작성: 축약명 변경 매핑 테이블 및 개편된 Session 라이프사이클 격리 흐름도 기록.

## 7. 신규 기능 구현 (Features)
- [ ] **가중치 기반 감성 스코어링** (`src/TextAnalyzer.cpp`): 
  - 단순히 첫 키워드에서 종료되는 로직을 폐기.
  - 문장 전체 순회하며 긍정/부정 단어 빈도를 누적 카운트.
  - $Score_{sentiment} = Count_{positive} - Count_{negative}$ 수식을 바탕으로 한 상대적 감성 평가 반환 로직 적용.
- [ ] **RAII 기반 CSV 영구 저장** (`src/FileHandler.cpp`): 
  - 콘솔 덤프(Stub) 로직 제거 후 `std::ofstream` 기반 파일 쓰기 적용.
  - UTF-8 BOM 인젝션 코드 (`\xEF\xBB\xBF`) 추가.
  - 피드백 본문 내 줄바꿈, 쉼표, 쌍따옴표를 방어하기 위한 이중 래핑(Double Quote Wrapping) 처리 및 `try-catch` 예외 처리.
- [ ] `feature.md` 작성: 가중치 감성 분석 및 물리적 파일(CSV) 저장 기능의 상세 명세서 기록.

## 8. 최종 산출물 및 종합 리포트 작성 (Documentation)
- [ ] `report.md` 작성: 
  - 리팩토링 전후 총 소스 코드 라인 수(LOC) 증감 비율 명시.
  - GTest 단위 테스트 타깃 최종 커버리지 및 복잡도 감소율 비교표 작성.
  - AI 협업 의사결정에 대한 기술 회고 수록.
- [ ] 5종 마크다운 파일(`analysis.md`, `bug_fix.md`, `refactoring.md`, `feature.md`, `report.md`)이 모두 정상적으로 생성되었는지 검수.
