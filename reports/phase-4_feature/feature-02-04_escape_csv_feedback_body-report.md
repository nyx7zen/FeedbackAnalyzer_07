# FEATURE-02-04: CSV 피드백 본문 이스케이프

**실행 일시:** 2026-05-22  
**담당자:** Claude Haiku 4.5  
**상태:** 완료 ✓

## 목표

피드백 본문 내 줄바꿈, 쉼표, 쌍따옴표 등 특수문자를 처리하여 CSV 형식의 필드 무결성을 보장한다.

## 발견

### 현재 구현

FileHandler.cpp의 `escapeCsvField()` 메서드가 CSV 필드 이스케이프를 구현합니다.

**구현 코드:**
```cpp
std::string FileHandler::escapeCsvField(const std::string& value) const {
    std::string escaped = "\"";
    for (const char ch : value) {
        if (ch == '"') {
            escaped += "\"\"";  // 쌍따옴표 2배 변환
        } else {
            escaped += ch;
        }
    }
    escaped += "\"";
    return escaped;
}
```

### 이스케이프 전략

| 특수문자 | 처리 방식 | 예시 |
|---|---|---|
| `"` (쌍따옴표) | `""` (2배) | `a"b` → `"a""b"` |
| `,` (쉼표) | 따옴표로 감쌈 | `a,b` → `"a,b"` |
| `\n` (줄바꿈) | 따옴표로 감쌈 | `a\nb` → `"a\nb"` |
| 기타 | 그대로 포함 | - |

### 적용 규칙

**RFC 4180 CSV 표준:**
1. 모든 필드를 쌍따옴표로 감쌈
2. 필드 내 쌍따옴표는 2개로 변환
3. 줄바꿈과 쉼마는 따옴표로 자동 처리

## 변경 사항

**코드 변경:** 없음 (이미 구현됨)

## 검증

### 테스트 결과

FileHandlerTest에서 이스케이프 검증 테스트 통과:

```cpp
// Test 6: CSV should contain feedback rows with field escaping
std::vector<Feedback> feedbacks;
feedbacks.emplace_back(u8"내용에 \"쌍따옴표\" 있음");

std::string content = fixture.readFileContent(outputPath);
bool hasEscapedQuotes = (content.find("\"\"") != std::string::npos);
```

**결과:** ✓ 통과

### 시나리오 검증

| 입력 | 출력 | 상태 |
|---|---|---|
| `test` | `"test"` | ✓ |
| `a"b` | `"a""b"` | ✓ |
| `a,b` | `"a,b"` | ✓ |
| `a\nb` | `"a\nb"` | ✓ |

## 기술 세부사항

### 알고리즘

1. 문자열 앞에 따옴표 추가
2. 각 문자 순회
3. 쌍따옴표 발견 시 2개로 변환
4. 문자열 뒤에 따옴표 추가

### 성능

- 시간 복잡도: O(n) (n = 문자열 길이)
- 공간 복잡도: O(n) (이스케이프된 문자열)

## CSV 호환성

### Microsoft Excel

- 따옴표로 감싼 필드 인식
- 쌍따옴표 변환 인식
- 멀티라인 필드 지원

### 표준 준수

- RFC 4180: CSV 형식 표준
- UTF-8 인코딩 호환

## 결론

FEATURE-02-04는 완료되었습니다. CSV 필드 이스케이프가 RFC 4180 표준을 따르며 구현되었고, 모든 테스트를 통과합니다.

**완료 여부:** ✓ 완료
