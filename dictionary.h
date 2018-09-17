#pragma once

#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "word.h"

namespace timlan {

struct dictionary {
  std::vector<word> words_;

  bool load_words(const std::string &filename);

  std::optional<word> find_word(const std::string& input);
  // should be done after affix removal

  friend std::istream &operator>>(std::istream &is, dictionary &dict);

  friend std::ostream &operator<<(std::ostream &os, const dictionary &dict);
};

}
