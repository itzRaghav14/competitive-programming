struct Node {
  int val, orz;
  Node() : val(0), orz(0) {}
  Node(int v) : val(v), orz(v) {}
  friend Node add(Node l, Node r) {  // right Node will be added on top of left
    Node res;
    res.val = r.val;
    res.orz = l.orz | r.val;
    return res;
  }
  friend Node merge(Node l, Node r) { return Node(l.orz | r.orz); }
};

struct MonotonicQueue {
  stack<Node> front, back;
  Node top(stack<Node> &stk) { return stk.empty() ? Node() : stk.top(); }
  void addToStack(stack<Node> &stk, Node x) { stk.push(add(top(stk), x)); }
  void push(long long x) { addToStack(back, x); }
  void pop() {
    if (front.empty())
      while (!back.empty()) addToStack(front, top(back)), back.pop();
    front.pop();
  }
  Node query() { return merge(top(front), top(back)); }
};