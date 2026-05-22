# FEATURE 단계 기능 명세

## 1. 개요

FEATURE 단계는 Feedback Analyzer에 가중치 기반 감성 스코어링과 CSV 영구 저장 기능을 추가하는 단계입니다. 2026-05-22에 5개 항목을 완료했습니다.

**주요 성과:**
- 가중치 기반 감성 스코어링: 긍정/부정 단어 누적 카운트로 상대적 감성 판정
- CSV 파일 영구 저장: std::ofstream 기반 RAII 파일 쓰기
- UTF-8 BOM 자동 추가: CSV 파일 호환성 보장
- CSV 필드 이스케이프: 쌍따옴표, 줄바꿈 등 특수문자 처리
- 파일 I/O 오류 처리: try-catch 기반 예외 처리

**단계 진행:**
- FEATURE-01: 가중치 감성 스코어링 (5개 항목 완료)
- FEATURE-02: CSV 저장 기능 (5개 항목 완료)
- FEATURE-03: 기능 명세 및 검증 (2개 항목 진행 중)

## 2. 가중치 기반 감성 스코어링

### 2.1 알고리즘

감성 점수는 다음 수식으로 계산됩니다:

```
Score = Count(긍정 키워드) - Count(부정 키워드)
```

**특징:**
- 문장 전체를 순회하며 모든 감성 키워드를 누적
- 긍정 단어가 많을수록 점수가 높음
- 부정 단어가 많을수록 점수가 낮음
- 상대적 비교로 감성 강도 표현

### 2.2 감성 판정 기준

| 조건 | 결과 | 비고 |
|---|---|---|
| Score >= 1 | 긍정 | 긍정 단어가 부정 단어를 1개 이상 초과 |
| -1 < Score < 1 | 중립 | 긍정과 부정이 대등하거나 비슷함 |
| Score <= -1 | 부정 | 부정 단어가 긍정 단어를 1개 이상 초과 |

**임계값:**
```cpp
kPositiveThreshold = 1   // 긍정 판정 최소값
kNegativeThreshold = -1  // 부정 판정 최대값
```

### 2.3 키워드 사전

**긍정 키워드 예시** (32개):
- 좋아요, 만족, 우수, 탁월, 훌륭, 나이스, 최고, 쾌적, 편리, ...

**부정 키워드 예시** (28개):
- 별로, 실망, 불만, 나쁨, 끔찍, 형편, 싫어, 불편, ...

**키워드 중복:**
- 중복 제거 완료: 기존 사전에 겹치는 단어 없음

### 2.4 구현 위치

| 파일 | 함수 | 역할 |
|---|---|---|
| TextAnalyzer.cpp | `detectSentiment()` | 입력 텍스트의 감성 판정 |
| TextAnalyzer.cpp | `getSentimentScore()` | 감성 점수 계산 및 반환 |
| TextAnalyzer.cpp | `getPositiveKeywordCount()` | 긍정 키워드 개수 |
| TextAnalyzer.cpp | `getNegativeKeywordCount()` | 부정 키워드 개수 |

### 2.5 테스트 커버리지

| 테스트 항목 | 상태 | 검증 |
|---|---|---|
| 긍정 문장 판정 | 통과 | Score >= 1 반환 |
| 부정 문장 판정 | 통과 | Score <= -1 반환 |
| 중립 문장 판정 | 통과 | -1 < Score < 1 반환 |
| 혼재 문장 판정 | 통과 | 상대적 점수 비교 |
| 빈 문장 처리 | 통과 | 중립 판정 (Score = 0) |

## 3. CSV 영구 저장

### 3.1 저장 프로세스

```
입력 피드백 → buildCsvContent() → CSV 문자열 → ofstream → 파일 저장
```

**흐름:**
1. 피드백 목록(std::vector<Feedback>) 입력
2. buildCsvContent()로 CSV 형식 문자열 생성
3. saveResult()로 std::ofstream을 통해 파일 쓰기
4. RAII 소멸자에 의한 자동 파일 닫기

### 3.2 CSV 형식

**구조:**
```
[UTF-8 BOM (3바이트)]
text\n
"긍정 피드백"\n
"부정 피드백"\n
...
```

**구성 요소:**
- 첫 3바이트: UTF-8 BOM (`\xEF\xBB\xBF`)
- 첫 행: 헤더 ("text")
- 이후 행: 이스케이프된 피드백 본문

### 3.3 CSV 필드 이스케이프

| 특수문자 | 처리 | 예시 |
|---|---|---|
| `"` (쌍따옴표) | `""`로 변환 | `a"b` → `a""b` |
| 줄바꿈 (\n) | 문자 그대로 포함 | 전체 필드를 "..."로 감싸서 처리 |
| 쉼표 (,) | 문자 그대로 포함 | 전체 필드를 "..."로 감싸서 처리 |

**적용 규칙:**
```cpp
// 모든 필드를 쌍따옴표로 감쌈
"필드 내용"

// 내부 따옴표는 2개로 변환
"필드 ""내용"""
```

### 3.4 파일 I/O 오류 처리

**try-catch 기반:**
```cpp
try {
    std::ofstream output(outputPath, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("파일 열기 실패");
    }
    output << csvContent;
    if (!output.good()) {
        throw std::runtime_error("파일 쓰기 실패");
    }
} catch (const std::exception& e) {
    // 예외 재던지기
    throw;
}
```

