# REFACTOR-01-01 실행 프롬프트

## 호출 문구

- `25번 진행`
- `REFACTOR-01-01 진행`
- `REFACTOR-01-01 항목을 진행해 주세요`
- `refactor: rename sent to analyzeSentiment 실행`

---

## 프롬프트

````md
Feedback Analyzer 네이밍 리팩토링 전문가 - 감성 분석 함수명 개선

`TODO.md`의 `REFACTOR-01-01 refactor: rename sent to analyzeSentiment` 항목을 실행하라.

목표는 `sent()` 선언부와 호출부를 모두 찾아 의미가 분명한 `analyzeSentiment()` 이름으로 변경하는 것이다.

제약:
- 동작 변경 금지
- 함수명 변경 범위만 최소 수정
- 테스트 기대값 변경 금지
- 공개 API 변경 영향이 있으면 호출부를 모두 함께 갱신
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 축약 함수명 `sent()`의 의미를 명확히 한다.
- 후속 기능 확장과 테스트 가독성을 높인다.

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
rg -n "\\bsent\\s*\\(" src tests
```

## Task
1. `sent()` 선언부와 정의부를 찾는다.
2. 모든 호출부를 찾는다.
3. 함수명을 `analyzeSentiment()`로 변경한다.
4. 주석 또는 문서에 `sent()`가 언급되어 있으면 필요한 범위에서 갱신한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 수정 파일, 변경한 함수명, 실행한 검증 명령, `REFACTOR-01-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: `sent()` 선언/정의/호출부를 모두 검색한다.
2. Frame: 이름 변경 외 동작 수정은 하지 않는다.
3. Contract: `sent()`와 동일한 입력/출력/예외 동작을 유지한다.
4. Trace: 호출 흐름이 새 이름으로 모두 이어지는지 확인한다.
5. Write: 선언부, 정의부, 호출부를 일괄 변경한다.
6. Verify: `cmake --build build`, `ctest --test-dir build --output-on-failure`를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


