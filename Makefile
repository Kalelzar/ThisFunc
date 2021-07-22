.PHONY: all debugBuild build test run

all: build

build:
	@cmake --build build/ninja -j 4

debugBuild:
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
	@./build/ninja/Release/ThisFunc_main

debug: debugBuild
	@valgrind -s ./build/ninja/Debug/ThisFunc_main
