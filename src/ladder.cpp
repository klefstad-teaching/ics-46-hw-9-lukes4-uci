#include "ladder.h"
#include <cmath>
#include <iostream>
#include <fstream>

void error(string word1, string word2, string msg);
bool edit_distance_within(const std::string& str1, const std::string& str2, int d);

bool is_adjacent(const std::string& word1, const std::string& word2) {
    if(word1.size() - word2.size() > 1 || word2.size() - word1.size() < -1) return false;
    for(size_t i = 0; i < fmax(word1.size(), word2.size()); ++i) {
        std::string word1_comp = word1;
        std::string word2_comp = word2;
        if(i < word1.size()) word1_comp.erase(word1_comp.begin() + i);
        if(i < word2.size()) word2_comp.erase(word2_comp.begin() + i);

        if(word1_comp == word2) return true;
        if(word1 == word2_comp) return true;
        if(word1_comp == word2_comp) return true;
    }

    return false;
}

std::vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    std::queue<std::vector<string>> ladder_queue; 
    ladder_queue.push([begin_word]);
    set<string> visited;
    visited.insert(begin_word);
    while(!ladder_queue.empty()) {
        vector<std::string> ladder = ladder_queue.top();
        ladder_queue.pop();
        std::string last_word = ladder[ladder.size() - 1];
        for(std::string word : word_list) {
            if(!(is_adjacent(last_word, word) && visited.find(word) == visited.end())) continue;
            visited.insert(word);
            vector<std::string> new_ladder = ladder;
            new_ladder.push_back(word);
            if(word == end_word) return new_ladder;
            ladder_queue.push(new_ladder);
        }
    }

    std::vector<std::string> empty;
    return empty;
}
void load_words(set<std::string> & word_list, const std::string& file_name) {
    std::ifstream in(file_name);
    for(std::string w; w >> in;) {
        word_list.insert(w);
    } 
}
void print_word_ladder(const vector<std::string>& ladder) {
    for(std::string w : ladder) {
        std::cout << w << " ";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<std::string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

