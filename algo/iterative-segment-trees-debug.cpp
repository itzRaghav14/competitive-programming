ostream& operator<<(ostream &out, Node node) {
    out << node.val;
    return out;
}

ostream& operator<<(ostream &out, SegmentTree sg) {
    out << "[ ";
    for (int i = 1; i < 2 * sg.n; i++) {
        out << sg.seg[i] << ' ';
        if (__builtin_popcount(i + 1) == 1) out << '\t';
    }
    out << "]";
    return out;
}
