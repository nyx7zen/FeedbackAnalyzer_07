# FINAL-01-01 실행 프롬프트

## 호출 문구

- `55번 진행`
- `FINAL-01-01 진행`
- `FINAL-01-01 항목을 진행해 주세요`
- `docs: add final report outline 실행`

---

## 프롬프트

````md
Feedback Analyzer 최종 리포트 구조 작성 전문가 - REPORT 단계 산출물

`TODO.md`의 `FINAL-01-01 docs: add final report outline` 항목을 실행하라.

목표는 `docs/final.md`를 작성하고, 최종 리포트 목차와 작성 기준을 만드는 것이다.

제약:
- 코드 변경 금지
- 실제 수행한 SPEC/RED/GREEN/REFACTOR/FEATURE 결과와 연결
- 추측은 추정으로 표시
- 문서와 세션 로그만 수정
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 전체 실습 결과를 하나의 최종 보고서 구조로 통합한다.
- 이후 LOC, 테스트, 복잡도, 회고 내용을 넣을 수 있는 목차를 준비한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `docs/bug_fix.md`
- `docs/refactoring.md`
- `docs/feature.md`
- `refs/project_purpose.md`
- `SESSION_NOTES.md`

## Task
1. 최종 보고서에 필요한 입력 문서를 확인한다.
2. `docs/final.md`를 생성하거나 기존 파일을 갱신한다.
3. 최종 리포트 목차와 작성 기준을 만든다.
4. 각 Phase별 요약을 채울 자리와 표 구조를 준비한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
`docs/final.md`는 다음 구조를 따른다.
```md
# Feedback Analyzer 최종 보고서

## 1. 프로젝트 개요

## 2. Phase별 수행 요약

## 3. 주요 문제와 해결

## 4. 리팩토링 결과

## 5. 기능 추가 결과

## 6. 테스트 및 검증

## 7. 정량 지표

## 8. AI 협업 회고

## 9. 최종 결론
```

최종 응답에는 작성한 파일, 목차 구성, `FINAL-01-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: 기존 산출 문서를 확인한다.
2. Frame: 최종 리포트 골격 작성에 집중한다.
3. Contract: 보고서 구조는 TODO Phase와 연결되어야 한다.
4. Trace: Phase별 산출물을 final 섹션으로 매핑한다.
5. Write: `docs/final.md`를 작성한다.
6. Verify: 필수 섹션이 있는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````



