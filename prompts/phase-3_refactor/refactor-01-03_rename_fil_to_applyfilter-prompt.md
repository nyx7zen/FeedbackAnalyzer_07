# REFACTOR-01-03 실행 프롬프트

## 호출 문구

- `27번 진행`
- `REFACTOR-01-03 진행`
- `REFACTOR-01-03 항목을 진행해 주세요`
- `refactor: rename fil to applyFilter 실행`

---

## 프롬프트

````md
Feedback Analyzer 네이밍 리팩토링 전문가 - 필터 적용 함수명 개선

`TODO.md`의 `REFACTOR-01-03 refactor: rename fil to applyFilter` 항목을 실행하라.

목표는 `fil()` 선언부와 호출부를 모두 찾아 의미가 분명한 `applyFilter()` 이름으로 변경하는 것이다.

제약:
- 동작 변경 금지
- 필터 조건 수정 금지
- 공개 API 이름 변경에 따른 호출부 누락 금지
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 축약 함수명 `fil()`을 필터 적용 책임이 드러나는 이름으로 바꾼다.
- 필터 관련 테스트와 후속 리팩토링의 가독성을 높인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Filters.h`
- `src/Filters.cpp`
- `src/main.cpp`
- `tests/`
- `docs/analysis.md`

권장 검색:
```powershell
rg -n "\\bfil\\s*\\(" src tests
```

## Task
1. `fil()` 선언부, 정의부, 호출부를 찾는다.
2. 이름을 `applyFilter()`로 변경한다.
3. 필터 테스트와 main 호출부를 함께 갱신한다.
4. build와 ctest를 실행한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 수정 파일, 변경한 함수명, 검증 결과, `REFACTOR-01-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: `fil()` 참조를 모두 찾는다.
2. Frame: 필터 로직은 바꾸지 않는다.
3. Contract: 기존 필터 결과를 유지한다.
4. Trace: main과 tests의 호출부를 새 이름으로 연결한다.
5. Write: 선언/정의/호출부를 변경한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


