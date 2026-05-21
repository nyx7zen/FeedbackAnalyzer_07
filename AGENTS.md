# AGENTS.md

## Language
- 사용자 응답과 생성하는 문서는 기본적으로 한국어를 사용한다.
- 코드 식별자와 API 이름은 기존 저장소 스타일을 따르되, 도메인 의미가 분명한 영어 이름을 우선한다.

## Project Context
- 이 저장소는 C++17, CMake 3.14+, cpp-httplib 기반의 Feedback Analyzer 웹 애플리케이션이다.
- 주 목적은 레거시 코드의 구조 개선, 테스트 가능성 확보, 상태 관리 정리, 기능 보강을 안전하게 수행하는 것이다.
- 소스 기준 경로는 `src/cpp`이며, 문서에 `src/...`로 적혀 있어도 실제 작업은 저장소 구조를 우선한다.

## Build And Test
- Windows MinGW 환경을 기본 전제로 본다.
- 기본 빌드 명령은 `cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe` 후 `cmake --build build`를 사용한다.
- 테스트를 추가하거나 수정했다면 가능하면 `ctest --output-on-failure`까지 확인한다.
- 테스트 프레임워크는 Google Test를 기본값으로 사용한다.

## Workflow
- 작업 전 관련 파일과 문서를 먼저 읽고, 기존 구조와 제약을 확인한 뒤 수정한다.
- 변경은 가능한 한 작은 단위로 유지하고, 요청 범위를 넘는 대규모 재설계는 피한다.
- `main.cpp`의 라우팅/UI 렌더링과 도메인 로직의 결합을 줄이는 방향을 우선한다.
- 전역 상태와 중복 로직은 새 기능 추가보다 먼저 정리 대상에 포함한다.
- 의미 있는 코드 변경, 문서 생성, 인코딩 변경, 설정 변경이 발생하면 루트의 `SESSION_NOTES.md`에 세션 로그를 함께 갱신한다.

## Code Quality Rules
- 하드코딩된 감성 문자열, 임계값, 매직 넘버는 `const` 또는 `static constexpr` 상수로 추출한다.
- 공개 클래스와 함수에는 필요한 경우 Doxygen 형식의 `@brief`, `@param`, `@return` 주석을 추가한다.
- 함수는 단일 책임을 지향하고, 20줄을 크게 넘는 함수는 가능한 범위에서 분해를 우선 검토한다.
- `sent`, `kw`, `fil` 같은 축약 이름보다 `analyzeSentiment`, `analyzeKeywords`, `applyFilter`처럼 의미가 명확한 이름을 선호한다.
- 중복 문자열 검색 로직은 공용 유틸리티로 통합하고, 같은 로직을 여러 클래스에 복제하지 않는다.

## State And Architecture
- 전역 `static` 상태는 테스트 격리를 해치므로 새 코드에서는 추가하지 않는다.
- 세션/상태 관리는 명시적인 API로 캡슐화하고, 초기화 또는 `clear()` 경로를 제공한다.
- `Session`은 키를 무시하는 더미 API가 아니라, 실제 조회 가능한 상태 저장소로 유지한다.

## Testing Rules
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다.
- 경계값 테스트를 중시한다. 빈 문자열, 특수문자, 긍정/부정 혼합 문장, 필터 조합, 상태 초기화 시나리오를 우선 포함한다.
- 테스트는 서로 독립적이어야 하며, `SetUp`/`TearDown` 또는 동등한 초기화 절차로 공유 상태를 리셋한다.

## Git And Collaboration
- 커밋 메시지는 Conventional Commits를 사용한다.
- 권장 접두사는 `feat`, `fix`, `refactor`, `test`, `docs`, `chore`이다.
- 원격 저장소에 직접 병합하는 흐름보다 PR 기반 협업을 전제로 변경 내역을 설명 가능하게 유지한다.

## Documentation Outputs
- 분석/리팩토링/기능 추가 작업이 크다면 루트 문서(`analysis.md`, `bug_fix.md`, `refactoring.md`, `feature.md`, `report.md`)와의 정합성을 확인한다.
- README, 가이드 문서, 프로젝트 목적 문서와 충돌하는 변경이 있으면 관련 문서도 함께 갱신한다.
