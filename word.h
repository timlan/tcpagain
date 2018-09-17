#pragma once
#include <exception>
#include <istream>
#include <ostream>
#include <string>

#include "word_catagory.h"

namespace timlan {

struct word {
  std::string english_;
  std::string timlan_;
  std::string description_;
  word_catagory catagory_;
  std::string definition_;
  std::string syntax_;
  bool is_real_;

  word(const std::string &word_string);
  word(
      const std::string &english,
      const std::string &timlan,
      const std::string &description,
      word_catagory catagory,
      const std::string &definition,
      const std::string &syntax,
      bool is_real = true);
  word() = default;

  friend std::istream &operator>>(std::istream &is, word &w);

  friend std::ostream &operator<<(std::ostream &os, const word &w);
};

class word_format_exception : public std::exception { };

}
