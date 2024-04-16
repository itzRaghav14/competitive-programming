#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Input {

};

struct Output {

};

Input getInput(ifstream &in) {
    Input input;

    return input;
}

Output getAns(ifstream &in) {
    Output out;

    return out;
}

void check(Input &in, Output &out, Output &ans) {

}

int32_t main(int argc, char *argv[]) {
    ifstream input_stream("io/input.txt");
    ifstream output_stream("io/output.txt");
    ifstream correct_output_stream("stress-testing/brute_output.txt");
    
    int t = 1;
    input_stream >> t;

    for (int tc = 1; tc <= t; tc++) {
        Input input = getInput(input_stream);
        Output output = getAns(output_stream);
        Output correct_output = getAns(correct_output_stream);
        check(input, output, correct_output);
    }

    return 0;
}