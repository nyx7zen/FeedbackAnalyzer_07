# REFACTOR-02-01 실행 프롬프트

## 호출 문구

- `32번 진행`
- `REFACTOR-02-01 진행`
- `REFACTOR-02-01 항목을 진행해 주세요`
- `refactor: add text utils containsAny 실행`

---

## 프롬프트

````md
Feedback Analyzer 텍스트 유틸리티 리팩토링 전문가 - containsAny 도입

`TODO.md`의 `REFACTOR-02-01 refactor: add text utils containsAny` 항목을 실행하라.

목표는 `src/TextUtils.h` 헤더 파일을 생성하고, `std::any_of`와 `std::string::find`를 활용한 `containsAny` 인라인 유틸리티 함수를 구현하는 것이다.

제약:
- 기존 분석/필터 동작 변경 금지
- 새 전역 상태 추가 금지
- 헤더 전용 inline 함수로 작게 구현
- 함수명과 namespace는 기존 스타일을 우선
- 사용자 응답과 생성 문서는 한국어로 작성

# PCTF

## Purpose
- 중복 문자열 검색 로직을 통합할 공용 유틸리티를 만든다.
- 이후 TextAnalyzer와 Filters에서 같은 검색 함수를 재사용하게 한다.

## Context
반드시 확인한다.
- `TODO.md`
- `AGENTS.md`
- `src/TextAnalyzer.cpp`
- `src/Filters.cpp`
- `src/Constants.h`
- `tests/`

## Task
1. 문자열 검색 중복 패턴을 확인한다.
2. `src/TextUtils.h`를 생성한다.
3. 문자열과 키워드 목록을 받아 포함 여부를 반환하는 `containsAny`를 구현한다.
4. 가능한 경우 단위 테스트를 추가하거나 기존 테스트로 컴파일을 검증한다.
5. build와 ctest를 실행한다.
6. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## Format
권장 방향:
```cpp
#pragma once

#include <algorithm>
#include <string>

namespace TextUtils {
template <typename Keywords>
inline bool containsAny(const std::string& text, const Keywords& keywords) {
    return std::any_of(keywords.begin(), keywords.end(), [&](const auto& keyword) {
        return text.find(keyword) != std::string::npos;
    });
}
}
```

최종 응답에는 추가한 파일, 함수 시그니처, 검증 결과, `REFACTOR-02-01` 완료 여부를 포함한다.

# 7-Step

1. Observe: 중복 문자열 검색 패턴을 확인한다.
2. Frame: 유틸리티 추가만 수행한다.
3. Contract: 포함 여부 결과는 기존 `find` 기반 판단과 같아야 한다.
4. Trace: 후속 대체 위치를 확인하되 이번 항목에서 과도하게 바꾸지 않는다.
5. Write: `src/TextUtils.h`를 작성한다.
6. Verify: build와 ctest를 실행한다.
7. Close: 세션 로그와 TODO 체크박스를 갱신한다.
````


