#include "fixionary.h"
#include "split.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <sstream>
#include <utility>

#include "affix.h"
#include "vos_node.h"

namespace timlan {

bool fixionary::load_affixes(const std::string &filename)
{
  std::fstream file{filename};

  file >> *this;

  return true;
}

std::optional<std::reference_wrapper<const affix>> fixionary::find_prefix(
    const std::string& input)
{
  for (const auto &a: affixes_) {
    if (input.size() >= a.timlan_.size()
        && input.compare(0, a.timlan_.size(), a.timlan_) == 0
        && a.prefix_)
      return {std::cref(a)};
  }

  return {};
}

std::optional<std::reference_wrapper<const affix>> fixionary::find_suffix(
    const std::string& input)
{
  for (const auto &a : affixes_) {
    if (input.size() >= a.timlan_.size()
        && input.compare(
          input.size() - a.timlan_.size(),
          a.timlan_.size(),
          a.timlan_) == 0
        && !a.prefix_)
      return {std::cref(a)};
  }

  return {};
}

std::istream &operator>>(std::istream &is, fixionary &fix)
{
  fix.affixes_.clear();

  std::string line_str{
      std::istreambuf_iterator<char>{is},
      std::istreambuf_iterator<char>{}};

  std::vector<std::string> lines{split(line_str, "<br />")};

  for (const auto &affix_line : lines) {
    if (affix_line == "")
      continue;

    try {
      affix new_affix{affix_line};
      fix.affixes_.emplace_back(std::move(new_affix));
    }
    catch (affix_format_exception) {
      std::cerr << "Failed to load line " << affix_line << "\n";
      is.setstate(std::ios::failbit);
    }
  }

  return is;
}

std::ostream &operator<<(std::ostream &os, const fixionary &fix)
{
  os << "START OF FIXIONARY\n";
  for (const auto &affix : fix.affixes_) {
    os << "  " << affix << "\n";
  }
  os << "END OF FIXIONARY";

  return os;
}

}
