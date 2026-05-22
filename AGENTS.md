# AGENTS.md

## Language
- 사용자 응답과 생성하는 문서는 기본적으로 한국어를 사용한다.
- 코드 식별자와 API 이름은 기존 저장소 스타일을 따르되, 도메인 의미가 분명한 영어 이름을 우선한다.
- 커밋 메시지는 Conventional Commits 형식을 사용한다.

## Project Context
- 이 저장소는 C++17, CMake 3.14+, cpp-httplib 기반의 Feedback Analyzer 웹 애플리케이션이다.
- 주 목적은 레거시 코드의 구조 개선, 테스트 가능성 확보, 상태 관리 정리, 기능 보강을 안전하게 수행하는 것이다.
- 소스 기준 경로는 문서에 `src/cpp` 또는 `src/...`로 적혀 있어도 실제 저장소 구조를 우선한다.
- 현재 주요 코드는 루트의 `src` 아래에 있다.

## Branch And Phase Strategy
- 실습 통합 브랜치는 `B_07`을 사용한다.
- 단계별 작업 브랜치는 `spec`, `red`, `green`, `refactor`, `feature`, `final`를 사용한다.
- 프로젝트 전용 Claude Code skill은 `.agents/skills/` 아래에서 관리한다.
  - `/run`: 특정 TODO 항목 실행용 skill.
    - 호출 예시: `/run RED-02-04`, `/run REFACTOR-03-03`, `FEATURE-02-02 항목을 진행해 주세요`, `FEATURE-02-02 진행`, `진행 FEATURE-02-02`, `1번 실행`
  - `/status`: 브랜치, Phase, TODO 진행 현황 확인용 skill.
    - 호출 예시: `/status`, `/status red`, `/status REFACTOR-03`, `현재 진행 현황을 보여주세요`, `현재 상태를 보여주세요.`, `상태`, `브랜치`, `할일`, `상태갱신`
- `TODO.md`의 브랜치 섹션명은 Phase 기준으로 해석한다.
  - `Phase-0: SPEC`
  - `Phase-1: RED`
  - `Phase-2: GREEN`
  - `Phase-3: REFACTOR`
  - `Phase-4: FEATURE`
  - `Phase-5: FINAL`
- 체크박스 항목 식별자는 `{브랜치대문자}-{서브섹션순번}-{항목순번}` 형식을 사용한다.
  - 예: `SPEC-01-01`, `RED-02-04`, `REFACTOR-03-03`
- 사용자가 `RED-02-04 항목을 진행해 주세요`처럼 요청하면, `TODO.md`에서 해당 항목과 하위 상세 진행 내용을 확인한 뒤 진행한다.
- 작업 완료 후 가능하면 해당 체크박스를 완료 상태로 갱신한다.

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
- 문서 변경만 수행한 경우 빌드/테스트를 실행하지 않았음을 명시한다.
- **각 TODO 항목 완료 후, 해당 프롬프트 파일에 대응하는 실행 보고서를 `reports/` 폴더에 자동으로 생성한다.** 보고서 파일명은 프롬프트 파일명과 동일하되 접미사만 `-prompt.md`에서 `-report.md`로 변경한다. 예: `spec-01-02_document_build_and_test_commands-prompt.md` → `spec-01-02_document_build_and_test_commands-report.md`. 보고서에는 실행 날짜, 작업 항목, 목표, 수행 작업, 생성된 산출물, 검증 결과, 다음 단계 등을 포함한다.
- **각 TODO 항목 완료 후 자동으로 커밋 및 푸시를 수행한다. 각 단계에서 사용자의 명시적 승인을 받은 후 진행한다:**
  - 커밋 단계: 변경 파일 목록과 커밋 메시지(`[{TODO_ID}] {type}: {description}`)를 표시하고 사용자 확인 요청
  - 푸시 단계: 현재 브랜치를 origin으로 푸시하기 전 사용자 확인 요청
  - 커밋/푸시 후 STATUS_SNAPSHOT.md를 갱신하여 최신 상태를 유지한다.

