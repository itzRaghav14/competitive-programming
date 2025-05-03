// Untested.
// lis[0] < lis[1] < lis[2] ...
int getLIS(vector<int> &arr) {
  vector<int> lis;
  for (int i = 0; i < n; i++) {
    int idx = lower_bound(arr.begin(), arr.end(), arr[i]) - arr.begin();
    if (idx == lis.size()) lis.push_back(arr[i]);
    else lis[idx] = arr[i];
  }
  return lis.size();
}