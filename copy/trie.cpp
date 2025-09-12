struct Node {
    Node* son[26]{};
    bool end = false;
};

class Trie {
    Node* root = new Node();

    int find(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) { // 道不同，不相为谋
                return 0;
            }
            cur = cur->son[c];
        }
        // 走过同样的路（2=完全匹配，1=前缀匹配）
        return cur->end ? 2 : 1;
    }

    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (Node* son : node->son) {
            destroy(son);
        }
        delete node;
    }

public:
    ~Trie() {
        destroy(root);
    }

    void insert(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (cur->son[c] == nullptr) { // 无路可走？
                cur->son[c] = new Node(); // new 出来！
            }
            cur = cur->son[c];
        }
        cur->end = true;
    }

    bool search(string word) {
        return find(word) == 2;
    }

    bool startsWith(string prefix) {
        return find(prefix) != 0;
    }
};
