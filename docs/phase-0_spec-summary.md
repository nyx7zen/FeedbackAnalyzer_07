# Phase-0: SPEC 단계 최종 보고서

**Phase:** Phase-0: SPEC (환경 및 지침 설정, 프로젝트 구조 진단)  
**완료 날짜:** 2026-05-22  
**총 항목:** 7/7 (100% 완료)  
**산출물:** 4개 분석 문서 + 4개 실행 보고서 (2600+ 라인)

---

## 1. SPEC 단계 개요

### 1.1 단계 목표

- ✅ B_07 브랜치 전략 정의
- ✅ 빌드 및 테스트 명령 문서화
- ✅ 프로젝트 지침 통일
- ✅ 현재 아키텍처 진단
- ✅ 전역 상태 위험 분석
- ✅ Main 결합도 분석
- ✅ 리팩토링 우선순위 수립

### 1.2 완료 항목

| 번호 | 항목 ID | 제목 | 산출물 |
|---:|---|---|---|
| 1 | SPEC-01-01 | B_07 브랜치 워크플로우 | docs/b07-branch-workflow.md |
| 2 | SPEC-01-02 | 빌드 및 테스트 명령 | docs/build-and-test.md |
| 3 | SPEC-01-03 | 프로젝트 지침 통일 | docs/alignment.md |
| 4 | SPEC-02-01 | 아키텍처 분석 | docs/analysis.md |
| 5 | SPEC-02-02 | 전역 상태 위험 분석 | docs/analysis-global-state.md |
| 6 | SPEC-02-03 | Main 결합도 분석 | docs/analysis-main-coupling.md |
| 7 | SPEC-02-04 | 리팩토링 우선순위 | docs/analysis-refactoring-priority.md |

---

## 2. 산출물 요약

### 2.1 설정 및 지침 문서 (SPEC-01)

#### SPEC-01-01: B_07 브랜치 워크플로우
- **내용:** 단계별 브랜치 전략 (spec → red → green → refactor → feature → final)
- **병합 흐름:** spec → red → green → refactor → feature → final → B_07 → main
- **상태:** ✅ 정의 완료

#### SPEC-01-02: 빌드 및 테스트 명령
- **빌드:** `cmake -S . -B build -G "MinGW Makefiles"` + `cmake --build build`
- **테스트:** `ctest --output-on-failure`
- **상태:** ✅ 문서화 완료

#### SPEC-01-03: 프로젝트 지침 통일
- **AGENTS.md:** 개발 규칙, 커밋 메시지, 테스트 규칙
- **CLAUDE.md:** Claude Code 사용자 지침
- **상태:** ✅ 지침 통일 완료

### 2.2 진단 분석 문서 (SPEC-02)

#### SPEC-02-01: 아키텍처 분석 (analysis.md)
- **구성:** 9개 섹션, 500+ 라인
- **내용:**
  - 현재 아키텍처 (monolithic main.cpp)
  - 4가지 주요 혼합 관심사 식별
  - 도메인 로직 평가 (TextAnalyzer, Filters는 깨끗함)
  - 리팩토링 위험도 분류 (🔴 CRITICAL, 🟡 HIGH, 🟢 LOW)
  - 제안된 계층형 아키텍처
- **핵심 발견:** main.cpp가 6-10배 큼, 모든 관심사 혼합

#### SPEC-02-02: 전역 상태 위험 분석 (analysis-global-state.md)
- **구성:** 10개 섹션, 600+ 라인
- **내용:**
  - 5개 전역 변수 분석 (fil_data, textAnalyzer, filters, fileHandler, sessions_)
  - 테스트 격리 실패 시나리오 (순서 의존, Flaky 테스트)
  - 다중 사용자 데이터 손상 타임라인
  - 근본 원인 분석
  - 정리 전략 (GREEN/REFACTOR 단계)
- **핵심 발견:** 전역 상태로 인한 테스트 격리 불가능

#### SPEC-02-03: Main 결합도 분석 (analysis-main-coupling.md)
- **구성:** 10개 섹션, 700+ 라인
- **내용:**
  - 5개 라우트 핸들러 상세 분석 (GET /, POST /analyze, /upload, /filter, GET /download)
  - 하드 결합/타이트 결합 식별
  - 의존성 그래프
  - 혼합된 5가지 관심사 분류
  - 리팩토링 분해 계획 (5개 컴포넌트)
  - 서비스 레이어 설계
- **핵심 발견:** 라우팅이 도메인 로직에 직접 결합, 단위 테스트 불가능

#### SPEC-02-04: 리팩토링 우선순위 (analysis-refactoring-priority.md)
- **구성:** 11개 섹션, 650+ 라인
- **내용:**
  - 7가지 이슈 우선순위 (1-7)
  - 🔴 CRITICAL 3가지 (fil_data, Session 정리, 테스트 리셋)
  - 🟡 HIGH 2가지 (의존성 주입, 요청 컨텍스트)
  - 🟡 MEDIUM 2가지 (HTML 추출, 유틸 추출)
  - 구현 로드맵 (RED/GREEN/REFACTOR)
  - 차단 관계도 및 임계값 분석
  - 1일, 3일, 1주일 타임라인
