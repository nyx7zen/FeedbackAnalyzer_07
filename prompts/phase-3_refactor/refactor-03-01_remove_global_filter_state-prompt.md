# REFACTOR-03-01 실행 프롬프트

## 호출 문구

- `37번 진행`
- `REFACTOR-03-01 진행`
- `REFACTOR-03-01 항목을 진행해 주세요`
- `refactor: remove global filter state 실행`

---

## 프롬프트

````md
Feedback Analyzer 전역 필터 상태 제거 전문가 - 명시적 상태 관리 전환

`TODO.md`의 `REFACTOR-03-01 refactor: remove global filter state` 항목을 실행하라.

목표는 `Filters.cpp`의 전역 static 상태(`fil_data` 등)를 식별하고, 새 전역 상태를 추가하지 않고 명시적 상태 관리 구조로 이동하는 것이다.

제약:
- 필터 결과 변경 금지
- 새 전역/static 상태 추가 금지
- 테스트 격리 흐름 유지
- API 변경이 필요하면 호출부와 테스트를 함께 갱신
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 필터 모듈의 숨은 상태를 제거해 테스트 독립성을 높인다.
- 요청 간 데이터 섞임 위험을 줄인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Filters.cpp`
- `src/Filters.h`
- `src/main.cpp`
- `tests/FiltersTest.cpp`
- `docs/analysis.md`

권장 검색:
```powershell
rg -n "static|fil_data|global|vector|map" src/Filters.cpp src/Filters.h tests
```

## Task
1. 필터 전역 상태 후보를 찾는다.
2. 읽기/쓰기 경로와 호출부를 추적한다.
3. 상태를 인자, 반환값, 세션 객체 중 가장 작은 변경으로 이동한다.
4. 테스트를 실행해 필터 동작을 보존한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 제거한 전역 상태, 새 상태 전달 방식, 테스트 결과, `REFACTOR-03-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: 필터 전역 상태와 사용처를 확인한다.
2. Frame: 숨은 상태 제거만 수행한다.
3. Contract: 필터 결과와 public 계약을 최대한 유지한다.
4. Trace: 상태 생성, 변경, 조회 흐름을 추적한다.
5. Write: 명시적 상태 전달로 변경한다.
6. Verify: 필터 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


