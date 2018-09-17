#include "dictionary.h"
#include "split.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <utility>

namespace timlan {

bool dictionary::load_words(const std::string &filename)
{
  std::fstream file{filename};

  file >> *this;

  return true;
}

std::optional<word> dictionary::find_word(const std::string& input)
{
  for (const auto &word : words_) {
    if (input == word.timlan_)
      return {word};
  }

  return {};
}

std::istream &operator>>(std::istream &is, dictionary &dict)
{
  dict.words_.clear();

  std::string line_str{
      std::istreambuf_iterator<char>{is},
      std::istreambuf_iterator<char>{}};

  std::vector<std::string> lines{split(line_str, "<br />")};

  for (const auto &word_line : lines) {
    if (word_line == "")
      continue;

    try {
      word new_word{word_line};
      dict.words_.emplace_back(std::move(new_word));
    }
    catch (word_format_exception) {
      std::cerr << "Failed to load line " << word_line << "\n";
      is.setstate(std::ios::failbit);
    }
  }

  return is;
}

std::ostream &operator<<(std::ostream &os, const dictionary &dict)
{
  os << "START OF DICT\n";
  for (const auto &word : dict.words_) {
    os << "  " << word << "\n";
  }
  os << "END OF DICT";

  return os;
}

}
