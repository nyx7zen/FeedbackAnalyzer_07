# REFACTOR-01-02 실행 프롬프트

## 호출 문구

- `26번 진행`
- `REFACTOR-01-02 진행`
- `REFACTOR-01-02 항목을 진행해 주세요`
- `refactor: rename kw to analyzeKeywords 실행`

---

## 프롬프트

````md
Feedback Analyzer 네이밍 리팩토링 전문가 - 키워드 분석 함수명 개선

`TODO.md`의 `REFACTOR-01-02 refactor: rename kw to analyzeKeywords` 항목을 실행하라.

목표는 `kw()` 선언부와 호출부를 모두 찾아 의미가 분명한 `analyzeKeywords()` 이름으로 변경하는 것이다.

제약:
- 동작 변경 금지
- 함수명 변경 범위만 최소 수정
- 키워드 추출 기준 변경 금지
- 테스트 기대값 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 축약 함수명 `kw()`의 의미를 명확히 한다.
- 테스트와 호출부에서 키워드 분석 책임을 쉽게 파악하게 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.h`
- `src/TextAnalyzer.cpp`
- `src/main.cpp`
- `tests/`
- `docs/analysis.md`

권장 검색:
```powershell
rg -n "\\bkw\\s*\\(" src tests
```

## Task
1. `kw()` 선언부, 정의부, 호출부를 찾는다.
2. 이름을 `analyzeKeywords()`로 변경한다.
3. include 또는 namespace 영향이 없는지 확인한다.
4. 관련 문서/주석의 함수명 언급을 갱신한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 수정 파일, 변경한 함수명, 테스트 결과, `REFACTOR-01-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: `kw()` 전체 참조를 검색한다.
2. Frame: 이름 변경만 수행한다.
3. Contract: 기존 키워드 분석 결과를 유지한다.
4. Trace: 모든 호출부가 새 이름을 사용하도록 확인한다.
5. Write: 선언/정의/호출을 갱신한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


