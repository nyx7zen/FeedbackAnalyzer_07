# **Cursor AI 실습 가이드 (C++ 개발자용)**

## **연습 \#4: Feedback Analyzer 레거시 개선 마스터 클래스**

본 가이드는 C++17, CMake 및 Google Test(GTest) 환경을 기반으로 기존의 레거시 코드를 전면 분석하고 안전하게 리팩토링하는 실전 워크플로우를 다룹니다.

이 프로젝트는 아키텍처 붕괴, 전역 상태 오용, 제어 흐름과 비즈니스 로직의 결합, 그리고 테스트의 부재로 인한 의미 침식(Semantic Erosion)을 직접 해결하며 대규모 코드베이스를 안전하게 진화시키는 AI 협업 능력을 기르는 데 목적이 있습니다.

## **1\. 공통 실습 환경 설정 및 연습 \#4 브랜치 전략**

### **1.1. VSCode C++ 필수 개발 환경 구성**

C++ 실습을 정상적으로 수행하기 위해서는 아래에 명시된 C++ 개발 환경과 빌드 설정이 사전에 구축되어 있어야 합니다.

* 필수 VSCode 확장 기능(Extensions):  
  * C/C++ (ms-vscode.cpptools): C++ 문법 강조, 디버깅, 인텔리센스 지원  
  * CMake Tools (ms-vscode.cmake-tools): CMake 빌드 시스템 연동 및 자동화  
  * C++ TestMate: Google Test 프레임워크와 VSCode 테스트 UI 연동 및 실행기 지원  
* CMake 기반 Google Test 연동 기준:  
  프로젝트의 CMake 설정 파일(CMakeLists.txt)에서 GTest 라이브러리를 안전하게 참조하고 연동해야 합니다.  
  find\_package(GTest REQUIRED)  
  target\_link\_libraries(test\_target GTest::gtest\_main)

* 프로젝트 빌드 및 테스트 자동화 스크립트 실행 명령어:  
  \# 빌드 캐시 디렉터리를 생성하고 소스 코드를 컴파일합니다.  
  cmake \-B build && cmake \--build build

  \# 테스트 타깃을 실행하여 결과를 출력하고 검증합니다.  
  cd build && ctest \--output-on-failure

### **1.2. 연습 \#4 브랜치 운용 및 협업 전략**

연습 \#4(FeedbackAnalyzer)에서는 변경 이력을 체계적으로 보존하고 상호 검토하기 위해 구조화된 브랜치 전략을 수행합니다.

* 연습 \#4 브랜치 구조 흐름:  
  maintdd (초기 레거시 기준점) \-\> refactoring (구조 개선 및 버그 수정) \-\> feature (가중치 스코어링 및 CSV 저장 기능 구현)  
* 협업 및 병합 제약 사항:  
  * 로컬에서 작업을 완료한 후 원격 저장소에 직접 병합(Merge)하지 않습니다.  
  * 반드시 GitHub 또는 작업 관리 도구 상에서 Pull Request(PR)를 생성하고 팀원을 리뷰어로 지정하여 코드 리뷰를 수행합니다.  
* 커밋 메시지 규칙 (Conventional Commits):  
  모든 작업 이력은 다음과 같은 형식의 접두사를 명확하게 작성하여 커밋을 진행합니다.  
  * feat: 새로운 기능 추가 (예: 가중치 감성 분석 구현)  
  * fix: 버그 수정 (예: 중립 필터 조건 식 오류 수정)  
  * refactor: 프로덕션 코드 리팩토링 (예: containsAny 중복 제거)  
  * test: 테스트 코드 추가 또는 수정 (예: TextAnalyzerTest Fixture 보강)  
  * docs: 문서 편집 (예: report.md 작성)  
  * chore: 빌드 스크립트 수정, 패키지 설정 등의 자잘한 작업 (예: CMakeLists.txt 옵션 변경)

### **1.3. .cursorrules 공통 설정 규칙 (연습 \#4 핵심 요약)**

Cursor AI가 설계 의도를 일관되게 학습하고 올바른 C++ 코드를 생성하도록 프로젝트 루트 디렉터리에 .cursorrules 파일을 생성하고 프로젝트의 페르소나 및 규칙을 다음과 같이 강제해야 합니다.

