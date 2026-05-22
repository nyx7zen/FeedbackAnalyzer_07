# Feedback Analyzer 리팩토링 TO DO 리스트

이 문서는 `refs/legacy/GEMINI.md` 및 `refs/legacy/guide.md`를 기반으로 작성된 프로젝트 리팩토링 및 기능 개선을 위한 작업 목록입니다. 각 단계별로 작업을 완료하며 체크해 나갈 수 있습니다.

## 브랜치 전략
- 실습 통합 브랜치: `B_07`
- 단계별 작업 브랜치: `spec` -> `red` -> `green` -> `refactor` -> `feature` -> `final`
- 단계번호 규칙: `{브랜치대문자}-{서브섹션순번}-{항목순번}` 예) `SPEC-01-01`
- 병합 흐름:
  - `spec` -> `B_07`: 환경 및 지침 설정, 분석 문서 작성
  - `red` -> `B_07`: 실패하는 테스트 작성
  - `green` -> `B_07`: 테스트 통과를 위한 최소 구현
  - `refactor` -> `B_07`: 동작 유지 상태에서 구조 개선
  - `feature` -> `B_07`: 신규 기능 구현
  - `final` -> `B_07`: 최종 산출물 및 종합 리포트 작성
  - `B_07` -> `main`: 실습 결과 최종 반영

## Phase-0: SPEC

### 환경 및 지침 설정
- [x] SPEC-01-01 `docs: define B_07 branch workflow`
  - `B_07` 통합 브랜치를 기준으로 실습 브랜치 전략을 정리한다.
  - `spec -> red -> green -> refactor -> feature -> final` 단계 흐름과 병합 순서를 문서화한다.
- [x] SPEC-01-02 `docs: document build and test commands`
  - MinGW/CMake 기본 빌드 명령을 정리한다.
  - 테스트 실행 기준으로 `ctest --output-on-failure` 사용 방식을 기록한다.
- [x] SPEC-01-03 `docs: align project instructions`
  - `AGENTS.md`, `refs/legacy/guide.md`, `refs/legacy/GEMINI.md`의 작업 지침을 확인한다.
  - 기존 문서와 TODO 항목이 충돌하지 않도록 기준을 맞춘다.

### 프로젝트 구조 및 문제점 진단
- [x] SPEC-02-01 `docs: add architecture analysis`
  - `docs/analysis.md`를 작성한다.
  - 현재 구조의 주요 리팩토링 위험과 개선 방향을 요약한다.
- [x] SPEC-02-02 `docs: analyze global state risks`
  - 전역 static 변수 사용 지점을 조사한다.
  - 테스트 격리 실패 위험성을 분석해 `docs/analysis.md`에 기록한다.
- [x] SPEC-02-03 `docs: analyze main coupling`
  - `main.cpp`와 핵심 도메인 로직 간 결합도를 진단한다.
  - 라우팅/UI 렌더링과 분석 로직이 섞인 영역을 식별한다.
- [x] SPEC-02-04 `docs: prioritize refactoring targets`
  - 네이밍 스멜과 중복 코드 집중 영역을 도출한다.
  - 상태 관리 문제를 포함해 개선 우선순위를 기록한다.

## Phase-1: RED

### 테스트 프레임워크 구축
- [x] RED-01-01 `test: configure gtest target`
  - CMake에 Google Test 기반 테스트 타깃을 추가한다.
  - 테스트 빌드와 실행이 가능한 최소 구성을 만든다.
- [x] RED-01-02 `test: add text analyzer fixture`
  - `tests/TextAnalyzerTest.cpp` 파일을 작성한다.
  - Fixture(`SetUp`, `TearDown`) 기본 구조를 만든다.
- [x] RED-01-03 `test: reset constants and session per test`
  - `Constants` 초기화 경로를 테스트 준비 단계에 반영한다.
  - `Session` 상태 격리 또는 Reset 로직을 테스트별로 적용한다.
- [x] RED-01-04 `test: enforce descriptive test names`
  - 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다.
  - 새 테스트가 동일한 네이밍 규칙을 지키도록 정리한다.

### RED 실패 테스트 작성
- [x] RED-02-01 `test: add empty input boundary test`
  - 빈 문자열 입력의 기대 동작을 정의한다.
  - 현재 구현에서 실패하는 경계값 테스트로 작성한다.
