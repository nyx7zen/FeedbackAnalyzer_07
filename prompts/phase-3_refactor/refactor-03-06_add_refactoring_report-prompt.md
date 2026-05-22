# REFACTOR-03-06 실행 프롬프트

## 호출 문구

- `42번 진행`
- `REFACTOR-03-06 진행`
- `REFACTOR-03-06 항목을 진행해 주세요`
- `docs: add refactoring report 실행`

---

## 프롬프트

````md
Feedback Analyzer 리팩토링 보고서 작성 전문가 - REFACTOR 단계 산출물

`TODO.md`의 `REFACTOR-03-06 docs: add refactoring report` 항목을 실행하라.

목표는 `docs/refactoring.md`를 작성하고, 축약명 변경 매핑 테이블과 개편된 Session 라이프사이클 격리 흐름도를 기록하는 것이다.

제약:
- 코드 변경 금지
- 실제 리팩토링 변경 내역과 테스트 결과에 근거해 작성
- 추측은 추정으로 표시
- 문서와 세션 로그만 수정
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- REFACTOR 단계에서 수행한 구조 개선을 추적 가능하게 문서화한다.
- 네이밍, 상수화, 중복 제거, 상태 관리 개선을 한 문서로 연결한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `docs/bug_fix.md`
- `SESSION_NOTES.md`
- `git diff`
- `src/`
- `tests/`

## Task
1. REFACTOR 단계 완료 항목과 변경 파일을 확인한다.
2. 축약명 변경 매핑을 정리한다.
3. 상수화/중복 제거/함수 분해 결과를 정리한다.
4. Session 라이프사이클 격리 흐름을 문서화한다.
5. 실행한 검증 명령과 결과를 기록한다.
6. `docs/refactoring.md`를 작성한다.
7. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
`docs/refactoring.md`는 다음 형식을 따른다.

```md
# 리팩토링 보고서

## 1. 개요

## 2. 네이밍 개선

| 변경 전 | 변경 후 | 근거 |
|---|---|---|

## 3. 상수화 및 중복 제거

## 4. 함수 분해와 책임 정리

## 5. 전역 상태 제거 및 Session 라이프사이클

```text
테스트 시작 -> Session 초기화 -> 값 저장/조회 -> clear -> 격리 확인
```

## 6. 검증 결과

## 7. 남은 리스크와 후속 작업
```

최종 응답에는 작성한 문서, 요약한 리팩토링 범위, 검증 결과, `REFACTOR-03-06` 완료 여부를 포함한다.

# 7-Step

1. Observe: REFACTOR 변경 내역과 테스트 결과를 확인한다.
2. Frame: 보고서 작성에 집중한다.
3. Contract: 실제 변경과 문서 내용이 일치해야 한다.
4. Trace: TODO 항목별 변경을 보고서 섹션으로 연결한다.
5. Write: `docs/refactoring.md`를 작성한다.
6. Verify: 필수 섹션과 검증 결과가 포함되었는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


