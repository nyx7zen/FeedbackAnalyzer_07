# FEATURE-03-01 실행 프롬프트

## 호출 문구

- `53번 진행`
- `FEATURE-03-01 진행`
- `FEATURE-03-01 항목을 진행해 주세요`
- `docs: add feature specification 실행`

---

## 프롬프트

````md
Feedback Analyzer 기능 명세 작성 전문가 - 가중치 감성 분석과 CSV 저장

`TODO.md`의 `FEATURE-03-01 docs: add feature specification` 항목을 실행하라.

목표는 `docs/feature.md`를 작성하고, 가중치 감성 분석과 물리적 파일(CSV) 저장 기능의 상세 명세를 기록하는 것이다.

제약:
- 코드 변경 금지
- 실제 구현과 테스트에 근거해 작성
- 불확실한 내용은 추정으로 표시
- 문서와 세션 로그만 수정
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- FEATURE 단계에서 추가한 사용자 가치를 명세 문서로 정리한다.
- 감성 스코어링과 CSV 저장의 입력/처리/출력 계약을 명확히 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/analysis.md`
- `docs/bug_fix.md`
- `docs/refactoring.md`
- `src/TextAnalyzer.*`
- `src/FileHandler.*`
- `tests/`
- `SESSION_NOTES.md`

## Task
1. FEATURE 단계 변경 내역을 확인한다.
2. 가중치 감성 분석 명세를 작성한다.
3. CSV 저장 명세를 작성한다.
4. 제한 사항과 오류 처리 기준을 기록한다.
5. `docs/feature.md`를 작성한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
`docs/feature.md`는 다음 형식을 따른다.
```md
# 기능 명세

## 1. 개요

## 2. 가중치 기반 감성 스코어링

## 3. CSV 영구 저장

## 4. 오류 처리

## 5. 테스트 기준

## 6. 남은 제약 사항
```

최종 응답에는 작성한 문서, 핵심 명세, `FEATURE-03-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: FEATURE 변경과 테스트를 확인한다.
2. Frame: 기능 명세 작성에 집중한다.
3. Contract: 문서는 실제 구현과 일치해야 한다.
4. Trace: 입력 -> 처리 -> 출력 흐름을 문서화한다.
5. Write: `docs/feature.md`를 작성한다.
6. Verify: 필수 섹션과 실제 코드 정합성을 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


