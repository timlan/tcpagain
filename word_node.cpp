#include "word_node.h"

namespace timlan {

word_node::word_node()
  : is_supplement_{false},
    is_verboid_{false}
{
}

std::ostream &operator<<(std::ostream &os, const word_node &w_n)
{
  os << "( ";

  if (w_n.supplement_)
    os << *w_n.supplement_ << " ";

  os << w_n.word_.english_ << " ";

  for (const affix &a : w_n.prefixes_)
    os << "[" << a.shorthand_ << "] ";

  for (const affix &a : w_n.suffixes_)
    os << "[" << a.shorthand_ << "] ";

  os << ")";

  return os;
}

}