* C++ 기술 스택 명시: C++17 / Google Test (GTest) / CMake 사용.  
* 클린 코드 규칙:  
  * 매직 넘버 제거: 코드 내 하드코딩된 임계값, 비율, 문자열은 모두 constexpr 혹은 const 상수로 추출할 것.  
  * Doxygen 형식 문서화: 모든 public 클래스, 인터페이스, 메서드, 함수에는 Doxygen 표준 규칙(@brief, @param, @return)을 준수하는 주석을 필수로 남길 것. 이 주석 정보는 Cursor AI가 코드베이스를 검색할 때 매우 중요한 시맨틱 컨텍스트로 활용됩니다.  
  * 단일 책임 함수: 한 함수의 길이는 최대 20줄을 넘지 않도록 제한할 것. 20줄이 넘어가는 코드는 즉시 서브루틴으로 추출(Extract Method)할 것을 AI에 지시합니다.  
* 테스트 주도 개발(TDD) 네이밍:  
  * 모든 단위 테스트 메서드명은 should\_\[결과\]\_when\_\[조건\] 포맷을 엄격히 적용할 것.  
  * (예: should\_returnNeutral\_when\_positiveAndNegativeScoresAreEquivalent)

### **1.4. CMakeLists.txt 구성 분석**

C++ 프로젝트 빌드와 Google Test 프레임워크 연동을 위한 표준 CMakeLists.txt 설정 구조입니다. GTest가 시스템에 사전에 설치되어 있거나, FetchContent 등을 통해 외부 종속성으로 안전하게 연동되도록 구성되어야 합니다.

cmake\_minimum\_required(VERSION 3.14)  
project(FeedbackAnalyzer LANGUAGES CXX)

set(CMAKE\_CXX\_STANDARD 17\)  
set(CMAKE\_CXX\_STANDARD\_REQUIRED ON)

\# 외부 라이브러리 및 GTest 검색  
find\_package(GTest REQUIRED)  
include\_directories(${GTEST\_INCLUDE\_DIRS})

\# 소스 파일 목록 정의  
set(SOURCES  
    src/main.cpp  
    src/TextAnalyzer.cpp  
    src/Filters.cpp  
    src/Session.cpp  
    src/Constants.cpp  
    src/FileHandler.cpp  
    src/Logger.cpp  
)

\# 실행 파일 생성  
add\_executable(FeedbackAnalyzer ${SOURCES})

\# 테스트 대상 라이브러리 분리 (테스트 러너와 공유 목적)  
add\_library(AnalyzerLib STATIC  
    src/TextAnalyzer.cpp  
    src/Filters.cpp  
    src/Session.cpp  
    src/Constants.cpp  
    src/FileHandler.cpp  
    src/Logger.cpp  
)

\# Google Test 타깃 생성  
add\_executable(runTests tests/TextAnalyzerTest.cpp)  
target\_link\_libraries(runTests PRIVATE AnalyzerLib GTest::gtest\_main)

## **2\. 파일 구조 및 역할 이해 (C++ 레거시의 민낯)**

이 프로젝트는 인위적으로 삽입된 다양한 코드 스멜(Code Smell)과 아키텍처적 결함을 가지고 있습니다. 리팩토링에 앞서 각 소스 파일의 논리적 한계와 비즈니스적 책임을 명확히 분석해야 합니다.

\[레거시 의존성 구조 시각화\]

  main.cpp (HTTP 진입점/HTML 렌더링)  
         │  
         ├───\> TextAnalyzer.cpp (감성/키워드 분석) ───\> Constants.cpp (하드코딩 사전)  
         │           │  
         │           ▼ (전역 변수 상태 공유 및 오용)  
         ├───\> Filters.cpp (데이터 필터링) \<────────── Session.cpp (전역 데이터 보관)  
         │  
         └───\> FileHandler.cpp (stub 출력만 지원)

### **각 컴포넌트 분석 리포트**

1. main.cpp  
   * 역할: httplib 기반 웹 서버 라우팅 및 HTML 화면(Thymeleaf 유사 템플릿 대체) 렌더링.  
   * 문제점: HTTP 요청 처리, 파싱 및 뷰(UI) 렌더링 로직이 비즈니스 연산 로직과 강하게 결합되어 있어 단위 테스트 작성이 원천적으로 불가능합니다.  
2. TextAnalyzer.h/.cpp  
   * 역할: 사용자가 입력한 피드백 원문의 키워드를 정적 맵과 대조하여 감성 점수를 분류하고 키워드를 추출.  
   * 문제점: 핵심 동작 메서드들이 sent(), kw()와 같이 도메인 의미를 상실한 극단적인 축약형 이름을 사용하고 있습니다. 또한 내부적으로 동일한 문자열 포함 검사 루프를 중복 작성하여 유지보수성을 크게 떨어뜨립니다.  