- [x] RED-02-02 `test: add special character input test`
  - 특수문자 입력 처리 기준을 테스트로 고정한다.
  - 분석 로직이 예외 없이 동작하는지 확인한다.
- [x] RED-02-03 `test: add mixed sentiment input test`
  - 긍정/부정 혼재 문장 시나리오를 작성한다.
  - 감성 판정 기준이 드러나도록 실패 테스트를 만든다.
- [x] RED-02-04 `test: add neutral filter test`
  - `중립` 필터 판정 결함을 드러내는 테스트를 작성한다.
  - 논리 연산자 및 분기 조건 오류를 검증 대상으로 둔다.
- [x] RED-02-05 `test: add filter combination tests`
  - 필터 조합 시나리오를 경계값 중심으로 작성한다.
  - 긍정/부정/중립 필터 조합 결과를 검증한다.
- [x] RED-02-06 `test: add session isolation test`
  - 테스트 간 공유 상태가 남지 않아야 함을 검증한다.
  - 상태 초기화 시나리오를 실패 테스트로 고정한다.

## Phase-2: GREEN

### 테스트 통과를 위한 최소 구현
- [ ] GREEN-01-01 `fix: correct neutral filter condition`
  - `src/Filters.cpp`의 `중립` 필터 판정 처리 로직 결함을 수정한다.
  - 논리 연산자와 분기 조건을 테스트 기대값에 맞춘다.
- [ ] GREEN-01-02 `fix: support multiline feedback input`
  - `src/main.cpp` 입력 폼 UI를 단일 라인 `input`에서 `textarea`로 변경한다.
  - 여러 줄 피드백 입력이 가능한지 확인한다.
- [ ] GREEN-01-03 `fix: add runtime log level control`
  - `src/Logger.cpp`에 warning/error/info 로그 레벨 제어 기능을 구현한다.
  - 불필요한 로그 노출을 차단할 수 있도록 한다.
- [ ] GREEN-01-04 `fix: reset shared state in tests`
  - RED 단계에서 작성한 상태 격리 테스트가 통과하도록 초기화 경로를 보강한다.
  - 테스트 간 전역 또는 세션 상태가 누수되지 않게 한다.

### 버그 수정 문서화
- [ ] GREEN-02-01 `docs: add bug fix report`
  - `docs/bug_fix.md`를 작성한다.
  - 버그 수정 전후 논리식과 동작 차이를 기록한다.
- [ ] GREEN-02-02 `docs: record bug verification logs`
  - 수정 후 실행한 테스트 명령을 `docs/bug_fix.md`에 남긴다.
  - 테스트 검증 로그와 결과를 기록한다.
- [ ] GREEN-02-03 `test: verify green regression suite`
  - RED 단계 테스트가 모두 GREEN이 되었는지 확인한다.
  - 필요한 회귀 테스트를 보강한다.

## Phase-3: REFACTOR

### 명명 규칙 개선 및 매직 넘버 상수화
- [ ] REFACTOR-01-01 `refactor: rename sent to analyzeSentiment`
  - `sent()` 선언부와 호출부를 찾는다.
  - 의미가 분명한 `analyzeSentiment()` 이름으로 변경한다.
- [ ] REFACTOR-01-02 `refactor: rename kw to analyzeKeywords`
  - `kw()` 선언부와 호출부를 찾는다.
  - 의미가 분명한 `analyzeKeywords()` 이름으로 변경한다.
- [ ] REFACTOR-01-03 `refactor: rename fil to applyFilter`
  - `fil()` 선언부와 호출부를 찾는다.
  - 의미가 분명한 `applyFilter()` 이름으로 변경한다.
- [ ] REFACTOR-01-04 `refactor: extract sentiment labels`
  - `"긍정"`, `"부정"`, `"중립"` 하드코딩 문자열을 식별한다.
  - 감성 라벨 문자열을 `const` 또는 `static constexpr` 상수로 추출한다.
- [ ] REFACTOR-01-05 `refactor: extract score constants`
  - `0.0f`, `1.0f` 등 감성 점수 관련 매직 넘버를 식별한다.
  - 점수 기준값을 `static constexpr` 상수로 정리한다.
