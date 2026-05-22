# REFACTOR-01-06 실행 프롬프트

## 호출 문구

- `30번 진행`
- `REFACTOR-01-06 진행`
- `REFACTOR-01-06 항목을 진행해 주세요`
- `refactor: clean duplicated sentiment keywords 실행`

---

## 프롬프트

````md
Feedback Analyzer 감성 사전 정제 전문가 - 중복 키워드 제거

`TODO.md`의 `REFACTOR-01-06 refactor: clean duplicated sentiment keywords` 항목을 실행하라.

목표는 `src/Constants.cpp`의 `SENTIMENT_KEYWORDS` 맵을 검토하고, 긍정/부정 사전 중복 키워드(예: "만족", "좋다")를 검출해 정제하는 것이다.

제약:
- 키워드 삭제/이동은 테스트 기대값과 문맥을 확인한 뒤 수행
- 감성 판정 기준을 임의로 크게 바꾸지 말 것
- 정제 근거를 세션 로그에 남길 것
- 필요하면 회귀 테스트를 함께 확인
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 같은 키워드가 상반된 감성 사전에 들어가 판정이 불안정해지는 위험을 줄인다.
- 후속 가중치 스코어링의 입력 사전을 신뢰 가능하게 만든다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/Constants.cpp`
- `src/Constants.h`
- `src/TextAnalyzer.cpp`
- `tests/`
- `docs/analysis.md`

## Task
1. `SENTIMENT_KEYWORDS` 구조를 확인한다.
2. 긍정/부정/중립 키워드 목록을 비교해 중복을 찾는다.
3. 중복 키워드별 감성 분류 근거를 판단한다.
4. 필요한 최소 정제를 수행한다.
5. 관련 테스트를 실행한다.
6. 정제 기준을 `SESSION_NOTES.md`에 기록한다.
7. `TODO.md`의 `REFACTOR-01-06` 체크박스를 `[x]`로 갱신한다.

## Format
최종 응답에는 제거/이동한 키워드, 판단 근거, 테스트 결과, `REFACTOR-01-06` 완료 여부를 포함한다.

# 7-Step

1. Observe: 감성 키워드 맵을 읽고 중복을 찾는다.
2. Frame: 사전 정제 외 로직 변경은 하지 않는다.
3. Contract: 한 키워드는 하나의 감성 의미로만 해석되게 한다.
4. Trace: 중복 키워드가 분석 결과에 미치는 영향을 확인한다.
5. Write: 최소 정제를 수행한다.
6. Verify: 감성 분석 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


