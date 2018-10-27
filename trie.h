#ifndef TRIE_H__
#define TRIE_H__

#include <ostream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#include <sstream>

struct Trie {
    using map_t = std::map<char, Trie*>;
    using set_t = std::set<std::string>;

    map_t children;

    /**
     * Find a character in the children
     *
     * @param ch  The character to search for
     * @return Pointer to the node, nullptr if not found
     */
    Trie* find(char ch);

    /**
     * Add a word to the trie
     *
     * @param word  The word to add to the trie
     */
    void add_word(const std::string& word);

    /**
     * Print out a trie
     *
     * @param out  The ostream to print to
     * @param indent  The indentation level
     */
    void print(std::ostream& out, int indent=0);

    /**
     * Find the set of possible completions starting with prefix
     *
     * @param prefix  The prefix to search for
     * @return Set of possible completions
     */
    set_t completions(const std::string& prefix);

    /**
     * Given a prefix string, traverse the tree until the Trie
     * whose children come after the prefix is found.
     *
     * If no matching Trie is found, nullptr is returned
     *
     * @param prefix  The prefix string
     * @return Pointer to the Trie in the Trie, nullptr if no Trie is found
     */
    Trie* find_prefix_end_node(const std::string& prefix);

    /**
     * Recursive completions helper function
     */
    void completions_helper(const std::string& prefix, std::set<std::string>& out);
};

#endif // TRIE_H__