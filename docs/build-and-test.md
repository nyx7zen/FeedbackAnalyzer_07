# 빌드 및 테스트 명령

## 개요

Feedback Analyzer 프로젝트는 **Windows MinGW 환경**에서 CMake를 기반으로 빌드됩니다. 이 문서는 프로젝트 빌드, 테스트 실행, 디버깅 명령을 정리합니다.

---

## 빌드 환경

### 요구사항

- **언어:** C++17
- **빌드 시스템:** CMake 3.14+
- **컴파일러:** MinGW (g++ 기반)
- **테스트 프레임워크:** Google Test (gtest)
- **웹 라이브러리:** cpp-httplib

### MinGW 설치 확인

```bash
g++ --version
gcc --version
mingw32-make --version
```

---

## 빌드 명령

### 초기 빌드 (첫 실행)

CMake 설정 및 빌드를 함께 수행합니다:

```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
```

**설명:**
- `-S .` : 소스 디렉토리 지정 (현재 디렉토리)
- `-B build` : 빌드 디렉토리 지정 (`build` 폴더)
- `-G "MinGW Makefiles"` : 제너레이터로 MinGW Makefiles 사용
- `-DCMAKE_CXX_COMPILER=...` : MinGW g++ 경로 명시 (Windows에서 필수)

### 증분 빌드 (변경사항만 다시 빌드)

```bash
cmake --build build
```

또는 MinGW make 직접 사용:

```bash
mingw32-make -C build
```

### Clean 빌드 (완전히 다시 빌드)

```bash
cmake --build build --clean-first
```

또는:

```bash
rm -rf build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build
```

---

## 실행 명령

### 메인 프로그램 실행

```bash
./build/feedback_analyzer
```

또는:

```bash
./build/Debug/feedback_analyzer.exe  # Windows debug 빌드
```

### 프로그램에 입력 제공

```bash
echo "test input" | ./build/feedback_analyzer
```

---

## 테스트 명령

### Google Test 프레임워크 설정

CMakeLists.txt에서 Google Test를 설정합니다:

```cmake
# 테스트 활성화
enable_testing()

# Google Test 추가
find_package(GTest REQUIRED)

# 테스트 타깃 정의
add_executable(feedback_analyzer_tests
    tests/TextAnalyzerTest.cpp
)

target_link_libraries(feedback_analyzer_tests PRIVATE GTest::gtest GTest::gtest_main)

# 테스트 등록
add_test(NAME AnalyzerTests COMMAND feedback_analyzer_tests)
```

### 테스트 실행

#### 모든 테스트 실행

```bash
ctest --output-on-failure
```

**옵션:**
- `--output-on-failure` : 실패한 테스트의 상세 출력 표시
- `-V` : Verbose 모드 (모든 테스트 상세 출력)
- `--verbose` : 동일 (`-V`와 동일)

#### 특정 테스트만 실행

```bash
ctest -R TextAnalyzer --output-on-failure
```

**설명:**
- `-R <regex>` : 정규식으로 테스트 이름 필터링
- 예: `-R "should_.*_when"` : `should_`로 시작하는 테스트만 실행

#### 병렬 테스트 실행

```bash
ctest --output-on-failure -j 4
```

**설명:**
- `-j <num>` : 병렬 실행 스레드 수 지정

#### 테스트 목록 확인

```bash
ctest --show-only
```

---

## 빌드 및 테스트 통합 워크플로우

### 개발 사이클 (일반적인 작업)

```bash
# 1. 코드 변경 (에디터에서 작업)

# 2. 증분 빌드
cmake --build build

# 3. 테스트 실행
ctest --output-on-failure -j 4

# 4. 메인 프로그램 테스트 (수동 테스트)
./build/feedback_analyzer
```

### CI/CD 파이프라인 (자동화)

```bash
# 1. 초기 설정
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe

# 2. 빌드
cmake --build build

# 3. 모든 테스트 실행 (상세 출력)
ctest --build-config Release --output-on-failure -V
```

---

## 자주 사용하는 명령어 요약

| 용도 | 명령 |
|------|------|
| 초기 설정 및 빌드 | `cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe && cmake --build build` |
| 증분 빌드 | `cmake --build build` |
| Clean 빌드 | `cmake --build build --clean-first` |
| 모든 테스트 | `ctest --output-on-failure` |
| 테스트 (상세) | `ctest --output-on-failure -V` |
| 병렬 테스트 | `ctest --output-on-failure -j 4` |
| 메인 프로그램 실행 | `./build/feedback_analyzer` |

---

## 문제 해결

### CMake 생성 오류

**오류:** `cmake: command not found`

**해결:**
- CMake를 설치하거나 PATH에 추가하세요.
- MinGW 환경에서는 `cmake --version` 확인 후 설치합니다.

### 컴파일러 오류

**오류:** `g++: command not found` 또는 `clang: command not found`

**해결:**
- MinGW g++ 경로를 명시하세요: `-DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe`
- 또는 환경 변수 설정: `set CMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe`

### 테스트 실패

**오류:** `No tests were found!!!`

**해결:**
- CMakeLists.txt에서 `enable_testing()` 호출 확인
- 테스트 소스 파일이 `tests/` 디렉토리에 있는지 확인
- CMakeLists.txt에서 테스트 타깃이 등록되었는지 확인

### 링크 오류

**오류:** `undefined reference to ...`

**해결:**
- 필요한 라이브러리가 `target_link_libraries()`에 포함되었는지 확인
- Google Test 라이브러리 경로 확인: `find_package(GTest REQUIRED)`

---

## 참고

- [CMake 공식 문서](https://cmake.org/cmake/help/latest/)
- [Google Test 가이드](https://github.com/google/googletest)
- [MinGW 설정 가이드](https://www.mingw-w64.org/)

