#pragma once

#include <functional>
#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

#include "affix.h"

namespace timlan {

struct fixionary {
  std::vector<affix> affixes_;

  fixionary() = default;
  fixionary(const fixionary &) = delete;
  fixionary(fixionary &&) = default;
  ~fixionary() = default;

  fixionary &operator=(const fixionary &) = delete;
  fixionary &operator=(fixionary &&) = default;

  bool load_affixes(const std::string &filename);

  std::optional<std::reference_wrapper<const affix>> find_prefix(
      const std::string& input);
  std::optional<std::reference_wrapper<const affix>> find_suffix(
      const std::string& input);

  friend std::istream &operator>>(std::istream &is, fixionary &fix);

  friend std::ostream &operator<<(std::ostream &os, const fixionary &fix);
};

}
