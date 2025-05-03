#!/bin/zsh
function compile_source {
    local compilation_output=$(g++-14 \
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
        -fno-sanitize-recover \
        -fstack-protector \
        -Wno-variadic-macros \
        "$1" -o "$2")
    echo "$compilation_output"
}

function run_source {
    "$1" <"$2" >"$3" 2>"$4"
    sed -i '' 's/\r$//' "$3"
}

# For compiling
if [ "$1" = "compile" ]; then
    compile_source "$2" a.exe
fi

# For running
if [ "$1" = "run" ]; then
    run_source ./a.exe io/input.txt io/output.txt io/error.txt
    # cat io/output.txt
fi

# For stress testing
if [ "$1" = "stress" ]; then
    # Compile everything
    compile_source main.cpp a.exe
    compile_source stress-testing/brute.cpp brute.exe
    compile_source stress-testing/gen.cpp gen.exe

    # Start running testcases until we find a failed testcase
    for ((i = 1; i <= 10000; i++)); do
        echo -e "TESTCASE: $i" >&2
        ./gen.exe "$i" >io/input.txt
        run_source ./a.exe io/input.txt io/output.txt io/error.txt
        run_source ./brute.exe io/input.txt io/expected_output.txt "/dev/null"
        diff=$(diff -w io/output.txt io/expected_output.txt)

        if [[ "${diff}" != "" ]]; then
            echo -e "\033[0;91mFAILED\033[0m\n" >&2
            echo -e "\n" >&2
            echo -e "\033[0;36mINPUT\033[0m" >&2
            cat io/input.txt >&2
            echo "" >&2
            echo -e "\033[0;36mOUTPUT\033[0m" >&2
            cat io/output.txt >&2
            echo "" >&2
            echo -e "\033[0;36mEXPECTED OUTPUT\033[0m" >&2
            cat io/expected_output.txt >&2
            echo "" >&2
            break
        fi
        echo -e "\033[0;92mPASSED\033[0m\n" >&2
    done
fi

# For stress testing with checker
if [ "$1" = "stress2" ]; then
    # Compile everything
    compile_source main.cpp a.exe
    compile_source stress-testing/gen.cpp gen.exe
    compile_source stress-testing/brute.cpp brute.exe
    compile_source stress-testing/checker.cpp checker.exe

    # Start running testcases until we find a failed testcase
    for ((i = 1; i <= 10000; i++)); do
        ./gen.exe "$i" >io/input.txt
        run_source ./a.exe io/input.txt io/output.txt io/error.txt
        run_source ./brute.exe io/input.txt io/expected_output.txt "/dev/null"
        ./checker.exe io/input.txt io/output.txt io/expected_output.txt

        if [ $? -ne 0 ]; then
            echo -e "\n" >&2
            echo -e "\033[0;36mINPUT\033[0m" >&2
            cat io/input.txt >&2
            echo "" >&2
            echo -e "\033[0;36mOUTPUT\033[0m" >&2
            cat io/output.txt >&2
            echo "" >&2
            echo -e "\033[0;36mEXPECTED OUTPUT\033[0m" >&2
            cat io/expected_output.txt >&2
            echo "" >&2
            break
        fi
        echo $i
    done
fi

if [ "$1" = "clean" ]; then
    rm -f *.exe
    rm -f a.out
fi

if [ "$1" = "interact" ]; then
    compile_source "$2" a.exe
    compile_source stress-testing/jury.cpp jury.exe
    build/interact.py -c ./a.exe ./jury.exe
fi

# For stress testing
if [ "$1" = "generate-tests" ]; then
    # Compile everything
    compile_source main.cpp a.exe
    compile_source stress-testing/gen.cpp gen.exe

    mkdir -p test-data

    # Start running testcases until we find a failed testcase
    for ((i = 1; i <= 20; i++)); do
        test_number=$(printf "%02d" $i)
        echo $test_number
        ./gen.exe "$i" >test-data/$test_number.in
        run_source ./a.exe test-data/$test_number.in test-data/$test_number.ok /dev/null
    done
fi

# For stress testing
if [ "$1" = "verify-tests" ]; then
    compile_source main.cpp a.exe

    # Start running testcases until we find a failed testcase
    for ((i = 1; i <= 20; i++)); do
        test_number=$(printf "%02d" $i)
        input_file="test-data/$test_number.in"
        output_file="io/output.txt"
        expected_output_file="test-data/$test_number.ok"

        echo -e "TESTCASE: $test_number" >&2
        run_source ./a.exe $input_file $output_file /dev/null
        diff=$(diff -w $output_file $expected_output_file)

        if [[ "${diff}" != "" ]]; then
            echo -e "\033[0;91mFAILED\033[0m\n" >&2
            echo -e "\n" >&2
            echo -e "\033[0;36mINPUT\033[0m" >&2
            cat $input_file >&2
            cat $input_file > io/input.txt
            echo "" >&2
            echo -e "\033[0;36mOUTPUT\033[0m" >&2
            cat $output_file >&2
            echo "" >&2
            echo -e "\033[0;36mEXPECTED OUTPUT\033[0m" >&2
            cat $expected_output_file >&2
            echo "" >&2
            break
        fi
        echo -e "\033[0;92mPASSED\033[0m\n" >&2
    done
fi

if [ "$1" = "verify-json" ]; then
    cat $2 | python3 -c "import sys,json;json.loads(sys.stdin.read());print ('OK')"
fi

if [ "$1" = "verify-problem-format" ]; then
    source .venv/bin/activate
    python problem-setting/test-problem.py
    deactivate
fi
