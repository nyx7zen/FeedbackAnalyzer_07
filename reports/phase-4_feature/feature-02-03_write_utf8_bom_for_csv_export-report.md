# FEATURE-02-03: CSV 내보내기 UTF-8 BOM 작성

**실행 일시:** 2026-05-22  
**담당자:** Claude Haiku 4.5  
**상태:** 완료 ✓

## 목표

CSV 파일 시작 위치에 UTF-8 BOM을 기록하여 Excel 및 다양한 텍스트 편집기에서 한글 인코딩 호환성을 보장한다.

## 발견

### 현재 구현

FileHandler.cpp의 `buildCsvContent()` 메서드에 UTF-8 BOM이 이미 포함되어 있습니다.

**구현 코드:**
```cpp
std::string FileHandler::buildCsvContent(const std::vector<Feedback>& data) const {
    std::string csv = "\xEF\xBB\xBF";  // UTF-8 BOM
    csv += "text\n";

    for (const auto& feedback : data) {
        csv += escapeCsvField(feedback.getText());
        csv += '\n';
    }

    return csv;
}
```

### UTF-8 BOM 정의

| 속성 | 값 |
|---|---|
| 바이트 수 | 3 |
| 16진수 | 0xEF 0xBB 0xBF |
| 문자열 표현 | `\xEF\xBB\xBF` |
| 목적 | 파일 인코딩 표시 및 호환성 |

### BOM 위치

- 파일의 최시작 (offset 0)
- 헤더("text") 직전
- 모든 데이터 행 이전

## 변경 사항

**코드 변경:** 없음 (이미 구현됨)

## 검증

### 테스트 결과

FileHandlerTest에서 BOM 검증 테스트 통과:
```cpp
// Test 3: CSV file should contain UTF-8 BOM
std::string content = fixture.readFileContent(outputPath);
bool hasBom = (content.size() >= 3 &&
              (unsigned char)content[0] == 0xEF &&
              (unsigned char)content[1] == 0xBB &&
              (unsigned char)content[2] == 0xBF);
```

**결과:** ✓ 통과

### BOM 검증 내용

- 파일 첫 3바이트 확인
- 각 바이트 값 검증
- UTF-8 BOM 표준 준수

## 기술 세부사항

| 항목 | 설명 |
|---|---|
| 인코딩 | UTF-8 |
| BOM 형식 | 3바이트 마커 |
| 호환성 | Microsoft Excel, 텍스트 편집기 |
| 표준 준수 | RFC 3629 |

## 효과

### Excel 호환성

UTF-8 BOM이 있으면 Excel에서 한글 CSV를 올바르게 인식합니다.
- BOM 없음: 한글 깨짐
- BOM 있음: 정상 표시

### 파일 크기 영향

CSV 파일 크기: 실제 내용 + 3 바이트 (BOM)

## 결론

FEATURE-02-03은 완료되었습니다. UTF-8 BOM이 buildCsvContent()의 시작 부분에 올바르게 삽입되며, 테스트를 통해 검증되었습니다.

**완료 여부:** ✓ 완료