- [ ] REFACTOR-01-06 `refactor: clean duplicated sentiment keywords`
  - `src/Constants.cpp`의 `SENTIMENT_KEYWORDS` 맵을 검토한다.
  - 긍정/부정 사전 중복 키워드(예: "만족", "좋다")를 검출하고 정제한다.
- [ ] REFACTOR-01-07 `docs: add public api doxygen comments`
  - 모든 public 클래스와 메서드를 검토한다.
  - 필요한 곳에 Doxygen 표준 규칙(`@brief`, `@param`, `@return`) 기반 주석을 추가한다.

### 중복 코드 제거 및 단일 책임 함수화
- [ ] REFACTOR-02-01 `refactor: add text utils containsAny`
  - `src/TextUtils.h` 헤더 파일을 생성한다.
  - `std::any_of`와 `std::string::find`를 활용한 `containsAny` 인라인 유틸리티 함수를 구현한다.
- [ ] REFACTOR-02-02 `refactor: reuse containsAny in text analyzer`
  - `src/TextAnalyzer.cpp`의 문자열 검색 중복 로직을 찾는다.
  - 해당 로직을 `TextUtils::containsAny` 호출로 대체한다.
- [ ] REFACTOR-02-03 `refactor: reuse containsAny in filters`
  - `src/Filters.cpp`의 문자열 검색 중복 로직을 찾는다.
  - 해당 로직을 공용 유틸리티 호출로 통합한다.
- [ ] REFACTOR-02-04 `refactor: split long text analyzer routines`
  - 20줄을 크게 넘는 분석 함수를 식별한다.
  - 서브루틴으로 추출해 단일 책임 원칙(SRP)을 강화한다.
- [ ] REFACTOR-02-05 `refactor: split long filter routines`
  - 필터 적용 함수의 긴 조건 분기와 판정 책임을 식별한다.
  - 작은 함수로 분리해 테스트와 유지보수가 쉬운 구조로 만든다.

### 전역 상태 해체 및 Session API 현대화
- [ ] REFACTOR-03-01 `refactor: remove global filter state`
  - `Filters.cpp`의 전역 static 상태(`fil_data` 등)를 식별한다.
  - 새 전역 상태를 추가하지 않고 명시적 상태 관리 구조로 이동한다.
- [ ] REFACTOR-03-02 `refactor: remove global analyzer state`
  - `TextAnalyzer.cpp`의 전역 static 상태(`globalSent` 등)를 식별한다.
  - 분석 결과 상태를 명시적으로 전달하거나 세션 API로 캡슐화한다.
- [ ] REFACTOR-03-03 `refactor: implement session storage map`
  - `Session.cpp/.h`에 `std::unordered_map` 구조를 도입한다.
  - `Session`을 키를 무시하는 더미 API가 아니라 실제 조회 가능한 상태 저장소로 개편한다.
- [ ] REFACTOR-03-04 `refactor: add feedback session clear api`
  - `FeedbackSession::clear()` 등 생명 주기 수동 제어 API를 제공한다.
  - 테스트와 요청 처리에서 상태 초기화가 가능하도록 한다.
- [ ] REFACTOR-03-05 `test: add session lifecycle regression tests`
  - 상태 초기화 시나리오 회귀 테스트를 추가한다.
  - 세션 격리 흐름이 유지되는지 검증한다.
- [ ] REFACTOR-03-06 `docs: add refactoring report`
  - `docs/refactoring.md`를 작성한다.
  - 축약명 변경 매핑 테이블과 개편된 Session 라이프사이클 격리 흐름도를 기록한다.

## Phase-4: FEATURE

### 가중치 기반 감성 스코어링
- [ ] FEATURE-01-01 `test: add weighted sentiment scoring tests`
  - 긍정/부정 단어 빈도 누적 기준 테스트를 작성한다.
  - 기존처럼 첫 키워드에서 종료되는 로직의 한계를 드러낸다.
- [ ] FEATURE-01-02 `feat: count positive and negative keywords`
  - 단순히 첫 키워드에서 종료되는 로직을 폐기한다.
  - 문장 전체를 순회하며 긍정/부정 단어 빈도를 누적 카운트한다.
- [ ] FEATURE-01-03 `feat: calculate relative sentiment score`
  - `Score_sentiment = Count_positive - Count_negative` 수식을 적용한다.
  - 상대적 감성 평가 반환 로직을 구현한다.
