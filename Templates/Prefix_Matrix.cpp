
// Prefix Matrix 
template <typename T>
class PreMatrix {
private:
	int n, m;
	vector<vector<long long>> pre;
	
	// define the value of keys here
	long long getVal (T key) {
		int val = 0;
		// val = key
		return val;
	}
	
	// take modulo if required
	long long add (int a, int b) {
		return a + b;
	}
	
	// take modulo if required
	long long diff (int a, int b) {
		return a - b;
	}
	
	// don't change
	long long get (int row, int col) {
		if(row < 0 || row >= n || col < 0 || col >= m) {
			return 0;
		}
		return pre[row][col];
	}
	
	// don't change
	void build () {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				pre[i][j] = add(get(i, j), get(i - 1, j));
				pre[i][j] = add(get(i, j), get(i, j - 1));
				pre[i][j] = diff(get(i, j), get(i - 1, j - 1));
			}
		}
	}
	
public:
	
	// don't change
	PreMatrix (vector<string> &mat) {
		n = mat.size();
		m = n ? mat[0].size() : 0;
		pre.resize(n, vector<long long> (m, 0));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				pre[i][j] = getVal(mat[i][j]);
			}
		}
		build();
	}
	
	// don't change
	PreMatrix (vector<vector<T>> &mat) {
		n = mat.size();
		m = n ? mat[0].size() : 0;
		pre.resize(n, vector<long long> (m, 0));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				pre[i][j] = getVal(mat[i][j]);
			}
		}
		build();
	}
	
	// don't change
	long long query (int sRow, int sCol, int eRow, int eCol) {
		long long sum = 0;
		sum = add(sum, get(eRow, eCol));
		sum = add(sum, get(sRow - 1, sCol - 1));
		sum = diff(sum, get(sRow - 1, eCol));
		sum = diff(sum, get(eRow, sCol - 1));
		return sum;
	}
};
