# Feedback Analyzer Prompt Index

이 문서는 `N번 진행` 요청을 TODO 식별자와 프롬프트 파일로 매핑하기 위한 인덱스다.

## Phase-0: SPEC

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 1 | SPEC-01-01 | `phase-0_spec/spec-01-01_define_b07_branch_workflow-prompt.md` |
| 2 | SPEC-01-02 | `phase-0_spec/spec-01-02_document_build_and_test_commands-prompt.md` |
| 3 | SPEC-01-03 | `phase-0_spec/spec-01-03_align_project_instructions-prompt.md` |
| 4 | SPEC-02-01 | `phase-0_spec/spec-02-01_add_architecture_analysis-prompt.md` |
| 5 | SPEC-02-02 | `phase-0_spec/spec-02-02_analyze_global_state_risks-prompt.md` |
| 6 | SPEC-02-03 | `phase-0_spec/spec-02-03_analyze_main_coupling-prompt.md` |
| 7 | SPEC-02-04 | `phase-0_spec/spec-02-04_prioritize_refactoring_targets-prompt.md` |

## Phase-1: RED

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 8 | RED-01-01 | `phase-1_red/red-01-01_configure_gtest_target-prompt.md` |
| 9 | RED-01-02 | `phase-1_red/red-01-02_add_text_analyzer_fixture-prompt.md` |
| 10 | RED-01-03 | `phase-1_red/red-01-03_reset_constants_and_session_per_test-prompt.md` |
| 11 | RED-01-04 | `phase-1_red/red-01-04_enforce_descriptive_test_names-prompt.md` |
| 12 | RED-02-01 | `phase-1_red/red-02-01_add_empty_input_boundary_test-prompt.md` |
| 13 | RED-02-02 | `phase-1_red/red-02-02_add_special_character_input_test-prompt.md` |
| 14 | RED-02-03 | `phase-1_red/red-02-03_add_mixed_sentiment_input_test-prompt.md` |
| 15 | RED-02-04 | `phase-1_red/red-02-04_add_neutral_filter_test-prompt.md` |
| 16 | RED-02-05 | `phase-1_red/red-02-05_add_filter_combination_tests-prompt.md` |
| 17 | RED-02-06 | `phase-1_red/red-02-06_add_session_isolation_test-prompt.md` |

## Phase-2: GREEN

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 18 | GREEN-01-01 | `phase-2_green/green-01-01_correct_neutral_filter_condition-prompt.md` |
| 19 | GREEN-01-02 | `phase-2_green/green-01-02_support_multiline_feedback_input-prompt.md` |
| 20 | GREEN-01-03 | `phase-2_green/green-01-03_add_runtime_log_level_control-prompt.md` |
| 21 | GREEN-01-04 | `phase-2_green/green-01-04_reset_shared_state_in_tests-prompt.md` |
| 22 | GREEN-02-01 | `phase-2_green/green-02-01_add_bug_fix_report-prompt.md` |
| 23 | GREEN-02-02 | `phase-2_green/green-02-02_record_bug_verification_logs-prompt.md` |
| 24 | GREEN-02-03 | `phase-2_green/green-02-03_verify_green_regression_suite-prompt.md` |

