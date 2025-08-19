#pragma once
#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    vector<int> nxt;
    TrieNode() {}
    TrieNode(int char_size) {
        nxt.resize(char_size, -1);
    }
};

template <typename Node = TrieNode>
struct Trie {
   public:
    vector<Node> nodes;
    int root;
    int char_size;
    int margin;
    bool init = false;
    int node_cnt;
    Trie(int char_size, int margin, int node_size = -1) : char_size(char_size), margin(margin) {
        if (node_size != -1) {
            init = true;
            nodes.resize(node_size);
            node_cnt = 0;
        }
        root = new_node();
    }

    int new_node() {
        if (init) {
            nodes[node_cnt] = Node(char_size);
            return node_cnt++;
        } else {
            nodes.push_back(Node(char_size));
            return nodes.size() - 1;
        }
    }

    void add(const string &s) {
        int n = s.size();
        int now = root;
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            if (nodes[now].nxt[c] == -1) {
                nodes[now].nxt[c] = new_node();
            }
            now = nodes[now].nxt[c];
        }
    }
};
