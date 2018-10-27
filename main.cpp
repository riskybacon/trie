#include <ostream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>

struct Node {
    using map_t = std::map<char, Node*>;

    map_t children;

    bool is_word() const {
        return children.empty();
    }

    Node* find(char ch) {
        auto itr = children.find(ch);
        if (itr != children.end()) {
            return itr->second;
        }

        return nullptr;
    }

    void add_word(const std::string& word) {
        Node* cur = this;

        for (auto ch : word) {
            // Does this character exist in children for the current node?
            Node * child = cur->find(ch);
            if (child == nullptr) {
                // Character not found, add child
                Node* new_node = new Node;
                cur->children[ch] = new_node;
                cur = new_node;
            } else {
                // Character found
                cur = child;
            }
        }
    }

    void print(std::ostream& out, int indent=0) {
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
};

int main(int, char**) {
    Node* root = new Node;
    root->add_word("car");
    root->add_word("cat");
    root->add_word("bob");
    root->add_word("bab");
    root->print(std::cout);
    return 0;
}
