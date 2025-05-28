#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Input {};

struct Output {};

Input getInput(ifstream &cin) {
  Input in;
  return in;
}

Output getAns(ifstream &cin) {
  Output out;
  return out;
}

void check(Input &in, Output &out, Output &ans) {

}

int32_t main(int32_t argc, char *argv[]) {
  assert(argc >= 4);
  ifstream input_stream(argv[1]);
  ifstream output_stream(argv[2]);
  ifstream correct_output_stream(argv[3]);

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