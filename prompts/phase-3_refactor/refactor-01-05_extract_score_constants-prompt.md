# REFACTOR-01-05 실행 프롬프트

## 호출 문구

- `29번 진행`
- `REFACTOR-01-05 진행`
- `REFACTOR-01-05 항목을 진행해 주세요`
- `refactor: extract score constants 실행`

---

## 프롬프트

````md
Feedback Analyzer 상수화 리팩토링 전문가 - 감성 점수 매직 넘버 추출

`TODO.md`의 `REFACTOR-01-05 refactor: extract score constants` 항목을 실행하라.

목표는 `0.0f`, `1.0f` 등 감성 점수 관련 매직 넘버를 식별하고, 점수 기준값을 `static constexpr` 상수로 정리하는 것이다.

제약:
- 점수 계산 결과 변경 금지
- 감성 분류 기준 변경 금지
- 점수와 무관한 숫자까지 과도하게 상수화하지 말 것
- 이름은 의미가 드러나게 작성
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 감성 점수 기준을 명명된 상수로 고정한다.
- 후속 가중치 기반 스코어링 기능의 기준점을 명확히 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Constants.h`
- `src/Constants.cpp`
- `src/TextAnalyzer.cpp`
- `src/Filters.cpp`
- `tests/`

권장 검색:
```powershell
rg -n "0\\.0f|1\\.0f|0\\.0|1\\.0|score|Score" src tests
```

## Task
1. 감성 점수 관련 숫자 리터럴을 찾는다.
2. 점수 기준값과 일반 숫자를 구분한다.
3. `static constexpr` 상수를 적절한 위치에 정의한다.
4. 관련 리터럴을 상수로 교체한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 추가한 상수명, 교체한 리터럴, 검증 결과, `REFACTOR-01-05` 완료 여부를 포함한다.

# 7-Step

1. Observe: 점수 관련 리터럴을 검색한다.
2. Frame: 점수 의미가 없는 숫자는 건드리지 않는다.
3. Contract: 기존 점수 결과를 유지한다.
4. Trace: 상수가 분석/필터/테스트에서 일관되게 쓰이는지 확인한다.
5. Write: 상수 정의와 참조 교체를 수행한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


