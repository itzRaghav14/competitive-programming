vector<int> manacher(string s) {
  string t = "#";
  for (auto c : s) {
    t += c;
    t += '#';
  }
  int n = t.size();
  vector<int> r(n);
  for (int i = 0, j = 0; i < n; i++) {
    if (2 * j - i >= 0 && j + r[j] > i) r[i] = min(r[2 * j - i], j + r[j] - i);
    while (i - r[i] >= 0 && i + r[i] < n && t[i - r[i]] == t[i + r[i]])
      r[i] += 1;
    if (i + r[i] > j + r[j]) j = i;
    r[i]--;
  }
  return vector<int>(begin(r) + 1, end(r) - 1);
}

bool isPalindrome(int l, int r, vector<int> &v_manacher) {
  return v_manacher[l + r] >= r - l + 1;
}