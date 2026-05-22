# FINAL-02-01 실행 프롬프트

## 호출 문구

- `60번 진행`
- `FINAL-02-01 진행`
- `FINAL-02-01 항목을 진행해 주세요`
- `docs: verify required markdown outputs 실행`

---

## 프롬프트

````md
Feedback Analyzer 최종 산출물 검수 전문가 - 필수 Markdown 5종 확인

`TODO.md`의 `FINAL-02-01 docs: verify required markdown outputs` 항목을 실행하라.

목표는 `docs/analysis.md`, `docs/bug_fix.md`, `docs/refactoring.md`, `docs/feature.md`, `docs/final.md` 생성 여부를 확인하고, 5종 마크다운 파일의 내용 충돌 여부를 검수하는 것이다.

제약:
- 코드 변경 금지
- 필수 문서 누락 시 생성보다 누락 사실과 필요한 다음 작업을 먼저 명확히 판단
- 문서 간 날짜, 테스트 결과, TODO 상태 충돌을 확인
- 검수 결과를 `docs/final.md` 또는 `SESSION_NOTES.md`에 남김
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 최종 제출 산출물 5종이 모두 존재하고 서로 모순되지 않게 한다.
- REPORT 최종 검수 기준을 문서화한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `docs/bug_fix.md`
- `docs/refactoring.md`
- `docs/feature.md`
- `docs/final.md`
- `SESSION_NOTES.md`

## Task
1. 필수 5종 Markdown 파일 존재 여부를 확인한다.
2. 각 문서의 핵심 섹션 존재 여부를 확인한다.
3. 문서 간 테스트 결과와 변경 요약이 충돌하는지 확인한다.
4. 검수 결과 표를 `docs/final.md`에 추가하거나 갱신한다.
5. 누락/충돌이 있으면 해결 또는 후속 작업으로 명시한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
검수 표:
```md
| 문서 | 존재 여부 | 핵심 내용 | 충돌 여부 | 조치 |
|---|---|---|---|---|
```

최종 응답에는 검수 결과, 누락/충돌 여부, `FINAL-02-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: 필수 문서 5종을 확인한다.
2. Frame: 최종 산출물 검수에 집중한다.
3. Contract: 존재 여부와 내용 충돌을 모두 확인한다.
4. Trace: 문서별 핵심 내용과 final 요약을 비교한다.
5. Write: 검수 결과를 기록한다.
6. Verify: 표의 상태가 실제 파일과 일치하는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````



