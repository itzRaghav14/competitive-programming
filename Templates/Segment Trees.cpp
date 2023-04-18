// === Segment Tree ===

struct item{
    int sum, mx, pre, suf;
};

class segtree{
public:
    
    vector<item> seg;
    int n;
    
    item NEUTRAL_ELEMENT = {0, -INF, -INF, -INF};
    
    item single(int val){
        int mxVal = max(0ll, val);
        return {val, mxVal, mxVal, mxVal};
    }
    
    item merge(item left, item right, int type = 1){
        
        item node = NEUTRAL_ELEMENT;
        
        
        
        return node;
        
    }
    
    
    segtree(vector<int> &arr, int size = -1){
        if(size == -1) size = arr.size();
        n = size;
        seg.resize(4 * n + 1);
        build(arr);
    }
    
    void build(vector<int> &arr, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n -  1;
        if(low == high){
            seg[ind] = single(arr[low]);
            return;
        }
        int mid = (low + high) / 2;
        build(arr, 2 * ind + 1, low, mid);
        build(arr, 2 * ind + 2, mid + 1, high);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    
    item query(int l, int r, int type = 1, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n - 1;
        if(low > r || high < l){
            return NEUTRAL_ELEMENT;
        }
        if(low >= l && high <= r) return seg[ind];
        int mid = (low + high) / 2;
        item left = query(l, r, 1, 2 * ind + 1, low, mid);
        item right = query(l, r, 1, 2 * ind + 2, mid + 1, high);
        return merge(left, right);        
    }
    
    void update(int i, int v, int ind = 0, int low = 0, int high = -1){
        if(high == -1) high = n - 1;
        if(low == high){
            seg[ind] = single(v);
            return;
        }
        int mid = (low + high) / 2;
        if(i <= mid) update(i, v, 2 * ind + 1, low, mid);
        else update(i, v, 2 * ind + 2, mid + 1, high);
        seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    
};