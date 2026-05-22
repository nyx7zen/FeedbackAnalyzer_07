# SPEC-01-02 실행 프롬프트

## 호출 문구

- `2번 진행`
- `SPEC-01-02 진행`
- `SPEC-01-02 항목을 진행해 주세요`
- `docs: document build and test commands 실행`

---

## 프롬프트

````md
Feedback Analyzer 빌드/테스트 명령 문서화 전문가 - Windows MinGW/CMake

`TODO.md`의 `SPEC-01-02 docs: document build and test commands` 항목을 실행하라.

너는 C++17, CMake, MinGW 기반 프로젝트의 재현 가능한 빌드/테스트 절차를 문서화하는 기술 문서 작성자다.
이번 작업의 목표는 Feedback Analyzer 프로젝트를 다른 작업자가 같은 방식으로 구성, 빌드, 테스트할 수 있도록 명령과 기준을 명확히 기록하는 것이다.

제약:
- 구현 코드 변경 금지
- 테스트 코드 작성 금지
- CMake 동작 변경 금지
- 실제 빌드/테스트 실행은 선택 사항이며, 문서화가 주목적이다
- 명령은 Windows PowerShell + MinGW 환경을 기본값으로 작성
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

MinGW/CMake 기준 빌드 명령과 테스트 실행 기준을 문서화한다.

문서에는 다음 목적이 드러나야 한다.

- 어떤 컴파일러와 CMake generator를 기본으로 쓰는지
- 최초 configure 명령과 반복 build 명령이 어떻게 다른지
- 테스트 실행 명령은 무엇인지
- 실패 시 어떤 로그를 우선 확인해야 하는지
- 문서 작업만 수행한 경우 빌드/테스트 미실행 사실을 어떻게 기록하는지

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `README.md`
- `CMakeLists.txt`
- `refs/project_purpose.md`

필요하면 다음 경로도 확인한다.

- `tests/`
- `build/`
- `src/`

프로젝트 전제:

- C++17 기반 프로젝트다.
- CMake 3.14 이상을 사용한다.
- Windows MinGW 환경을 기본 전제로 한다.
- 기본 컴파일러 경로는 `C:/mingw64/bin/g++.exe`이다.
- 기본 테스트 실행 기준은 `ctest --output-on-failure`이다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `SPEC-01-02` 항목을 확인한다.
2. `AGENTS.md`의 Build And Test 지침을 확인한다.
3. `CMakeLists.txt`에서 프로젝트 이름, C++ 표준, 실행 타깃, 테스트 타깃 구성 여부를 확인한다.
4. `README.md`에 이미 빌드/테스트 명령이 있는지 확인한다.
5. 기존 문서와 충돌하지 않도록 빌드/테스트 명령을 정리한다.
6. 필요한 문서를 작성하거나 갱신한다.
7. 문서 변경이 발생하면 `SESSION_NOTES.md`에 세션 로그를 추가한다.
8. 작업 완료 후 `TODO.md`의 `SPEC-01-02` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

빌드/테스트 문서는 기존 문서 구조에 맞춰 작성한다.
추천 위치는 다음 순서로 판단한다.

1. `README.md`에 사용자 실행 안내로 추가
2. `docs/build_and_test.md`로 별도 문서 생성
3. `docs/analysis.md`의 환경 섹션에 요약

문서에는 최소한 다음 섹션을 포함한다.

```md
# 빌드 및 테스트 명령

## 1. 환경 전제

## 2. 최초 CMake 구성

## 3. 빌드

## 4. 테스트 실행

## 5. 실패 시 확인 지점

## 6. 문서 작업 시 검증 기록 기준
```

필수 명령:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `SPEC-01-02` 완료 여부
- 빌드/테스트 실행 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

`AGENTS.md`, `CMakeLists.txt`, `README.md`를 읽고 현재 빌드/테스트 기준을 확인한다.

확인할 질문:

- CMake 최소 버전은 무엇인가?
- C++ 표준은 무엇인가?
- 실행 파일 타깃 이름은 무엇인가?
- 테스트 타깃이 이미 존재하는가?
- README와 AGENTS의 명령이 충돌하는가?

## Step 2. Frame

이번 작업은 명령 문서화가 범위다.

수행하지 말아야 할 일:

- CMake 타깃 추가
- 테스트 프레임워크 설치
- 소스 코드 수정
- 의존성 다운로드

## Step 3. Contract

빌드/테스트 명령 계약을 다음처럼 고정한다.

- 최초 구성은 `cmake -S . -B build -G "MinGW Makefiles" ...`를 사용한다.
- 반복 빌드는 `cmake --build build`를 사용한다.
- 테스트는 가능한 경우 `ctest --test-dir build --output-on-failure`를 사용한다.
- 테스트 타깃이 아직 없으면 “테스트 타깃 미구성” 상태를 문서에 기록한다.

## Step 4. Trace

사용자가 저장소를 받은 뒤 실행하는 흐름을 순서대로 적는다.

```text
저장소 확인 -> CMake configure -> build 생성 -> 실행 파일 빌드 -> ctest 실행 -> 실패 로그 확인
```

## Step 5. Write

문서를 작성하거나 갱신한다.

문장 기준:

- 명령은 복사해서 실행 가능한 PowerShell 코드블록으로 작성한다.
- 경로 구분자는 프로젝트 기존 스타일과 Windows 환경을 고려한다.
- 테스트가 아직 준비되지 않은 경우에도 실행 기준은 명확히 둔다.
- “필요 시” 같은 표현은 구체적인 조건과 함께 쓴다.

## Step 6. Verify

작성 후 다음 조건을 자체 검수한다.

- `AGENTS.md`의 기본 빌드 명령과 일치한다.
- `CMakeLists.txt`의 현재 타깃 구성과 충돌하지 않는다.
- 테스트 명령에 `--output-on-failure`가 포함되어 있다.
- 문서만 변경했다면 빌드/테스트 미실행 사실을 기록한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 문서화 로그를 추가한다.
- `TODO.md`의 `SPEC-01-02` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일, 완료 여부, 검증 여부, 다음 추천 항목을 간결히 보고한다.
````


