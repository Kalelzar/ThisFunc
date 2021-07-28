.PHONY: all debugBuild build test run docs

all: build

${PWD}/build/ninja:
	@cmake -G "Ninja Multi-Config" -B build/ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=true

docs:
	@doxygen doxygen

build: ${PWD}/build/ninja
	@cmake --build build/ninja -j 4

debugBuild: ${PWD}/build/ninja
	@cmake --build build/ninja -j 4 --config Debug

test: build
	@ctest -j 4 --test-dir build/ninja -C Release

debugTest: debugBuild
	@valgrind -s ctest -j 4 --test-dir build/ninja --output-on-failure -C Debug

debugRetest: debugBuild
	@valgrind -s ctest -j 4 --rerun-failed --test-dir build/ninja --output-on-failure -C Debug

retest: build
	@ctest -j 4 --rerun-failed --test-dir build/ninja -C Release

run: build
	@rlwrap ./build/ninja/Release/ThisFunc_main

debug: debugBuild
	@valgrind -s ./build/ninja/Debug/ThisFunc_main
bench: build
	@./build/ninja/bench/Release/ThisFunc_bench

debugBench: debugBuild
	@valgrind -s ./build/ninja/bench/Debug/ThisFunc_bench