**처리 대상:**
- 파일 열기 실패
- 쓰기 중 I/O 오류
- 디스크 공간 부족 등

### 3.5 구현 위치

| 파일 | 함수 | 역할 |
|---|---|---|
| FileHandler.cpp | `saveResult()` | ofstream 기반 파일 쓰기 |
| FileHandler.cpp | `save()` | 기본 경로("filtered_feedback.csv")로 저장 |
| FileHandler.cpp | `buildCsvContent()` | CSV 형식 문자열 생성 |
| FileHandler.cpp | `escapeCsvField()` | 필드 이스케이프 처리 |

### 3.6 API

```cpp
// 경로 지정 저장
void saveResult(const std::vector<Feedback>& data, 
                const std::string& outputPath) const;

// 기본 경로 저장
void save(const std::vector<Feedback>& data) const;

// CSV 내용 구성
std::string buildCsvContent(const std::vector<Feedback>& data) const;
```

### 3.7 테스트 커버리지

| 테스트 항목 | 상태 | 검증 |
|---|---|---|
| 파일 생성 | 통과 | saveResult() 후 파일 존재 확인 |
| UTF-8 BOM | 통과 | 파일 첫 3바이트 검증 |
| 헤더 행 | 통과 | "text" 헤더 포함 확인 |
| 데이터 행 | 통과 | 3개 피드백 저장 시 3개 행 생성 |
| 필드 이스케이프 | 통과 | 쌍따옴표 변환 (`""`) 확인 |
| 빈 피드백 | 통과 | 빈 목록도 헤더만 저장 |
| 내용 일치 | 통과 | buildCsvContent() == 파일 내용 |

## 4. 오류 처리

### 4.1 파일 I/O 오류

**발생 상황:**
- 디렉토리 권한 없음
- 디스크 공간 부족
- 파일 읽기/쓰기 실패

**처리 방식:**
```cpp
try {
    // 파일 쓰기 작업
} catch (const std::exception& e) {
    throw;  // 호출자로 예외 전파
}
```

### 4.2 입력 검증

**피드백 유효성:**
- 빈 문자열: 중립으로 판정 (점수 = 0)
- UTF-8 인코딩: 기본 가정
- 최대 길이: 제한 없음 (메모리 범위 내)

## 5. 테스트 기준

### 5.1 단위 테스트

**TextAnalyzerTest 항목:**
- 긍정 감정 문장 판정
- 부정 감정 문장 판정
- 중립 감정 문장 판정
- 혼재 감정 문장 판정
- 빈 입력 처리
- 특수문자 포함 처리

**FileHandlerTest 항목:**
- 핸들러 인스턴스 생성
- CSV 파일 생성
- UTF-8 BOM 확인
- 헤더 행 작성
- 데이터 행 작성
- 필드 이스케이프 처리
- 빈 피드백 목록 처리
- buildCsvContent() 일치성

### 5.2 테스트 실행 명령

```powershell
# 빌드
cmake --build build

# 테스트 실행
ctest --test-dir build --output-on-failure
```

## 6. 남은 제약 사항

### 6.1 CSV 저장 경로

**현재 제약:**
- 기본 저장 경로: "filtered_feedback.csv"
- 상대 경로 기준: 애플리케이션 실행 디렉토리

**개선 방향:**
- 절대 경로 지원
- 사용자 설정 디렉토리 지원

### 6.2 성능 고려사항

**대용량 피드백:**
- 메모리 기반 CSV 생성 (스트리밍 미지원)
- 대량(>10,000개) 피드백 처리 시 메모리 사용량 증가

### 6.3 인코딩

**현재 지원:**
- UTF-8 (BOM 포함)

**미지원:**
- UTF-16, EUC-KR 등 다른 인코딩

### 6.4 감성 사전 확장

**현재 상태:**
- 고정된 키워드 사전 (Constants.cpp)

**개선 방향:**
- 동적 키워드 추가/제거
- 사용자 정의 사전 로딩

## 7. 검증 결과

### 7.1 빌드 상태

| 항목 | 결과 | 비고 |
|---|---|---|
| CMake 구성 | 통과 | MinGW 호환 |
| 소스 컴파일 | 통과 | 경고 0개 |
| 테스트 링크 | 통과 | 8개 테스트 바이너리 생성 |

### 7.2 기능별 검증

| 기능 | 명령 | 결과 | 비고 |
|---|---|---|---|
| 감성 스코어링 | `./build/feedback_analyzer_test` | 통과 | 모든 시나리오 검증 |
| CSV 저장 | `./build/filehandler_test` | 통과 | 8개 테스트 모두 통과 |
| 통합 빌드 | `cmake --build build` | 통과 | 모든 타깃 성공 |

### 7.3 테스트 요약

```
FileHandlerTest 실행 결과:
- should_instantiate_handler_without_error: PASS
- should_create_csv_file_when_feedback_is_saved: PASS
- should_include_utf8_bom_in_csv_file: PASS
- should_write_header_row_in_csv_file: PASS
- should_write_feedback_rows_in_csv_file: PASS
- should_escape_csv_field_with_quotes: PASS
- should_write_header_even_with_empty_feedback_list: PASS
- should_match_buildCsvContent_when_saved: PASS

총 테스트: 8개
통과: 8개
실패: 0개
성공률: 100%
```
