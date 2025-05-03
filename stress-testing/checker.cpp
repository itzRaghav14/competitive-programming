#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Input {
  int n;
};

struct Output {
  string ans;
};

Input getInput(ifstream &cin) {
  Input in;
  cin >> in.n;
  return in;
}

Output getAns(ifstream &cin) {
  Output out;
  cin >> out.ans;
  return out;
}

void check(Input &in, Output &out, Output &ans) {
  if (out.ans != ans.ans) exit(1);
}

int32_t main(int32_t argc, char* argv[]) {
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