# RED-01-01 실행 프롬프트

## 호출 문구

- `8번 진행`
- `RED-01-01 진행`
- `RED-01-01 항목을 진행해 주세요`
- `test: configure gtest target 실행`

---

## 프롬프트

````md
Feedback Analyzer GTest 테스트 타깃 구성 전문가 - C++17/CMake RED 단계

`TODO.md`의 `RED-01-01 test: configure gtest target` 항목을 실행하라.

너는 C++17, CMake, Google Test 기반 테스트 환경을 최소 변경으로 구성하는 테스트 인프라 담당자다.
이번 작업의 목표는 Feedback Analyzer 프로젝트에 GTest 기반 테스트 타깃을 추가하고, 테스트 빌드와 실행이 가능한 최소 구성을 만드는 것이다.

제약:
- 생산 코드의 동작 변경 금지
- 테스트 인프라와 필요한 최소 테스트 스켈레톤만 추가
- 기존 CMake 타깃과 빌드 명령을 깨지 않기
- Windows MinGW 환경을 기본 전제로 작성
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

RED 단계의 실패 테스트를 작성할 수 있도록 GTest 실행 기반을 만든다.

완료 후 다음이 가능해야 한다.

- `cmake --build build`로 테스트 타깃까지 빌드할 수 있다.
- `ctest --test-dir build --output-on-failure`로 테스트를 실행할 수 있다.
- 이후 `tests/TextAnalyzerTest.cpp` 같은 테스트 파일을 자연스럽게 추가할 수 있다.
- 테스트 타깃 구성 방식이 `AGENTS.md`의 MinGW/CMake 기준과 충돌하지 않는다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `CMakeLists.txt`
- `README.md`
- `src/`
- `tests/`가 있으면 해당 폴더

프로젝트 전제:

- C++17 프로젝트다.
- CMake 3.14 이상을 사용한다.
- 테스트 프레임워크는 Google Test를 기본값으로 한다.
- 기존 실행 애플리케이션 빌드를 깨면 안 된다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `RED-01-01` 항목을 확인한다.
2. `CMakeLists.txt`의 현재 타깃 구성을 읽는다.
3. 테스트 대상 소스와 `main.cpp` 의존성을 분리할 수 있는지 확인한다.
4. `tests/` 폴더가 없으면 생성한다.
5. GTest 기반 테스트 타깃을 CMake에 추가한다.
6. 최소 smoke test 또는 빈 테스트 스켈레톤을 추가해 테스트 실행 경로를 만든다.
7. 가능한 경우 configure, build, ctest를 실행한다.
8. 문서 또는 설정 변경이 발생하면 `SESSION_NOTES.md`에 로그를 추가한다.
9. 작업 완료 후 `TODO.md`의 `RED-01-01` 체크박스를 `[x]`로 갱신한다.

## 1.4 Format

변경 후보:

- `CMakeLists.txt`
- `tests/CMakeLists.txt` 또는 루트 CMake 내 테스트 섹션
- `tests/SmokeTest.cpp`
- `SESSION_NOTES.md`
- `TODO.md`

테스트 명령:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
ctest --test-dir build --output-on-failure
```

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- `RED-01-01` 완료 여부
- 실행한 빌드/테스트 명령과 결과
- 실패했다면 실패 원인과 다음 조치
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

CMake 구조와 소스 구성을 확인한다.

확인할 질문:

- 테스트 타깃이 이미 있는가?
- `main.cpp`를 테스트 타깃에 함께 링크하면 중복 `main` 문제가 생기는가?
- 도메인 소스만 별도 라이브러리로 묶을 필요가 있는가?
- 외부 GTest를 어떻게 가져오는 것이 현재 환경에서 가장 안전한가?

## Step 2. Frame

이번 작업은 테스트 인프라 구축이다.

수행하지 말아야 할 일:

- 기능 버그 수정
- 분석 로직 리팩토링
- RED 실패 테스트 대량 추가
- 임의의 패키지 매니저 도입

## Step 3. Contract

테스트 인프라 계약을 다음처럼 고정한다.

- 테스트 파일은 `tests/` 아래에 둔다.
- CTest에서 발견 가능한 테스트 타깃을 만든다.
- 테스트 실행 실패와 빌드 실패를 구분해 보고한다.
- 네트워크 의존이 필요한 경우 승인 또는 대체 경로를 명확히 한다.

## Step 4. Trace

빌드 흐름을 추적한다.

```text
CMake configure -> GTest 준비 -> 테스트 실행 파일 빌드 -> add_test 등록 -> ctest 실행
```

## Step 5. Write

CMake와 최소 테스트 파일을 작성한다.

문장/코드 기준:

- CMake 변경은 기존 스타일과 버전을 따른다.
- 테스트 이름은 이후 규칙인 `should_[result]_when_[condition]` 흐름을 방해하지 않는다.
- 테스트 스켈레톤은 생산 코드 동작을 바꾸지 않는다.

## Step 6. Verify

가능하면 configure, build, ctest를 실행한다.

검증 기준:

- 테스트 타깃이 빌드된다.
- CTest가 테스트를 발견한다.
- 실패가 있다면 인프라 문제인지 의도된 RED 실패인지 구분한다.

## Step 7. Close

마무리 작업:

- `SESSION_NOTES.md`에 테스트 인프라 구성 로그를 추가한다.
- `TODO.md`의 `RED-01-01` 체크박스를 `[x]`로 변경한다.
- 최종 응답에서 변경 파일, 검증 결과, 다음 추천 항목을 간결히 보고한다.
````


