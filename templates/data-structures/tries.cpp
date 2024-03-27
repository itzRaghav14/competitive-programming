struct Node {
    Node* links[26];
    int isStart;
    int isEnd;

    Node() {
        for (int i = 0; i < 26; i++)
            links[i] = NULL;
        isStart = 0;
        isEnd = 0;
    }

    bool contains(char ch) {
        return links[ch - 'a'] != NULL;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch) {
        links[ch - 'a'] = new Node();
    }
};

struct Trie {
    Node* root = NULL;

    Trie() {
        root = new Node();
    }

    void insert(string str) {
        Node* node = root;
        for (auto ch : str) {
            if (!node->contains(ch)) {
                node->put(ch);
            }
            node = node->get(ch);
            node->isStart++;
        }
        node->isEnd++;
    }

    bool search(string str) {
        Node* node = root;
        for (auto ch : str) {
            if (!node->contains(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return node->isEnd;
    }

    bool searchPrefix(string str) {
        Node* node = root;
        for (auto ch : str) {
            if (!node->contains(ch)) {
                return false;
            }
            node = node->get(ch);
        }
        return node->isStart;
    }

    void erase(string str) {
        if (!search(str)) return;
        Node* node = root;
        for (auto ch : str) {
            node = node->get(ch);
            node->isStart--;
        }
        node->isEnd--;
    }
};