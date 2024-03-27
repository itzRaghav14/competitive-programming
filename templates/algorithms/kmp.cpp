// returns the pi function
// pi[i] = length of the longest proper prefix of the substring str[0...i] 
//         which is also a suffix of this substring
vector<int> prefix_function(string str) {
    int n = str.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && str[pi[j]] != str[i]) {
            j = pi[j] - 1;
        }
        if (j >= 0) pi[i] = pi[j] + 1;
    }
    return pi;
}

// return the indexes of the occurrences of the pattern in the text
vector <int> search(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    string str = pattern + "#" + text;
    vector<int> pi = prefix_function(str);
    vector<int> ans;
    for (int i = 2 * m; i <= n + m; i++) {
        if (pi[i] >= m) ans.push_back(i - 2 * m);
    }
    return ans;
}