#include "vos_node.h"

namespace timlan {

std::ostream &operator<<(std::ostream &os, const vos_node &v_n)
{
  os << "( ";

  if (v_n.subject_)
    os << *v_n.subject_ << " ";

  os << v_n.word_node_ << " ";

  if (v_n.object_)
    os << *v_n.object_ << " ";

  os << ")";

  return os;
}

std::ostream &operator<<(
    std::ostream &os,
    const std::vector<vos_node> &nodes) {
  for (const auto &node : nodes) {
    os << node << " . ";
  }

  return os;
}

}
