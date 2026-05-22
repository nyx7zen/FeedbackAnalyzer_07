# FEATURE-02-04 실행 프롬프트

## 호출 문구

- `51번 진행`
- `FEATURE-02-04 진행`
- `FEATURE-02-04 항목을 진행해 주세요`
- `feat: escape csv feedback body 실행`

---

## 프롬프트

````md
Feedback Analyzer CSV 필드 이스케이프 구현 전문가 - RFC 스타일 Double Quote Wrapping

`TODO.md`의 `FEATURE-02-04 feat: escape csv feedback body` 항목을 실행하라.

목표는 피드백 본문 내 줄바꿈, 쉼표, 쌍따옴표를 처리하고, 이중 래핑(Double Quote Wrapping) 방식으로 CSV 필드를 방어하는 것이다.

제약:
- CSV 필드 이스케이프는 재사용 가능한 작은 함수로 구현
- 쉼표/줄바꿈/따옴표가 없는 필드는 기존 출력과 호환
- 쌍따옴표는 `""`로 이스케이프
- 테스트로 특수 필드 사례를 검증
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 사용자 피드백 본문이 CSV 구조를 깨뜨리지 않게 한다.
- 여러 줄 피드백과 쉼표 포함 문장을 안전하게 저장한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/FileHandler.cpp`
- `src/FileHandler.h`
- `tests/`
- `GREEN-01-02` 다중 행 입력 변경 내역

## Task
1. 현재 CSV 행 출력 방식을 확인한다.
2. CSV 필드 escape helper를 구현한다.
3. 쉼표, 줄바꿈, 쌍따옴표 포함 피드백 테스트를 추가한다.
4. CSV 저장 테스트와 전체 테스트를 실행한다.
5. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
이스케이프 예:
```text
hello, world -> "hello, world"
hello "world" -> "hello ""world"""
line1\nline2 -> "line1\nline2"
```

최종 응답에는 escape 규칙, 추가한 테스트, 테스트 결과, `FEATURE-02-04` 완료 여부를 포함한다.

# 7-Step

1. Observe: 현재 CSV 필드 조립 방식을 확인한다.
2. Frame: CSV 본문 이스케이프 구현에 집중한다.
3. Contract: 구조 문자는 안전하게 quote 처리되어야 한다.
4. Trace: raw feedback -> escaped field -> csv row 흐름을 확인한다.
5. Write: escape helper와 호출부를 구현한다.
6. Verify: CSV edge case 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