- [ ] FEATURE-01-04 `feat: classify sentiment from weighted score`
  - 계산된 점수에 따라 긍정/부정/중립 결과를 반환한다.
  - 점수 기준값은 상수화된 값을 사용한다.
- [ ] FEATURE-01-05 `test: add mixed sentiment scoring regression`
  - 긍정/부정 혼재 문장에 대한 회귀 테스트를 추가한다.
  - 경계값과 동률 점수 처리 기준을 검증한다.

### RAII 기반 CSV 영구 저장
- [ ] FEATURE-02-01 `test: add csv persistence tests`
  - CSV 저장 파일 생성 테스트를 작성한다.
  - 기본 행 출력과 저장 결과를 검증한다.
- [ ] FEATURE-02-02 `feat: persist feedback with ofstream`
  - `src/FileHandler.cpp`의 콘솔 덤프(Stub) 로직을 제거한다.
  - `std::ofstream` 기반 파일 쓰기 로직을 적용한다.
- [ ] FEATURE-02-03 `feat: write utf8 bom for csv export`
  - CSV 파일 시작 위치에 UTF-8 BOM을 기록한다.
  - BOM 인젝션 코드(`\xEF\xBB\xBF`)를 추가한다.
- [ ] FEATURE-02-04 `feat: escape csv feedback body`
  - 피드백 본문 내 줄바꿈, 쉼표, 쌍따옴표를 처리한다.
  - 이중 래핑(Double Quote Wrapping) 방식으로 CSV 필드를 방어한다.
- [ ] FEATURE-02-05 `feat: handle csv persistence errors`
  - 파일 쓰기 실패 상황을 `try-catch`로 처리한다.
  - 예외 처리와 로그 경로를 추가한다.

### 기능 명세 문서화
- [ ] FEATURE-03-01 `docs: add feature specification`
  - `docs/feature.md`를 작성한다.
  - 가중치 감성 분석과 물리적 파일(CSV) 저장 기능의 상세 명세를 기록한다.
- [ ] FEATURE-03-02 `docs: record feature verification`
  - 기능 테스트 명령을 `docs/feature.md`에 기록한다.
  - 검증 결과와 남은 제약 사항을 정리한다.

## Phase-5: FINAL

### 최종 산출물 및 종합 리포트 작성
- [ ] FINAL-01-01 `docs: add final report outline`
  - `docs/final.md`를 작성한다.
  - 최종 리포트 목차와 작성 기준을 만든다.
- [ ] FINAL-01-02 `docs: record loc comparison`
  - 리팩토링 전후 총 소스 코드 라인 수(LOC)를 확인한다.
  - LOC 증감 비율을 `docs/final.md`에 명시한다.
- [ ] FINAL-01-03 `docs: record test coverage summary`
  - GTest 단위 테스트 타깃의 최종 커버리지 정보를 정리한다.
  - 테스트 범위와 결과를 비교표로 작성한다.
- [ ] FINAL-01-04 `docs: record complexity reduction summary`
  - 복잡도 감소율 또는 함수 분해 결과를 요약한다.
  - 리팩토링 전후 구조 개선 효과를 기록한다.
- [ ] FINAL-01-05 `docs: add ai collaboration retrospective`
  - AI 협업 의사결정에 대한 기술 회고를 작성한다.
  - 도움이 된 지점, 한계, 다음 개선 방향을 수록한다.

### 최종 검수
- [ ] FINAL-02-01 `docs: verify required markdown outputs`
  - `docs/analysis.md`, `docs/bug_fix.md`, `docs/refactoring.md`, `docs/feature.md`, `docs/final.md` 생성 여부를 확인한다.
  - 5종 마크다운 파일의 내용 충돌 여부를 검수한다.
- [ ] FINAL-02-02 `test: run final regression suite`
  - 최종 `cmake --build build`를 실행한다.
  - 가능하면 `ctest --output-on-failure`까지 확인한다.
- [ ] FINAL-02-03 `docs: update session notes for final handoff`
  - 최종 변경 요약을 `SESSION_NOTES.md`에 기록한다.
  - 검증 결과와 다음 작업자를 위한 인수인계 내용을 남긴다.

