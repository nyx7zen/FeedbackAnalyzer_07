# **프로젝트 컨텍스트 정의서: Feedback Analyzer**

이 문서는 Gemini CLI 및 Gemini Code Assist가 프로젝트의 구조적 제약 사항, 구현 목표, 브랜치 전략 및 C++ 코딩 표준을 분석하기 위해 참조하는 정적 컨텍스트 파일입니다.

## **1\. 프로젝트 기본 명세 및 환경 정보**

### **1.1. 기술 스택 규격**

* 언어 표준: C++17  
* 빌드 시스템: CMake 3.14 이상  
* 단위 테스트 프레임워크: Google Test (GTest)  
* 의존성 라이브러리: cpp-httplib (HTTP 서버), nlohmann/json (JSON 파싱 필요 시)

### **1.2. 로컬 빌드 및 컴파일 명령어 (MinGW 환경 기준)**

\# 빌드 디렉터리 초기화 및 g++ 컴파일러 명시 설정  
rmdir /q /s build  
cmake \-S . \-B build \-G "MinGW Makefiles" \-DCMAKE\_CXX\_COMPILER=C:/mingw64/bin/g++.exe

\# 컴파일 및 실행 파일 빌드  
cmake \--build build

\# 웹 애플리케이션 서버 실행  
build\\feedback\_analyzer.exe

### **1.3. 유닛 테스트 빌드 및 실행 명령어**

\# 전체 빌드 및 테스트 타깃 실행  
cmake \-B build && cmake \--build build  
cd build && ctest \--output-on-failure

## **2\. 브랜치 전략 및 협업 제약 조건 (연습 \#4 전용)**

### **2.1. 브랜치 생명 주기 및 흐름**

변경 이력을 안전하게 보존하고 단계별 점진적 개선을 추적하기 위해 다음 순서로 브랜치를 전환하며 개발을 수행합니다.

maintdd (레거시 코드 진입점) \-\> refactoring (구조 개선 및 버그 수정) \-\> feature (신규 기능 추가)

### **2.2. 협업 제약 사항**

* 로컬 작업 완료 후 원격 저장소에 직접 병합(Merge)하는 행위를 일체 금지합니다.  
* 반드시 GitHub 또는 작업 도구 상에서 Pull Request(PR)를 발행하고 팀원을 리뷰어로 지정하여 코드 검증을 완료한 후 병합 절차를 진행합니다.

### **2.3. 커밋 메시지 정책 (Conventional Commits)**

모든 커밋 메시지는 작업 속성에 따라 다음 접두사를 의무적으로 부여합니다.

* feat: 가중치 감성 분석, RAII CSV 파일 물리 저장 등 신규 기능 구현  
* fix: 중립 필터 조건문 분기 결함 등 오작동 버그 수정  
* refactor: 메서드 추출, 전역 변수 제거, 중복 제거 등 구조적 개선  
* test: Google Test 픽스처 설계 및 테스트 케이스 보강  
* docs: md 형식의 보고서 파일 작성 및 문서 수정  
* chore: CMakeLists.txt 빌드 설정 보강 등 기타 인프라 작업

## **3\. C++ 코딩 표준 및 비즈니스 제약 규칙 (.cursorrules 통합)**

Gemini CLI가 새로운 소스 코드를 생성하거나 기존 소스를 리팩토링할 때 반드시 엄수해야 하는 무결성 제약 조건입니다.

* 매직 넘버 상수화: 하드코딩된 원시 문자열("긍정", "부정", "중립") 또는 스코어 연산 임계값은 모두 헤더 내에 static constexpr 또는 const 상수로 관리해야 합니다.  
* 단일 책임 함수 지향: 단일 함수 혹은 메서드의 길이는 최대 20줄을 초과할 수 없습니다. 20줄 초과 시 의무적으로 서브루틴으로 추출(Extract Method)을 수행합니다.  
* Doxygen 문서화: 모든 public 접근 제어자를 갖는 클래스, 인터페이스, 함수, 메서드에는 Doxygen 표준 스키마(@brief, @param, @return)에 부합하는 주석을 누락 없이 기재합니다.  
* 테스트 메서드 네이밍 규칙: 모든 GTest 케이스 식별자는 should\_\[결과\]\_when\_\[조건\] 템플릿을 철저히 유지합니다.

## **4\. 레거시 코드 스멜 및 버그 요약 (개선 대상 분석)**

현재 리팩토링 대상인 maintdd 브랜치의 소스 코드는 다음과 같은 심각한 아키텍처적 결함과 설계상 오류를 포함하고 있습니다.

