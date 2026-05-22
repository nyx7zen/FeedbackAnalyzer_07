# REFACTOR-03-02 실행 프롬프트

## 호출 문구

- `38번 진행`
- `REFACTOR-03-02 진행`
- `REFACTOR-03-02 항목을 진행해 주세요`
- `refactor: remove global analyzer state 실행`

---

## 프롬프트

````md
Feedback Analyzer 전역 분석 상태 제거 전문가 - TextAnalyzer 상태 캡슐화

`TODO.md`의 `REFACTOR-03-02 refactor: remove global analyzer state` 항목을 실행하라.

목표는 `TextAnalyzer.cpp`의 전역 static 상태(`globalSent` 등)를 식별하고, 분석 결과 상태를 명시적으로 전달하거나 세션 API로 캡슐화하는 것이다.

제약:
- 분석 결과 변경 금지
- 새 전역/static 상태 추가 금지
- 상태 전달 방식은 테스트 가능성을 우선
- 세션 저장소 변경은 `REFACTOR-03-03`과 충돌하지 않게 최소화
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 분석 모듈의 숨은 상태를 제거한다.
- 테스트 간 분석 결과 누수와 요청 간 섞임을 방지한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Session.cpp`
- `src/Session.h`
- `src/main.cpp`
- `tests/TextAnalyzerTest.cpp`
- `docs/analysis.md`

권장 검색:
```powershell
rg -n "static|global|globalSent|sentiment|Session" src/TextAnalyzer.cpp src/TextAnalyzer.h tests
```

## Task
1. 분석 전역 상태 후보를 찾는다.
2. 상태가 필요한지, 반환값으로 대체 가능한지 판단한다.
3. 최소 변경으로 명시적 전달 구조로 바꾼다.
4. TextAnalyzer 테스트와 전체 테스트를 실행한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 제거한 상태, 새 전달 구조, 테스트 결과, `REFACTOR-03-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: 분석 상태 후보와 호출부를 확인한다.
2. Frame: 숨은 분석 상태 제거에 집중한다.
3. Contract: 동일 입력은 동일 분석 결과를 반환한다.
4. Trace: 분석 결과 생성과 소비 흐름을 추적한다.
5. Write: 반환값 또는 명시적 객체로 상태를 이동한다.
6. Verify: 분석 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


