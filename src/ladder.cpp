#include "ladder.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <algorithm>

void error(std::string word1, std::string word2, std::string msg);

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    if (str1.size() - str2.size() > d || str2.size() - str1.size() > d) return false;
    return true;
}

std::string lowercase(std::string word) {
    
    // for(size_t i = word.size() - 1; i >= 0; --i) word[i] = std::tolower(word[i]);
    // return word;
    
    for_each(word.begin(), word.end(), [](char& c) {
        c = tolower(c);
    });
    return word;
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    if(!edit_distance_within(word1, word2, 1)) return false;
    for(size_t i = 0; i < fmax(word1.size(), word2.size()); ++i) {
        std::string word1_comp = word1;
        std::string word2_comp = word2;
        if(i < word1.size()) word1_comp.erase(word1_comp.begin() + i);
        if(i < word2.size()) word2_comp.erase(word2_comp.begin() + i);

        // std::cout << "word1 = " << word1 <<" ";
        // std::cout << "word2 = " << word2 << " ";
        // std::cout << "word1_comp = " << word1_comp <<" ";
        // std::cout << "word2_comp = " << word2_comp << " ";
        // std::cout << std::endl;

        if(word1_comp == word2) return true;
        if(word1 == word2_comp) return true;
        if(word1_comp == word2_comp) return true;
    }

    return false;
}

std::vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {
    // std::string begin_word_lower = std::transform(begin_word.begin(), begin_word.end(), begin_word.begin(), std::tolower);
    // std::string end_word_lower = std::transform(end_word.begin(), end_word.end(), end_word.begin(), std::tolower);

    std::string begin_word_lower = lowercase(begin_word);
    std::string end_word_lower = lowercase(end_word);
    
    std::queue<std::vector<string>> ladder_queue; 
    std::vector<string> begin;
    begin.push_back(begin_word_lower);
    ladder_queue.push(begin);
    set<string> visited;
    visited.insert(begin_word_lower);
    while(!ladder_queue.empty()) {
        vector<std::string> ladder = ladder_queue.front();
        ladder_queue.pop();
        std::string last_word = ladder[ladder.size() - 1];
        for(std::string word : word_list) {
            if(!(is_adjacent(last_word, word) && visited.find(word) == visited.end())) continue;
            visited.insert(word);
            vector<std::string> new_ladder = ladder;
            new_ladder.push_back(word);
            if(word == end_word_lower) return new_ladder;
            ladder_queue.push(new_ladder);
        }
    }

    std::vector<std::string> empty;
    return empty;
}
void load_words(set<std::string> & word_list, const std::string& file_name) {
    std::ifstream in(file_name);
    for(std::string w; in >> w;) {
        word_list.insert(lowercase(w));
    } 
}
void print_word_ladder(const vector<std::string>& ladder) {
    for(std::string w : ladder) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {

    set<std::string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

