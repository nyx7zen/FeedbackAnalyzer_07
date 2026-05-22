# FINAL-01-05 실행 프롬프트

## 호출 문구

- `59번 진행`
- `FINAL-01-05 진행`
- `FINAL-01-05 항목을 진행해 주세요`
- `docs: add ai collaboration retrospective 실행`

---

## 프롬프트

````md
Feedback Analyzer AI 협업 회고 작성 전문가 - 기술 의사결정 리뷰

`TODO.md`의 `FINAL-01-05 docs: add ai collaboration retrospective` 항목을 실행하라.

목표는 AI 협업 의사결정에 대한 기술 회고를 작성하고, 도움이 된 지점, 한계, 다음 개선 방향을 `docs/final.md`에 수록하는 것이다.

제약:
- 코드 변경 금지
- 과장된 표현보다 실제 의사결정과 작업 흐름 중심으로 작성
- 세션 로그와 TODO 흐름에 근거
- 개인 정보나 불필요한 감상문 형태는 피할 것
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- AI 협업이 리팩토링/TDD/문서화에 어떻게 기여했는지 정리한다.
- 한계와 다음 개선 방향을 실무적으로 남긴다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `SESSION_NOTES.md`
- `docs/final.md`
- `docs/analysis.md`
- `docs/refactoring.md`
- `docs/feature.md`

## Task
1. 세션 로그에서 주요 의사결정과 작업 흐름을 확인한다.
2. AI가 도움이 된 지점을 기술적으로 분류한다.
3. 한계와 주의해야 할 지점을 기록한다.
4. 다음 개선 방향을 작성한다.
5. `docs/final.md`의 AI 협업 회고 섹션을 추가하거나 갱신한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
보고서 섹션:
```md
## AI 협업 회고

### 도움이 된 지점

### 한계와 주의점

### 다음 개선 방향
```

최종 응답에는 회고에 담은 핵심 항목, `FINAL-01-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: 세션 로그와 보고서를 확인한다.
2. Frame: AI 협업 회고 작성에 집중한다.
3. Contract: 실제 작업 근거를 기반으로 작성한다.
4. Trace: 의사결정 -> AI 도움 -> 결과 -> 한계 흐름을 정리한다.
5. Write: `docs/final.md`에 회고를 추가한다.
6. Verify: 회고가 과장 없이 기술적인지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