1. 축약어 오용으로 인한 의미 침식:  
   sent(), kw(), fil() 등의 암호화된 명칭들을 도메인 개념이 투영된 analyzeSentiment(), analyzeKeywords(), applyFilter() 등으로 일괄 복원해야 합니다.  
   2.Constants.cpp 내 감성 사전 무결성 붕괴:  
   동일한 한국어 단어가 긍정 사전과 부정 사전에 모두 중복 배정되어 정확도가 유실되었습니다. 중복 요소를 식별하여 정제해야 합니다.  
2. 비공개 유틸리티 로직 중복:  
   TextAnalyzer와 Filters에 각각 중복 정의된 서브스트링 매칭 함수 containsAny()를 전역적으로 재사용할 수 있는 src/TextUtils.h로 분리해야 합니다.  
3. 전역 static 변수 남용으로 인한 테스트 격리 불가능성:  
   fil\_data, globalSent, globalKw 등 공유 전역 필드가 다수의 유닛 테스트들 사이에서 오염되어 부작용을 일으킵니다. 이를 전면 폐지하고 상태 전이를 컨텍스트 단위로 캡슐화해야 합니다.  
4. Session 컴포넌트의 가짜 API 구현:  
   전달받은 조회 키값을 내부에서 무시하고 정적 변수를 통째로 넘겨주는 비기능적 설계를 수정하여 std::unordered\_map 기반의 온전한 격리 조회 세션으로 개편합니다.  
5. FileHandler 기능 미구현:  
   분석 결과를 물리 저장소에 기록하는 saveResult() 함수가 단순히 콘솔 로그 출력에 머무르는 스텁 상태입니다. 실제 로컬 디스크 파일 출력으로 정상화합니다.

## **5\. 핵심 리팩토링 및 기능 개선 세부 규격**

### **5.1. src/TextUtils.h (중복 검색 로직의 단일화)**

C++17 표준 알고리즘인 std::any\_of와 std::string::find를 결합하여 불필요한 메모리 할당 없이 빠르게 문자열 존재 여부를 파악하는 인라인 공통 유틸리티 클래스를 설계합니다.

\#ifndef TEXT\_UTILS\_H  
\#define TEXT\_UTILS\_H

\#include \<string\>  
\#include \<vector\>  
\#include \<algorithm\>

namespace TextUtils {  
    /\*\*  
     \* @brief 원본 문자열 내에 후보 키워드 배열 중 단 하나라도 매칭되는 요소가 있는지 선형 탐색을 수행합니다.  
     \* @param targetText 검색 대상 원문  
     \* @param keywords 찾고자 하는 키워드 목록  
     \* @return 매칭 요소 존재 시 true, 부재 시 false  
     \*/  
    inline bool containsAny(const std::string& targetText, const std::vector\<std::string\>& keywords) {  
        if (targetText.empty() || keywords.empty()) {  
            return false;  
        }  
        return std::any\_of(keywords.begin(), keywords.end(), \[\&targetText\](const std::string& keyword) {  
            if (keyword.empty()) return false;  
            return targetText.find(keyword) \!= std::string::npos;  
        });  
    }  
}

\#endif // TEXT\_UTILS\_H

### **5.2. src/FileHandler.cpp (RAII 기반 CSV 파일 영구 저장소)**

기존의 빈 콘솔 덤프를 걷어내고, 자원 소멸 시 파일 스트림이 자동으로 안전하게 회수되는 RAII 입출력을 실현합니다. 파일 쓰기 중 발생하는 예외는 try-catch로 포획하여 상위 서버 런타임 크래시를 방지하고, 엑셀 깨짐을 정비하기 위해 BOM 바이너리를 헤더에 안전하게 추가합니다.

\#include "FileHandler.h"  
\#include \<fstream\>  
\#include \<iostream\>  
\#include \<stdexcept\>

