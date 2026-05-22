# REFACTOR-01-04 실행 프롬프트

## 호출 문구

- `28번 진행`
- `REFACTOR-01-04 진행`
- `REFACTOR-01-04 항목을 진행해 주세요`
- `refactor: extract sentiment labels 실행`

---

## 프롬프트

````md
Feedback Analyzer 상수화 리팩토링 전문가 - 감성 라벨 문자열 추출

`TODO.md`의 `REFACTOR-01-04 refactor: extract sentiment labels` 항목을 실행하라.

목표는 `"긍정"`, `"부정"`, `"중립"` 하드코딩 문자열을 식별하고, 감성 라벨 문자열을 `const` 또는 `static constexpr` 상수로 추출하는 것이다.

제약:
- 감성 판정 동작 변경 금지
- 문자열 값 변경 금지
- 상수 위치는 기존 `Constants` 구조를 우선
- 중복 상수 정의 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 감성 라벨 문자열 중복을 줄인다.
- 오타와 비교 문자열 불일치 위험을 낮춘다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Constants.h`
- `src/Constants.cpp`
- `src/TextAnalyzer.cpp`
- `src/Filters.cpp`
- `src/main.cpp`
- `tests/`

권장 검색:
```powershell
rg -n "\"긍정\"|\"부정\"|\"중립\"" src tests
```

## Task
1. 감성 라벨 문자열 사용 위치를 찾는다.
2. 기존 상수 관리 위치를 확인한다.
3. 라벨 상수를 정의한다.
4. 하드코딩 문자열을 상수 참조로 교체한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 추가한 상수명, 교체 위치, 검증 결과, `REFACTOR-01-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: 감성 문자열 사용처를 검색한다.
2. Frame: 문자열 값과 로직은 유지한다.
3. Contract: 라벨 상수는 단일 출처로 관리한다.
4. Trace: 분석, 필터, UI, 테스트 비교가 같은 상수를 쓰는지 확인한다.
5. Write: 상수 정의와 참조 교체를 수행한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


