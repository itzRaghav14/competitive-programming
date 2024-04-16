#!/usr/bin/bash
function compile_source {
    local compilation_output=$(g++ \
        --std=c++2a \
        -include build/stdafx.h \
        -DitzzRaghav \
        -Wall \
        -Wextra \
        -pedantic \
        -O2 \
        -Wshadow \
        -Wformat=2 \
        -Wfloat-equal \
        -Wconversion \
        -Wlogical-op \
        -Wshift-overflow=2 \
        -Wduplicated-cond \
        -Wcast-qual \
        -Wcast-align \
        -D_GLIBCXX_DEBUG \
        -D_GLIBCXX_DEBUG_PEDANTIC \
        -D_FORTIFY_SOURCE=2 \
        -fsanitize=address \
        -fsanitize=undefined \
        -fno-sanitize-recover \
        -fstack-protector \
        -Wno-variadic-macros \
        $1 -o $2)
    echo "$compilation_output"
}

function run_source {
	$1 <$2 >$3 2>$4
	sed -i 's/\r$//' $3
}

# For compiling
if [ $1 == "compile" ]; then
	compile_source $2 a.exe
fi

# For running
if [ $1 == "run" ]; then
	run_source ./a.exe io/input.txt io/output.txt io/error.txt
	# cat io/output.txt
fi

# For stress testing
if [ $1 = "stress" ]; then
	# Compile everything
	compile_source main.cpp a.exe
	compile_source stress-testing/gen.cpp gen.exe
	compile_source stress-testing/brute.cpp brute.exe

	# Start running testcases until we find a failed testcase
	for ((i = 1; i <= 10000; i++)); do
		echo "RUNNING TEST $i ..."
		./gen.exe $i >io/input.txt

		run_source ./a.exe io/input.txt io/output.txt io/error.txt
		run_source ./brute.exe io/input.txt stress-testing/brute_output.txt stress-testing/brute_error.txt

		diff=$(diff -w io/output.txt stress-testing/brute_output.txt)
		if [[ "${diff}" != "" ]]; then
            RED='\033[0;31m'
            CYAN='\033[0;36m'
            NC='\033[0m'
            INPUTS=$(cat io/input.txt)
            echo -e "${CYAN}${INPUTS}${NC}"
            echo -e "${RED}FAILED${NC}"
            break
		else
            GREEN='\033[32m'
            NC='\033[0m'
            echo -e "${GREEN}PASSED${NC}"
		fi
        echo ""
	done
fi

# For stress testing with checker
if [ $1 = "stress2" ]; then
	# Compile everything
	compile_source main.cpp a.exe
	compile_source stress-testing/gen.cpp gen.exe
	compile_source stress-testing/brute.cpp brute.exe
    compile_source stress-testing/checker.cpp checker.exe

	# Start running testcases until we find a failed testcase
	for ((i = 1; i <= 10000; i++)); do
		echo "RUNNING TEST $i ..."
		./gen.exe $i >io/input.txt

		run_source ./a.exe io/input.txt io/output.txt io/error.txt
		run_source ./brute.exe io/input.txt stress-testing/brute_output.txt stress-testing/brute_error.txt
        ./checker.exe

        if [ $? -ne 0 ]; then
            RED='\033[0;31m'
            CYAN='\033[0;36m'
            NC='\033[0m'
            INPUTS=$(cat io/input.txt)
            echo -e "${CYAN}${INPUTS}${NC}"
            echo -e "${RED}FAILED${NC}"
            break
        else
            GREEN='\033[32m'
            NC='\033[0m'
            echo -e "${GREEN}PASSED${NC}"
        fi
        echo ""
	done
fi

if [ $1 == "clean" ]; then
    rm -f *.exe
    rm -f a.out
    rm -f stress-testing/brute_output.txt
    rm -f stress-testing/brute_error.txt
fi

if [ $1 == "interact" ]; then
    compile_source $2 a.exe
    compile_source stress-testing/jury.cpp jury.exe
    build/interact.py -c ./a.exe ./jury.exe
fi