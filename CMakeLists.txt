cmake_minimum_required(VERSION 3.9)
project(ModernCppChallenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Export compile commands for use with clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if ($ENV{VALGRIND})
    message("Setting up for memory check")
    find_program(MEMORYCHECK_COMMAND valgrind)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --error-exitcode=42")
    include(CTest)
    enable_testing()
endif ()

# treat all / extra / pedantic warnings as errors
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
    include_directories("${gmock_SOURCE_DIR}/include")
endif ()

# boost
find_package(Boost COMPONENTS system filesystem date_time REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

if ($ENV{COVERAGE})
    message("Setting up for coverage")
    enable_testing()
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -g -O0 --coverage")
endif ()

add_executable(ModernCppChallengeMath
        src/math/sum_of_naturals.cpp
        src/math/sum_of_naturals.h
        tst/math/sum_of_naturals_test.cpp
        src/math/greatest_common_divisor.cpp
        src/math/greatest_common_divisor.h
        tst/math/greatest_common_divisor_test.cpp
        src/math/least_common_multiple.cpp
        src/math/least_common_multiple.h
        tst/math/least_common_multiple.cpp
        src/math/largest_prime.cpp
        src/math/largest_prime.h
        tst/math/largest_prime_test.cpp
        src/math/sexy_prime_pairs.cpp
        src/math/sexy_prime_pairs.h
        tst/math/sexy_primes_pair_test.cpp
        src/math/abundant_numbers.cpp
        src/math/abundant_numbers.h
        tst/math/abundant_numbers_test.cpp
        src/math/amicable_numbers.cpp
        src/math/amicable_numbers.h
        tst/math/amicable_numbers_test.cpp
        src/math/armstrong_numbers.cpp
        src/math/armstrong_numbers.h
        tst/math/armstrong_numbers_test.cpp
        src/math/prime_factors.cpp
        src/math/prime_factors.h
        tst/math/prime_factors_test.cpp src/math/gray_code.cpp
        src/math/gray_code.h
        tst/math/gray_code_test.cpp
        tst/math/numerical_to_roman_test.cpp
        src/math/numerical_to_roman.cpp
        src/math/numerical_to_roman.h
        src/math/collatz_sequence.cpp
        src/math/collatz_sequence.h
        tst/math/collatz_sequence_test.cpp
        src/math/compute_pi.h
        tst/math/compute_pi_test.cpp
        src/math/isbn_validate.cpp
        src/math/isbn_validate.h
        tst/math/isbn_validate_test.cpp)
target_link_libraries(ModernCppChallengeMath gtest_main gmock_main)
add_test(NAME MathTest COMMAND ModernCppChallengeMath)

add_executable(ModernCppChallengeLang
        src/lang/IPv4.cpp
        src/lang/IPv4.h
        tst/lang/IPv4_test.cpp
        src/lang/BasicArray.h
        tst/lang/BasicArray_test.cpp
        src/lang/container_minimum.h
        tst/lang/container_minimum_test.cpp
        src/lang/value_adder.h
        tst/lang/value_adder_test.cpp
        src/lang/contains_helpers.h
        tst/lang/contains_helpers_test.cpp src/lang/unique_handle.h
        tst/lang/unique_handle_test.cpp
        src/lang/temperature_scales.h
        tst/lang/temperature_scales_test.cpp)
target_link_libraries(ModernCppChallengeLang gtest_main gmock_main)
add_test(NAME LangTest COMMAND ModernCppChallengeLang)

add_executable(ModernCppChallengeString
        src/string/bin2str.h        tst/string/bin2str_test.cpp
        src/string/str2bin.h        tst/string/str2bin_test.cpp
        src/string/capitalize.h     tst/string/capitalize_test.cpp
        src/string/join.h           tst/string/join_test.cpp
        src/string/tokenize.h       tst/string/tokenize_test.cpp
        src/string/longest_palindrome.h tst/string/longest_palindrome_test.cpp
        src/string/license_plate.h  tst/string/license_plate_test.cpp src/string/parse_uri.h tst/string/parse_uri_test.cpp src/string/date_transform.h tst/string/date_transform_test.cpp)
target_link_libraries(ModernCppChallengeString gtest_main gmock_main)
add_test(NAME StringTest COMMAND ModernCppChallengeString)

add_executable(ModernCppChallengeStreamFS
        src/stream_fs/pascal_triangle.h tst/stream_fs/pascal_triangle_test.cpp
        src/stream_fs/tabular_printing.h src/stream_fs/tabular_printing.cpp tst/stream_fs/tabular_printing_test.cpp
        src/stream_fs/remove_empty_lines.h tst/stream_fs/remove_empty_lines_test.cpp
        src/stream_fs/directory_size.h tst/stream_fs/directory_size_test.cpp
        tst/stream_fs/filesystem_helpers.h
        src/stream_fs/remove_old_files.h tst/stream_fs/remove_old_files_test.cpp
        src/stream_fs/regex_find.h tst/stream_fs/regex_find_test.cpp src/stream_fs/logger.h src/stream_fs/logger.cpp tst/stream_fs/logger_test.cpp)
target_link_libraries(ModernCppChallengeStreamFS gtest_main gmock_main stdc++fs ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
add_test(NAME StreamFSTest COMMAND ModernCppChallengeStreamFS)

add_executable(ModernCppChallengeDatetime src/datetime/function_timer.h tst/datetime/function_timer_test.cpp src/datetime/date.cpp src/datetime/date.h tst/datetime/day_diff_test.cpp tst/datetime/day_of_the_week_test.cpp tst/datetime/date_of_the_year_test.cpp src/datetime/timezone_meeting.cpp src/datetime/timezone_meeting.h tst/datetime/timezone_meeting_test.cpp src/datetime/calendar.cpp src/datetime/calendar.h tst/datetime/calendar_test.cpp)
target_link_libraries(ModernCppChallengeDatetime gtest_main gmock_main ${Boost_DATE_TIME_LIBRARY})
add_test(NAME DatetimeTest COMMAND ModernCppChallengeDatetime)
