#pragma once
#include <bits/stdc++.h>

#include <cstdint>

#include "./structure/others/trie.hpp"
using namespace std;

struct Node : public TrieNode {
    int cnt;
    Node(int char_size) : TrieNode(char_size) {
        cnt = 0;
    }
};

struct BinaryTrie : public Trie<Node> {
    BinaryTrie() : Trie(2, '0') {}
    explicit BinaryTrie(int node_size) : Trie(2, '0', node_size) {}

    void add_number(uint64_t x, int max_bit = 63) {
        int now = root;
        for (int i = max_bit; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (nodes[now].nxt[b] == -1) {
                nodes[now].nxt[b] = new_node();
            }
            now = nodes[now].nxt[b];
            nodes[now].cnt++;
        }
    }

    void erase_number(uint64_t x, int max_bit = 63) {
        int now = root;
        for (int i = max_bit; i >= 0; i--) {
            int b = (x >> i) & 1;
            now = nodes[now].nxt[b];
            nodes[now].cnt--;
        }
    }

    uint64_t max_xor(uint64_t x, int max_bit = 63) {
        int now = root;
        uint64_t ans = 0;
        for (int i = max_bit; i >= 0; i--) {
            int b = (x >> i) & 1;
            int want = b ^ 1;
            if (nodes[now].nxt[want] != -1 && nodes[nodes[now].nxt[want]].cnt > 0) {
                ans |= (1ULL << i);
                now = nodes[now].nxt[want];
            } else if (nodes[now].nxt[b] != -1 && nodes[nodes[now].nxt[b]].cnt > 0) {
                now = nodes[now].nxt[b];
            } else {
                break;
            }
        }
        return ans;
    }
};