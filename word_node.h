#pragma once
#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include "affix.h"
#include "word.h"

namespace timlan {

struct word_node {
  word word_;

  std::vector<std::reference_wrapper<const affix>> prefixes_;
  std::vector<std::reference_wrapper<const affix>> suffixes_;

  std::unique_ptr<word_node> supplement_;

  // strictly speaking not necessary but makes things easier...
  bool is_supplement_;
  bool is_verboid_;

  word_node();
};

std::ostream &operator<<(std::ostream &os, const word_node &w_n);

}