## Code Quality Rules
- 하드코딩된 감성 문자열, 임계값, 매직 넘버는 `const` 또는 `static constexpr` 상수로 추출한다.
- 공개 클래스와 함수에는 필요한 경우 Doxygen 형식의 `@brief`, `@param`, `@return` 주석을 추가한다.
- 함수는 단일 책임을 지향하고, 20줄을 크게 넘는 함수는 가능한 범위에서 분해를 우선 검토한다.
- `sent`, `kw`, `fil` 같은 축약 이름보다 `analyzeSentiment`, `analyzeKeywords`, `applyFilter`처럼 의미가 명확한 이름을 선호한다.
- 중복 문자열 검색 로직은 공용 유틸리티로 통합하고, 같은 로직을 여러 클래스에 복제하지 않는다.

## State And Architecture
- 전역 `static` 상태는 테스트 격리를 해치므로 새 코드에서는 추가하지 않는다.
- 기존 전역 상태는 명시적인 API 또는 세션 객체로 캡슐화한다.
- 세션/상태 관리는 명시적인 API로 캡슐화하고, 초기화 또는 `clear()` 경로를 제공한다.
- `Session`은 키를 무시하는 더미 API가 아니라, 실제 조회 가능한 상태 저장소로 유지한다.

## Testing Rules
- 테스트 이름은 `should_[result]_when_[condition]` 형식을 따른다.
- 경계값 테스트를 중시한다. 빈 문자열, 특수문자, 긍정/부정 혼합 문장, 필터 조합, 상태 초기화 시나리오를 우선 포함한다.
- 테스트는 서로 독립적이어야 하며, `SetUp`/`TearDown` 또는 동등한 초기화 절차로 공유 상태를 리셋한다.

## Git And Collaboration

### 커밋 메시지 규칙
- 커밋 메시지는 Conventional Commits를 사용한다.
- 권장 접두사는 `feat`, `fix`, `refactor`, `test`, `docs`, `chore`이다.
- 각 커밋에는 해당 TODO 항목 식별자를 접두사로 붙인다.
  - 형식: `[{TODO_ID}] {type}: {description}`
  - 예: `[SPEC-01-01] docs: define B_07 branch workflow`
  - 예: `[RED-02-04] test: add empty input boundary test`
  - 예: `[REFACTOR-03-02] refactor: rename kw to analyzeKeywords`

### PR 제목 및 설명
- PR 제목에는 Phase 정보와 TODO 식별자를 포함한다.
  - 형식: `[Phase-{n}: {PHASE}] {type}: {description} ({TODO_ID})`
  - 예: `[Phase-0: SPEC] docs: define B_07 branch workflow (SPEC-01-01)`
  - 예: `[Phase-2: GREEN] fix: correct neutral filter condition (GREEN-01-01)`
- PR 본문에는 다음 항목을 포함한다:
  - 요약 (Summary): 변경 내용의 목적과 범위
  - 변경사항 (Changes): 수정된 파일 또는 추가된 기능
  - 검증 (Verification): 빌드/테스트 여부 및 결과
  - 다음 단계 (Next Steps): 후속 TODO 항목

### 협업 흐름
- 원격 저장소에 직접 병합하는 흐름보다 PR 기반 협업을 전제로 변경 내역을 설명 가능하게 유지한다.
- 각 단계별 브랜치(`spec`, `red`, `green`, `refactor`, `feature`, `final`)의 변경 사항을 B_07으로 PR을 생성한다.
- PR 검토 후 B_07에 병합하고, 최종적으로 B_07에서 main으로 병합한다.
- **자동 커밋/푸시 워크플로우:**
  - 각 TODO 항목(`/run` 스킬) 완료 후 자동으로 다음을 수행한다:
    1. 변경된 파일 목록 및 커밋 메시지 사전 안내
    2. 사용자 승인 후 커밋 실행
    3. 커밋 해시 및 메시지 확인
    4. 사용자 승인 후 origin 푸시 실행
    5. 푸시 성공 확인
  - 커밋 메시지는 `[{TODO_ID}] {type}: {description}` 형식을 자동으로 생성한다.
  - 푸시 후 STATUS_SNAPSHOT.md를 갱신하여 다음 세션이 최신 상태를 인식하도록 한다.

