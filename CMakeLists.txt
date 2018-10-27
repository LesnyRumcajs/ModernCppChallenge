cmake_minimum_required(VERSION 3.12)
project(ModernCppChallenge)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

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
endif()

add_executable(ModernCppChallenge src/math/sum_of_naturals.cpp src/math/sum_of_naturals.h tst/math/sum_of_naturals_test.cpp src/math/greatest_common_divisor.cpp src/math/greatest_common_divisor.h tst/math/greatest_common_divisor_test.cpp src/math/least_common_multiple.cpp src/math/least_common_multiple.h tst/math/least_common_multiple.cpp src/math/largest_prime.cpp src/math/largest_prime.h tst/math/largest_prime_test.cpp src/math/sexy_prime_pairs.cpp src/math/sexy_prime_pairs.h tst/math/sexy_primes_pair_test.cpp src/math/abundant_numbers.cpp src/math/abundant_numbers.h tst/math/abundant_numbers_test.cpp src/math/amicable_numbers.cpp src/math/amicable_numbers.h tst/math/amicable_numbers_test.cpp src/math/armstrong_numbers.cpp src/math/armstrong_numbers.h tst/math/armstrong_numbers_test.cpp src/math/prime_factors.cpp src/math/prime_factors.h tst/math/prime_factors_test.cpp src/math/gray_code.cpp src/math/gray_code.h tst/math/gray_code_test.cpp tst/math/numerical_to_roman_test.cpp src/math/numerical_to_roman.cpp src/math/numerical_to_roman.h src/math/collatz_sequence.cpp src/math/collatz_sequence.h tst/math/collatz_sequence_test.cpp src/math/compute_pi.h tst/math/compute_pi_test.cpp)
target_link_libraries(ModernCppChallenge gtest_main gmock_main)