3. Filters.h/.cpp  
   * 역할: 분석된 피드백 목록 중에서 특정 감성 카테고리나 키워드를 기준으로 컬렉션을 정제.  
   * 문제점: 메서드명이 fil()과 같이 매우 축약되어 있으며, 무엇보다 '중립' 감성 필터 로직에 치명적인 조건문 분기 버그가 있어 정상적인 통계가 나오지 않습니다.  
4. Session.h/.cpp  
   * 역할: 애플리케이션 수명 주기 동안 로드된 전체 피드백 데이터 상태를 인메모리에 임시 유지.  
   * 문제점: 객체 생성 없이 정적 변수(static std::vector)를 전역적으로 노출하여 멀티스레드 환경에서 데이터 경합(Race Condition) 위험을 유발하며, 단위 테스트들이 공유 전역 상태를 오염시켜 서로 간섭하게 만듭니다.  
5. Constants.h/.cpp  
   * 역할: 한글 감성 키워드 및 분류 사전 데이터 보관.  
   * 문제점: 정적 맵 데이터 초기화 시 동일한 한글 키워드(예: "좋아요", "만족")가 '긍정'과 '부정' 맵 양쪽에 모두 중복 등록되어 분석 신뢰성을 크게 손상시키고 있습니다.  
6. FileHandler.h/.cpp  
   * 역할: 분석 결과 및 피드백 상태를 파일 시스템에 안전하게 저장하고 로드하는 역할.  
   * 문제점: 실제 파일 쓰기 입출력 로직 없이 단순히 콘솔창에 std::cout 로그만 찍어두고 성공으로 넘어가는 대표적인 스텁(Stub) 방치 코드입니다.

## **3\. 실제 코드에서 발견되는 6가지 개선 포인트 상세 분석**

리팩토링을 시작하기 전, Cursor AI와 코드 검토 세션을 진행하며 아래의 6대 핵심 코드 스멜을 기술적으로 정밀하게 진단하고 공유해야 합니다.

### **3.1. 극단적으로 생략된 명명 규칙 (Syntactic Erosion)**

* 레거시 코드: sent(), kw(), fil(), fil\_data  
* 기술적 한계: 이와 같은 불명확한 단축 네이밍은 코드의 시맨틱 가독성을 저하시킵니다. Cursor AI 역시 축약된 명명 규칙 내에서는 도메인 규칙을 제대로 오해하여 버그를 생산할 가능성이 기하급수적으로 올라갑니다.  
* 리팩토링 방향: analyzeSentiment(), analyzeKeywords(), applyFilter(), FilterResult와 같이 "동사 \+ 명사" 형태를 가지는 명확한 도메인 어휘로 정제합니다.

### **3.2. 정적 키워드 사전의 충돌 및 중복**

* 레거시 코드: SENTIMENT\_KEYWORDS\["긍정"\] 및 \["부정"\] 양쪽에 동일한 문자열 배열이 중복 할당됨.  
* 기술적 한계: "만족스럽다"나 "좋다"라는 키워드가 양쪽 사전에 동시에 존재하여 연산 결과가 왜곡되는 비즈니스 데이터 무결성 결함을 초래합니다.  
* 리팩토링 방향: 중복 키워드를 완벽히 제거하고, 단어의 어미 변화를 정교하게 분리하거나 중복 검사 로직을 사전 초기화 시 수행하여 정합성을 방어합니다.

### **3.3. 비즈니스 로직의 분산 및 중복 선언 (containsAny 스멜)**

* 레거시 코드: TextAnalyzer와 Filters 구현부 내에 문자열을 임시 순회하며 서브스트링 존재 유무를 확인하는 중복 함수가 각각 선언되어 있음.  
* 기술적 한계: 동일 로직의 파편화로 인해 특정 버그를 수정할 때 한쪽만 수정하고 다른 한쪽은 누락하는 정합성 붕괴(Divergent Change) 리스크가 큽니다.  
* 리팩토링 방향: C++17 표준의 std::any\_of와 string::find를 결합하여 단일 헤더인 TextUtils.h 내에 인라인 함수로 완전히 일원화합니다.

### **3.4. 전역 정적 변수 오용으로 인한 테스트 격리 실패**

