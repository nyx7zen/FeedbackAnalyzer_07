# FINAL-02-03 실행 프롬프트

## 호출 문구

- `62번 진행`
- `FINAL-02-03 진행`
- `FINAL-02-03 항목을 진행해 주세요`
- `docs: update session notes for final handoff 실행`

---

## 프롬프트

````md
Feedback Analyzer 최종 인수인계 기록 전문가 - SESSION_NOTES 마감 정리

`TODO.md`의 `FINAL-02-03 docs: update session notes for final handoff` 항목을 실행하라.

목표는 최종 변경 요약을 `SESSION_NOTES.md`에 기록하고, 검증 결과와 다음 작업자를 위한 인수인계 내용을 남기는 것이다.

제약:
- 코드 변경 금지
- 최종 상태를 과장 없이 기록
- 남은 실패/미검증 항목을 숨기지 말 것
- TODO 체크 상태와 실제 산출물 상태를 맞춰 확인
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 다음 작업자가 현재 프로젝트 상태를 빠르게 이어받을 수 있게 한다.
- 최종 산출물, 검증 결과, 남은 리스크를 한 곳에 정리한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `SESSION_NOTES.md`
- `docs/final.md`
- `docs/analysis.md`
- `docs/bug_fix.md`
- `docs/refactoring.md`
- `docs/feature.md`
- `git status`

## Task
1. 최종 변경 파일과 TODO 진행 상태를 확인한다.
2. 최종 빌드/테스트 검증 결과를 확인한다.
3. 필수 산출물 5종 생성 여부를 확인한다.
4. `SESSION_NOTES.md`에 최종 인수인계 로그를 추가한다.
5. 필요한 경우 `docs/final.md`의 최종 결론과 맞는지 확인한다.
6. `TODO.md`의 `FINAL-02-03` 체크박스를 `[x]`로 갱신한다.

## Format
세션 로그 형식:
```md
### YYYY-MM-DD HH:MM - 최종 인수인계
- Goal:
- Changes:
- Decisions:
- Verification:
- Remaining:
- Next:
```

최종 응답에는 최종 변경 요약, 검증 결과, 남은 리스크, `FINAL-02-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: TODO, docs, git status, 세션 로그를 확인한다.
2. Frame: 최종 인수인계 기록에 집중한다.
3. Contract: 다음 작업자가 바로 이어받을 수 있는 정보를 남긴다.
4. Trace: 산출물 -> 검증 -> 남은 리스크 -> 다음 작업 흐름을 정리한다.
5. Write: `SESSION_NOTES.md`에 최종 로그를 추가한다.
6. Verify: 로그가 실제 상태와 충돌하지 않는지 확인한다.
7. Close: TODO 체크박스와 최종 응답을 정리한다.
````


