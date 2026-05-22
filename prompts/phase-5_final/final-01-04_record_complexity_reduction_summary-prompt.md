# FINAL-01-04 실행 프롬프트

## 호출 문구

- `58번 진행`
- `FINAL-01-04 진행`
- `FINAL-01-04 항목을 진행해 주세요`
- `docs: record complexity reduction summary 실행`

---

## 프롬프트

````md
Feedback Analyzer 복잡도 감소 요약 전문가 - 리팩토링 효과 문서화

`TODO.md`의 `FINAL-01-04 docs: record complexity reduction summary` 항목을 실행하라.

목표는 복잡도 감소율 또는 함수 분해 결과를 요약하고, 리팩토링 전후 구조 개선 효과를 `docs/final.md`에 기록하는 것이다.

제약:
- 코드 변경 금지
- 복잡도 수치 도구가 없으면 함수 분해/책임 분리 결과로 대체하고 명시
- 실제 리팩토링 변경 내역에 근거
- 과장된 효과 표현 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 리팩토링의 구조 개선 효과를 정량/정성 지표로 설명한다.
- 긴 함수 분해, 중복 제거, 전역 상태 제거의 효과를 최종 보고서에 연결한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/final.md`
- `docs/refactoring.md`
- `docs/analysis.md`
- `src/`
- `SESSION_NOTES.md`

## Task
1. 리팩토링 전후 주요 변경을 확인한다.
2. 함수 분해, 네이밍 개선, 상수화, 중복 제거, 상태 관리 개선을 분류한다.
3. 복잡도 도구 결과가 있으면 기록한다.
4. 도구 결과가 없으면 함수/책임 단위 개선 표를 작성한다.
5. `docs/final.md`에 복잡도 감소 요약을 추가한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
보고서 표:
```md
| 영역 | 변경 전 문제 | 변경 후 구조 | 효과 |
|---|---|---|---|
```

최종 응답에는 사용한 기준, 구조 개선 요약, `FINAL-01-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: 리팩토링 보고서와 변경 파일을 확인한다.
2. Frame: 복잡도/구조 개선 요약에 집중한다.
3. Contract: 도구가 없으면 “정성 요약”이라고 명시한다.
4. Trace: 문제 영역 -> 변경 내용 -> 효과 흐름을 정리한다.
5. Write: `docs/final.md`에 기록한다.
6. Verify: `docs/refactoring.md`와 충돌하지 않는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