* 레거시 코드: static std::vector\<Feedback\> fil\_data;  
* 기술적 한계: 유닛 테스트 러너는 여러 테스트 케이스를 순차적 혹은 병렬적으로 수행합니다. 이때 전역 상태가 오염되어 있다면, 앞선 테스트가 입력한 데이터 때문에 뒤의 독립적인 테스트가 무조건 실패하는 부작용이 발생합니다.  
* 리팩토링 방향: 정적 전역 변수를 제거하고, 상태 보관 책임을 명확히 분리한 FeedbackSession 컨테이너 인스턴스를 컨텍스트 객체로 전달하는 아키텍처로 선회해야 합니다.

### **3.5. 이름값만 존재하는 껍데기 세션 설계**

* 레거시 코드: getOldDataFromSession(const std::string& key) 함수가 매개변수 key값을 전혀 활용하지 않고 전역 컬렉션을 조건 없이 통째로 반환함.  
* 기술적 한계: 의도가 완전히 누락되어 추후 복수 세션 관리나 다중 사용자 세션을 지원하도록 확장할 때 시스템이 오작동하게 됩니다.  
* 리팩토링 방향: 맵(std::unordered\_map) 구조를 적용하여 키값에 대응하는 상태 컬렉션을 추적하도록 온전히 고쳐야 합니다.

### **3.6. 실질적 동작이 없는 콘솔 스텁 (FileHandler)**

* 레거시 코드: void saveResult() { std::cout \<\< "save..." \<\< std::endl; }  
* 기술적 한계: 프로덕션 환경에서도 데이터가 유지되지 않고 유실되며, 사용자 통계 화면과 원시 피드백 데이터 간의 격차가 극대화됩니다.  
* 리팩토링 방향: C++ std::ofstream과 RAII 자원 관리 기법을 활용하여 예외가 발생하더라도 리소스 가상 포인터가 즉시 닫히고 디스크에 안전하게 쓰기가 마무리되도록 견고하게 구현합니다.

## **4\. 8단계 학습 가이드 및 Cursor AI 프롬프트 전략**

Cursor AI와 협업하여 단계별 리팩토링을 빈틈없이 수행하기 위한 실무 8단계 프로세스 및 각 단계별 프롬프트 시나리오 가이드입니다.

### **1단계: 프로젝트 구조 및 아키텍처적 문제점 정밀 진단**

* 작업 목표: 전체 소스 코드의 위상과 결합도를 시각화하고, 분석 방향성을 도출합니다.  
* Cursor Chat 실행 프롬프트:  
  @Codebase 이 C++ 기반 Feedback Analyzer 프로젝트의 전체 코드 구조와 아키텍처적 결함을 분석해줘.  
  특히 전역 static 변수 사용으로 인한 테스트 격리 실패 위험성, main.cpp와 핵심 도메인 로직 간의 결합도,   
  그리고 네이밍 스멜 및 중복 코드가 집중된 부분을 찾아내고, 개선 우선순위를 포함하여 정리한   
  analysis.md 보고서를 프로젝트 루트에 한글 마크다운 형식으로 작성해서 저장해줘.

### **2단계: 테스트 격리 프레임워크 구축 (Google Test 90%+ 타깃)**

