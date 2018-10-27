#include <iostream>
#include <iomanip>
#include "trie.h"

Trie* Trie::find(char ch) {
    auto itr = children.find(ch);
    if (itr != children.end()) {
        return itr->second;
    }

    return nullptr;
}

void Trie::add_word(const std::string& word) {
    Trie* cur = this;

    for (auto ch : word) {
        // Does this character exist in children for the current node?
        Trie* child = cur->find(ch);
        if (child == nullptr) {
            // Character not found, add child
            Trie* new_trie = new Trie;
            cur->children[ch] = new_trie;
            cur = new_trie;
        } else {
            // Character found
            cur = child;
        }
    }
}


void Trie::print(std::ostream& out, int indent) {
    if (children.size() == 0) {
        return;
    }

    for (auto itr : children) {
        if (indent > 0) {
            out << std::setw(indent) << ' ';
        }

        out << itr.first << std::endl;
        itr.second->print(out, indent + 1);
    }
}


Trie::set_t Trie::completions(const std::string& prefix) {
    set_t out;
    Trie* parent = find_prefix_end_node(prefix);
    if (parent != nullptr) {
        parent->completions_helper(prefix, out);
    }
    return out;
}


Trie* Trie::find_prefix_end_node(const std::string& prefix) {
    if (prefix.length() == 0) {
        return nullptr;
    }
    int depth = 0;
    Trie* cur = this;

    while (depth < prefix.length()) {
        Trie* child = cur->find(prefix[depth]);
        if (child == nullptr) {
            return nullptr;
        }

        cur = child;
        depth++;
    }

    return cur;
}

void Trie::completions_helper(const std::string& prefix, std::set<std::string>& out) {
    if (children.empty()) {
        out.insert(prefix);
    } else {
        for (auto itr : children) {
            std::stringstream ss;
            ss << prefix << itr.first;
            itr.second->completions_helper(ss.str(), out);
        }
    }
}