## Phase-3: REFACTOR

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 25 | REFACTOR-01-01 | `phase-3_refactor/refactor-01-01_rename_sent_to_analyzesentiment-prompt.md` |
| 26 | REFACTOR-01-02 | `phase-3_refactor/refactor-01-02_rename_kw_to_analyzekeywords-prompt.md` |
| 27 | REFACTOR-01-03 | `phase-3_refactor/refactor-01-03_rename_fil_to_applyfilter-prompt.md` |
| 28 | REFACTOR-01-04 | `phase-3_refactor/refactor-01-04_extract_sentiment_labels-prompt.md` |
| 29 | REFACTOR-01-05 | `phase-3_refactor/refactor-01-05_extract_score_constants-prompt.md` |
| 30 | REFACTOR-01-06 | `phase-3_refactor/refactor-01-06_clean_duplicated_sentiment_keywords-prompt.md` |
| 31 | REFACTOR-01-07 | `phase-3_refactor/refactor-01-07_add_public_api_doxygen_comments-prompt.md` |
| 32 | REFACTOR-02-01 | `phase-3_refactor/refactor-02-01_add_text_utils_containsany-prompt.md` |
| 33 | REFACTOR-02-02 | `phase-3_refactor/refactor-02-02_reuse_containsany_in_text_analyzer-prompt.md` |
| 34 | REFACTOR-02-03 | `phase-3_refactor/refactor-02-03_reuse_containsany_in_filters-prompt.md` |
| 35 | REFACTOR-02-04 | `phase-3_refactor/refactor-02-04_split_long_text_analyzer_routines-prompt.md` |
| 36 | REFACTOR-02-05 | `phase-3_refactor/refactor-02-05_split_long_filter_routines-prompt.md` |
| 37 | REFACTOR-03-01 | `phase-3_refactor/refactor-03-01_remove_global_filter_state-prompt.md` |
| 38 | REFACTOR-03-02 | `phase-3_refactor/refactor-03-02_remove_global_analyzer_state-prompt.md` |
| 39 | REFACTOR-03-03 | `phase-3_refactor/refactor-03-03_implement_session_storage_map-prompt.md` |
| 40 | REFACTOR-03-04 | `phase-3_refactor/refactor-03-04_add_feedback_session_clear_api-prompt.md` |
| 41 | REFACTOR-03-05 | `phase-3_refactor/refactor-03-05_add_session_lifecycle_regression_tests-prompt.md` |
| 42 | REFACTOR-03-06 | `phase-3_refactor/refactor-03-06_add_refactoring_report-prompt.md` |

## Phase-4: FEATURE

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 43 | FEATURE-01-01 | `phase-4_feature/feature-01-01_add_weighted_sentiment_scoring_tests-prompt.md` |
| 44 | FEATURE-01-02 | `phase-4_feature/feature-01-02_count_positive_and_negative_keywords-prompt.md` |
| 45 | FEATURE-01-03 | `phase-4_feature/feature-01-03_calculate_relative_sentiment_score-prompt.md` |
| 46 | FEATURE-01-04 | `phase-4_feature/feature-01-04_classify_sentiment_from_weighted_score-prompt.md` |
| 47 | FEATURE-01-05 | `phase-4_feature/feature-01-05_add_mixed_sentiment_scoring_regression-prompt.md` |
| 48 | FEATURE-02-01 | `phase-4_feature/feature-02-01_add_csv_persistence_tests-prompt.md` |
| 49 | FEATURE-02-02 | `phase-4_feature/feature-02-02_persist_feedback_with_ofstream-prompt.md` |
| 50 | FEATURE-02-03 | `phase-4_feature/feature-02-03_write_utf8_bom_for_csv_export-prompt.md` |
| 51 | FEATURE-02-04 | `phase-4_feature/feature-02-04_escape_csv_feedback_body-prompt.md` |
| 52 | FEATURE-02-05 | `phase-4_feature/feature-02-05_handle_csv_persistence_errors-prompt.md` |
| 53 | FEATURE-03-01 | `phase-4_feature/feature-03-01_add_feature_specification-prompt.md` |
| 54 | FEATURE-03-02 | `phase-4_feature/feature-03-02_record_feature_verification-prompt.md` |

## Phase-5: FINAL

| 번호 | TODO ID | 프롬프트 파일 |
|---:|---|---|
| 55 | FINAL-01-01 | `phase-5_final/final-01-01_add_final_outline-prompt.md` |
| 56 | FINAL-01-02 | `phase-5_final/final-01-02_record_loc_comparison-prompt.md` |
| 57 | FINAL-01-03 | `phase-5_final/final-01-03_record_test_coverage_summary-prompt.md` |
| 58 | FINAL-01-04 | `phase-5_final/final-01-04_record_complexity_reduction_summary-prompt.md` |
| 59 | FINAL-01-05 | `phase-5_final/final-01-05_add_ai_collaboration_retrospective-prompt.md` |
| 60 | FINAL-02-01 | `phase-5_final/final-02-01_verify_required_markdown_outputs-prompt.md` |
| 61 | FINAL-02-02 | `phase-5_final/final-02-02_run_final_regression_suite-prompt.md` |
| 62 | FINAL-02-03 | `phase-5_final/final-02-03_update_session_notes_for_final_handoff-prompt.md` |


