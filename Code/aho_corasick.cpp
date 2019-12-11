// This version of aho_corasick uses more memory and depends on a small constant-sized alphabet, but it's slightly
// faster in runtime.
template<char MIN_CHAR = 'a', int ALPHABET = 26>
struct aho_corasick {
    struct node {
        // suff = the index of the node of the longest suffix of the current node that's also in the tree.
        //   Also see "blue arcs" on Wikipedia: https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm
        // dict = the index of the node of the longest suffix of the current node that's in the word list.
        //   Also see "green arcs" on Wikipedia.
        // depth = normal trie depth (root is 0).
        // word_index = the index of the *first* word ending at this node. -1 if none.
        // word_count = the total number of words ending at this node.
        // link = the trie connections and/or suffix connections from this node.
        int suff = -1, dict = -1, depth = 0;
        int word_index = -1, word_count = 0;

        int link[ALPHABET];

        node() {
            fill(link, link + ALPHABET, -1);
        }

        int& operator[](char c) {
            return link[c - MIN_CHAR];
        }
    };

    vector<node> nodes;
    vector<string> words;
    vector<int> word_location;
    vector<int> word_indices_by_depth;
    vector<int> defer;

    aho_corasick(const vector<string> &_words = {}) {
        if (!_words.empty())
            build(_words);
    }

    // Builds the adj list based on suffix parents. Often we want to perform DP and/or queries on this tree.
    vector<vector<int>> build_suffix_adj() const {
        vector<vector<int>> adj(nodes.size());

        for (int i = 1; i < (int) nodes.size(); i++)
            adj[nodes[i].suff].push_back(i);

        return adj;
    }

    int get_or_add_child(int current, char c) {
        if (nodes[current][c] >= 0)
            return nodes[current][c];

        int index = nodes.size();
        nodes[current][c] = index;
        nodes.emplace_back();
        nodes.back().depth = nodes[current].depth + 1;
        return index;
    }

    int add_word(const string &word, int word_index) {
        assert(!nodes.empty());
        int current = 0;

        for (char c : word)
            current = get_or_add_child(current, c);

        if (nodes[current].word_index < 0)
            nodes[current].word_index = word_index;

        nodes[current].word_count++;
        return current;
    }

    // Returns where in the trie we should end up after starting at `location` and adding char `c`.
    int get_suffix_link(int location, char c) const {
        if (location >= 0)
            location = nodes[location].link[c - MIN_CHAR];

        return max(location, 0);
    }

    void build(const vector<string> &_words) {
        nodes.assign(1, node());
        words = _words;
        stable_sort(words.begin(), words.end());
        word_location.resize(words.size());
        defer.resize(words.size());
        int max_depth = 0;

        for (int i = 0; i < (int) words.size(); i++) {
            word_location[i] = add_word(words[i], i);
            max_depth = max(max_depth, nodes[word_location[i]].depth);
            defer[i] = i;

            if (i > 0 && words[i] == words[i - 1])
                defer[i] = defer[i - 1];
        }

        // Create a list of word indices in decreasing order of depth, in linear time.
        vector<vector<int>> indices_by_depth(max_depth + 1, vector<int>());
        word_indices_by_depth.clear();

        for (int i = 0; i < (int) words.size(); i++)
            indices_by_depth[nodes[word_location[i]].depth].push_back(i);

        for (int depth = max_depth; depth >= 0; depth--)
            for (int index : indices_by_depth[depth])
                word_indices_by_depth.push_back(index);

        // Solve suffix parents by traversing in order of depth (BFS order).
        vector<int> q = {0};

        for (int i = 0; i < (int) q.size(); i++) {
            int current = q[i];

            for (char c = MIN_CHAR; c < MIN_CHAR + ALPHABET; c++) {
                int &index = nodes[current][c];

                if (index >= 0) {
                    // Find index's suffix parent by traversing suffix parents of current until one of them has a child c.
                    int suffix_parent = get_suffix_link(nodes[current].suff, c);
                    nodes[index].suff = suffix_parent;
                    nodes[index].word_count += nodes[suffix_parent].word_count;
                    nodes[index].dict = nodes[suffix_parent].word_index >= 0 ? suffix_parent : nodes[suffix_parent].dict;
                    q.push_back(index);
                } else {
                    index = get_suffix_link(nodes[current].suff, c);
                }
            }
        }
    }

    // Counts the number of matches of each word in O(text length + num words).
    vector<int> count_matches(const string &text) const {
        vector<int> matches(words.size(), 0);
        int current = 0;

        for (char c : text) {
            current = get_suffix_link(current, c);
            int dict_node = nodes[current].word_index >= 0 ? current : nodes[current].dict;

            if (dict_node >= 0)
                matches[nodes[dict_node].word_index]++;
        }

        // Iterate in decreasing order of depth.
        for (int word_index : word_indices_by_depth) {
            int location = word_location[word_index];
            int dict_node = nodes[location].dict;

            if (dict_node >= 0)
                matches[nodes[dict_node].word_index] += matches[word_index];
        }

        for (int i = 0; i < (int) words.size(); i++)
            matches[i] = matches[defer[i]];

        return matches;
    }

    // Counts the total number of matches of all words within text in O(text length).
    long long count_total_matches(const string &text) const {
        long long matches = 0;
        int current = 0;

        for (char c : text) {
            current = get_suffix_link(current, c);
            matches += nodes[current].word_count;
        }

        return matches;
    }
};
/**
	aho_corasick AC;
    AC.build(words);
**/