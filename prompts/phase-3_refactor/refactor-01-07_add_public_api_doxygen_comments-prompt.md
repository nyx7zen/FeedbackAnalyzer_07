# REFACTOR-01-07 실행 프롬프트

## 호출 문구

- `31번 진행`
- `REFACTOR-01-07 진행`
- `REFACTOR-01-07 항목을 진행해 주세요`
- `docs: add public api doxygen comments 실행`

---

## 프롬프트

````md
Feedback Analyzer Public API 문서화 전문가 - Doxygen 주석 보강

`TODO.md`의 `REFACTOR-01-07 docs: add public api doxygen comments` 항목을 실행하라.

목표는 모든 public 클래스와 메서드를 검토하고, 필요한 곳에 Doxygen 표준 규칙(`@brief`, `@param`, `@return`) 기반 주석을 추가하는 것이다.

제약:
- 동작 변경 금지
- 구현 내부에 과도한 설명 주석 추가 금지
- public API 중심으로만 보강
- 이미 명확한 주석은 중복하지 말 것
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 주요 public API의 사용 의도를 문서화한다.
- 후속 리팩토링에서 API 계약을 보존하기 쉽게 만든다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/*.h`
- `docs/analysis.md`
- `docs/refactoring.md`가 있으면 해당 문서

권장 검색:
```powershell
rg -n "class |struct |public:|\\);" src -g "*.h"
```

## Task
1. public 클래스와 함수 목록을 확인한다.
2. 주석이 필요한 API와 불필요한 API를 구분한다.
3. 필요한 곳에 Doxygen 주석을 추가한다.
4. 코드 정렬과 포맷을 유지한다.
5. build를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
권장 형식:
```cpp
/**
 * @brief 피드백 텍스트의 감성 결과를 분석한다.
 * @param text 분석할 피드백 본문
 * @return 감성 라벨 또는 점수 결과
 */
```

최종 응답에는 주석을 추가한 헤더, 검증 결과, `REFACTOR-01-07` 완료 여부를 포함한다.

# 7-Step

1. Observe: 헤더의 public API를 확인한다.
2. Frame: 문서 주석만 추가한다.
3. Contract: 주석은 실제 동작과 일치해야 한다.
4. Trace: 파라미터와 반환값의 의미를 코드에서 확인한다.
5. Write: Doxygen 주석을 추가한다.
6. Verify: build를 실행해 문법 오류가 없는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