## Documentation Outputs
- `Cursor AI_퀴즈 - 문제.docx`는 과제물 제출 결과 파일이므로 반드시 루트 폴더에 유지한다.
- `refs/project_purpose.md`는 강의 교재 기반의 프로젝트 개요 및 목적 문서이므로 반드시 참고한다.
- `refs/` 폴더는 프로젝트 참고자료를 보관하는 영역이며, 실행 산출물이나 최종 보고서 산출물과 구분한다.
  - `refs/project_purpose.md`: 프로젝트 개요, 목적, 학습 목표를 설명하는 필수 참고 문서.
  - `refs/external/`: 다른 프로젝트에서 가져온 읽기 좋은 참고 문서, 예시 TODO, 브랜치 전략, 테스트 계획 등을 보관한다.
  - `refs/source/`: 다른 프로젝트나 강의에서 받은 원본/증빙 자료, 변환 전 DOCX/PDF/XLSX/TXT 등을 보관한다.
  - `refs/legacy/`: 현재 운영 기준에서는 밀려난 이전 지침, 도구별 지침, 변경 전 기준본을 보관한다.
- `docs`, `prompts`, `reports` 폴더는 평가 근거가 되는 핵심 결과물 영역으로 취급한다.
- `prompts/`는 단계별 실행용 상세 프롬프트 정의를 저장한다.
- `reports/`는 단계별 프롬프트 실행 결과 요약을 저장한다. **각 TODO 항목(`/run` 스킬 호출)이 완료되면 대응하는 실행 보고서를 자동으로 생성한다.** 결과 파일명은 대응 프롬프트 파일명과 같은 본문 이름을 사용하고 접미사만 `-report.md`로 작성한다. 예: `prompts/phase-0_spec/spec-01-02_document_build_and_test_commands-prompt.md` → `reports/phase-0_spec/spec-01-02_document_build_and_test_commands-report.md`.
  - **보고서 생성 규칙:**
    - 실행 날짜 및 작업 항목 ID
    - 목표 (Goal): 해당 TODO 항목의 목표
    - 수행 작업 (Changes): 생성된 문서, 수정된 코드, 추가된 테스트 등
    - 생성된 산출물 (Outputs): 파일 목록 및 설명
    - 검증 결과 (Verification): 빌드/테스트 실행 여부, 결과 요약
    - 다음 단계 (Next Steps): 추천 TODO 항목 및 실행 명령
    - 요약 (Summary): 작업 완료 여부 및 핵심 결과
- `docs/`는 phase 종료 시점 문서를 저장한다. phase 문서 파일명은 `phase-{n}_{phase}-document.md` 형식을 사용하며 번호는 0 기반(`phase-0`~`phase-5`)으로 관리한다.
- `prompts/` 파일명 규칙은 `{todo_id_lower}_{slug_lower}-prompt.md`를 사용한다.
- 분석/리팩토링/기능 추가 작업이 크다면 `docs/` 문서(`docs/analysis.md`, `docs/bug_fix.md`, `docs/refactoring.md`, `docs/feature.md`, `docs/final.md`)와의 정합성을 확인한다. 이 5종 문서는 TODO 요구 산출물로 유지한다.
- README, 가이드 문서, `refs/project_purpose.md`와 충돌하는 변경이 있으면 관련 문서도 함께 갱신한다.
- 최종 산출물 검수 시 다음 5종 마크다운 파일이 모두 정상적으로 생성되었는지 확인한다.
  - `docs/analysis.md`
  - `docs/bug_fix.md`
  - `docs/refactoring.md`
  - `docs/feature.md`
  - `docs/final.md`

