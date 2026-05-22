cmake_minimum_required(VERSION 3.14)
project(FeedbackAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core library (without main.cpp)
add_library(feedback_analyzer_lib
    src/cpp/Constants.cpp
    src/cpp/Filters.cpp
    src/cpp/Logger.cpp
    src/cpp/Session.cpp
    src/cpp/TextAnalyzer.cpp
    src/cpp/UIComponents.cpp
    src/cpp/FileHandler.cpp
)

target_include_directories(feedback_analyzer_lib PUBLIC src/cpp)

if(WIN32)
    target_compile_definitions(feedback_analyzer_lib PRIVATE
        _WIN32_WINNT=0x0A00
        WINVER=0x0A00
    )
    target_link_libraries(feedback_analyzer_lib PRIVATE ws2_32)
endif()

# Main executable (disabled until main.cpp compilation errors are fixed in GREEN phase)
# add_executable(feedback_analyzer
#     src/cpp/main.cpp
# )
# target_link_libraries(feedback_analyzer PRIVATE feedback_analyzer_lib)

# Google Test and testing setup
enable_testing()

find_package(GTest QUIET)

if(GTest_FOUND)
    message(STATUS "GTest found: ${GTest_DIR}")

    add_executable(feedback_analyzer_test
        tests/SmokeTest.cpp
    )

    target_link_libraries(feedback_analyzer_test PRIVATE feedback_analyzer_lib GTest::gtest GTest::gtest_main)
    target_include_directories(feedback_analyzer_test PRIVATE src/cpp)

    add_test(NAME smoke_test COMMAND feedback_analyzer_test)
else()
    # Minimal test framework without GTest for initial setup
    message(STATUS "GTest not found. Using minimal test framework.")

    # Create a simple test target that links the library
    add_executable(feedback_analyzer_test
        tests/SmokeTest.cpp
    )

    target_link_libraries(feedback_analyzer_test PRIVATE feedback_analyzer_lib)
    target_include_directories(feedback_analyzer_test PRIVATE src/cpp)

    # Register with CTest
    add_test(NAME smoke_test COMMAND feedback_analyzer_test)

    message(STATUS "")
    message(STATUS "Note: Currently using minimal test framework.")
    message(STATUS "To use Google Test, install it and reconfigure:")
    message(STATUS "  - Install: vcpkg install gtest:x64-windows (recommended)")
    message(STATUS "  - Or: apt-get install libgtest-dev (Linux)")
    message(STATUS "  - Or: brew install googletest (macOS)")
endif()
