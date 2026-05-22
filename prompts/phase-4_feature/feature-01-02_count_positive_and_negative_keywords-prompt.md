# FEATURE-01-02 실행 프롬프트

## 호출 문구

- `44번 진행`
- `FEATURE-01-02 진행`
- `FEATURE-01-02 항목을 진행해 주세요`
- `feat: count positive and negative keywords 실행`

---

## 프롬프트

````md
Feedback Analyzer 키워드 빈도 누적 구현 전문가 - 감성 분석 FEATURE

`TODO.md`의 `FEATURE-01-02 feat: count positive and negative keywords` 항목을 실행하라.

목표는 단순히 첫 키워드에서 종료되는 로직을 폐기하고, 문장 전체를 순회하며 긍정/부정 단어 빈도를 누적 카운트하는 것이다.

제약:
- 기존 public API를 가능하면 유지
- 키워드 사전의 의미를 임의로 바꾸지 말 것
- 첫 키워드 조기 반환 제거 시 기존 테스트를 함께 확인
- 새 전역 상태 추가 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 감성 분석이 문장 전체의 긍정/부정 신호를 반영하게 한다.
- 후속 상대 점수 계산의 입력값을 만든다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/TextAnalyzer.h`
- `src/Constants.cpp`
- `src/TextUtils.h`
- `tests/TextAnalyzerTest.cpp`

## Task
1. 현재 감성 분석이 첫 키워드에서 종료되는지 확인한다.
2. 긍정/부정 키워드 카운트 helper를 설계한다.
3. 문장 전체에서 빈도를 누적하도록 구현한다.
4. `FEATURE-01-01` 테스트를 실행한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 추가/변경한 함수, 카운트 기준, 테스트 결과, `FEATURE-01-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: 현재 조기 반환 로직을 찾는다.
2. Frame: 빈도 카운트 구현에 집중한다.
3. Contract: 긍정/부정 키워드 출현 횟수를 각각 누적한다.
4. Trace: text -> positive count / negative count 흐름을 확인한다.
5. Write: 카운트 로직을 구현한다.
6. Verify: 관련 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


