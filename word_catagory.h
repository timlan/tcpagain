#pragma once
#include <ostream>
#include <string>

// NB this is misspelt deliberately

namespace timlan {

enum class word_catagory {
  unknown,
  verb,
  noun
};

std::ostream &operator<<(std::ostream &os, word_catagory cat);

word_catagory get_word_catagory(const std::string &catagory_str);

}
