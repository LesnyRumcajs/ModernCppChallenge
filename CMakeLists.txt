cmake_minimum_required(VERSION 3.9)
project(ModernCppChallenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Export compile commands for use with clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

if ($ENV{VALGRIND})
    message("Setting up for memory check")
    find_program(MEMORYCHECK_COMMAND valgrind)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --error-exitcode=42")
endif ()

# treat all / extra / pedantic warnings as errors
IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

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

# boost
find_package(Boost COMPONENTS system filesystem date_time REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

find_package(pugixml REQUIRED)
if (pugixml_FOUND)
    include_directories(${pugixml_INCLUDE_DIRS})
endif()

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
        src/string/bin2str.h tst/string/bin2str_test.cpp
        src/string/str2bin.h tst/string/str2bin_test.cpp
        src/string/capitalize.h tst/string/capitalize_test.cpp
        src/string/join.h tst/string/join_test.cpp
        src/string/tokenize.h tst/string/tokenize_test.cpp
        src/string/longest_palindrome.h tst/string/longest_palindrome_test.cpp
        src/string/license_plate.h tst/string/license_plate_test.cpp src/string/parse_uri.h tst/string/parse_uri_test.cpp src/string/date_transform.h tst/string/date_transform_test.cpp)
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

add_executable(ModernCppChallengeAlgorithmsDataStructs src/algorithms_data_structs/priority_queue.h tst/algorithms_data_structs/priority_queue_test.cpp src/algorithms_data_structs/circular_buffer.h tst/algorithms_data_structs/circular_buffer_test.cpp src/algorithms_data_structs/circular_iterator.h src/algorithms_data_structs/double_buffer.h tst/algorithms_data_structs/double_buffer_test.cpp src/algorithms_data_structs/most_frequent.h tst/algorithms_data_structs/most_frequent_test.cpp src/algorithms_data_structs/text_histogram.h tst/algorithms_data_structs/text_histogram_test.cpp src/algorithms_data_structs/phone_numbers_filter.h tst/algorithms_data_structs/phone_numbers_filter_test.cpp src/algorithms_data_structs/phone_numbers_transform.h tst/algorithms_data_structs/phone_numbers_transform_test.cpp src/algorithms_data_structs/phone_numbers_filter.cpp src/algorithms_data_structs/phone_numbers_transform.cpp src/algorithms_data_structs/permutation.h tst/algorithms_data_structs/permutation_test.cpp src/algorithms_data_structs/movies_rating.h tst/algorithms_data_structs/movies_rating_test.cpp src/algorithms_data_structs/pairwise.h tst/algorithms_data_structs/pairwise_test.cpp src/algorithms_data_structs/zip.h tst/algorithms_data_structs/zip_test.cpp src/algorithms_data_structs/select.h tst/algorithms_data_structs/select_test.cpp src/algorithms_data_structs/sort.h tst/algorithms_data_structs/sort_test.cpp src/algorithms_data_structs/shortest_path.h tst/algorithms_data_structs/shortest_path_test.cpp src/algorithms_data_structs/weasel_program.h src/algorithms_data_structs/weasel_program.cpp tst/algorithms_data_structs/weasel_test.cpp src/algorithms_data_structs/game_of_life.h src/algorithms_data_structs/game_of_life.cpp)

target_link_libraries(ModernCppChallengeAlgorithmsDataStructs gtest_main gmock_main)
add_test(NAME AlgorithmsDataStructsTest COMMAND ModernCppChallengeAlgorithmsDataStructs)

add_executable(ModernCppChallengeWeaselShow src/algorithms_data_structs/weasel_program.h src/algorithms_data_structs/weasel_program.cpp src/algorithms_data_structs/weasel_run.cpp)
add_executable(ModernCppChallengeGameOfLife src/algorithms_data_structs/game_of_life.h src/algorithms_data_structs/game_of_life.cpp src/algorithms_data_structs/game_of_life_run.cpp)

add_executable(ModernCppChallengeConcurrency
        src/concurrency/parallel_transform.h tst/concurrency/parallel_transform_test.cpp src/concurrency/parallel_search_threads.h tst/concurrency/parallel_search_threads_test.cpp src/concurrency/parallel_search_async.h tst/concurrency/parallel_search_async_test.cpp src/concurrency/parallel_sort.h tst/concurrency/parallel_sort_test.cpp src/concurrency/sync_log.h tst/concurrency/sync_log_test.cpp src/concurrency/custom_service_system.h tst/concurrency/custom_service_system_test.cpp)
target_link_libraries(ModernCppChallengeConcurrency gtest_main gmock_main tbb)
add_test(NAME ConcurrencyTest COMMAND ModernCppChallengeConcurrency)

add_executable(ModernCppChallengeConcurrencyBenchmark src/concurrency/parallel_transform_benchmark.cpp src/concurrency/parallel_transform_benchmark.cpp )
target_link_libraries(ModernCppChallengeConcurrencyBenchmark tbb)

add_executable(ModernCppChallengeCustomServiceSystemSimulation src/concurrency/custom_service_system.h src/concurrency/custom_service_system_simulation.cpp src/concurrency/custom_service_system_simulation.cpp)
target_link_libraries(ModernCppChallengeCustomServiceSystemSimulation pthread tbb)

add_executable(ModernCppChallengeDesignPatterns src/design_patterns/password_validator.h tst/design_patterns/password_validator_test.cpp src/design_patterns/password_generator.h tst/design_patterns/password_generator_test.cpp src/design_patterns/social_insurance_number_generator.h tst/design_patterns/social_insurance_number_generator_test.cpp src/design_patterns/acceptance_system.h tst/design_patterns/acceptance_system_test.cpp src/design_patterns/observed_vector.h tst/design_patterns/observed_vector.cpp src/design_patterns/price_calculator.h tst/design_patterns/price_calculator_test.cpp)
target_link_libraries(ModernCppChallengeDesignPatterns gtest_main gmock_main)
add_test(NAME DesignPatternsTest COMMAND ModernCppChallengeDesignPatterns)

add_executable(ModernCppChallengeSerialization src/serialization/xml_serde.h tst/serialization/xml_serde_test.cpp src/serialization/xml_xpath.h tst/serialization/xml_xpath_test.cpp)
target_link_libraries(ModernCppChallengeSerialization gtest_main gmock_main boost_serialization pugixml)
add_test(NAME SerializationTest COMMAND ModernCppChallengeSerialization)