- **핵심 발견:** 3가지 임계 수정으로 GREEN 단계 가능

---

## 3. 핵심 발견사항

### 3.1 CRITICAL 이슈 (🔴 - 모든 것 차단)

**이슈 #1: 전역 fil_data**
- **위치:** main.cpp 라인 16, 332, 361
- **문제:** 모든 요청과 테스트 간 공유
- **영향:** 다중 사용자 데이터 손상, 테스트 격리 실패
- **수정 난이도:** LOW
- **수정 시간:** 1-2시간
- **수정 단계:** GREEN-01-01

**이슈 #2: Session 종료 없음**
- **위치:** Session.cpp 라인 3
- **문제:** 세션 누적, 정리 안 됨, 다중 사용자 깨짐
- **영향:** 메모리 누수, 세션 격리 실패
- **수정 난이도:** MEDIUM
- **수정 시간:** 2-3시간
- **수정 단계:** GREEN-01-02

**이슈 #3: 테스트 상태 리셋 없음**
- **위치:** 테스트 TearDown (작성 필요)
- **문제:** 테스트 간 상태 누수, 순서 의존
- **영향:** Flaky 테스트, 재현 불가능
- **수정 난이도:** LOW
- **수정 시간:** 1시간
- **수정 단계:** GREEN-01-03

### 3.2 HIGH 우선순위 이슈 (🟡 - 테스트 차단)

**이슈 #4: 의존성 주입 없음**
- **문제:** TextAnalyzer/Filters Mock 불가능
- **수정 난이도:** MEDIUM
- **수정 단계:** GREEN-02-01

**이슈 #5: HTTP/Session 결합**
- **문제:** 요청 → 세션 바인딩 없음, 다중 사용자 미지원
- **수정 난이도:** MEDIUM
- **수정 단계:** GREEN-02-02

### 3.3 MEDIUM 우선순위 이슈 (🟡 - 개선)

**이슈 #6: HTML 인라인**
- **수정 단계:** REFACTOR-01-02

**이슈 #7: 유틸 인라인**
- **수정 단계:** REFACTOR-01-03

---

## 4. 아키텍처 평가

### 4.1 현재 상태: Monolithic

```
main.cpp (372 lines)
├─ HTTP 라우팅 (5 라우트)
├─ 비즈니스 로직 (피드백 추가, 필터링, 분석)
├─ HTML 렌더링 (130 라인)
├─ Form/CSV 파싱 (240 라인)
└─ 전역 상태 (4개 싱글톤 + 1개 맵)
```

**문제:**
- 단위 테스트 불가능 (모든 로직이 라우트에 임베드됨)
- 전역 상태로 인한 테스트 격리 실패
- 도메인 로직과 HTTP 강한 결합

### 4.2 도메인 로직 평가

| 컴포넌트 | 상태 | 평가 |
|---------|------|------|
| TextAnalyzer | ✅ 깨끗함 | 순수 함수, 테스트 가능 |
| Filters | ✅ 깨끗함 | 순수 함수, 테스트 가능 |
| Constants | ✅ 우수 | 불변 전역, 좋은 패턴 |
| Session | 🟡 부분적 | API 있으나 정리 없음 |
| main.cpp | 🔴 문제 | 모든 관심사 혼합 |

### 4.3 목표 상태: 계층형

```
RequestHandler (140 라인)
├─ FeedbackService
├─ FilterService
├─ CsvExporter
└─ HtmlRenderer

Service Layer
├─ 테스트 가능
├─ Mock 주입 가능
└─ 독립적 배포 가능

Domain Layer (불변)
├─ TextAnalyzer
├─ Filters
└─ Constants
```

---

## 5. RED 단계 준비

### 5.1 RED 단계 테스트 맵핑

| 테스트 | 노출 이슈 | 현재 상태 |
|--------|---------|---------|
| fil_data 격리 | Critical #1 | FAILS |
| Session 격리 | Critical #2 | FAILS |
| Constants 안정성 | Critical #3 | FAILS |
| Mock 테스트 | High #4 | FAILS |
| 다중 사용자 | High #5 | FAILS |

### 5.2 RED 단계 체크리스트

- [ ] RED-01-01: Google Test 설정
- [ ] RED-01-02: TextAnalyzer Fixture
- [ ] RED-01-03: Constants/Session 초기화
- [ ] RED-01-04: 테스트 네이밍 규칙
- [ ] RED-02-01: 빈 입력 테스트
- [ ] RED-02-02: 특수문자 테스트
- [ ] RED-02-03: 혼합 감정 테스트
- [ ] RED-02-04: 중립 필터 테스트 ← **이슈 #1 노출**
- [ ] RED-02-05: 필터 조합 테스트
- [ ] RED-02-06: 세션 격리 테스트 ← **이슈 #2 노출**

