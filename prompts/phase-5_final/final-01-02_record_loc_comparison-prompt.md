# FINAL-01-02 실행 프롬프트

## 호출 문구

- `56번 진행`
- `FINAL-01-02 진행`
- `FINAL-01-02 항목을 진행해 주세요`
- `docs: record loc comparison 실행`

---

## 프롬프트

````md
Feedback Analyzer LOC 비교 기록 전문가 - 리팩토링 전후 정량 지표

`TODO.md`의 `FINAL-01-02 docs: record loc comparison` 항목을 실행하라.

목표는 리팩토링 전후 총 소스 코드 라인 수(LOC)를 확인하고, LOC 증감 비율을 `docs/final.md`에 명시하는 것이다.

제약:
- 코드 변경 금지
- LOC 계산 기준을 명확히 기록
- 리팩토링 전 기준이 없으면 현재 기준과 비교 가능한 대체 기준을 명시
- 자동 생성물, build 폴더, 외부 참고자료는 제외
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 리팩토링 전후 코드 규모 변화를 정량적으로 설명한다.
- LOC 증가/감소가 구조 개선과 어떤 관계가 있는지 해석한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/final.md`
- `SESSION_NOTES.md`
- `src/`
- `tests/`
- `git diff` 또는 기준 커밋 정보

## Task
1. LOC 계산 대상 파일 범위를 정한다.
2. 현재 LOC를 계산한다.
3. 리팩토링 전 기준을 git 또는 문서에서 찾는다.
4. 전후 비교표와 증감 비율을 계산한다.
5. `docs/final.md`에 LOC 비교 섹션을 추가하거나 갱신한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
보고서 표:
```md
| 구분 | 대상 | LOC | 비고 |
|---|---|---:|---|
| 리팩토링 전 |  |  |  |
| 리팩토링 후 |  |  |  |

증감률: `((after - before) / before) * 100`
```

최종 응답에는 계산 기준, LOC 결과, `FINAL-01-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: LOC 기준과 비교 기준을 확인한다.
2. Frame: 정량 지표 기록에 집중한다.
3. Contract: 제외/포함 기준을 문서화한다.
4. Trace: 파일 목록 -> 줄 수 -> 비교표 흐름을 확인한다.
5. Write: `docs/final.md`에 기록한다.
6. Verify: 계산식과 숫자를 재확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


