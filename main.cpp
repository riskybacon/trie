#include <ostream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>

struct Node {
    using map_t = std::map<char, Node*>;
    using set_t = std::set<std::string>;

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

    /**
     * Find the set of possible completions starting with prefix
     *
     * @param prefix  The prefix to search for
     * @return Set of possible completions
     */
    set_t completions(const std::string& prefix) {
        set_t out;
        Node* parent = find_prefix_end_node(prefix);
        if (parent != nullptr) {
            parent->completions_helper(prefix, out);
        }
        return out;
    }

    /**
     * Given a prefix string, traverse the tree until the node
     * whose children come after the prefix is found.
     *
     * If no matching node is found, nullptr is returned
     *
     * @param prefix  The prefix string
     * @return Pointer to the node in the Trie, nullptr if no node is found
     */
    Node* find_prefix_end_node(const std::string& prefix) {
        if (prefix.length() == 0) {
            return nullptr;
        }
        int depth = 0;
        Node* cur = this;

        while (depth < prefix.length()) {
            Node* child = cur->find(prefix[depth]);
            if (child == nullptr) {
                return nullptr;
            }

            cur = child;
            depth++;
        }

        return cur;
    }

    /**
     * Recursive completions helper function
     */
    void completions_helper(const std::string& prefix, std::set<std::string>& out) {
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

};

int main(int, char**) {
    Node* root = new Node;
    root->add_word("car");
    root->add_word("can");
    root->add_word("catb");
    root->add_word("clll");
    root->add_word("bob");
    root->add_word("bab");

    // find possibilities:
    std::string prefix("c");
    Node::set_t completions = root->completions(prefix);

    if (!completions.empty()) {
        for (auto completion : completions) {
            std::cout << completion << std::endl;
        }
    } else {
        std::cout << "No completions found" << std::endl;
    }

    return 0;
}
