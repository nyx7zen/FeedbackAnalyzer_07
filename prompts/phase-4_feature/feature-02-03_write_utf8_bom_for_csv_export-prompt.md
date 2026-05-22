# FEATURE-02-03 실행 프롬프트

## 호출 문구

- `50번 진행`
- `FEATURE-02-03 진행`
- `FEATURE-02-03 항목을 진행해 주세요`
- `feat: write utf8 bom for csv export 실행`

---

## 프롬프트

````md
Feedback Analyzer CSV UTF-8 BOM 구현 전문가 - Excel 호환 출력

`TODO.md`의 `FEATURE-02-03 feat: write utf8 bom for csv export` 항목을 실행하라.

목표는 CSV 파일 시작 위치에 UTF-8 BOM을 기록하고, BOM 인젝션 코드(`\xEF\xBB\xBF`)를 추가하는 것이다.

제약:
- BOM은 파일 시작 위치에 한 번만 기록
- 기존 CSV 내용 순서를 깨지 말 것
- 이미 파일에 append하는 구조라면 중복 BOM 위험을 검토
- 테스트로 첫 3바이트를 확인
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 한글 CSV가 Excel 등에서 UTF-8로 인식되도록 한다.
- CSV 저장 결과의 인코딩 호환성을 높인다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/FileHandler.cpp`
- `src/FileHandler.h`
- `tests/`
- `docs/feature.md`가 있으면 해당 문서

## Task
1. 현재 CSV 파일 열기 모드와 쓰기 순서를 확인한다.
2. 파일 시작에 UTF-8 BOM을 기록한다.
3. 첫 3바이트가 `EF BB BF`인지 검증하는 테스트를 추가 또는 갱신한다.
4. append 모드에서 중복 BOM이 생기지 않는지 확인한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
최종 응답에는 BOM 기록 위치, 중복 방지 기준, 테스트 결과, `FEATURE-02-03` 완료 여부를 포함한다.

# 7-Step

1. Observe: FileHandler의 파일 열기 모드와 write 순서를 확인한다.
2. Frame: BOM 기록 구현에 집중한다.
3. Contract: 새 CSV 파일의 첫 바이트는 UTF-8 BOM이어야 한다.
4. Trace: open file -> write BOM -> write csv rows 흐름을 확인한다.
5. Write: BOM 쓰기 로직을 추가한다.
6. Verify: 파일 바이트 테스트와 전체 테스트를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


