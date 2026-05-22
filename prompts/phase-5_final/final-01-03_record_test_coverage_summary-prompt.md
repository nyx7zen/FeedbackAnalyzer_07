# FINAL-01-03 실행 프롬프트

## 호출 문구

- `57번 진행`
- `FINAL-01-03 진행`
- `FINAL-01-03 항목을 진행해 주세요`
- `docs: record test coverage summary 실행`

---

## 프롬프트

````md
Feedback Analyzer 테스트 커버리지 요약 전문가 - 최종 테스트 범위 기록

`TODO.md`의 `FINAL-01-03 docs: record test coverage summary` 항목을 실행하라.

목표는 GTest 단위 테스트 타깃의 최종 커버리지 정보를 정리하고, 테스트 범위와 결과를 비교표로 작성하는 것이다.

제약:
- 코드 변경 금지
- 실제 커버리지 도구가 없으면 테스트 범위 요약으로 대체하고 명시
- 테스트 명령과 결과는 실제 실행 또는 최근 검증 기록에 근거
- 실패/미검증 영역을 숨기지 말 것
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 최종 테스트가 어떤 모듈과 위험을 보호하는지 설명한다.
- 정량 커버리지와 정성 테스트 범위를 구분해 기록한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/final.md`
- `docs/bug_fix.md`
- `docs/feature.md`
- `tests/`
- `CMakeLists.txt`
- `SESSION_NOTES.md`

## Task
1. GTest 타깃과 테스트 파일 목록을 확인한다.
2. 테스트 케이스가 보호하는 영역을 분류한다.
3. 가능하면 최종 `ctest` 결과를 확인한다.
4. 커버리지 도구 결과가 있으면 기록하고, 없으면 범위 요약으로 대체한다.
5. `docs/final.md`에 테스트 커버리지/범위 섹션을 추가한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
보고서 표:
```md
| 테스트 파일 | 대상 모듈 | 보호하는 동작 | 결과 |
|---|---|---|---|
```

최종 응답에는 테스트 파일 목록, 검증 결과, 커버리지 도구 사용 여부, `FINAL-01-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: 테스트 타깃과 테스트 파일을 확인한다.
2. Frame: 테스트 범위 요약에 집중한다.
3. Contract: 도구 기반 커버리지와 범위 요약을 구분한다.
4. Trace: 테스트 파일 -> 대상 모듈 -> 보호 동작 흐름을 정리한다.
5. Write: `docs/final.md`에 기록한다.
6. Verify: 테스트 목록과 문서 표가 일치하는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


