#include "ladder.h"
#include <iostream>

int main() {
    set<std::string> word_list;

    load_words(word_list, "src/words.txt");
    std::vector<std::string> cat_dog = generate_word_ladder("work", "play", word_list);
    print_word_ladder(cat_dog);
    std::cout << "size of work -> play is " << cat_dog.size() << std::endl;

    // verify_word_ladder();

    // my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    // my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    // my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    // my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    // my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    // my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}