* 작업 목표: 기존의 코드 동작을 보호할 방어막으로서 실패하는 단위 테스트(TDD Red 단계)를 사전에 구축합니다.  
* Cursor Chat 실행 프롬프트:  
  @TextAnalyzer.cpp @Filters.cpp @FileHandler.cpp 이 핵심 클래스들의 동작을 철저히 검증하기 위한   
  Google Test 기반 단위 테스트 코드를 \`tests/TextAnalyzerTest.cpp\`에 작성해줘.  
  \- 전역 정적 맵의 상태 초기화 및 소멸 흐름을 Fixture 클래스의 SetUp()과 TearDown()을 통해 철저히 제어해줘.  
  \- 테스트 케이스 네이밍은 \`should\_\[expected\]\_\_when\_\[condition\]\` 규칙을 완벽하게 따라줘.  
  \- 빈 문자열 피드백, 극단적인 특수문자, 긍정/부정 키워드가 혼재된 경계값 케이스를 반드시 포함해줘.

### **3단계: 3대 긴급 수정 버그 트래킹 및 정상화**

* 작업 목표: '중립' 필터의 논리적 결함 등 즉각적인 런타임 크래시 혹은 오작동 버그를 수정합니다.  
* Cursor Chat 실행 프롬프트:  
  현재 시스템 내 치명적인 3대 버그를 정밀하게 추적해서 수정해줘:  
  1\. @Filters.cpp 파일의 '중립' 필터 판정 처리에서 논리 연산자 혹은 조건 분기 조건이 누락되거나 왜곡되어,   
     긍정/부정 스코어가 0일 때 정상적으로 필터링되지 않는 버그를 즉각 수정해줘.  
  2\. @main.cpp 파일의 입력 폼 UI에서 텍스트 입력창이 단일 라인 input이 아닌, 장문의 피드백을 자연스럽게   
     입력받을 수 있도록 textarea 형태의 multiline 구조로 수정 및 렌더링 로직을 연결해줘.  
  3\. @Logger.cpp의 파일 저장 및 화면 출력 로그 레벨(warning/error/info)을 동적으로 안전하게 제어하여   
     의미 없는 로그 노출을 제어하도록 고쳐줘.

### **4단계: 네이밍 스멜 교정 및 매직 넘버 상수화 (시맨틱 보존)**

* 작업 목표: 축약어를 완전히 걷어내고, 코드 가독성을 극대화합니다.  
* Cursor Chat 실행 프롬프트:  
  @Constants.cpp @TextAnalyzer.cpp @Filters.cpp 파일 전반의 네이밍과 하드코딩된 값들을 개선해줘:  
  \- \`sent()\`, \`kw()\`, \`fil()\`과 같은 극단적인 축약형 메서드명을 각각 \`analyzeSentiment()\`,   
    \`analyzeKeywords()\`, \`applyFilter()\` 등 명확한 도메인 동사-명사 조합으로 일괄 변경해줘.  
  \- 하드코딩되어 있던 문자열 "긍정", "부정", "중립" 및 판단 조건으로 쓰이는 0.0f, 1.0f 등의 매직 넘버들을   
    적절한 헤더 파일 내에 Doxygen 주석이 완벽히 첨부된 \`static constexpr\` 상수로 추출해줘.

### **5단계: 중복 코드의 완벽한 박멸 및 단일 책임 함수화**

* 작업 목표: 코드 중복률을 0%로 낮추고 함수 길이를 20줄 이하로 압축합니다.  
* Cursor Chat 실행 프롬프트:  
  @TextAnalyzer.cpp @Filters.cpp 소스 코드 내에서 구현이 중복되어 있는 문자열 순회 검색 비즈니스 로직을   
  완벽히 제거하고, 이를 C++17 표준의 \`std::any\_of\` 기반의 고성능 인라인 함수로 추상화한   
  \`src/TextUtils.h\` 파일로 깔끔히 추출하여 양쪽에서 재사용하도록 교체해줘.  
  또한, 모든 비즈니스 함수들이 20줄 규칙을 넘지 않도록 리팩토링하고 위반하는 함수는 세부 책임을 가진   
  작은 함수들로 더 쪼개줘.

### **6단계: Session 전역 상태 해체 및 API 현대화**

* 작업 목표: 공유 자원 경합 문제를 완전히 해결하고 테스트 독립성을 보장합니다.  
* Cursor Chat 실행 프롬프트:  
  @Session.cpp @TextAnalyzer.cpp @Filters.cpp 파일에 산재되어 유닛 테스트 독립성을 가로막는   
  글로벌 전역 static 필드 상태(\`fil\_data\`, \`globalSent\`)를 완전히 소멸시켜줘.  
  대신 세션 상태를 스레드 안전하게 다울 수 있도록 \`FeedbackSession\` 클래스를 싱글톤 혹은 컨텍스트   
  객체 전달 방식으로 디자인하고, 데이터 관리 생명 주기를 수동으로 제어 및 리셋할 수 있는 clear() API를   
  제공하도록 설계해줘.

### **7단계: 가중치 스코어링 알고리즘 및 CSV 파일 실전 저장 구현 (신규 피처)**

* 작업 목표: 정량적 비즈니스 기능을 정교화하고 디스크 영구 저장 계층을 확보합니다.  
* Cursor Chat 실행 프롬프트:  
  @TextAnalyzer.cpp @FileHandler.cpp 파일에 비즈니스 가치를 더하는 2가지 요구사항을 실전에 바로 쓰일 수   
  있을 만큼 고도화해서 완벽히 구현해줘:  
  1\. 감성 분석 시 단순히 첫 번째 검색된 키워드에 우선 매칭되어 종료되는 레거시의 취약한 알고리즘 대신,   
     문장 전체의 긍정 키워드 수와 부정 키워드 수를 각각 누적해서 상대적 우위를 측정하여 판별하는   
     가중치 기반 감성 스코어링 수식($Score\_{sentiment} \= Count\_{positive} \- Count\_{negative}$)을 설계 및 적용해줘.  
  2\. FileHandler 클래스의 saveToCsv()가 단순히 std::cout을 콘솔에 뿜어내던 Mock 형태를 걷어내고,   
     std::ofstream 스트림을 사용하는 RAII 패턴을 완벽히 적용해서 디스크 상의 지정된 경로에 데이터를   
     물리적으로 저장하게 구현해줘. 인코딩 깨짐을 극복하기 위한 UTF-8 BOM 인젝션 코드 및 데이터 내의 콤마(,)   
     문자 처리를 위한 예외처리(Double Quote Wrapping)를 필수적으로 견고하게 코딩하고, 실패 확률에 대한   
     테스트 코드도 tests/에 추가해줘.

### **8단계: 리팩토링 및 개선 내역 종합 레포팅 문서화**

* 작업 목표: 최종 검증과 리팩토링 효과를 객관적으로 증명하고 정리합니다.  
* Cursor Chat 실행 프롬프트:  
  @Codebase 수고했어\! 이제 우리가 성공적으로 개선한 이번 Feedback Analyzer 리팩토링 전후의 차이를   
  철저히 분석한 보고서 report.md를 작성해줘.  
  이 보고서에는 1\. 분석 배경 및 목표, 2\. 개선된 주요 결함 일람표, 3\. 핵심 수정 파일들의 Before vs After   
  코드 블록 및 상세한 대조 설명, 4\. GTest 커버리지 및 리팩토링 후 복잡도 감소율 변화, 5\. Cursor AI와   
  협업하며 거친 의사결정에 대한 기술 회고를 명시해야 해. 반드시 설명이나 추가 인삿말은 생략하고   
  마크다운 파일의 알짜 알맹이 내용만으로 가득 채워 정렬해줘.

## **5\. 핵심 구현 코드 가이드 (C++ 표준 및 모던 설계 패턴)**

실습 가이드 전반의 기준이 되는, 구조적으로 완벽한 모던 C++17 구현 핵심 파일 명세서들입니다.

### **격리된 유닛 테스트 프레임워크 (tests/TextAnalyzerTest.cpp)**

이 단위 테스트는 전역 상태가 제거된 세션 객체를 사용하며, GTest가 보장하는 완전히 독립된 테스트 환경을 보여줍니다.

\#include \<gtest/gtest.h\>  
\#include "../src/TextAnalyzer.h"  
\#include "../src/Constants.h"  
\#include "../src/Session.h"

/\*\*  
 \* @brief TextAnalyzer의 감성 분석 및 키워드 추출 동작을 격리하여 정밀 검증하기 위한 GTest Fixture 클래스입니다.  
 \*/  
class TextAnalyzerTest : public ::testing::Test {  
protected:  
    /\*\*  
     \* @brief 각 테스트 케이스가 구동되기 전, 상수 사전 초기화 및 전역 세션 상태를 엄격히 리셋합니다.  
     \*/  
    void SetUp() override {  
        Constants::init();  
        FeedbackSession::clear();  
    }

    /\*\*  
     \* @brief 테스트가 종료될 때마다 오염될 수 있는 인메모리 상태를 깨끗이 제거하여 테스트 독립성을 보장합니다.  
     \*/  
    void TearDown() override {  
        FeedbackSession::clear();  
    }  
};

/\*\*  
 \* @brief 문장 내에 명확한 긍정 어휘들이 다수 포함되어 있을 경우 감성 카테고리를 '긍정'으로 선언하는지 검증합니다.  
 \*/  
TEST\_F(TextAnalyzerTest, should\_returnPositive\_when\_feedbackContainsDominantPositiveKeywords) {  
    // Arrange (준비)  
    std::vector\<Feedback\> feedbacks \= {  
        Feedback(1, "이 서비스는 진심으로 만족스럽고 배송 또한 최고 수준으로 빠릅니다")  
    };  
    TextAnalyzer analyzer;

    // Act (실행)  
    auto analysisResult \= analyzer.analyzeSentiment(feedbacks);

    // Assert (단언)  
    EXPECT\_EQ(analysisResult\["긍정"\], 1);  
    EXPECT\_EQ(analysisResult\["부정"\], 0);  
    EXPECT\_EQ(analysisResult\["중립"\], 0);  
}

/\*\*  
 \* @brief 긍정 키워드와 부정 키워드의 출현 개수가 완전히 동일할 경우 최종 평가를 '중립'으로 정합하게 유도하는지 평가합니다.  
 \*/  
TEST\_F(TextAnalyzerTest, should\_returnNeutral\_when\_positiveAndNegativeScoresAreEquivalent) {  
    // Arrange  
    std::vector\<Feedback\> feedbacks \= {  
        Feedback(2, "디자인은 참 좋았어요 다만 내부 마감 불량이라 실망스럽습니다") // 긍정: 좋았어요(1) | 부정: 실망스럽습니다(1)  
    };  
    TextAnalyzer analyzer;

    // Act  
    auto analysisResult \= analyzer.analyzeSentiment(feedbacks);

    // Assert  
    EXPECT\_EQ(analysisResult\["중립"\], 1);  
    EXPECT\_EQ(analysisResult\["긍정"\], 0);  
    EXPECT\_EQ(analysisResult\["부정"\], 0);  
}

### **🔧 헬퍼 함수 중복 제거 (src/TextUtils.h)**

헤더 단독 정의(Header-only) 인라인 유틸리티 파일입니다. 불필요한 번역 단위를 줄여주며, 캐시 친화적인 벡터 연속 메모리를 std::any\_of로 순회하여 오버헤드가 사실상 무시 가능한 고성능 루프를 달성합니다.

\#ifndef TEXT\_UTILS\_H  
\#define TEXT\_UTILS\_H

\#include \<string\>  
\#include \<vector\>  
\#include \<algorithm\>

namespace TextUtils {  
    /\*\*  
     \* @brief 문자열 원문 내에 전달된 키워드 목록 중 하나라도 일치하는 서브스트링이 존재하는지 선형 탐색을 수행합니다.  
     \* @param targetText 검색 대상이 되는 원본 피드백 텍스트 문장  
     \* @param keywords 탐색하고자 하는 후보 키워드 리스트 (std::vector\<std::string\>)  
     \* @return 일치하는 키워드가 존재할 경우 true를 반환하며, 일절 매칭이 없으면 false를 반환합니다.  
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

### **💾 RAII 기반 CSV 출력 구현 (src/FileHandler.cpp)**

예외가 발생하는 순간 가상 머신이나 런타임 콜스택이 정리되면서도 리소스 핸들이 해제되는 C++ 고유의 자원 획득 즉시 초기화(RAII) 방식의 완벽한 영구 저장 모듈 예시입니다.

\#include "FileHandler.h"  
\#include \<fstream\>  
\#include \<iostream\>  
\#include \<stdexcept\>

/\*\*  
 \* @brief 최종 가공 완료된 피드백 컬렉션을 지정된 경로상에 안전하게 영구 CSV 파일로 기록합니다.  
 \* @param data 저장하고자 하는 가공된 피드백 리스트  
 \* @param path 디스크 물리 파일 경로  
 \* @return 성공 여부를 불리언값으로 반환하며, 실패 시 에러 사유를 로깅합니다.  
 \*/  
bool FileHandler::saveToCsv(const std::vector\<Feedback\>& data, const std::string& path) {  
    if (path.empty()) {  
        std::cerr \<\< "\[Error\] 유효하지 않은 디스크 출력 경로입니다." \<\< std::endl;  
        return false;  
    }

    // std::ofstream 생성자에서 파일 디스크립터 핸들을 즉시 획득 (RAII)  
    std::ofstream fileStream(path, std::ios::out | std::ios::trunc);  
      
    if (\!fileStream.is\_open()) {  
        std::cerr \<\< "\[Error\] 파일 쓰기 스트림을 개방할 수 없습니다. 경로 권한 확인 필요: " \<\< path \<\< std::endl;  
        return false;  
    }

    try {  
        // Microsoft Excel 등 외부 도구에서 한국어(UTF-8) 인코딩 자동 인식을 돕기 위한 UTF-8 BOM 인젝션  
        fileStream \<\< "\\xEF\\xBB\\xBF";  
          
        // CSV 헤더 라인 작성  
        fileStream \<\< "id,sentiment,text\\n";  
          
        for (const auto& feedback : data) {  
            std::string cleanedText \= feedback.getText();  
              
            // 데이터 무결성 방어: 피드백 본문 내 줄바꿈(\\n)이나 쌍따옴표(")가 존재할 경우 CSV 손상을 막기 위한 문자열 치환 가공  
            size\_t pos \= 0;  
            while ((pos \= cleanedText.find("\\"", pos)) \!= std::string::npos) {  
                cleanedText.replace(pos, 1, "\\"\\""); // 쌍따옴표 이중 래핑  
                pos \+= 2;  
            }

            // 개별 엔티티 출력 처리 및 이탈 위험 쉼표(,) 보정을 위해 본문 양 끝을 더블 쿼터로 봉인  
            fileStream \<\< feedback.getId() \<\< ","  
                       \<\< feedback.getSentiment() \<\< ","  
                       \<\< "\\"" \<\< cleanedText \<\< "\\"\\n";  
        }  
          
    } catch (const std::exception& e) {  
        std::cerr \<\< "\[Critical\] 파일 입출력 과정에서 치명적인 런타임 예외가 발생했습니다: " \<\< e.what() \<\< std::endl;  
        return false;  
    }

    // 함수의 블록을 탈출할 때 std::ofstream 소멸자가 호출되며 파일 락을 해제하고 스트림을 자동으로 close 처리함  
    return true;  
}

### **📈 가중치 기반 정밀 감성 분석 엔진 (src/TextAnalyzer.cpp)**

피드백 본문을 단 한 차례만 탐색하면서도, 긍정과 부정의 상대적 총점 가중치를 정교하게 저울질하는 고품질 비즈니스 연산 메서드입니다.

\#include "TextAnalyzer.h"  
\#include "Constants.h"  
\#include "TextUtils.h"  
\#include \<map\>

/\*\*  
 \* @brief 원본 피드백 본문의 긍정 및 부정 키워드 개수를 누적 계산하여 상대 평가 가중치 스코어를 계산하고 분류합니다.  
 \* @param text 분석 타깃 문자열 원문  
 \* @return 분류 완료된 결과 레이블 문자열 ("긍정", "부정", "중립")을 리턴합니다.  
 \*/  
std::string TextAnalyzer::classifyWeightedSentiment(const std::string& text) {  
    if (text.empty()) {  
        return "중립";  
    }

    int positiveScore \= 0;  
    int negativeScore \= 0;

    // 긍정 사전 키워드 매칭율 산출 (Constants에 등록된 최신 사전을 동적 대조)  
    for (const auto& keyword : Constants::SENTIMENT\_KEYWORDS\["긍정"\]) {  
        size\_t currentPos \= 0;  
        // 문장 내에 특정 키워드가 중복 사용된 빈도까지 정확히 계량하기 위해 반복 탐색 루프 설계  
        while ((currentPos \= text.find(keyword, currentPos)) \!= std::string::npos) {  
            positiveScore++;  
            currentPos \+= keyword.length();  
        }  
    }

    // 부정 사전 키워드 매칭율 산출  
    for (const auto& keyword : Constants::SENTIMENT\_KEYWORDS\["부정"\]) {  
        size\_t currentPos \= 0;  
        while ((currentPos \= text.find(keyword, currentPos)) \!= std::string::npos) {  
            negativeScore++;  
            currentPos \+= keyword.length();  
        }  
    }

    // 상대 가중치 분석 판별 규칙 적용 (수식: Score \= Positive \- Negative)  
    if (positiveScore \> negativeScore) {  
        return "긍정";  
    } else if (negativeScore \> positiveScore) {  
        return "부정";  
    }

    // 점수가 완전히 동점이거나, 일치하는 키워드가 전무한 경우 상호 모순을 제어하기 위해 최종 "중립" 처리  
    return "중립";  
}

## **6\. 연습 \#4 필수 제출 산출물 목록 및 검증 스키마**

리팩토링 과정이 마무리되고 테스트가 완벽히 통과하면 다음 5가지 리포트 마크다운(.md) 문서들이 정상적으로 빌드 및 패키징되어 제출 영역에 도달했는지 커밋 히스토리와 디렉터리를 확인하십시오.

| 산출물 파일명 | 핵심 검증 스키마 및 수록 필수 내역 |
| :---- | :---- |
| **analysis.md** | 6대 레거시 코드 스멜의 심각도(Critical/Major/Minor) 진단 지표와 원인 분석 보고서 |
| **bug\_fix.md** | 중립 필터 조건문 분기 버그 수정 전후 논리식 설명 및 runTests 검증 로깅 로그 기록 |
| **refactoring.md** | 축약명 변경 매핑 테이블 및 전역 static을 걷어내고 개편한 세션 라이프사이클 다이어그램 |
| **feature.md** | 가중치 분석 알고리즘과 std::ofstream UTF-8 BOM CSV 출력 기능 구현 및 한계 극복 리포트 |
| **report.md** | **정량적 측정 보고서:** 리팩토링 전후 LOC(Lines of Code) 변화 및 순환 복잡도 감소율 비교표 |

