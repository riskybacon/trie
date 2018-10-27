#include <ostream>
#include <iostream>
#include <map>
#include <queue>

struct Node {
    using map_t = std::map<char, Node*>;

    map_t children;

    bool is_word() const {
        return children.empty();
    }

    bool contains(char ch) const {
        return children.find(ch) != children.end();
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
            Node* child = find(ch);
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

    void print(std::ostream& out) {

        std::queue<Node*> q;
        q.push(this);

        while(!q.empty()) {
            const Node * node = q.front();
            q.pop();

            for (auto itr : node->children) {
                out << itr.first << ",";
                q.push(itr.second);
            }

            out << std::endl;
        }
    }
};

int main(int, char**) {
    Node* root = new Node;
    root->add_word("Car");
    root->add_word("Cat");
    root->print(std::cout);
    return 0;
}
