# FEATURE-03-02 실행 프롬프트

## 호출 문구

- `54번 진행`
- `FEATURE-03-02 진행`
- `FEATURE-03-02 항목을 진행해 주세요`
- `docs: record feature verification 실행`

---

## 프롬프트

````md
Feedback Analyzer 기능 검증 기록 전문가 - FEATURE 테스트 로그 문서화

`TODO.md`의 `FEATURE-03-02 docs: record feature verification` 항목을 실행하라.

목표는 기능 테스트 명령을 `docs/feature.md`에 기록하고, 검증 결과와 남은 제약 사항을 정리하는 것이다.

제약:
- 가능하면 실제 build/ctest를 실행
- 실행하지 못한 명령은 이유를 명확히 기록
- 긴 로그 전체가 아니라 핵심 결과를 표로 요약
- 코드 변경 금지
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- FEATURE 단계 기능이 어떤 테스트로 검증되었는지 추적 가능하게 남긴다.
- 남은 제약과 후속 REPORT 단계 검수 기준을 정리한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `docs/feature.md`
- `tests/`
- `CMakeLists.txt`
- `SESSION_NOTES.md`

검증 명령 후보:
```powershell
cmake --build build
ctest --test-dir build --output-on-failure
```

## Task
1. `docs/feature.md`의 검증 섹션을 확인한다.
2. build와 ctest를 실행한다.
3. 기능별 테스트 결과를 정리한다.
4. 실패 또는 미검증 항목을 남은 제약 사항으로 기록한다.
5. `docs/feature.md`를 갱신한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
`docs/feature.md`에 다음 섹션을 추가하거나 갱신한다.
```md
## 검증 결과

| 기능 | 명령 | 결과 | 비고 |
|---|---|---|---|

## 남은 제약 사항
```

최종 응답에는 실행한 명령, 검증 결과, 남은 제약, `FEATURE-03-02` 완료 여부를 포함한다.

# 7-Step

1. Observe: feature 문서와 테스트 구성을 확인한다.
2. Frame: 검증 기록 작성에 집중한다.
3. Contract: 실제 실행 결과와 문서 내용이 일치해야 한다.
4. Trace: test command -> result -> feature.md 기록 흐름을 확인한다.
5. Write: 검증 결과를 문서화한다.
6. Verify: 문서가 실행 결과와 충돌하지 않는지 확인한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