---

## 6. GREEN 단계 준비

### 6.1 임계 수정 (필수)

| 우선순위 | 항목 | 노력 | 시간 |
|---------|------|------|------|
| 1 | fil_data 제거 | LOW | 1-2h |
| 2 | Session 정리 | MEDIUM | 2-3h |
| 3 | 테스트 TearDown | LOW | 1h |

**합계:** 4-6시간 → 임계 이슈 해결

### 6.2 고우선순위 개선 (권장)

| 항목 | 노력 | 시간 |
|------|------|------|
| 의존성 주입 | MEDIUM | 4-6h |
| 요청 컨텍스트 | MEDIUM | 4-6h |

**합계:** 8-12시간 → GREEN 단계 완료

---

## 7. 예상 노력도

### 7.1 전체 리팩토링

**임계 수정만 (최소):**
- GREEN: 4-6시간
- 총: **4-6시간**

**임계 + 고우선순위 (표준):**
- GREEN: 12-18시간
- 총: **12-18시간 = 2-3일**

**전체 (포괄):**
- REFACTOR: 8-12시간 (HTML/유틸 추출)
- 총: **4-7일**

---

## 8. 주요 성과

### 8.1 문서화

- ✅ 4개 심층 분석 문서 (2450+ 라인)
- ✅ 7개 항목별 실행 보고서
- ✅ 아키텍처 개요 + 상세 분석
- ✅ 리팩토링 로드맵 및 우선순위
- ✅ 구체적 시나리오 및 코드 예제

### 8.2 기술 기반

- ✅ 문제점 정량화 (7가지 명확한 이슈)
- ✅ 우선순위 프레임워크 (1-7 순서)
- ✅ 차단 관계도 (무엇이 뭘 막는지)
- ✅ 노력도 추정 (LOW/MEDIUM, 시간 단위)
- ✅ 타임라인 옵션 (1일/3일/1주)

---

## 9. 다음 단계

### 9.1 즉시 (오늘)
- ✅ SPEC 단계 완료
- ✅ RED 단계 시작 준비

### 9.2 RED 단계 (테스트 작성)
- 실패 테스트 작성 (7가지 이슈 노출)
- Google Test 프레임워크 설정
- 테스트 네이밍 규칙 적용

### 9.3 GREEN 단계 (임계 수정)
1. fil_data 제거/이동 (GREEN-01-01)
2. Session 정리 구현 (GREEN-01-02)
3. 테스트 TearDown (GREEN-01-03)
4. Constants 리셋 (GREEN-01-04)
5. 의존성 주입 추가 (GREEN-02-01)
6. 요청 컨텍스트 (GREEN-02-02)

### 9.4 REFACTOR 단계 (구조)
- HTML 렌더러 추출
- 유틸 함수 추출
- 서비스 레이어 구현

---

## 10. 참고 자료

### 10.1 분석 문서

| 문서 | 초점 | 라인 |
|------|------|------|
| [analysis.md](analysis.md) | 전체 아키텍처 | 500+ |
| [analysis-global-state.md](analysis-global-state.md) | 전역 상태 위험 | 600+ |
| [analysis-main-coupling.md](analysis-main-coupling.md) | HTTP/도메인 결합 | 700+ |
| [analysis-refactoring-priority.md](analysis-refactoring-priority.md) | 우선순위 및 로드맵 | 650+ |

### 10.2 실행 보고서

- `reports/phase-0_spec/spec-01-01_*.md`
- `reports/phase-0_spec/spec-01-02_*.md`
- `reports/phase-0_spec/spec-01-03_*.md`
- `reports/phase-0_spec/spec-02-01_*.md`
- `reports/phase-0_spec/spec-02-02_*.md`
- `reports/phase-0_spec/spec-02-03_*.md`
- `reports/phase-0_spec/spec-02-04_*.md`

---

## 요약

**SPEC 단계에서 현재 프로젝트의 아키텍처를 완전히 진단했습니다.**

**핵심 발견:**
- 도메인 로직은 깨끗함 ✅
- HTTP 레이어는 모든 관심사 혼합 🔴
- 전역 상태로 인한 테스트 격리 불가능 🔴

**임계 경로:**
1. 3가지 CRITICAL 이슈 수정 (4-6시간)
2. 2가지 HIGH 이슈 수정 (8-12시간)
3. 2가지 MEDIUM 이슈 수정 (8-12시간)

**총 노력:** 4-7일

**상태:** ✅ SPEC 완료 → RED 단계 준비됨

---

**생성 날짜:** 2026-05-22  
**최종 검토:** 모든 항목 완료, 산출물 검증 완료  
**다음 문서:** [Phase-1: RED 단계 프롬프트]
