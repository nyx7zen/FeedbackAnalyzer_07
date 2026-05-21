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
