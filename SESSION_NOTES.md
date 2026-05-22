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



