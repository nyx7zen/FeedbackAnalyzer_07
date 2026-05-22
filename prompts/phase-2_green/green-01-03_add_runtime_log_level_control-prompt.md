# GREEN-01-03 실행 프롬프트

## 호출 문구

- `20번 진행`
- `GREEN-01-03 진행`
- `GREEN-01-03 항목을 진행해 주세요`
- `fix: add runtime log level control 실행`

---

## 프롬프트

````md
Feedback Analyzer 런타임 로그 레벨 제어 구현 전문가 - Logger 최소 수정

`TODO.md`의 `GREEN-01-03 fix: add runtime log level control` 항목을 실행하라.

너는 C++ 애플리케이션의 로깅 노출 수준을 최소 변경으로 제어하는 유지보수 담당자다.
이번 작업의 목표는 `src/Logger.cpp`에 warning/error/info 로그 레벨 제어 기능을 구현하고, 불필요한 로그 노출을 차단할 수 있도록 하는 것이다.

제약:
- 기존 Logger 공개 API를 우선 확인하고 호환성 유지
- 새 전역 상태 추가는 피하고, 필요하면 명시적 API 또는 클래스 상태로 캡슐화
- 로그 출력 포맷을 불필요하게 변경하지 말 것
- 관련 없는 로깅 리팩토링 금지
- 사용자 응답과 생성 문서는 한국어로 작성

---

# 1) PCTF 원칙

## 1.1 Purpose

런타임에서 로그 레벨을 제어할 수 있게 한다.

완료 후 다음이 만족되어야 한다.

- info, warning, error 중 출력 허용 레벨을 제어할 수 있다.
- 낮은 우선순위 로그를 숨길 수 있다.
- 기존 로그 호출부가 가능하면 그대로 동작한다.
- 테스트 또는 수동 검증으로 로그 레벨 동작을 확인할 수 있다.

## 1.2 Context

반드시 먼저 다음 파일을 확인한다.

- `TODO.md`
- `AGENTS.md`
- `src/Logger.h`
- `src/Logger.cpp`
- `src/main.cpp`
- `tests/` 내 Logger 관련 테스트
- `docs/analysis.md`

파일이 없다면 실제 저장소 구조를 우선한다.

## 1.3 Task

다음 작업을 순서대로 수행한다.

1. `TODO.md`에서 `GREEN-01-03` 항목을 확인한다.
2. `Logger.h/.cpp`의 현재 API와 출력 방식을 확인한다.
3. 로그 레벨 타입 또는 상수를 정의할 위치를 결정한다.
4. 런타임에 현재 로그 레벨을 설정하는 API를 추가한다.
5. info/warning/error 로그가 설정 레벨에 따라 출력되도록 최소 구현한다.
6. 가능하면 Logger 테스트를 추가하거나 기존 테스트를 보강한다.
7. build와 ctest를 실행한다.
8. `SESSION_NOTES.md`와 `TODO.md`를 갱신한다.

## 1.4 Format

권장 API 방향:

```cpp
enum class LogLevel {
    Info,
    Warning,
    Error
};

void setLogLevel(LogLevel level);
```

실제 API 이름은 기존 코드 스타일과 충돌하지 않게 정한다.

최종 응답에는 다음을 포함한다.

- 수정한 파일 목록
- 추가/변경한 Logger API
- 로그 레벨 동작 요약
- 빌드/테스트 결과
- `GREEN-01-03` 완료 여부
- 다음 추천 TODO 항목

---

# 2) 7-Step 실행 절차

## Step 1. Observe

Logger의 현재 구조를 관찰한다.

확인할 질문:

- Logger가 클래스인가, 네임스페이스 함수인가?
- 현재 info/warning/error 함수가 있는가?
- 로그 출력 대상은 stdout, stderr, 파일 중 무엇인가?
- 테스트에서 출력을 캡처할 수 있는가?

## Step 2. Frame

이번 작업은 로그 레벨 제어 최소 구현이다.

수행하지 말아야 할 일:

- 로깅 프레임워크 교체
- 로그 파일 영구 저장 구현
- 모든 호출부 대규모 변경

## Step 3. Contract

로그 레벨 계약을 다음처럼 고정한다.

- 현재 레벨보다 낮은 중요도의 로그는 출력하지 않는다.
- error는 warning보다 중요하고 warning은 info보다 중요하다.
- 기본 레벨은 기존 동작과 최대한 호환되게 정한다.

## Step 4. Trace

```text
setLogLevel -> log call -> level comparison -> output or suppress
```

## Step 5. Write

Logger API와 구현을 최소 변경으로 작성한다.

## Step 6. Verify

빌드와 테스트를 실행하고, 테스트가 없으면 최소한 컴파일 검증과 수동 검증 방법을 기록한다.

## Step 7. Close

`SESSION_NOTES.md`와 `TODO.md`를 갱신하고 결과를 보고한다.
````


