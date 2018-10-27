#include "trie.h"

void test1() {
    Trie* root = new Trie;
    root->add_word("car");
    root->add_word("can");
    root->add_word("catb");
    root->add_word("clll");
    root->add_word("bob");
    root->add_word("bab");

    Trie::set_t expected;
    expected.insert("can");
    expected.insert("car");
    expected.insert("catb");
    expected.insert("clll");

    // find possibilities:
    std::string prefix("c");
    Trie::set_t completions = root->completions(prefix);

    if (expected != completions) {
        std::cout << "[FAIL] 1. expected completions: " << std::endl;
        for (auto completion : expected) {
            std::cout << completion << std::endl;
        }
    }

    prefix = "ca";
    expected.erase(expected.find("clll"));
    completions = root->completions(prefix);
    if (expected != completions) {
        std::cout << "[FAIL] 2. expected completions: " << std::endl;
        for (auto completion : expected) {
            std::cout << completion << std::endl;
        }
    }
}

void test2() {
    Trie* root = new Trie;
    root->add_word("car");
    root->add_word("can");
    root->add_word("catb");
    root->add_word("clll");
    root->add_word("bob");
    root->add_word("bab");

    // find possibilities:
    std::string prefix("g");
    Trie::set_t completions = root->completions(prefix);

    if (!completions.empty()) {
        std::cout << "[FAIL] 3. expected completions to be empty, but got" << std::endl;
        for (auto completion : completions) {
            std::cout << completion << std::endl;
        }
    }

    completions = root->completions("");
    if (!completions.empty()) {
        std::cout << "[FAIL] 4. expected completions to be empty, but got" << std::endl;
        for (auto completion : completions) {
            std::cout << completion << std::endl;
        }
    }
}

int main(int, char**) {
    test1();
    test2();
    return 0;
}