bool FileHandler::saveToCsv(const std::vector\<Feedback\>& data, const std::string& path) {  
    if (path.empty()) {  
        std::cerr \<\< "\[Error\] 유효하지 않은 파일 경로입니다." \<\< std::endl;  
        return false;  
    }

    std::ofstream fileStream(path, std::ios::out | std::ios::trunc);  
    if (\!fileStream.is\_open()) {  
        std::cerr \<\< "\[Error\] 파일 개방에 실패했습니다: " \<\< path \<\< std::endl;  
        return false;  
    }

    try {  
        // UTF-8 인코딩 인식을 지원하기 위한 BOM 주입  
        fileStream \<\< "\\xEF\\xBB\\xBF";  
        fileStream \<\< "id,sentiment,text\\n";  
          
        for (const auto& feedback : data) {  
            std::string cleanedText \= feedback.getText();  
              
            // 본문 내 쌍따옴표가 구조를 깨뜨리지 않도록 이중 래핑 처리  
            size\_t pos \= 0;  
            while ((pos \= cleanedText.find("\\"", pos)) \!= std::string::npos) {  
                cleanedText.replace(pos, 1, "\\"\\"");  
                pos \+= 2;  
            }

            fileStream \<\< feedback.getId() \<\< ","  
                       \<\< feedback.getSentiment() \<\< ","  
                       \<\< "\\"" \<\< cleanedText \<\< "\\"\\n";  
        }  
    } catch (const std::exception& e) {  
        std::cerr \<\< "\[Critical\] 파일 입출력 예외 발생: " \<\< e.what() \<\< std::endl;  
        return false;  
    }

    return true;  
}

### **5.3. src/TextAnalyzer.cpp (가중치 스코어링 감성 분석 알고리즘)**

문장의 첫 부분에서 탐색 키워드가 걸리는 즉시 단정을 내리던 불완전한 조건 구조를 폐지합니다. 전체 본문 내부의 긍정 가중치 포인트와 부정 가중치 포인트를 개별 카운트 연산하여 총합 격차를 비교 분석하는 상대적 감성 평가 모델로 수정합니다.

\#include "TextAnalyzer.h"  
\#include "Constants.h"  
\#include "TextUtils.h"

std::string TextAnalyzer::classifyWeightedSentiment(const std::string& text) {  
    if (text.empty()) {  
        return "중립";  
    }

    int positiveScore \= 0;  
    int negativeScore \= 0;

    // 긍정 표현 가중치 누적  
    for (const auto& keyword : Constants::SENTIMENT\_KEYWORDS\["긍정"\]) {  
        size\_t currentPos \= 0;  
        while ((currentPos \= text.find(keyword, currentPos)) \!= std::string::npos) {  
            positiveScore++;  
            currentPos \+= keyword.length();  
        }  
    }

    // 부정 표현 가중치 누적  
    for (const auto& keyword : Constants::SENTIMENT\_KEYWORDS\["부정"\]) {  
        size\_t currentPos \= 0;  
        while ((currentPos \= text.find(keyword, currentPos)) \!= std::string::npos) {  
            negativeScore++;  
            currentPos \+= keyword.length();  
        }  
    }

    if (positiveScore \> negativeScore) {  
        return "긍정";  
    } else if (negativeScore \> positiveScore) {  
        return "부정";  
    }

    return "중립";  
}

### **5.4. tests/TextAnalyzerTest.cpp (GTest Fixture 독립 단위 테스트 구조)**

유닛 테스트 케이스 실행 전에 매번 Constants를 정제하고 인메모리 세션을 격리하여 상호 부작용을 원천 차단하는 유닛 테스트의 바이블 픽스처 구조입니다.

\#include \<gtest/gtest.h\>  
\#include "../src/TextAnalyzer.h"  
\#include "../src/Constants.h"  
\#include "../src/Session.h"

class TextAnalyzerTest : public ::testing::Test {  
protected:  
    void SetUp() override {  
        Constants::init();  
        FeedbackSession::clear();  
    }

    void TearDown() override {  
        FeedbackSession::clear();  
    }  
};

TEST\_F(TextAnalyzerTest, should\_returnPositive\_when\_feedbackContainsDominantPositiveKeywords) {  
    std::vector\<Feedback\> feedbacks \= {  
        Feedback(1, "이 서비스는 진심으로 만족스럽고 배송 또한 최고 수준으로 빠릅니다")  
    };  
    TextAnalyzer analyzer;

    auto analysisResult \= analyzer.analyzeSentiment(feedbacks);

    EXPECT\_EQ(analysisResult\["긍정"\], 1);  
    EXPECT\_EQ(analysisResult\["부정"\], 0);  
    EXPECT\_EQ(analysisResult\["중립"\], 0);  
}

## **6\. 최종 유닛 테스트 완료 후 제출할 레포팅 파일 양식**

리팩토링과 테스트 검증 절차가 성공적으로 종결되면 프로젝트 내에 다음 다섯 가지 보고용 산출물들이 md 확장자 형태로 안전하게 포함 및 push 되었는지 형상 관리를 검사하십시오.

* analysis.md: 6대 핵심 코드 스멜의 세부 발생 원인과 아키텍처적 위험도를 분석하여 기록한 정밀 명세서.  
* bug\_fix.md: Filters 컴포넌트의 중립 필터 분기 오류 해결 전후 논리식 대조 및 단위 테스트 실행 결과 기록 문서.  
* refactoring.md: 축약 단축 네이밍 교정 표(Mapping Table) 및 static 전역 변수를 제거하고 구성한 Session 라이프사이클 격리 흐름도.  
* feature.md: RAII 기법을 투영한 파일 저장 및 가중치 감성 분석 알고리즘 구현의 완성도를 기재한 기능 개발 명세서.  
* report.md: 리팩토링 전후의 총 소스 코드 라인 수(LOC) 증감 비율 및 단위 테스트 타깃 최종 커버리지 달성도를 정량적으로 대조한 실무 종합 보고서.