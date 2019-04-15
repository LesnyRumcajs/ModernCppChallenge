#!/bin/bash
clang-tidy -p cmake-build-debug/compile_commands.json \
	tst/algorithms_data_structs/*.cpp \
	-checks=-*,modernize-*,clang-analyzer-*,performance-*,readibility-*,misc-*,llvm-*,cert-*,bugprone-*,hicpp-*,mpi-*,google-*,-llvm-header-guard,-llvm-namespace-comment,-google-readability-namespace-comments,-google-runtime-int \
	-header-filter=.*
