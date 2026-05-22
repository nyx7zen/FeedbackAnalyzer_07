# CLAUDE.md — Feedback Analyzer

## 프로젝트 개요

고객 피드백 데이터를 수집·분류·시각화하는 C++17 기반 웹 애플리케이션.
**목적**: 레거시 코드 스멜을 직접 식별하고 단계적으로 리팩토링하는 실습 프로젝트.

- 런타임: `http://localhost:8080`
- 빌드 시스템: CMake 3.14+, MinGW g++
- 테스트 프레임워크: Google Test (GTest)
- 의존성: cpp-httplib (헤더 전용), nlohmann/json (선택)

---

## 빌드 및 실행

```powershell
# 빌드 (빌드 디렉터리 초기화 포함)
rmdir /q /s build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe
cmake --build build

# 실행
build\feedback_analyzer.exe

# 테스트
cmake -B build && cmake --build build
cd build && ctest --output-on-failure
```

---

## 프로젝트 구조

```
FeedbackAnalyzer_07/
├── src/cpp/
│   ├── main.cpp          # HTTP 서버, 라우팅, HTML 렌더링 (God Function 포함)
│   ├── httplib.h          # cpp-httplib 헤더 전용 라이브러리
│   ├── Feedback.h         # 피드백 데이터 모델
│   ├── TextAnalyzer.h/cpp # 감성 분석, 키워드 추출
│   ├── Filters.h/cpp      # 피드백 필터링
│   ├── UIComponents.h/cpp # UI 컴포넌트
│   ├── Session.h/cpp      # 전역 상태 관리 (리팩토링 대상)
│   ├── Logger.h/cpp       # 로그 출력
│   ├── Constants.h/cpp    # 감성 키워드 사전
│   ├── FileHandler.h/cpp  # CSV 파일 처리 (현재 stub 상태)
│   └── TextUtils.h        # 공통 유틸리티 (리팩토링 후 추가 예정)
├── tests/                 # GTest 단위 테스트
├── CMakeLists.txt
└── build/                 # 빌드 산출물 (커밋 제외)
```

---

## 브랜치 전략

```
maintdd (레거시 기준점) → refactoring (구조 개선 및 버그 수정) → feature (신규 기능)
```

- 로컬에서 직접 병합 금지 — 반드시 GitHub PR을 통해 팀원 리뷰 후 병합

---

## 커밋 메시지 규칙 (Conventional Commits)

| 접두사 | 용도 |
|--------|------|
| `feat:` | 신규 기능 (가중치 감성 분석, CSV 저장 등) |
| `fix:` | 버그 수정 (중립 필터 오류 등) |
| `refactor:` | 구조 개선 (메서드 추출, 전역 변수 제거 등) |
| `test:` | GTest 케이스 추가/수정 |
| `docs:` | 마크다운 문서 작성 |
| `chore:` | CMakeLists.txt 등 인프라 변경 |

---

## C++ 코딩 표준

### 필수 규칙

1. **매직 넘버 상수화**: 하드코딩된 문자열("긍정", "부정", "중립") 및 임계값은 헤더 내 `static constexpr` 또는 `const` 상수로 관리
2. **단일 책임 함수**: 함수 길이 최대 20줄. 초과 시 의무적으로 서브루틴 추출(Extract Method)
3. **Doxygen 문서화**: 모든 `public` 클래스·메서드·함수에 `@brief`, `@param`, `@return` 주석 필수
4. **테스트 네이밍**: GTest 케이스는 `should_[결과]_when_[조건]` 형식 엄수

### 네이밍 교정 (리팩토링 대상)

| Before (레거시) | After (개선) |
|----------------|-------------|
| `sent()` | `analyzeSentiment()` |
| `kw()` | `analyzeKeywords()` |
| `fil()` | `applyFilter()` |
| `fil_data` | 세션 컨텍스트 객체로 이동 |
| `globalSent`, `globalKw` | `FeedbackSession` 내부 상태로 캡슐화 |

---

## 알려진 코드 스멜 및 개선 대상

| 파일 | 문제 | 우선순위 |
|------|------|---------|
| `main.cpp` | HTML 렌더링·라우팅·비즈니스 로직 혼재 (God Function) | 높음 |
| `Filters.cpp` | '중립' 필터 조건문 버그 (논리 연산자 오류) | 높음 |
| `Session.cpp` | 전역 `static` 변수로 테스트 격리 불가 | 높음 |
| `Constants.cpp` | 긍정/부정 사전에 동일 키워드 중복 등록 | 중간 |
| `TextAnalyzer.cpp` + `Filters.cpp` | `containsAny()` 로직 중복 구현 | 중간 |
| `FileHandler.cpp` | `saveResult()`가 콘솔 출력만 하는 stub 상태 | 중간 |
| `main.cpp` | 텍스트 입력창이 단일 라인 `<input>` (멀티라인 미지원) | 낮음 |
| `Logger.cpp` | 로그 레벨 동적 제어 미구현 | 낮음 |

---

## 리팩토링 8단계 로드맵

1. **구조 진단** → `analysis.md` 작성
2. **GTest 프레임워크 구축** → `tests/TextAnalyzerTest.cpp` (커버리지 90%+ 목표)
3. **긴급 버그 수정** → 중립 필터, textarea 멀티라인, 로그 레벨 → `bug_fix.md`
4. **네이밍 & 상수화** → `refactoring.md`
5. **중복 코드 제거** → `TextUtils.h` 추출, 함수 20줄 이하 준수
6. **전역 상태 해체** → `FeedbackSession` API 현대화
7. **신규 기능 구현** → 가중치 감성 스코어링, RAII CSV 저장 → `feature.md`
8. **최종 보고서** → `report.md` (LOC 증감, 커버리지, 복잡도 비교)

---

## 신규 기능 명세

### 가중치 감성 분석 (`TextAnalyzer`)

- 기존: 첫 번째 키워드 매칭 즉시 종료
- 개선: 전체 문장 순회 후 `Score = Count(긍정) - Count(부정)` 수식 적용

### RAII CSV 저장 (`FileHandler`)

- `std::ofstream` 기반 실제 파일 쓰기
- UTF-8 BOM(`\xEF\xBB\xBF`) 주입 (Excel 호환)
- 쌍따옴표 이중 래핑(Double Quote Wrapping) 처리
- `try-catch` 예외 처리

---

## 제출 산출물 (5종 마크다운)

| 파일 | 내용 |
|------|------|
| `analysis.md` | 6대 코드 스멜 심각도 분석 |
| `bug_fix.md` | 버그 수정 전후 논리식 대조 및 테스트 로그 |
| `refactoring.md` | 네이밍 매핑 테이블 + Session 라이프사이클 다이어그램 |
| `feature.md` | 가중치 분석 및 CSV 저장 기능 명세 |
| `report.md` | 리팩토링 전후 LOC·커버리지·복잡도 정량 비교 |
