
// === Segment Tree ===

struct Item{
    long long sum;
    int mx, mn;
};

template <typename T>
class SegmentTree{
private: 
	
	int size = 0;
	vector<Item> seg;
	
    Item NEUTRAL_ELEMENT = {0, -MX, MX};
	
	Item single (int val) {
		return {val, val, val};
	}
	
	Item merge (Item left, Item right) {
		Item node = NEUTRAL_ELEMENT;
		node.sum = left.sum + right.sum;
		node.mn = min(left.mn, right.mn);
		node.mx = max(left.mx, right.mx);
		return node;
	}
	
    void build (int low, int high, int ind, vector<T> &arr) {
    	if(low == high) {
    		seg[ind] = single(arr[low]);
    		return;
    	}
    	int mid = (low + high) / 2;
    	int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
    	build(low, mid, leftInd, arr);
    	build(mid + 1, high, rightInd, arr);
    	seg[ind] = merge(seg[leftInd], seg[rightInd]);
    }
	
	Item query (int low, int high, int ind, int left, int right) {
		if(low > right || high < left) {
			return NEUTRAL_ELEMENT;
		}
		if(low >= left && high <= right) {
			return seg[ind];
		}
		int mid = (low + high) / 2;
		int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
		Item leftItem = query(low, mid, leftInd, left, right);
		Item rightItem = query(mid + 1, high, rightInd, left, right);
		return merge(leftItem, rightItem);
	}
	
	void update (int low, int high, int ind, int index, int value) {
		if(low == high) {
			seg[ind] = single(value);
			return;
		}
		int mid = (low + high) / 2;
		int leftInd = 2 * ind + 1, rightInd = 2 * ind + 2;
		if(index <= mid) update(low, mid, leftInd, index, value);
		else update(mid + 1, high, rightInd, index, value);
		seg[ind] = merge(seg[leftInd], seg[rightInd]);
	}
	
public:
	
	SegmentTree () {
		
	}
    
    SegmentTree (int n) {
    	size = n;
    	seg.resize(4 * size + 1);
    }
    
    SegmentTree (vector<T> &arr) {
    	size = arr.size();
    	seg.resize(4 * size + 1);
    	build(arr);
    }
    
    void build (vector<T> &arr) {
    	build(0, size - 1, 0, arr);
    }
    
    Item query (int left, int right) {
    	return query(0, size - 1, 0, left, right);
    }
    
    void update (int index, int value) {
    	return update(0, size - 1, 0, index, value);
    }
};
